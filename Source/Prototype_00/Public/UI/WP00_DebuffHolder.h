// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "WP00_DebuffHolder.generated.h"

class UHorizontalBox;

UCLASS()
class PROTOTYPE_00_API UWP00_DebuffHolder : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddDebuff(const FGameplayTag& Tag);
	void RemoveDebuff(const FGameplayTag& Tag);
	void RemoveDebuffs();
	
private:
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* DebuffHolderBox;
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, UTexture2D*> TagsDic;
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UWP00_KeyWidget> DebuffWidgetClass;
};
