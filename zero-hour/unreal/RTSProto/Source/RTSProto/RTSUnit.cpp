#include "RTSUnit.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

ARTSUnit::ARTSUnit()
{
	bReplicates = true;
	// Protótipo: todas as unidades são sempre enviadas a todos os clientes.
	// Na F3, com névoa de guerra, isso deve virar relevância por visão do time.
	bAlwaysRelevant = true;

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 50.f);

	bUseControllerRotationYaw = false;
	UCharacterMovementComponent* Move = GetCharacterMovement();
	Move->bOrientRotationToMovement = true;
	Move->RotationRate = FRotator(0.f, 540.f, 0.f);
	Move->MaxWalkSpeed = 450.f;

	// Formas básicas da própria engine: nenhum asset externo.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(GetCapsuleComponent());
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyMesh->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.9f));
	if (CubeMesh.Succeeded())
	{
		BodyMesh->SetStaticMesh(CubeMesh.Object);
	}

	SelectionRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionRing"));
	SelectionRing->SetupAttachment(GetCapsuleComponent());
	SelectionRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SelectionRing->SetRelativeLocation(FVector(0.f, 0.f, -49.f));
	SelectionRing->SetRelativeScale3D(FVector(1.1f, 1.1f, 0.02f));
	SelectionRing->SetVisibility(false);
	if (CylinderMesh.Succeeded())
	{
		SelectionRing->SetStaticMesh(CylinderMesh.Object);
	}
}

void ARTSUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARTSUnit, TeamId);
}

void ARTSUnit::BeginPlay()
{
	Super::BeginPlay();
	ApplyTeamColor();
}

void ARTSUnit::SetTeam(int32 NewTeam)
{
	if (!HasAuthority())
	{
		return;
	}
	TeamId = NewTeam;
	ApplyTeamColor(); // OnRep só roda nos clientes; o servidor aplica aqui.
}

void ARTSUnit::OnRep_TeamId()
{
	ApplyTeamColor();
}

void ARTSUnit::ApplyTeamColor()
{
	if (!BodyMesh || !BodyMesh->GetStaticMesh())
	{
		return;
	}
	if (!BodyMaterial)
	{
		BodyMaterial = BodyMesh->CreateAndSetMaterialInstanceDynamic(0);
	}
	if (!BodyMaterial)
	{
		return;
	}

	FLinearColor Color(0.5f, 0.5f, 0.5f);
	if (TeamId == 0)
	{
		Color = FLinearColor(0.1f, 0.35f, 1.f);
	}
	else if (TeamId == 1)
	{
		Color = FLinearColor(1.f, 0.2f, 0.1f);
	}
	// "Color" é o parâmetro do material padrão das BasicShapes.
	BodyMaterial->SetVectorParameterValue(TEXT("Color"), Color);
}

void ARTSUnit::SetSelected(bool bNewSelected)
{
	if (SelectionRing)
	{
		SelectionRing->SetVisibility(bNewSelected);
	}
}

void ARTSUnit::CommandMoveTo(const FVector& Destination)
{
	if (!HasAuthority())
	{
		return;
	}
	if (AAIController* AI = Cast<AAIController>(GetController()))
	{
		AI->MoveToLocation(Destination, 25.f);
	}
}
