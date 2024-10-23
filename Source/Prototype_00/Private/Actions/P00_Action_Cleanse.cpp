// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_Action_Cleanse.h"

#include "P00_ActionHandlerComponent.h"
#include "P00_AICharacter.h"
#include "P00_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

UP00_Action_Cleanse::UP00_Action_Cleanse()
{
	LightCost = 5.f;
	ActionMontage = nullptr;
	CleanseAnimDelay = 1.5f;
	ParticleSystem = nullptr;
	SpellSound = nullptr;
	QueryChannel = ECC_WorldDynamic;
	TraceRadius = 100.f;
}

void UP00_Action_Cleanse::StartAction(AActor* Instigator)
{
	Super::StartAction(Instigator);

	if (AP00_PlayerCharacter* Char = Cast<AP00_PlayerCharacter>(Instigator))
	{
		if (ensureMsgf(ActionMontage, TEXT("UP00_Action_Cleanse::StartAction: ActionMontage is NULL")))
		{
			Char -> PlayAnimMontage(ActionMontage);

			if (ensureMsgf(SpellSound, TEXT("StartAction: SpellSound is NULL")))
			{
				UGameplayStatics::PlaySoundAtLocation(this, SpellSound, Instigator -> GetActorLocation());
			}
			
			FTimerHandle CleanseDelay_TimerHandle;
			FTimerHandle CleanseFinished_TimerHandle;
			
			GetWorld() -> GetTimerManager().SetTimer(CleanseDelay_TimerHandle, [&, Char]{ ExecuteCleanse(Char); }, CleanseAnimDelay, false);
			GetWorld() -> GetTimerManager().SetTimer(CleanseFinished_TimerHandle, [&, Instigator]{ StopAction(Instigator); }, ActionMontage -> GetPlayLength(), false);
				
		}
	}
}

void UP00_Action_Cleanse::StopAction(AActor* Instigator)
{
	Super::StopAction(Instigator);
}

void UP00_Action_Cleanse::ExecuteCleanse(AP00_PlayerCharacter* Instigator)
{
	TArray<FOverlapResult> OverlapResultsArr;
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(QueryChannel);

	if (ensureMsgf(ParticleSystem, TEXT("StartAction: ParticleSystem is NULL")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, Instigator -> GetActorLocation());
	}
	
	if(GetWorld() -> OverlapMultiByObjectType(OverlapResultsArr, Instigator -> GetActorLocation(), FQuat::Identity, QueryParams, FCollisionShape::MakeSphere(TraceRadius)))
	{
		//DrawDebugSphere(GetWorld(), Instigator -> GetActorLocation(), TraceRadius, 32.f, bIsHit ? FColor::Green : FColor::Red, false, 2.f);
		
		TArray<AP00_AICharacter*> MinionsArr;
		
		for (FOverlapResult HitResult : OverlapResultsArr)
		{
			if (HitResult.GetActor())
			{
				if (AP00_AICharacter* Minion = Cast<AP00_AICharacter>(HitResult.GetActor()))
				{
					MinionsArr.AddUnique(Minion);
				}
			}
		}

		if (!MinionsArr.IsEmpty())
		{
			for (AP00_AICharacter* Minion : MinionsArr)
			{
				if (Minion)
				{
					Minion -> Cleanse(Instigator);
				}
			}

			return;
		}
	}

	Instigator -> ReduceLight(LightCost, Instigator);
}
