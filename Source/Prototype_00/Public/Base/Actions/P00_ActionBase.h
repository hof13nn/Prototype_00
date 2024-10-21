// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "P00_ActionBase.generated.h"

class UP00_ActionHandlerComponent;

UCLASS(Blueprintable)
class PROTOTYPE_00_API UP00_ActionBase : public UObject
{
	GENERATED_BODY()

public:
	bool CanStart(AActor* Instigator) const;
	virtual void StartAction(AActor* Instigator);
	virtual void StopAction(AActor* Instigator);
	FName GetActionName() const;
	bool GetIsActive() const;
	bool GetIsAutoStart() const;
	void SetIsAutoStart(const bool& Value);
	UP00_ActionHandlerComponent* GetOwningComponent() const;
	virtual UWorld* GetWorld() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Action", meta=(AllowPrivateAccess="true"))
	bool bIsAutoStart;
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer GrantsTags;
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer BlockedTags;

private:
	UPROPERTY(EditDefaultsOnly, Category="Action", meta=(AllowPrivateAccess="true"))
	FName Name;
	UPROPERTY(EditDefaultsOnly, Category="Action", meta=(AllowPrivateAccess="true"))
	bool bIsActive;
};
