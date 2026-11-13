#include "RTSHUD.h"

#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "RTSPlayerController.h"

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();

	ARTSPlayerController* PC = Cast<ARTSPlayerController>(GetOwningPlayerController());
	if (!PC)
	{
		return;
	}

	if (PC->IsSelecting())
	{
		const FVector2D A = PC->GetSelectionStart();
		const FVector2D B = PC->GetSelectionCurrent();
		const float X = FMath::Min(A.X, B.X);
		const float Y = FMath::Min(A.Y, B.Y);
		const float W = FMath::Abs(B.X - A.X);
		const float H = FMath::Abs(B.Y - A.Y);

		const FLinearColor Line(0.2f, 1.f, 0.2f, 1.f);
		DrawRect(FLinearColor(0.2f, 1.f, 0.2f, 0.15f), X, Y, W, H);
		DrawLine(X, Y, X + W, Y, Line);
		DrawLine(X, Y + H, X + W, Y + H, Line);
		DrawLine(X, Y, X, Y + H, Line);
		DrawLine(X + W, Y, X + W, Y + H, Line);
	}

	const FString Info = FString::Printf(TEXT("Time: %d   Selecionadas: %d"), PC->GetTeam(), PC->GetSelectedCount());
	DrawText(Info, FLinearColor::White, 20.f, 20.f, GEngine ? GEngine->GetMediumFont() : nullptr);
}
