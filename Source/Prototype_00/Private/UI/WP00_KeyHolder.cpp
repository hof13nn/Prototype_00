// Fill out your copyright notice in the Description page of Project Settings.


#include "WP00_KeyHolder.h"
#include "WP00_KeyWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"

void UWP00_KeyHolder::AddKey(const FGameplayTag& Tag)
{
	if (!TagsDic.IsEmpty() && ensureMsgf(KeyWidgetClass, TEXT("%s::AddKey: KeyWidgetClass is NULL")))
	{
		UTexture2D* KeyTexture = *TagsDic.Find(Tag);
		
		if (UWP00_KeyWidget* KeyImage = CreateWidget<UWP00_KeyWidget>(this, KeyWidgetClass))
		{
			if (KeyHolderBox -> AddChildToHorizontalBox(KeyImage))
			{
				KeyImage -> SetKeyTexture(KeyTexture);
				KeyImagesDic.Emplace(Tag, KeyImage);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("%s::AddKey: Couldn't create Image Slot"), *GetNameSafe(this));
			}
		}
	}
}

void UWP00_KeyHolder::RemoveKey(const FGameplayTag& Tag)
{
	if (!KeyImagesDic.IsEmpty())
	{
		UWP00_KeyWidget* KeyImage = KeyImagesDic.FindAndRemoveChecked(Tag);
		KeyImage -> RemoveFromParent();
	}
}

void UWP00_KeyHolder::RemoveKeys()
{
	if (!KeyImagesDic.IsEmpty())
	{
		for (TTuple<FGameplayTag, UWP00_KeyWidget*> KeyImage : KeyImagesDic)
		{
			if (KeyImage.Value)
			{
				KeyImage.Value -> RemoveFromParent();
			}
		}

		KeyImagesDic.Empty();
	}
}
