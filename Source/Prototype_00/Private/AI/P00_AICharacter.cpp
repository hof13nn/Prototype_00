// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_AICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
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
	PawnSensingComponent -> OnHearNoise.AddDynamic(this, &ThisClass::OnHearPawn);
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

void AP00_AICharacter::OnHearPawn(APawn* InstigatorActor, const FVector& Location, float Volume)
{
	// FString DebugMsg = FString::Printf(TEXT("%s::OnHearPawn: %s Detected"), *GetNameSafe(this), *GetNameSafe(InstigatorActor));
	// GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Green, DebugMsg);
	
	SetTarget(InstigatorActor);
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
	if (ensureMsgf(DrainLightAnim, TEXT("DrainLightAnim is NULL")))
	{
		if (PlayAnimMontage(DrainLightAnim) > 0.f)
		{
			if (ParticleSystemComponent && ParticleSystemComponent -> GetFXSystemAsset())
			{
				ParticleSystemComponent -> ActivateSystem();
			}
		}
	}
}

void AP00_AICharacter::StopDrainLightEffect()
{
	StopAnimMontage();

	if (ParticleSystemComponent)
	{
		ParticleSystemComponent -> DeactivateImmediate();
	}
}

void AP00_AICharacter::Cleanse(AP00_PlayerCharacter* PlayerCharacter)
{
	bIsAlive = false;
	
	DeactivateAI();

	if (PlayerCharacter)
	{
		PlayerCharacter -> GetActionComponent() -> StopActionByName(this, DrainLightName);

		if (StoredLight > 0.f)
		{
			if (ensureMsgf(LightEnergyClass, TEXT("Cleanse: LightEnergyClass is Null")))
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				SpawnParameters.Instigator = PlayerCharacter;

				FHitResult HitResult;
				FVector StartLoc = GetActorLocation();
				FVector EndLoc = StartLoc + GetActorUpVector() * -500.f;
			
				//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, true, 3.f);
			
				if (GetWorld() -> LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Visibility))
				{
					FVector Offset = GetActorForwardVector() * -150.f + GetActorUpVector() * 50.f;
					const FVector SpawnLocation = HitResult.Location + Offset;
					const FRotator Rotation = FRotator::ZeroRotator;
					const FTransform Transform = FTransform(Rotation, SpawnLocation);
		
					if (AP00_Pickup_LightEnergy* LightEnergy = GetWorld() -> SpawnActor<AP00_Pickup_LightEnergy>(LightEnergyClass, Transform, SpawnParameters))
					{
						LightEnergy -> SetLightAmount(StoredLight);
					}
				}
			}
		}
	}
}

void AP00_AICharacter::DeactivateAI()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController -> GetBrainComponent() -> StopLogic(TEXT("Killed"));
	}
	
	GetMesh() -> SetAllBodiesSimulatePhysics(true);
	GetMesh() -> SetCollisionProfileName(TEXT("Ragdoll"));
	GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement() -> DisableMovement();
	ParticleSystemComponent -> DeactivateImmediate();

	GetWorld() -> GetTimerManager().SetTimer(DestroyAI_TimerHandle, [&]{ Destroy(); }, 5.f, false);
}

void AP00_AICharacter::AddStoredLight(const float& Value)
{
	StoredLight += Value;
}

FName AP00_AICharacter::GetDrainLightName() const
{
	return DrainLightName;
}

