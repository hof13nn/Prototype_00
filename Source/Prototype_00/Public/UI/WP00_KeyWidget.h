// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WP00_KeyWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class PROTOTYPE_00_API UWP00_KeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetKeyTexture(UTexture2D* Color);

private:
	UPROPERTY(meta=(BindWidget))
	UImage* Image;
};
