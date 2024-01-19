// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace SI_NativeGameplayTagLibrary
{
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_None)
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Cancel);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Confirm);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_HoldConfirm);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI_Follow);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI_MoveTo);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_AI_Wait);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gadget_UsePrimary);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gadget_UseSecondary);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Drop);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Pickup);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Pull);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Interact_Push);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_AdaptableAction);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_Observation);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_ObserveObject);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_PossessMovable);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Nick_PossessIndicator);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Construct_Flashlight);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Construct_Lockpicks);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Construct);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Ability_Gizbo_Deconstruct);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Actor);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Actor_Interactable);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Actor_Observable);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio_Music);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio_Music_Playing);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Audio_Music_Pause);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Default);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Following);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_MoveTo);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_None);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Patrolling);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Waiting);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Behavior_Wandering);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_OutDoor);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_InDoor);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_Observation);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Camera_Mode_PossessMovable);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Debug);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Debug_DisableAllMedia);

	// Dialogue
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_BubbleDialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_PrimaryDialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_CorrectedDialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_DefaultResponse);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_PressDialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Dialogue_Struct_ResponseDialogue);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget_Flashlight);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget_Lockpicks);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Gadget_Camera);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State_Playing);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State_Paused);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Game_State_Loading);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Interact);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_AdaptableAction);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_CancelAbility);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ConfirmAbility);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_HoldConfirmAbility);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Dialogue_Exit);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Dialogue_Next);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Dialogue_Previous);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Media_Skip);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Down);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Left);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Right);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_MultiOption_Up);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ObserveObject);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ToggleGizboControls);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ToggleObservationMode);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_ToggleSystemMenu);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_UseGadget);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_UseGadgetSecondary);

	// Gizbo Commands
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_Follow);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Down);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Left);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Right);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_MultiOption_Up);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_UseGadget);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Action_Gizbo_UseGadgetSecondary);	
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_MoveForward);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_MoveRight);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_TurnRate);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Input_Axis_1D_LookUpRate);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Activate);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Deactivate);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Pickup);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Drop);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Push);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Interaction_Pull);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media_Cinematic);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media_TitleCard);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Media_Video);

	// Player State
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Dialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Exploration);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Inactive);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Interrogation);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Menu);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Media);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_Observation);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_PossessIndicator);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_Player_State_PossessMovable);
		
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_GadgetsOne);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_GadgetsTwo);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_Gizbo);	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_HUD_QuickAction_Movable);
	
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Map);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_System);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Game);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Vendor);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Interrogation);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Dialogue);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Menu_Validation);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen_Loading);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen_Video);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Screen_TitleCard);

	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Prompt);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Prompt_Interact);
	SI_PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SITag_UI_Prompt_Skip);
}