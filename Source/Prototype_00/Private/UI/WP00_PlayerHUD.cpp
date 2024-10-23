// Fill out your copyright notice in the Description page of Project Settings.


#include "WP00_PlayerHUD.h"

UWP00_LightProgressBar* UWP00_PlayerHUD::GetLightProgressBar() const
{
	return LightProgressBar;
}

UWP00_KeyHolder* UWP00_PlayerHUD::GetKeyHolder() const
{
	return KeyHolder;
}

UWP00_DebuffWidget* UWP00_PlayerHUD::GetDebuffWidget() const
{
	return DebuffWidget;
}
