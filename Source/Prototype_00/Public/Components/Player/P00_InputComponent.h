// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_InputConfig.h"
#include "Components/ActorComponent.h"
#include "P00_InputComponent.generated.h"

class AP00_PlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROTOTYPE_00_API UP00_InputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP00_InputComponent();
	
	void InitInput(AP00_PlayerController* PlayerController);

private:
	bool AddMappingContext(const UP00_InputConfig* Config);
	bool InitEnhancedInputComponent(const UP00_InputConfig* Config);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleTurn(const FInputActionValue& InputActionValue);
	void HandleJump(const FInputActionValue& InputActionValue);
	void HandleFire(const FInputActionValue& InputActionValue);
	
private:
	UPROPERTY(VisibleAnywhere)
	AP00_PlayerController* PlayerControllerPtr;
	UPROPERTY(VisibleAnywhere)
	UP00_InputConfig* InputConfig;
};
