// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "P00_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_00_API AP00_GameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;
};
