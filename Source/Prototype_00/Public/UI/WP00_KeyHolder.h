// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "WP00_KeyHolder.generated.h"

class UWP00_KeyWidget;
class UHorizontalBox;
class UImage;

UCLASS()
class PROTOTYPE_00_API UWP00_KeyHolder : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddKey(const FGameplayTag& Tag);
	void RemoveKey(const FGameplayTag& Tag);
	void RemoveKeys();
private:
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* KeyHolderBox;
	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, UWP00_KeyWidget*> KeyImagesDic;
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, UTexture2D*> TagsDic;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWP00_KeyWidget> KeyWidgetClass;
};
