#pragma once

#include "CoreMinimal.h"


class PROTOTYPE_00_API FTagLibrary
{
public:
};

class PROTOTYPE_00_API FCollisionProfileLibrary
{
public:
};

class PROTOTYPE_00_API FSocketLibrary
{
public:
};


class PROTOTYPE_00_API FPathLibrary
{
public:
	inline static const FString InputConfigPath = TEXT("/Game/Prototype_00/Input/InputConfigData/DA_InputConfig.DA_InputConfig");
	inline static const FString IMC_BaseContextPath = TEXT("/Game/Prototype_00/Input/Context/IMC_Base.IMC_Base");
	inline static const FString IA_MovePath = TEXT("/Game/Prototype_00/Input/Actions/IA_Move.IA_Move");
	inline static const FString IA_TurnPath = TEXT("/Game/Prototype_00/Input/Actions/IA_Turn.IA_Turn");
	inline static const FString IA_JumpPath = TEXT("/Game/Prototype_00/Input/Actions/IA_Jump.IA_Jump");
	inline static const FString IA_FirePath = TEXT("/Game/Prototype_00/Input/Actions/IA_Fire.IA_Fire");
	inline static const FString IA_InteractPath = TEXT("/Game/Prototype_00/Input/Actions/IA_Interact.IA_Interact");
};

class PROTOTYPE_00_API FAIKeyLibrary
{
public:
};

class PROTOTYPE_00_API FActionNamesLibrary
{
public:
};