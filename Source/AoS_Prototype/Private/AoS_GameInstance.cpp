// Fill out your copyright notice in the Description page of Project Settings.


#include "AoS_GameInstance.h"

#include "Characters/AoS_Character.h"
#include "Characters/AoS_CharacterData.h"
#include "Characters/AoS_Nick.h"
#include "GameFramework/PlayerStart.h"

// Subsystems
#include "UI/AoS_UIManager.h"
#include "Cases/AoS_CaseManager.h"
#include "Levels/AoS_LevelManager.h"
#include "World/AoS_WorldManager.h"

#include "Data/AoS_MapData.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

UAoS_GameInstance::UAoS_GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UAoS_MapData> MainMenuAsset(TEXT("/Game/AoS/Maps/Menus/DA_MainMenu"));
	MainMenu = MainMenuAsset.Object;
	
	bIsInMenu = false;
}

void UAoS_GameInstance::ResetCase(FString CaseToResetName)
{
	if (CaseManager)
	{
		if (CaseToResetName == "All")
		{
			CaseManager->ResetAllCases();
		}
		else
		{
			CaseManager->ResetCase(CaseToResetName);
		}
	}
}

void UAoS_GameInstance::SpawnPlayer()
{
	if (!CDA_NickSpade) {return;}
	if (!CDA_NickSpade->CharacterClass){return;}
	
	if (const APlayerStart* PlayerStart = GetPlayerStart())
	{
		if (!NickSpadeCharacter)
		{
			const FActorSpawnParameters PlayerSpawnParameters;
			NickSpadeCharacter = GetWorld()->SpawnActor<AAoS_Nick>(CDA_NickSpade->CharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), PlayerSpawnParameters);
		}
		else
		{
			NickSpadeCharacter->SetActorLocation(PlayerStart->GetActorLocation());
			NickSpadeCharacter->SetActorRotation(PlayerStart->GetActorRotation());
		}
	}

	if (AoS_PlayerController)
	{
		AoS_PlayerController->Possess(NickSpadeCharacter);
	}
}

EPlayerMode UAoS_GameInstance::GetPlayerMode() const
{
	return PlayerMode;
}

AAoS_PlayerController* UAoS_GameInstance::GetAOSPlayerController()
{
	return AoS_PlayerController;
}

void UAoS_GameInstance::SetPlayerMode(EPlayerMode InPlayerMode)
{
	PlayerMode = InPlayerMode;
	OnPlayerModeChanged.Broadcast(InPlayerMode);
}

void UAoS_GameInstance::SetIsInMenu(const bool bInMenu)
{
	bIsInMenu = bInMenu;
}

void UAoS_GameInstance::SetupLevelBindings()
{
	LevelManager->OnBeginLevelLoad.AddDynamic(this, &UAoS_GameInstance::OnLevelBeginLoad);
	LevelManager->OnLevelLoaded.AddDynamic(this, &UAoS_GameInstance::OnLevelFinishLoad);
	LevelManager->OnLevelUnloaded.AddDynamic(this, &UAoS_GameInstance::OnLevelFinishUnload);
}

void UAoS_GameInstance::SetupUIBindings()
{
	
}

void UAoS_GameInstance::SetupCaseBindings()
{
	
}

void UAoS_GameInstance::OnLevelBeginLoad(UAoS_MapData* LoadingLevel)
{
	if (UIManager)
	{
		UIManager->DisplayLoadingScreen(true);
	}
}

void UAoS_GameInstance::OnLevelFinishLoad(UAoS_MapData* LoadedLevel)
{
	if (!AoS_PlayerController)
	{
		AoS_PlayerController = Cast<AAoS_PlayerController>(GetFirstLocalPlayerController());
	}
	SpawnPlayer();
	if (bIsInMenu)
	{
		AoS_PlayerController->bShowMouseCursor = true;
		AoS_PlayerController->SetInputMode(FInputModeUIOnly());
	}
	else
	{
		AoS_PlayerController->bShowMouseCursor = false;
		AoS_PlayerController->SetInputMode(FInputModeGameOnly());
	}
	GetWorld()->GetTimerManager().SetTimer(LoadingScreenDelayHandle, this, &UAoS_GameInstance::PostLoadingScreenDelay, 5.0f);
}

void UAoS_GameInstance::OnLevelFinishUnload(UAoS_MapData* UnloadedLevel)
{

}

void UAoS_GameInstance::Init()
{
	Super::Init();
	
	CaseManager = GetSubsystem<UAoS_CaseManager>();
	UIManager = GetSubsystem<UAoS_UIManager>();
	LevelManager = GetSubsystem<UAoS_LevelManager>();
	WorldManager = GetSubsystem<UAoS_WorldManager>();
	if(LevelManager)
	{
		SetupLevelBindings();
		if (!LevelManager->GetCurrentStreamingLevel())
		{
			LevelManager->LoadLevel(MainMenu, false);
		}
	}
	
}

void UAoS_GameInstance::PostLoadingScreenDelay()
{
	if (UIManager)
	{
		UIManager->DisplayLoadingScreen(false);
	}
}

APlayerStart* UAoS_GameInstance::GetPlayerStart() const
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	for (AActor* CurrentActor : PlayerStartActors)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(CurrentActor))
		{
			return PlayerStart;
		}
	}
	return nullptr;
}
