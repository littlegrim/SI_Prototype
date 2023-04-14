// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace AoS_NativeGameplayTagLibrary
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Audio);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Audio_Music);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Audio_Music_Pause);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode_OutDoor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode_InDoor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Camera_Mode_Observation);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State_Playing);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State_Paused);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Game_State_Loading);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Interact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_ToggleObservationMode);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_ToggleSystemMenu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_ObserveObject);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Media_Skip);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Dialogue_Next);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Dialogue_Previous);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Dialogue_Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Gizbo_Follow);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Gizbo_MoveTo);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Action_Gizbo_MoveToConfirm);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Axis);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Axis_1D_MoveForward);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Axis_1D_MoveRight);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Axis_1D_TurnRate);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Input_Axis_1D_LookUpRate);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media_Cinematic);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media_Video);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Media_TitleCard);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Exploration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Observation);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Menu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Media);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Dialogue);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Interrogation);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_Player_State_Inactive);
		
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_HUD);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_Map);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_System);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_Game);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_Vendor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_Interrogation);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_Dialogue);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Menu_Validation);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Screen);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Screen_Loading);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Screen_Video);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Screen_TitleCard);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Prompt);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Prompt_Interact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(AOSTag_UI_Prompt_Skip);
}