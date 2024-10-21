// Fill out your copyright notice in the Description page of Project Settings.


#include "WP00_ProgressBar.h"

#include "Components/ProgressBar.h"

void UWP00_ProgressBar::UpdateProgressBarValue(const float& Delta)
{
	ProgressBar -> SetPercent(Delta);
}
