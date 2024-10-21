// Fill out your copyright notice in the Description page of Project Settings.


#include "WP00_KeyWidget.h"

#include "Components/Image.h"

void UWP00_KeyWidget::SetKeyTexture(UTexture2D* Color)
{
	if (Image)
	{
		Image -> SetBrushFromTexture(Color, true);
	}
}