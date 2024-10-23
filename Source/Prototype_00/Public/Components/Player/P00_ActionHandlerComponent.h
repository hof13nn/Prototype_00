// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "P00_ActionHandlerComponent.generated.h"


class UP00_ActionBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROTOTYPE_00_API UP00_ActionHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP00_ActionHandlerComponent();

	void AddAction(AActor* Instigator, TSubclassOf<UP00_ActionBase> ActionClass);
	void RemoveAction(UP00_ActionBase* Action);
	bool StartActionByName(AActor* Instigator, const FName& ActionName);
	bool StopActionByName(AActor* Instigator, const FName& ActionName);
	UP00_ActionBase* GetActionByName(AActor* Instigator, const FName& ActionName);
	void AddTag(const FGameplayTag& Tag);
	void AddKeyTag(const FGameplayTag& Tag);
	void AddKeyTags(const FGameplayTagContainer& Tags);
	void AddTags(const FGameplayTagContainer& Tags);
	void RemoveTag(const FGameplayTag& Tag);
	void RemoveTags(const FGameplayTagContainer& Tags);
	UFUNCTION(BlueprintCallable)
	bool HasKeyTag(const FGameplayTag& Tag) const;
	UFUNCTION(BlueprintCallable)
	bool HasKeyTags(const FGameplayTagContainer& Tags) const;
	bool HasTag(const FGameplayTag& Tag) const;
	bool HasTags(const FGameplayTagContainer& Tags) const;
	FGameplayTagContainer GetKeyTags() const;
protected:
	virtual void OnRegister() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TMap<UP00_ActionBase*, AActor*> ActionsDic;
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UP00_ActionBase>> ActionClassesArr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tags", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer ActiveGameplayTags;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tags", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer KeyTags;

};
