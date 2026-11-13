#include "RTSGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "RTSCameraPawn.h"
#include "RTSHUD.h"
#include "RTSPlayerController.h"
#include "RTSUnit.h"

ARTSGameMode::ARTSGameMode()
{
	DefaultPawnClass = ARTSCameraPawn::StaticClass();
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	HUDClass = ARTSHUD::StaticClass();
}

void ARTSGameMode::PostLogin(APlayerController* NewPlayer)
{
	// O time é definido antes do Super, porque o Super chama ChoosePlayerStart.
	ARTSPlayerController* RTSPlayer = Cast<ARTSPlayerController>(NewPlayer);
	if (RTSPlayer)
	{
		RTSPlayer->SetTeam(NextTeam++);
	}

	Super::PostLogin(NewPlayer);

	if (RTSPlayer)
	{
		SpawnStartingUnits(RTSPlayer);
	}
}

AActor* ARTSGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	// Um Player Start por time, em ordem de nome, para os jogadores não nascerem no mesmo lugar.
	TArray<APlayerStart*> Starts;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		Starts.Add(*It);
	}
	if (Starts.Num() == 0)
	{
		return Super::ChoosePlayerStart_Implementation(Player);
	}
	Starts.Sort([](const APlayerStart& A, const APlayerStart& B) { return A.GetName() < B.GetName(); });

	const ARTSPlayerController* RTSPlayer = Cast<ARTSPlayerController>(Player);
	const int32 Team = RTSPlayer ? FMath::Max(RTSPlayer->GetTeam(), 0) : 0;
	return Starts[Team % Starts.Num()];
}

void ARTSGameMode::SpawnStartingUnits(ARTSPlayerController* Player)
{
	APawn* CameraPawn = Player->GetPawn();
	if (!CameraPawn)
	{
		return;
	}

	// Acha o chão abaixo do ponto inicial.
	FVector Origin = CameraPawn->GetActorLocation();
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CameraPawn);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Origin + FVector(0.f, 0.f, 1000.f), Origin - FVector(0.f, 0.f, 5000.f), ECC_Visibility, Params))
	{
		Origin = Hit.Location;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const int32 Cols = 3;
	const float Spacing = 150.f;
	for (int32 i = 0; i < StartingUnits; ++i)
	{
		const FVector Offset((i / Cols) * Spacing, (i % Cols - 1) * Spacing, 60.f);
		ARTSUnit* Unit = GetWorld()->SpawnActor<ARTSUnit>(ARTSUnit::StaticClass(), Origin + Offset, FRotator::ZeroRotator, SpawnParams);
		if (Unit)
		{
			Unit->SetTeam(Player->GetTeam());
		}
	}
}
