// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WP00_ProgressBar.generated.h"

class UProgressBar;

UCLASS()
class PROTOTYPE_00_API UWP00_ProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateProgressBarValue(const float& Delta);

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
};
