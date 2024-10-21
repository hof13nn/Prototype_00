// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "P00_BaseCharacter.h"
#include "WP00_LightProgressBar.h"
#include "P00_PlayerCharacter.generated.h"

class UWP00_KeyHolder;
class UP00_ActionHandlerComponent;
class IP00_Interactable;
class AP00_PickupBase;
class AP00_LightActor;
class AP00_PlayerController;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class PROTOTYPE_00_API AP00_PlayerCharacter : public AP00_BaseCharacter
{
	GENERATED_BODY()

public:
	AP00_PlayerCharacter();
	void InitInput(AP00_PlayerController* PlayerController);
	void SpawnLightActor(UWP00_LightProgressBar* LightProgressBar);
	void SetKeyHolder(UWP00_KeyHolder* KeyHolder);
	bool ResetLightToMax();
	bool IncreaseLight(const float& Amount);
	void ReduceLight(const float& Amount);
	bool AddKey(const FGameplayTag& Tag);
	
	UFUNCTION(BlueprintCallable)
	bool GetIsAlive() const;

protected:
	virtual void PostInitializeComponents() override;
	
private:
	void SetupCameraComponent();
	void SetupComponents();
	void OnLightExhausted();
	
private:
	void ExecutePlayerMove(const FInputActionValue& InputActionValue);
	void ExecutePlayerTurn(const FInputActionValue& InputActionValue);
	void ExecutePlayerJump(const FInputActionValue& InputActionValue);
	void ExecutePlayerFire(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Player | State")
	bool bIsAlive;
	UPROPERTY(EditAnywhere, Category = "Player | Light")
	TSubclassOf<AP00_LightActor> LightActorClass;
	UPROPERTY()
	AP00_LightActor* LightActorPtr;
	UPROPERTY()
	UWP00_KeyHolder* KeyHolderPtr;
	UPROPERTY(EditDefaultsOnly, Category= "Tags")
	FGameplayTag MovementTag;
};
