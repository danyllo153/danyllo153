#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTSUnit.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

/**
 * Unidade básica do protótipo.
 * O servidor é a autoridade: só ele define o time e dá ordens de movimento.
 * A movimentação é replicada para os clientes pelo CharacterMovementComponent.
 */
UCLASS()
class RTSPROTO_API ARTSUnit : public ACharacter
{
	GENERATED_BODY()

public:
	ARTSUnit();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Só no servidor. */
	void SetTeam(int32 NewTeam);
	int32 GetTeam() const { return TeamId; }

	/** Só visual, no cliente local. */
	void SetSelected(bool bNewSelected);

	/** Só no servidor: manda a unidade andar até o destino usando o NavMesh. */
	void CommandMoveTo(const FVector& Destination);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_TeamId();

	void ApplyTeamColor();

	UPROPERTY(VisibleAnywhere, Category = "RTS")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "RTS")
	TObjectPtr<UStaticMeshComponent> SelectionRing;

	UPROPERTY(ReplicatedUsing = OnRep_TeamId, VisibleInstanceOnly, Category = "RTS")
	int32 TeamId = INDEX_NONE;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> BodyMaterial;
};
