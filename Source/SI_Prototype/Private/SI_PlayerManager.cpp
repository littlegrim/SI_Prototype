// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_PlayerManager.h"
#include "SI_GameplayTagManager.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Controllers/SI_PlayerController.h"
#include "Data/Maps/SI_MapData.h"
#include "Levels/SI_LevelManager.h"
#include "Characters/SI_Nick.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"

void USI_PlayerManager::RequestNewPlayerState(const FGameplayTag& InPlayerState)
{
	if(!InPlayerState.IsValid() || !SITagManager->HasParentTag(InPlayerState,SITag_Player_State)) {return;}

	SITagManager->ReplaceTagWithSameParent(InPlayerState, SITag_Player_State);

	PreviousPlayerState = CurrentPlayerState;
	CurrentPlayerState = InPlayerState;	
}

const FGameplayTag& USI_PlayerManager::GetCurrentPlayerState() const
{
	return CurrentPlayerState;
}

const FGameplayTag& USI_PlayerManager::GetPreviousPlayerState() const
{
	return PreviousPlayerState;
}

void USI_PlayerManager::ShowWorld(bool bShouldShow, bool bShouldFade)
{
	if (!IsValid(PlayerController)) {return;}

	if(bShouldShow)
	{
		if(bShouldFade)
		{
			PlayerController->PlayerCameraManager->StartCameraFade(1, 0, .5, FLinearColor::Black, false, true);
		}
		else
		{
			PlayerController->PlayerCameraManager->StartCameraFade(1, 0, 0, FLinearColor::Black, false, true);
		}
	}
	else
	{
		if(bShouldFade)
		{
			PlayerController->PlayerCameraManager->StartCameraFade(0, 1, .5, FLinearColor::Black, false, true);
		}
		else
		{
			PlayerController->PlayerCameraManager->StartCameraFade(0, 1, .0, FLinearColor::Black, false, true);
		}
	}

	bShowWorld = bShouldShow;
}

void USI_PlayerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);	
}

void USI_PlayerManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	if(!IsValid(GetWorld())) return;
	
	Super::OnGameplayTagAdded(InAddedTag);
		
	if (SITagManager->HasParentTag(InAddedTag, SITag_UI_Menu))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Menu,SITag_Player_State);
		if (!IsValid(PlayerController)){return;}
		PlayerController->SetMenuMode(true);
		return;
	}
	if (SITagManager->HasParentTag(InAddedTag, SITag_UI_Screen))
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Inactive,SITag_Player_State);
		return;
	}
	if (SITagManager->HasParentTag(InAddedTag, SITag_Media))
	{
		SecondaryMediaTag = InAddedTag;
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Media,SITag_Player_State);
		return;
	}
	
	if(SITagManager->HasParentTag(InAddedTag, SITag_Ability_Nick))
	{
		CurrentAbilityTag = InAddedTag;
		PlayerDelegateContainer.Find(SITag_Ability_Nick)->Execute();
	}
	
	if(!SITagManager->HasParentTag(InAddedTag, SITag_Player)){return;}
	
	if(SITagManager->HasParentTag(InAddedTag, SITag_Player_State))
	{
		CurrentPlayerState = InAddedTag;
	}

	if(InAddedTag == SITag_Player_State_Media)
	{
		if (!IsValid(PlayerController)){return;}
		PlayerController->AddInputMappingByTag(InAddedTag, SecondaryMediaTag);
		PlayerDelegateContainer.Find(InAddedTag)->Execute();
		return;
	}
	
	PlayerDelegateContainer.Find(InAddedTag)->Execute();

	if (!IsValid(PlayerController)){return;}
	PlayerController->AddInputMappingByTag(InAddedTag);
}

void USI_PlayerManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	if(!IsValid(GetWorld())) return;
	
	Super::OnGameplayTagRemoved(InRemovedTag);

	if(SITagManager->HasParentTag(InRemovedTag, SITag_Ability_Nick))
	{
		CurrentAbilityTag = InRemovedTag;
		TryCancelAbilityByTag();
	}
	
	if (SITagManager->HasParentTag(InRemovedTag, SITag_UI_Menu))
	{
		SITagManager->RemoveTag(SITag_Player_State_Menu);
		if (!IsValid(PlayerController)){return;}
		PlayerController->SetMenuMode(false);
		return;
	}
	
	if (SITagManager->HasParentTag(InRemovedTag, SITag_UI_Screen))
	{
		SITagManager->RemoveTag(SITag_Player_State_Inactive);
		return;
	}
	
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_Player)){return;}
	
	if(SITagManager->HasParentTag(InRemovedTag, SITag_Player_State))
	{
		PreviousPlayerState = InRemovedTag;
	}

	if (!IsValid(PlayerController)){return;}
	PlayerController->RemoveInputMappingByTag(InRemovedTag);
}

void USI_PlayerManager::OnPlayerStart()
{
	Super::OnPlayerStart();

	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	
	ShowWorld(false, false);
}

void USI_PlayerManager::OnGameModeBeginPlay()
{
	Super::OnGameModeBeginPlay();
	
	if(!bShowWorld)
	{
		ShowWorld(true, true);
	}
}

void USI_PlayerManager::InitializeDelegates()
{
	Super::InitializeDelegates();

	ActivateAbilityDelegate.BindUObject(this, &ThisClass::TryActivateAbilityByTag);
	DialogueStateDelegate.BindUObject(this, &ThisClass::SetupDialogueState);
	ExplorationStateDelegate.BindUObject(this, &ThisClass::SetupExplorationState);
	InactiveStateDelegate.BindUObject(this, &ThisClass::SetupInactiveState);
	InterrogationStateDelegate.BindUObject(this, &ThisClass::SetupInterrogationState);
	MediaStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	MenuStateDelegate.BindUObject(this, &ThisClass::SetupMenuState);
	ObservationStateDelegate.BindUObject(this, &ThisClass::SetupObservationState);
	PossessMovableStateDelegate.BindUObject(this, &ThisClass::SetupPossessMovableState);
	
}

void USI_PlayerManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();

	PlayerDelegateContainer.Add(SITag_Ability_Nick, ActivateAbilityDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Dialogue, DialogueStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Exploration, ExplorationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Inactive, InactiveStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Interrogation, InterrogationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Media, MediaStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Menu, MenuStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_Observation, ObservationStateDelegate);
	PlayerDelegateContainer.Add(SITag_Player_State_PossessMovable, PossessMovableStateDelegate);
	
}

void USI_PlayerManager::TryActivateAbilityByTag()
{
	if(!IsValid(NickAbilitySystemComponent))
	{
		NickAbilitySystemComponent = PlayerController->GetNick()->GetSIAbilitySystemComponent();
	}

	USI_GameplayAbility* CurrentAbility = NickAbilitySystemComponent->GetGameplayAbilityByTag(CurrentAbilityTag);

	if(!IsValid(CurrentAbility)) return;
	
	if(NickAbilitySystemComponent->TryActivateAbilitiesByTag(CurrentAbilityTag.GetSingleTagContainer(), false))
	{
		ActiveAbilitiesContainer.Add(CurrentAbilityTag, CurrentAbility);
	}
}

void USI_PlayerManager::TryCancelAbilityByTag()
{	
	USI_GameplayAbility* CurrentAbility = NickAbilitySystemComponent->GetGameplayAbilityByTag(CurrentAbilityTag);

	if(!IsValid(CurrentAbility)) return;
	
	if(!ActiveAbilitiesContainer.IsEmpty() && *ActiveAbilitiesContainer.Find(CurrentAbilityTag) == CurrentAbility)
	{
		NickAbilitySystemComponent->CancelAbility(CurrentAbility);
	}
}

void USI_PlayerManager::SetupDialogueState()
{
}

void USI_PlayerManager::SetupExplorationState()
{
	USI_LevelManager* SILevelManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_LevelManager>();
	if (!IsValid(SILevelManager) || !IsValid(SILevelManager->GetCurrentMap())){return;}
	if (SILevelManager->GetCurrentMap()->MapType == SITag_Map_Type_Interior)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_InDoor, SITag_Camera_Mode);
		return;
	}
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_OutDoor, SITag_Camera_Mode);
}

void USI_PlayerManager::SetupInactiveState()
{
}

void USI_PlayerManager::SetupInterrogationState()
{
}

void USI_PlayerManager::SetupMenuState()
{
}

void USI_PlayerManager::SetupObservationState()
{
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_Observation, SITag_Camera_Mode);
}

void USI_PlayerManager::SetupPossessMovableState()
{
	SITagManager->ReplaceTagWithSameParent(SITag_Camera_Mode_PossessMovable, SITag_Camera_Mode);
}
