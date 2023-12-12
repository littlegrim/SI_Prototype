// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace SI_NativeGameplayTagLibrary
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_None)
	
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
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Actor)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Actor_Interactable)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Actor_Observable)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio_Music)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio_Music_Playing)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio_Music_Pause)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Default)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Following)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_MoveTo)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_None)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Patrolling)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Waiting)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Wandering)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_OutDoor)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_InDoor)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_Observation)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_PossessMovable)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Debug)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Debug_DisableAllMedia)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_PrimaryDialogue)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_CorrectedDialogue)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_DefaultResponse)


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget_Flashlight)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget_Lockpicks)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget_Camera)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State_Playing)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State_Paused)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State_Loading)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Interact)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_AdaptableAction)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_CancelAbility)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ConfirmAbility)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_HoldConfirmAbility)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Dialogue_Exit)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Dialogue_Next)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Dialogue_Previous)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Media_Skip)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Down)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Left)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Right)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Up)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ObserveObject)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ToggleGizboControls)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ToggleObservationMode)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ToggleSystemMenu)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_UseGadget)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_UseGadgetSecondary)

	// Gizbo Commands
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_Follow)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Down)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Left)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Right)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Up)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_UseGadget)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_UseGadgetSecondary)	
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_MoveForward)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_MoveRight)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_TurnRate)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_LookUpRate)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Activate)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Deactivate)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Pickup)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Drop)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Push)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Pull)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media_Cinematic)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media_TitleCard)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media_Video)

	// Player State
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Dialogue)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Exploration)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Inactive)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Interrogation)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Menu)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Media)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Observation)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_PossessIndicator)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_PossessMovable)
		
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_Movable)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_GadgetsOne)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_GadgetsTwo)
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Map)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_System)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Game)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Vendor)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Interrogation)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Dialogue)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Validation)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen_Loading)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen_Video)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen_TitleCard)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Prompt)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Prompt_Interact)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Prompt_Skip)
}