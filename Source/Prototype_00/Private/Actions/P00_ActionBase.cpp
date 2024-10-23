// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_ActionBase.h"
#include "P00_ActionHandlerComponent.h"

bool UP00_ActionBase::CanStart(AActor* Instigator) const
{
	if (bIsActive)
	{
		UE_LOG(LogTemp, Error, TEXT("%s::CanStart: Action is already active"), *GetNameSafe(this));
		return false;
	}

	UP00_ActionHandlerComponent* AC = GetOwningComponent();
	
	return !AC -> HasTags(BlockedTags);
}

void UP00_ActionBase::StartAction(AActor* Instigator)
{
	UP00_ActionHandlerComponent* AC = GetOwningComponent();
	AC -> AddTags(GrantsTags);
	AC -> AddTags(BlockedTags);
	bIsActive = true;
}

void UP00_ActionBase::StopAction(AActor* Instigator)
{
	UP00_ActionHandlerComponent* AC = GetOwningComponent();
	AC -> RemoveTags(GrantsTags);
	AC -> RemoveTags(BlockedTags);
	bIsActive = false;
}

FName UP00_ActionBase::GetActionName() const
{
	return Name;
}

bool UP00_ActionBase::GetIsActive() const
{
	return bIsActive;
}

bool UP00_ActionBase::GetIsAutoStart() const
{
	return bIsAutoStart;
}

void UP00_ActionBase::SetIsAutoStart(const bool& Value)
{
	bIsAutoStart = Value;
}

UP00_ActionHandlerComponent* UP00_ActionBase::GetOwningComponent() const
{
	return Cast<UP00_ActionHandlerComponent>(GetOuter());
}

UWorld* UP00_ActionBase::GetWorld() const
{
	if (const UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp -> GetWorld();
	}
	
	return nullptr;
}
