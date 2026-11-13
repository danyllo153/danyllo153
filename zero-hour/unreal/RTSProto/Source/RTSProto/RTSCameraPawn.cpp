#include "RTSCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputCoreTypes.h"

ARTSCameraPawn::ARTSCameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	// A posição da câmera é só do jogador local; não precisa ser replicada.
	SetReplicatingMovement(false);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	SpringArm->TargetArmLength = 2000.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 8.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLocallyControlled())
	{
		return;
	}
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		return;
	}

	// Câmera com yaw 0: frente = +X, direita = +Y.
	FVector Dir = FVector::ZeroVector;
	if (PC->IsInputKeyDown(EKeys::W) || PC->IsInputKeyDown(EKeys::Up))    { Dir.X += 1.f; }
	if (PC->IsInputKeyDown(EKeys::S) || PC->IsInputKeyDown(EKeys::Down))  { Dir.X -= 1.f; }
	if (PC->IsInputKeyDown(EKeys::D) || PC->IsInputKeyDown(EKeys::Right)) { Dir.Y += 1.f; }
	if (PC->IsInputKeyDown(EKeys::A) || PC->IsInputKeyDown(EKeys::Left))  { Dir.Y -= 1.f; }

	float MouseX = 0.f;
	float MouseY = 0.f;
	int32 SizeX = 0;
	int32 SizeY = 0;
	PC->GetViewportSize(SizeX, SizeY);
	if (SizeX > 0 && SizeY > 0 && PC->GetMousePosition(MouseX, MouseY))
	{
		if (MouseX <= EdgeSize)         { Dir.Y -= 1.f; }
		if (MouseX >= SizeX - EdgeSize) { Dir.Y += 1.f; }
		if (MouseY <= EdgeSize)         { Dir.X += 1.f; }
		if (MouseY >= SizeY - EdgeSize) { Dir.X -= 1.f; }
	}

	if (!Dir.IsNearlyZero())
	{
		// Velocidade proporcional ao zoom, para o movimento parecer constante na tela.
		const float ZoomFactor = SpringArm->TargetArmLength / 2000.f;
		AddActorWorldOffset(Dir.GetSafeNormal() * PanSpeed * ZoomFactor * DeltaTime);
	}
}

void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::MouseScrollUp, IE_Pressed, this, &ARTSCameraPawn::ZoomIn);
	PlayerInputComponent->BindKey(EKeys::MouseScrollDown, IE_Pressed, this, &ARTSCameraPawn::ZoomOut);
}

void ARTSCameraPawn::ZoomIn()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - ZoomStep, MinZoom, MaxZoom);
}

void ARTSCameraPawn::ZoomOut()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + ZoomStep, MinZoom, MaxZoom);
}
