#include "RTSPlayerController.h"

#include "Components/InputComponent.h"
#include "EngineUtils.h"
#include "InputCoreTypes.h"
#include "Net/UnrealNetwork.h"
#include "RTSUnit.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARTSPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARTSPlayerController, TeamId);
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		SetInputMode(Mode);
	}
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Teclas fixas no código para o protótipo não depender de assets de input.
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ARTSPlayerController::OnSelectPressed);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ARTSPlayerController::OnSelectReleased);
	InputComponent->BindKey(EKeys::RightMouseButton, IE_Pressed, this, &ARTSPlayerController::OnCommandPressed);
}

void ARTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bSelecting)
	{
		float X = 0.f;
		float Y = 0.f;
		if (GetMousePosition(X, Y))
		{
			SelectionCurrent = FVector2D(X, Y);
		}
	}
}

void ARTSPlayerController::OnSelectPressed()
{
	float X = 0.f;
	float Y = 0.f;
	if (GetMousePosition(X, Y))
	{
		bSelecting = true;
		SelectionStart = SelectionCurrent = FVector2D(X, Y);
	}
}

void ARTSPlayerController::OnSelectReleased()
{
	if (!bSelecting)
	{
		return;
	}
	bSelecting = false;
	ClearSelection();

	const FVector2D Min(FMath::Min(SelectionStart.X, SelectionCurrent.X), FMath::Min(SelectionStart.Y, SelectionCurrent.Y));
	const FVector2D Max(FMath::Max(SelectionStart.X, SelectionCurrent.X), FMath::Max(SelectionStart.Y, SelectionCurrent.Y));
	const bool bIsClick = (Max - Min).Size() < 6.f;

	ARTSUnit* Closest = nullptr;
	float ClosestDist = 35.f; // raio de clique em pixels

	for (TActorIterator<ARTSUnit> It(GetWorld()); It; ++It)
	{
		ARTSUnit* Unit = *It;
		if (!IsValid(Unit) || Unit->GetTeam() != TeamId)
		{
			continue;
		}

		FVector2D Screen;
		if (!ProjectWorldLocationToScreen(Unit->GetActorLocation(), Screen))
		{
			continue;
		}

		if (bIsClick)
		{
			const float Dist = FVector2D::Distance(Screen, SelectionStart);
			if (Dist < ClosestDist)
			{
				ClosestDist = Dist;
				Closest = Unit;
			}
		}
		else if (Screen.X >= Min.X && Screen.X <= Max.X && Screen.Y >= Min.Y && Screen.Y <= Max.Y)
		{
			SelectedUnits.Add(Unit);
			Unit->SetSelected(true);
		}
	}

	if (bIsClick && Closest)
	{
		SelectedUnits.Add(Closest);
		Closest->SetSelected(true);
	}
}

void ARTSPlayerController::ClearSelection()
{
	for (const TWeakObjectPtr<ARTSUnit>& Unit : SelectedUnits)
	{
		if (Unit.IsValid())
		{
			Unit->SetSelected(false);
		}
	}
	SelectedUnits.Reset();
}

void ARTSPlayerController::OnCommandPressed()
{
	TArray<ARTSUnit*> Units;
	for (const TWeakObjectPtr<ARTSUnit>& Unit : SelectedUnits)
	{
		if (Unit.IsValid())
		{
			Units.Add(Unit.Get());
		}
	}
	if (Units.Num() == 0)
	{
		return;
	}

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		ServerMoveUnits(Units, Hit.Location);
	}
}

void ARTSPlayerController::ServerMoveUnits_Implementation(const TArray<ARTSUnit*>& Units, FVector_NetQuantize Destination)
{
	// Não confiar no cliente: só aceita unidades válidas do próprio time, sem repetição e com limite.
	TArray<ARTSUnit*> Valid;
	for (ARTSUnit* Unit : Units)
	{
		if (IsValid(Unit) && Unit->GetTeam() == TeamId)
		{
			Valid.AddUnique(Unit);
		}
		if (Valid.Num() >= MaxUnitsPerCommand)
		{
			break;
		}
	}
	if (Valid.Num() == 0)
	{
		return;
	}

	// Formação simples em grade ao redor do destino.
	const int32 Cols = FMath::CeilToInt(FMath::Sqrt(static_cast<float>(Valid.Num())));
	const int32 Rows = FMath::DivideAndRoundUp(Valid.Num(), Cols);
	const float Spacing = 120.f;

	for (int32 i = 0; i < Valid.Num(); ++i)
	{
		const int32 Row = i / Cols;
		const int32 Col = i % Cols;
		const FVector Offset(
			(Row - (Rows - 1) * 0.5f) * Spacing,
			(Col - (Cols - 1) * 0.5f) * Spacing,
			0.f);
		Valid[i]->CommandMoveTo(FVector(Destination) + Offset);
	}
}
