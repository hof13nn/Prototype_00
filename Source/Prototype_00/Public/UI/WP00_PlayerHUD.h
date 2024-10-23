// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WP00_PlayerHUD.generated.h"

class UWP00_DebuffWidget;
class UWP00_KeyHolder;
class UWP00_LightProgressBar;

UCLASS()
class PROTOTYPE_00_API UWP00_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UWP00_LightProgressBar* GetLightProgressBar() const;
	UWP00_KeyHolder* GetKeyHolder() const;
	UWP00_DebuffWidget* GetDebuffWidget() const;
	
private:
	UPROPERTY(meta=(BindWidget))
	UWP00_LightProgressBar* LightProgressBar;
	UPROPERTY(meta=(BindWidget))
	UWP00_KeyHolder* KeyHolder;
	UPROPERTY(meta=(BindWidget))
	UWP00_DebuffWidget* DebuffWidget;
};
