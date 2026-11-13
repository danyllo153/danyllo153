#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/** Desenha a caixa de seleção e um texto de depuração. */
UCLASS()
class RTSPROTO_API ARTSHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
};
