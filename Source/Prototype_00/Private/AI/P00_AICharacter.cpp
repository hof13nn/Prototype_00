// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_AICharacter.h"

#include "AIController.h"
#include "P00_ActionHandlerComponent.h"
#include "P00_Pickup_LightEnergy.h"
#include "P00_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Sound/SoundCue.h"


AP00_AICharacter::AP00_AICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsAlive = true;
	StoredLight = 0.f;
	SetupComponents();
}

void AP00_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AP00_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent -> OnSeePawn.AddDynamic(this, &ThisClass::OnSeePawn);
}

void AP00_AICharacter::SetupComponents()
{
	if (!PawnSensingComponent)
	{
		PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
	}

	if (!ParticleSystemComponent)
	{
		ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));

		if (ParticleSystemComponent)
		{
			ParticleSystemComponent -> SetAutoActivate(false);
			ParticleSystemComponent -> SetupAttachment(RootComponent);
		}
	}
}

void AP00_AICharacter::OnSeePawn(APawn* Pawn)
{
	SetTarget(Pawn);
}

void AP00_AICharacter::SetTarget(AActor* NewTarget)
{
	if (ensure(NewTarget))
	{
		AAIController* AIController = Cast<AAIController>(GetController());

		if (ensure(AIController))
		{
			UBlackboardComponent* BlackboardComponent = AIController -> GetBlackboardComponent();

			if (ensure(BlackboardComponent))
			{
				BlackboardComponent -> SetValueAsObject("Target", NewTarget);
			}
		}
	}
}

void AP00_AICharacter::MakeSound()
{
	if (bIsAlive && ensureMsgf(MinionSound, TEXT("ExecuteTask: MinionSound is NULL")))
	{
		UGameplayStatics::PlaySoundAtLocation(this, MinionSound, GetActorLocation());
	}
}

void AP00_AICharacter::ExecuteDrainLightEffect()
{
	if (ParticleSystemComponent && ParticleSystemComponent -> GetFXSystemAsset())
	{
		ParticleSystemComponent -> ActivateSystem();
	}
}

void AP00_AICharacter::Cleanse(AP00_PlayerCharacter* PlayerCharacter)
{
	DeactivateAI();

	if (PlayerCharacter)
	{
		PlayerCharacter -> GetActionComponent() -> StopActionByName(this, DrainLightName);

		if (ensureMsgf(LightEnergyClass, TEXT("Cleanse: LightEnergyClass is Null")))
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParameters.Instigator = this;
		
			const FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * -100.f);
			const FRotator Rotation = FRotator::ZeroRotator;
			const FTransform Transform = FTransform(Rotation, SpawnLocation);
		
			if (AP00_Pickup_LightEnergy* LightEnergy = GetWorld() -> SpawnActor<AP00_Pickup_LightEnergy>(LightEnergyClass, Transform, SpawnParameters))
			{
				LightEnergy -> SetLightAmount(StoredLight);
				//UE_LOG(LogTemp, Error, TEXT("AP00_AICharacter::Cleanse: Couldn't spawn Projectile"));
			}
		}
	}
}

void AP00_AICharacter::DeactivateAI()
{
	bIsAlive = false;
	GetMesh() -> SetAllBodiesSimulatePhysics(true);
	GetMesh() -> SetCollisionProfileName(TEXT("Ragdoll"));
	GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement() -> DisableMovement();
	ParticleSystemComponent -> DeactivateImmediate();
}

void AP00_AICharacter::AddStoredLight(const float& Value)
{
	StoredLight += Value;
}

