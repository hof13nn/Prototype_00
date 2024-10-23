// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "P00_PlayerController.generated.h"

class UWP00_PlayerHUD;
class UP00_InputComponent;

struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnExecuteInputAction, const FInputActionValue&)

UCLASS()
class PROTOTYPE_00_API AP00_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AP00_PlayerController();

	UFUNCTION(BlueprintCallable)
	void SetGameInput(const bool Value);
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	
private:
	void SetupComponents();
	void SetInputGameOnly();
	void SetInputUIOnly();
public:
	FOnExecuteInputAction OnCharacterMove;
	FOnExecuteInputAction OnCharacterTurn;
	FOnExecuteInputAction OnCharacterJump;
	FOnExecuteInputAction OnCharacterFire;

private:
	UPROPERTY(VisibleAnywhere)
	UP00_InputComponent* InputHandlerComponent;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWP00_PlayerHUD> PlayerHUDClass;
	UPROPERTY()
	UWP00_PlayerHUD* PlayerHUDPtr;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HelpWindowClass;
	UPROPERTY()
	UUserWidget* HelpWindowPtr;
	UPROPERTY()
	FGameplayTagContainer KeyTags;
	UPROPERTY()
	bool bIsRepossessed;
};
