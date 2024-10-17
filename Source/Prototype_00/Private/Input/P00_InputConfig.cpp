// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_InputConfig.h"
#include "P00_StringLibrarary.h"

bool UP00_InputConfig::SetupInputActions()
{
	IMC_BaseContext = LoadObject<UInputMappingContext>(this, *FPathLibrary::IMC_BaseContextPath);
	IA_Move = LoadObject<UInputAction>(this, *FPathLibrary::IA_MovePath);
	IA_Turn = LoadObject<UInputAction>(this, *FPathLibrary::IA_TurnPath);
	IA_Jump = LoadObject<UInputAction>(this, *FPathLibrary::IA_JumpPath);
	IA_Fire = LoadObject<UInputAction>(this, *FPathLibrary::IA_FirePath);
	IA_Interact = LoadObject<UInputAction>(this, *FPathLibrary::IA_InteractPath);

	if (!IMC_BaseContext.IsValid() || !IA_Move.IsValid() || !IA_Turn.IsValid() || !IA_Jump.IsValid() || !IA_Fire.IsValid() || !IA_Interact.IsValid())
	{
		return false;
	}

	return true;
}
