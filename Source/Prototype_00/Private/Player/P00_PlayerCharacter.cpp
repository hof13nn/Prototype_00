// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_PlayerCharacter.h"
#include "InputActionValue.h"
#include "P00_ActionHandlerComponent.h"
#include "P00_Interactable.h"
#include "P00_LightActor.h"
#include "P00_PlayerController.h"
#include "P00_StringLibrarary.h"
#include "WP00_KeyHolder.h"
#include "WP00_LightProgressBar.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

AP00_PlayerCharacter::AP00_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bIsAlive = true;
	SetupCameraComponent();
	SetupComponents();
}

void AP00_PlayerCharacter::SetupCameraComponent()
{
	if (!SpringArmComponent)
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

		if (ensure(SpringArmComponent))
		{
			SpringArmComponent -> TargetArmLength = 500.f;
			SpringArmComponent -> bUsePawnControlRotation = true;
			SpringArmComponent -> SetupAttachment(RootComponent);
			
			if (!CameraComponent)
			{
				CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

				if (ensure(CameraComponent))
				{
					CameraComponent -> SetupAttachment(SpringArmComponent);
				}
			}
		}
	}
}

void AP00_PlayerCharacter::SetupComponents()
{
}

void AP00_PlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent() -> OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	}
}

void AP00_PlayerCharacter::InitInput(AP00_PlayerController* PlayerController)
{
	PlayerController -> OnCharacterMove.AddUObject(this, &ThisClass::ExecutePlayerMove);
	PlayerController -> OnCharacterTurn.AddUObject(this, &ThisClass::ExecutePlayerTurn);
	PlayerController -> OnCharacterJump.AddUObject(this, &ThisClass::ExecutePlayerJump);
	PlayerController -> OnCharacterFire.AddUObject(this, &ThisClass::ExecutePlayerFire);
}

void AP00_PlayerCharacter::SpawnLightActor(UWP00_LightProgressBar* LightProgressBar)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;

	if (ensureMsgf(LightActorClass, TEXT("%s::SpawnLightActor: Light Actor Class is NULL"), *GetNameSafe(this)))
	{
		LightActorPtr = GetWorld() -> SpawnActor<AP00_LightActor>(LightActorClass, FTransform(), SpawnParameters);
		
		if (LightActorPtr)
		{
			const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
			
			LightActorPtr -> AttachToComponent(GetMesh(), AttachmentTransformRules, *FSocketLibrary::PlayerLightSocket);
			LightActorPtr -> OnLightExhausted.BindUObject(this, &ThisClass::OnLightExhausted);
			
			LightActorPtr -> InitLightActor(LightProgressBar);
		}
	}
}

void AP00_PlayerCharacter::SetKeyHolder(UWP00_KeyHolder* KeyHolder)
{
	if (KeyHolder)
	{
		KeyHolderPtr = KeyHolder;
	}
}

void AP00_PlayerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor -> Implements<UP00_Interactable>())
	{
		FString DebugMsg = FString::Printf(TEXT("%s::OnOverlap: Overlaping %s"), *GetNameSafe(this), *GetNameSafe(OtherActor));
		GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Green, DebugMsg);
		IP00_Interactable::Execute_StartInteract(OtherActor, this);
	}
}

void AP00_PlayerCharacter::ExecutePlayerMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (!ActionHandlerComponent -> HasTag(MovementTag) && Controller)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AP00_PlayerCharacter::ExecutePlayerTurn(const FInputActionValue& InputActionValue)
{
}

void AP00_PlayerCharacter::ExecutePlayerJump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AP00_PlayerCharacter::ExecutePlayerFire(const FInputActionValue& InputActionValue)
{
	if (ActionHandlerComponent)
	{
		ActionHandlerComponent -> StartActionByName(this, *FActionNamesLibrary::A_Cleanse);
	}
}

bool AP00_PlayerCharacter::ResetLightToMax()
{
	if (LightActorPtr && LightActorPtr -> CanReset())
	{
		if (!LightActorPtr -> ResetToMaxLightRadius())
		{
			UE_LOG(LogTemp, Error, TEXT("%s::ResetLightToMax: Couldn't reset Light"), *GetNameSafe(this));
			return false;
		}

		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("%s::ResetLightToMax: LightActorPtr is NULL"), *GetNameSafe(this));
	return false;
}

bool AP00_PlayerCharacter::IncreaseLight(const float& Amount)
{
	if (LightActorPtr)
	{
		return LightActorPtr -> IncreaseLight(Amount);;
	}

	return false;
}

void AP00_PlayerCharacter::ReduceLight(const float& Amount)
{
	if (LightActorPtr)
	{
		LightActorPtr -> ReduceLight(Amount);
	}
}

bool AP00_PlayerCharacter::AddKey(const FGameplayTag& Tag)
{
	if (ActionHandlerComponent && KeyHolderPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s::AddKey: Adding %s"), *GetNameSafe(this), *Tag.ToString())
		ActionHandlerComponent -> AddTag(Tag);
		KeyHolderPtr -> AddKey(Tag);
		return true;
	}

	return false;
}

void AP00_PlayerCharacter::OnLightExhausted()
{
	bIsAlive = false;

	if (AP00_PlayerController* PC = Cast<AP00_PlayerController>(GetController()))
	{
		DisableInput(PC);
		GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

bool AP00_PlayerCharacter::GetIsAlive() const
{
	return bIsAlive;
}