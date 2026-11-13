#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Câmera de RTS vista de cima: WASD/setas ou borda da tela para mover,
 * roda do mouse para zoom. Só se move no cliente local.
 */
UCLASS()
class RTSPROTO_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ARTSCameraPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void ZoomIn();
	void ZoomOut();

	UPROPERTY(VisibleAnywhere, Category = "RTS")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "RTS")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "RTS")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "RTS")
	float PanSpeed = 2500.f;

	UPROPERTY(EditAnywhere, Category = "RTS")
	float EdgeSize = 15.f;

	UPROPERTY(EditAnywhere, Category = "RTS")
	float ZoomStep = 200.f;

	UPROPERTY(EditAnywhere, Category = "RTS")
	float MinZoom = 800.f;

	UPROPERTY(EditAnywhere, Category = "RTS")
	float MaxZoom = 4000.f;
};
