// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "P00_InputConfig.generated.h"

UCLASS()
class PROTOTYPE_00_API UP00_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	bool SetupInputActions();
	
	UPROPERTY(VisibleDefaultsOnly, Category= "Context Settings")
	TSoftObjectPtr<UInputMappingContext> IMC_BaseContext;
	UPROPERTY(VisibleDefaultsOnly, Category= "Context Settings")
	int32 ContextPriority;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TSoftObjectPtr<UInputAction> IA_Move;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TSoftObjectPtr<UInputAction> IA_Turn;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TSoftObjectPtr<UInputAction> IA_Jump;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TSoftObjectPtr<UInputAction> IA_Fire;
	UPROPERTY(VisibleDefaultsOnly, Category= "Input Actions")
	TSoftObjectPtr<UInputAction> IA_Interact;
};
