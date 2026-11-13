#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSGameMode.generated.h"

class ARTSPlayerController;

/**
 * Só existe no servidor. Distribui os times, escolhe o ponto inicial
 * de cada jogador e cria as unidades iniciais.
 */
UCLASS()
class RTSPROTO_API ARTSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARTSGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

protected:
	void SpawnStartingUnits(ARTSPlayerController* Player);

	UPROPERTY(EditAnywhere, Category = "RTS")
	int32 StartingUnits = 6;

private:
	int32 NextTeam = 0;
};
