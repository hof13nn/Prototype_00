// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "P00_Interactable.generated.h"

UINTERFACE()
class UP00_Interactable : public UInterface
{
	GENERATED_BODY()
};

class PROTOTYPE_00_API IP00_Interactable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void StartInteract(APawn* InstigatorPawn);
	UFUNCTION(BlueprintNativeEvent)
	void EndInteract(APawn* InstigatorPawn);
};
