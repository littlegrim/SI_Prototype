// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_UIManager.h"
#include "SI_GameInstance.h"

// Subsystems
#include "SI_GameplayTagManager.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "Data/Cases/SI_CaseManager.h"
#include "Media/SI_MediaManager.h"
#include "Levels/SI_LevelManager.h"

// Case Data
#include "Data/Cases/SI_CaseData.h"
#include "Data/Cases/SI_PartData.h"
#include "Data/Cases/SI_ObjectiveData.h"

// UI
#include "UI/SI_DialogueBox.h"
#include "UI/SI_HUD.h"
#include "UI/SI_UserWidget.h"
#include "UI/SI_MoviePlayerWidget.h"
#include "UI/SI_InteractionWidget.h"
#include "UI/SI_CaseTitleCard.h"
#include "UI/SI_SkipWidget.h"

#include "Controllers/SI_PlayerController.h"
#include "Data/Maps/SI_MenuMapData.h"
#include "Data/Media/SI_VideoDataAsset.h"
#include "GameModes/SI_GameMode.h"
#include "SI_NativeGameplayTagLibrary.h"

#if !UE_BUILD_SHIPPING
static TAutoConsoleVariable<int32> CvarDisableTitleCard(
	TEXT("CheatDisableTitleCards"),
	0,
	TEXT("Disables the titles cards after accepting a case.\n")
	TEXT("<=0: enabled\n")
	TEXT("  1: disabled\n"),
	ECVF_Scalability | ECVF_RenderThreadSafe);
#endif

DEFINE_LOG_CATEGORY(LogSI_UIManager);

USI_UIManager::USI_UIManager()
{
}

void USI_UIManager::OnGameInstanceInit()
{
	Super::OnGameInstanceInit();
	
	BindCaseManagerDelegates();
}

void USI_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);	
}
//Called from listener of GameplayTagManager OnTagAddedDelegate.Broadcast() in AddNewGameplayTag()
void USI_UIManager::OnGameplayTagAdded(const FGameplayTag& InAddedTag)
{
	Super::OnGameplayTagAdded(InAddedTag);

	CurrentUITag = InAddedTag;
	
	if(InAddedTag == SITag_Game_State_Loading)
	{
		SITagManager->ReplaceTagWithSameParent(SITag_UI_Screen_Loading, SITag_UI);
	}

	if(InAddedTag == SITag_Player_State_Exploration)
	{
		SITagManager->AddNewGameplayTag(SITag_UI_HUD);
	}

	if(InAddedTag == SITag_Media_Video)
	{
		SITagManager->AddNewGameplayTag(SITag_UI_Screen_Video);
	}
	
	if(!SITagManager->HasParentTag(InAddedTag, SITag_UI)){return;}
	
	if(SITagManager->HasParentTag(InAddedTag, SITag_UI_HUD_QuickAction))
	{
		AddUIDelegateContainer.Find(SITag_UI_HUD_QuickAction)->Execute();

		if(InAddedTag != SITag_UI_HUD_QuickAction_GadgetsOne)
		{
			SITagManager->RemoveTag(SITag_UI_HUD_QuickAction_GadgetsOne);
		}
		return;
	}

	AddUIDelegateContainer.Find(InAddedTag)->Execute();
}	
//Called from listener of GameplayTagManager OnTagRemovedDelegate.Broadcast() in RemoveTag()
void USI_UIManager::OnGameplayTagRemoved(const FGameplayTag& InRemovedTag)
{
	Super::OnGameplayTagRemoved(InRemovedTag);

	if(InRemovedTag == SITag_Game_State_Loading)
	{
		SITagManager->RemoveTag(SITag_UI_Screen_Loading);
	}

	if(InRemovedTag == SITag_Player_State_Exploration)
	{
		SITagManager->RemoveTag(SITag_UI_HUD);
	}

	if(InRemovedTag == SITag_Media_Video)
	{
		SITagManager->RemoveTag(SITag_UI_Screen_Video);
	}
	
	if(!SITagManager->HasParentTag(InRemovedTag, SITag_UI)){return;}
	
	if (InRemovedTag == SITag_UI_Screen_Loading)
	{
		DisplayLoadingScreen(false, true);
		return;
	}
	if (InRemovedTag == SITag_UI_Screen_Video)
	{
		RemoveMoviePlayerWidget();
		return;
	}
	if (InRemovedTag == SITag_UI_Screen_TitleCard)
	{
		RemoveCaseTitleCard();
		return;
	}

	if(InRemovedTag != SITag_UI_HUD_QuickAction_GadgetsOne && SITagManager->HasParentTag(InRemovedTag, SITag_UI_HUD_QuickAction))
	{
		SITagManager->AddNewGameplayTag(SITag_UI_HUD_QuickAction_GadgetsOne);
	}
	
	RemoveSIWidget(GetWidgetByTag(InRemovedTag));
	UIWidgetContainer.Remove(InRemovedTag);
}

void USI_UIManager::BindCaseManagerDelegates()
{
	/*USI_CaseManager* CaseManager = GameInstance->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}

	// Case Bindings
	CaseManager->OnCaseAccepted.AddDynamic(this, &ThisClass::OnCaseAccepted);
	CaseManager->OnCaseActivated.AddDynamic(this, &ThisClass::OnCaseActivated);
	CaseManager->OnCaseComplete.AddDynamic(this, &ThisClass::OnCaseCompleted);

	// Part Bindings
	CaseManager->OnPartActivated.AddDynamic(this, &ThisClass::OnPartActivated);
	CaseManager->OnPartComplete.AddDynamic(this, &ThisClass::OnPartCompleted);

	// Objective Bindings
	CaseManager->OnObjectiveActivated.AddDynamic(this, &ThisClass::OnObjectiveActivated);
	CaseManager->OnObjectiveComplete.AddDynamic(this, &ThisClass::OnObjectiveCompleted);*/
}

void USI_UIManager::DelayWidgetCreation(TSubclassOf<USI_UserWidget> InWidgetClass, FGameplayTag InUITag)
{
	FSimpleDelegate NewDelegate;
	NewDelegate.BindUObject(this, &ThisClass::CreateSIWidgetAndAddToViewport, InWidgetClass, InUITag);

	WidgetCreationDelayDelegates.Add(NewDelegate);
}

void USI_UIManager::InitializeDelegates()
{
	Super::InitializeDelegates();
	
	AddHUDDelegate.BindUObject(this, &ThisClass::CreatePlayerHUD);
	AddLoadingScreenDelegate.BindUObject(this, &ThisClass::DisplayLoadingScreen, true, true);
	AddVideoScreenDelegate.BindUObject(this, &ThisClass::CreateMoviePlayerWidget);
	AddSystemMenuDelegate.BindUObject(this, &ThisClass::ToggleSystemMenu);
	AddMapMenuDelegate.BindUObject(this, &ThisClass::CreateMapMenu);
	UpdateQuickActionDelegate.BindUObject(this, &ThisClass::UpdateQuickActionWidget);
}

void USI_UIManager::InitializeDelegateMaps()
{
	Super::InitializeDelegateMaps();
	
	AddUIDelegateContainer.Add(SITag_UI_Menu_Game, AddGameMenuDelegate);
	AddUIDelegateContainer.Add(SITag_UI_Menu_Map, AddMapMenuDelegate);
	AddUIDelegateContainer.Add(SITag_UI_Menu_System, AddSystemMenuDelegate);
	AddUIDelegateContainer.Add(SITag_UI_Menu_Vendor, AddVendorMenuDelegate);
	AddUIDelegateContainer.Add(SITag_UI_HUD, AddHUDDelegate);
	AddUIDelegateContainer.Add(SITag_UI_HUD_QuickAction, UpdateQuickActionDelegate);
	AddUIDelegateContainer.Add(SITag_UI_Screen_Loading, AddLoadingScreenDelegate);
	AddUIDelegateContainer.Add(SITag_UI_Screen_Video, AddVideoScreenDelegate);
}

void USI_UIManager::CreatePlayerHUD()
{
	if (!IsValid(GameInstance->GetGameMode()) || IsValid(PlayerHUD)){return;}
	
	PlayerHUD = Cast<USI_HUD>(CreateSIWidget(GameInstance->GetGameMode()->PlayerHUD_Class, SITag_UI_HUD));
	if(IsValid(PlayerHUD))
	{
		PlayerHUD->AddToViewport();
	}
}

void USI_UIManager::CreateMoviePlayerWidget()
{
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(GameInstance) || !IsValid(GameInstance->GetGameMode())){return;}

	MoviePlayerWidget = Cast<USI_MoviePlayerWidget>(CreateSIWidget(GameInstance->GetGameMode()->MoviePlayerWidget, SITag_UI_Screen_Video));
	
	if (IsValid(MoviePlayerWidget))
	{
		const USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>();
		if (IsValid(MediaManager) && IsValid(MediaManager->GetLoadedVideo()))
		{
			MoviePlayerWidget->SetMediaTexture(MediaManager->GetLoadedVideo()->MediaTexture);
			MoviePlayerWidget->SetMediaPlayer(MediaManager->GetLoadedVideo()->MediaPlayer);
			MoviePlayerWidget->SetMediaSource(MediaManager->GetLoadedVideo()->MediaSource);
			MoviePlayerWidget->AddToViewport();
			MoviePlayerWidget->PlayVideo();
		}
		else
		{
			
		}
	}
}

void USI_UIManager::RemoveMoviePlayerWidget()
{
	if (!IsValid(MoviePlayerWidget)){return;}
	
	MoviePlayerWidget->OnVideoStopped();
	RemoveSIWidget(MoviePlayerWidget);
}

void USI_UIManager::ShowCaseTitleCard()
{
	if (!TitleCardDelayDelegate.IsBound()){return;}
#if !UE_BUILD_SHIPPING
	if (CvarDisableTitleCard.GetValueOnGameThread() == 1) {return;}
#endif
	
	TitleCardDelayDelegate.Execute();
	if (IsValid(CaseTitleCardWidget))
	{
	}
	TitleCardDelayDelegate.Unbind();
}

void USI_UIManager::CreateCaseTitleCard(USI_CaseData* InCase, bool bShouldFadeIn)
{
	if (!IsValid(InCase)) {return;}

	CaseTitleCardWidget = CreateWidget<USI_CaseTitleCard>(GetWorld()->GetFirstPlayerController(), InCase->TitleCardWidget);
	if (IsValid(CaseTitleCardWidget))
	{
		CaseTitleCardWidget->AddToViewport();
		CaseTitleCardWidget->ShowTitleCard(InCase->CaseName, InCase->TitleCardBackground, InCase->TitleCardMusic, InCase->TitleCardLength, bShouldFadeIn);
	}
}

void USI_UIManager::RemoveCaseTitleCard()
{
	RemoveSIWidget(CaseTitleCardWidget);
	
	USI_CaseManager* CaseManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_CaseManager>();
	if (!IsValid(CaseManager)) {return;}
	
	CaseManager->OnCaseTitleCardComplete().Broadcast();
}

USI_UserWidget* USI_UIManager::CreateSIWidget(TSubclassOf<USI_UserWidget> InWidgetClass, FGameplayTag InUITag)
{
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if(!IsValid(InWidgetClass)) {return nullptr;}

	if (!IsValid(PlayerController))
	{
		DelayWidgetCreation(InWidgetClass, InUITag);
		return nullptr;
	}
	
	USI_UserWidget* SIWidget = CreateWidget<USI_UserWidget>(PlayerController, InWidgetClass);
	if (IsValid(SIWidget))
	{
		UIWidgetContainer.Add(InUITag, SIWidget);
		
		if (SITagManager->HasParentTag(InUITag, SITag_UI_Menu))
		{
			PlayerController->SetFocusedWidget(SIWidget);
		}
	}

	return SIWidget;
}

void USI_UIManager::CreateSIWidgetAndAddToViewport(TSubclassOf<USI_UserWidget> InWidgetClass, FGameplayTag InUITag)
{
	USI_UserWidget* SIWidget = CreateSIWidget(InWidgetClass, InUITag);
	if(IsValid(SIWidget))
	{
		SIWidget->AddToViewport();
	}
}

void USI_UIManager::RemoveSIWidget(USI_UserWidget* InWidgetPtr)
{
	if (!IsValid(InWidgetPtr)){return;}
	
	InWidgetPtr->RemoveFromParent();
	InWidgetPtr = nullptr;
}

USI_UserWidget* USI_UIManager::GetWidgetByTag(const FGameplayTag InWidgetTag)
{
	for (TPair<FGameplayTag, USI_UserWidget*>& CurrentWidgetPair : UIWidgetContainer)
	{
		if (CurrentWidgetPair.Key == InWidgetTag)
		{
			return CurrentWidgetPair.Value;
		}
	}
	
	return nullptr;
}

void USI_UIManager::CreateMapMenu()
{
	USI_LevelManager* LevelManager = GameInstance->GetSubsystem<USI_LevelManager>();
	if (!IsValid(LevelManager) || IsValid(MapMenu)){return;}

	const USI_MenuMapData* MenuMapData = Cast<USI_MenuMapData>(LevelManager->GetCurrentMap());
	if (!IsValid(MenuMapData) || !IsValid(MenuMapData->MapMenuWidgetClass)){return;}

	MapMenu = CreateSIWidget(MenuMapData->MapMenuWidgetClass, SITag_UI_Menu_Map);
	if(IsValid(MapMenu))
	{
		MapMenu->AddToViewport();
	}
}

void USI_UIManager::CreateSystemMenu()
{
	if (!IsValid(GameInstance->GetGameMode())){return;}

	SystemMenu = CreateSIWidget(GameInstance->GetGameMode()->SystemMenuClass, SITag_UI_Menu_System);
	if(IsValid(SystemMenu))
	{
		SystemMenu->AddToViewport();
	}
}

void USI_UIManager::ToggleSystemMenu()
{
	if (!IsValid(SystemMenu))
	{
		CreateSystemMenu();
	}
	else
	{
		SystemMenu->RemoveFromParent();
	}
}

USI_SkipWidget* USI_UIManager::CreateSkipWidget()
{
	PlayerController = Cast<ASI_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!IsValid(PlayerController) || !IsValid(GameInstance->GetGameMode())){return nullptr;}
	
	SkipWidget = CreateWidget<USI_SkipWidget>(PlayerController,  GameInstance->GetGameMode()->SkipWidget);
	if (IsValid(SkipWidget))
	{
		SkipWidget->AddToViewport();
	}
	return SkipWidget;
}

void USI_UIManager::AddActiveInteractionWidget(USI_InteractionWidget* InInteractionWidget)
{
	if (IsValid(InInteractionWidget))
	{
		ActiveInteractionWidgets.AddUnique(InInteractionWidget);
	}
}

void USI_UIManager::RemoveActiveInteractionWidget(USI_InteractionWidget* InInteractionWidget)
{
	if (IsValid(InInteractionWidget))
	{
		ActiveInteractionWidgets.Remove(InInteractionWidget);
	}
}

void USI_UIManager::UpdateQuickActionWidget()
{
	if(!IsValid(PlayerHUD)){return;}
	
	PlayerHUD->UpdateQuickActionWidget(CurrentUITag);
}

FGameplayTag USI_UIManager::GetQuickActionAbilityTag(const FGameplayTag& InQuickActionTag)
{
	if(!IsValid(PlayerHUD)){return SITag_None;}
	
	return PlayerHUD->GetQuickActionAbilityTag(InQuickActionTag);
}

void USI_UIManager::DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade)
{
	const ASI_GameMode* GameMode = Cast<ASI_GameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)){return;}
	
	if (bShouldDisplay)
	{
		if (GameMode->LoadingScreens.Num() > 0)
		{
			const int32 RandNumb = FMath::RandRange(0, GameMode->LoadingScreens.Num() - 1);
			if (const TSubclassOf<USI_UserWidget> SelectedLoadingScreen = GameMode->LoadingScreens[RandNumb])
			{
				LoadingScreen = CreateSIWidget(SelectedLoadingScreen, SITag_UI_Screen_Loading);
				
				if (IsValid(LoadingScreen) && IsValid(GameInstance))
				{
					GameInstance->GetGameViewportClient()->AddViewportWidgetContent(LoadingScreen->TakeWidget());
				}
			}
		}
	}
	else
	{
		if (IsValid(LoadingScreen))
		{
			if (bShouldFade)
			{
				LoadingScreen->FadeOutWidget();
				LoadingScreen = nullptr;
			}
			else
			{
				GameInstance->GetGameViewportClient()->RemoveViewportWidgetContent(LoadingScreen->TakeWidget());
				LoadingScreen = nullptr;
			}
		}
	}
}

void USI_UIManager::DisplayDialogueBox()
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())){return;}

	PlayerHUD->GetDialogueBox()->RefreshDialogueBox();
	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Visible);
}

void USI_UIManager::HideDialogueBox()
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetDialogueBox())) { return; }

	PlayerHUD->GetDialogueBox()->SetVisibility(ESlateVisibility::Hidden);
}

void USI_UIManager::HideActiveInteractionWidgets()
{
	if (ActiveInteractionWidgets.Num() <= 0){return;}
	for (USI_InteractionWidget* CurrentInteractionWidget : ActiveInteractionWidgets)
	{
		if (IsValid(CurrentInteractionWidget))
		{
			CurrentInteractionWidget->HideWidget();
		}
	}
	
	ActiveInteractionWidgets.Empty();
}

void USI_UIManager::LoadingScreenFadeDelay()
{
	LoadingScreenFadeDelayDelegate.BindUObject(this, &USI_UIManager::DisplayLoadingScreen, false, false);
	GetWorld()->GetTimerManager().SetTimer(LoadingScreenFadeDelayHandle, LoadingScreenFadeDelayDelegate, 20.0f, false);
}

void USI_UIManager::OnCaseAccepted(USI_CaseData* AcceptedCase)
{
	if (!IsValid(AcceptedCase) || !IsValid(PlayerHUD)) {return;}
	
	if (IsValid(AcceptedCase->TitleCardWidget))
	{
		PlayerHUD->ShowCaseAcceptedWidget();
		//TitleCardDelayDelegate.BindUObject(this, &ThisClass::CreateCaseTitleCard, AcceptedCase, GameInstance->GetPreviousPlayerMode() == EPlayerMode::PM_ExplorationMode);
	}
}

void USI_UIManager::OnCaseActivated(USI_CaseData* ActivatedCase)
{
	
}

void USI_UIManager::OnCaseCompleted(USI_CaseData* CompletedCase)
{
	
}

void USI_UIManager::OnPartActivated(USI_PartData* ActivatedPart)
{
	
}

void USI_UIManager::OnPartCompleted(USI_PartData* CompletedPart)
{
	
}

void USI_UIManager::OnPlayerStart()
{
	Super::OnPlayerStart();

	for(FSimpleDelegate& CurrentDelegate : WidgetCreationDelayDelegates)
	{
		if(CurrentDelegate.IsBound())
		{
			CurrentDelegate.Execute();
			CurrentDelegate.Unbind();
		}
	}
	WidgetCreationDelayDelegates.Empty();
}

void USI_UIManager::OnObjectiveActivated(USI_ObjectiveData* ActivatedObjective)
{
	
}

void USI_UIManager::OnObjectiveCompleted(USI_ObjectiveData* CompletedObjective)
{
	
}

TArray<USI_InteractionWidget*>& USI_UIManager::GetActiveInteractionWidgets()
{
	return ActiveInteractionWidgets;
}

USI_MoviePlayerWidget* USI_UIManager::GetMoviePlayerWidget() const
{
	return MoviePlayerWidget;
}

USI_HUD* USI_UIManager::GetPlayerHUD()
{
	return PlayerHUD;
}
