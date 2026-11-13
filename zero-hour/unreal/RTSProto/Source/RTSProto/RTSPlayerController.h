#pragma once

#include "CoreMinimal.h"
#include "Engine/NetSerialization.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class ARTSUnit;

/**
 * Controle do jogador: seleção por clique/caixa e ordem de movimento.
 * A seleção é local; a ordem vai ao servidor por RPC e é validada lá.
 */
UCLASS()
class RTSPROTO_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Só no servidor (GameMode). */
	void SetTeam(int32 NewTeam) { TeamId = NewTeam; }
	int32 GetTeam() const { return TeamId; }

	bool IsSelecting() const { return bSelecting; }
	FVector2D GetSelectionStart() const { return SelectionStart; }
	FVector2D GetSelectionCurrent() const { return SelectionCurrent; }
	int32 GetSelectedCount() const { return SelectedUnits.Num(); }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	void OnSelectPressed();
	void OnSelectReleased();
	void OnCommandPressed();
	void ClearSelection();

	UFUNCTION(Server, Reliable)
	void ServerMoveUnits(const TArray<ARTSUnit*>& Units, FVector_NetQuantize Destination);

	UPROPERTY(Replicated, VisibleInstanceOnly, Category = "RTS")
	int32 TeamId = INDEX_NONE;

	/** Limite de unidades por ordem (proteção contra mensagens abusivas). */
	static constexpr int32 MaxUnitsPerCommand = 100;

private:
	TArray<TWeakObjectPtr<ARTSUnit>> SelectedUnits;
	bool bSelecting = false;
	FVector2D SelectionStart = FVector2D::ZeroVector;
	FVector2D SelectionCurrent = FVector2D::ZeroVector;
};
