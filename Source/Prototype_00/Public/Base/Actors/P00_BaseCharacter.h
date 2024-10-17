// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "P00_BaseCharacter.generated.h"

UCLASS()
class PROTOTYPE_00_API AP00_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AP00_BaseCharacter();

protected:
	virtual void BeginPlay() override;
};
