// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace SI_AbilityGameplayTagLibrary
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Cancel)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Confirm)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_HoldConfirm)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI_Follow)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI_MoveTo)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI_Wait)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gadget_UsePrimary)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gadget_UseSecondary)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Drop)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Pickup)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Pull)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Push)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_AdaptableAction)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_Observation)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_ObserveObject)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_PossessMovable)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_PossessIndicator)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Construct_Flashlight)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Construct_Lockpicks)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Construct)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Deconstruct)
}