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
		ActionsDic.Emplace(NewAction, Instigator);

		if (NewAction -> GetIsAutoStart())
		{
			if (NewAction -> CanStart(Instigator))
			{
				//UE_LOG(LogTemp, Warning, TEXT("%s::AddAction: Starting %s"), *GetNameSafe(GetOwner()), *NewAction -> GetActionName().ToString());
				NewAction -> StartAction(Instigator);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("%s::AddAction: Couldn't start action"), *GetNameSafe(GetOwner()));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s::AddAction: Action isn't set to Auto-Start"), *GetNameSafe(GetOwner()));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s::AddAction: Couldn't create action"), *GetNameSafe(GetOwner()));
	}
}

void UP00_ActionHandlerComponent::RemoveAction(UP00_ActionBase* Action)
{
	if (Action && !Action -> GetIsActive())
	{
		ActionsDic.Remove(Action);
	}
}

bool UP00_ActionHandlerComponent::StartActionByName(AActor* Instigator, const FName& ActionName)
{
	for ( TTuple<UP00_ActionBase*, AActor*> Action : ActionsDic)
	{
		if (Action.Key && Action.Key -> GetActionName() == ActionName)
		{
			if (!Action.Key -> CanStart(Instigator))
			{
				// FString FailedMsg = FString::Printf(TEXT("Failed to Start %s"), *ActionName.ToString());
				// GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FailedMsg);
				return false;
			}
			
			Action.Key -> StartAction(Instigator);
			return true;
		}
	}

	// FString FailedMsg = FString::Printf(TEXT(" %s deesn't exist"), *ActionName.ToString());
	// GEngine -> AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FailedMsg);
	
	return false;
}

bool UP00_ActionHandlerComponent::StopActionByName(AActor* Instigator, const FName& ActionName)
{
	for (TTuple<UP00_ActionBase*, AActor*> Action : ActionsDic)
	{
		if (Action.Key && Action.Key -> GetActionName() == ActionName && Action.Value == Instigator )
		{
			if (Action.Key -> GetIsActive())
			{
				Action.Key -> StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}

UP00_ActionBase* UP00_ActionHandlerComponent::GetActionByName(AActor* Instigator, const FName& ActionName)
{
	for (TTuple<UP00_ActionBase*, AActor*>  Action : ActionsDic)
	{
		if (Action.Key && Action.Key -> GetActionName() == ActionName)
		{
			if (!Action.Key -> GetIsActive())
			{
				return Action.Key;
			}
		}
	}

	return nullptr;
}

void UP00_ActionHandlerComponent::AddTag(const FGameplayTag& Tag)
{
	ActiveGameplayTags.AddTag(Tag);
}

void UP00_ActionHandlerComponent::AddKeyTag(const FGameplayTag& Tag)
{
	KeyTags.AddTag(Tag);
}

void UP00_ActionHandlerComponent::AddKeyTags(const FGameplayTagContainer& Tags)
{
	KeyTags.AppendTags(Tags);
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

bool UP00_ActionHandlerComponent::HasKeyTag(const FGameplayTag& Tag) const
{
	return KeyTags.HasTag(Tag);;
}

bool UP00_ActionHandlerComponent::HasKeyTags(const FGameplayTagContainer& Tags) const
{
	return KeyTags.HasAll(Tags);
}

bool UP00_ActionHandlerComponent::HasTag(const FGameplayTag& Tag) const
{
	return ActiveGameplayTags.HasTag(Tag);
}

bool UP00_ActionHandlerComponent::HasTags(const FGameplayTagContainer& Tags) const
{
	return ActiveGameplayTags.HasAny(Tags);
}

FGameplayTagContainer UP00_ActionHandlerComponent::GetKeyTags() const
{
	return KeyTags;
}

