// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_ActionHandlerComponent.h"

#include "P00_ActionBase.h"

UP00_ActionHandlerComponent::UP00_ActionHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UP00_ActionHandlerComponent::OnRegister()
{
	Super::OnRegister();

	if (!ActionClassesArr.IsEmpty())
	{
		for (TSubclassOf<UP00_ActionBase> ActionClass : ActionClassesArr)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
}

void UP00_ActionHandlerComponent::AddAction(AActor* Instigator, TSubclassOf<UP00_ActionBase> ActionClass)
{
	if (!ActionClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s::AddAction: Action Class is NULL"), *GetNameSafe(GetOwner()));
		return;
	}

	if (UP00_ActionBase* NewAction = NewObject<UP00_ActionBase>(this, ActionClass))
	{
		ActionsArr.Emplace(NewAction);

		if (NewAction -> GetIsAutoStart() && NewAction -> CanStart(Instigator))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s::AddAction: Starting %s"), *GetNameSafe(GetOwner()), *NewAction -> GetActionName().ToString());
			NewAction -> StartAction(Instigator);
		}
	}
}

void UP00_ActionHandlerComponent::RemoveAction(UP00_ActionBase* Action)
{
	if (Action && !Action -> GetIsActive())
	{
		ActionsArr.Remove(Action);
	}
}

bool UP00_ActionHandlerComponent::StartActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UP00_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			if (!Action -> CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to Start %s"), *ActionName.ToString());
				GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FailedMsg);
				return false;
			}
			
			Action -> StartAction(Instigator);
			return true;
		}
	}

	FString FailedMsg = FString::Printf(TEXT(" %s deesn't exist"), *ActionName.ToString());
	GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FailedMsg);
	
	return false;
}

bool UP00_ActionHandlerComponent::StopActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UP00_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			if (Action -> GetIsActive())
			{
				Action -> StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}

UP00_ActionBase* UP00_ActionHandlerComponent::GetActionByName(AActor* Instigator, const FName& ActionName)
{
	for (UP00_ActionBase* Action : ActionsArr)
	{
		if (Action && Action -> GetActionName() == ActionName)
		{
			if (!Action -> GetIsActive())
			{
				return Action;
			}
		}
	}

	return nullptr;
}

void UP00_ActionHandlerComponent::AddTag(const FGameplayTag& Tag)
{
	ActiveGameplayTags.AddTag(Tag);
}

void UP00_ActionHandlerComponent::AddTags(const FGameplayTagContainer& Tags)
{
	ActiveGameplayTags.AppendTags(Tags);
}

void UP00_ActionHandlerComponent::RemoveTag(const FGameplayTag& Tag)
{
	ActiveGameplayTags.RemoveTag(Tag);
}

void UP00_ActionHandlerComponent::RemoveTags(const FGameplayTagContainer& Tags)
{
	ActiveGameplayTags.RemoveTags(Tags);
}

bool UP00_ActionHandlerComponent::HasTag(const FGameplayTag& Tag) const
{
	if (!ActiveGameplayTags.IsEmpty())
	{
		return ActiveGameplayTags.HasTag(Tag);;
	}

	return false;
}

bool UP00_ActionHandlerComponent::HasTags(const FGameplayTagContainer& Tags) const
{
	if (!ActiveGameplayTags.IsEmpty())
	{
		return ActiveGameplayTags.HasAll(Tags);;
	}

	return false;
}

