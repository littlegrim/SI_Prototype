// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_UIManager.generated.h"

class UAoS_SkipWidget;
class UAoS_InteractionWidget;
class UAoS_InteractionPrompt;
class UMediaPlayer;
class UAoS_MoviePlayerWidget;
class UAoS_DialogueManager;
class UAoS_Objective;
class UAoS_Part;
class UAoS_Case;
class AAoS_PlayerController;
class UAoS_HUD;
class UAoS_UserWidget;
class UAoS_MapData;
class UAoS_CaseTitleCard;

enum class EPlayerMode : uint8;

UCLASS()
class AOS_PROTOTYPE_API UAoS_UIManager : public UAoS_GameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the creation and display of the various UI in Ace of Spades
	
public:

	UAoS_UIManager();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreatePlayerHUD();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPlayerHUD(bool bShouldShow);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemovePlayerHUD();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateMoviePlayerWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveMoviePlayerWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowCaseTitleCard();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateCaseTitleCard(UAoS_Case* InCase, bool bShouldFadeIn = false);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveCaseTitleCard();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateMainMenu();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveMainMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	UAoS_SkipWidget* CreateSkipWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveSkipWidget();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplayLoadingScreen(bool bShouldDisplay, bool bShouldFade);
	
	// Case Manager Delegates
	UFUNCTION()
	void OnCaseAccepted(UAoS_Case* AcceptedCase);
	UFUNCTION()
	void OnCaseActivated(UAoS_Case* ActivatedCase);
	UFUNCTION()
	void OnCaseCompleted(UAoS_Case* CompletedCase);

	UFUNCTION()
	void OnPartActivated(UAoS_Part* ActivatedPart);
	UFUNCTION()
	void OnPartCompleted(UAoS_Part* CompletedPart);

	UFUNCTION()
	void SetMenuMode(bool bInMenu = false, UAoS_UserWidget* WidgetToFocus = nullptr);

	UFUNCTION()
	void AddActiveInteractionWidget(UAoS_InteractionWidget* InInteractionWidget);
	UFUNCTION()
	void RemoveActiveInteractionWidget(UAoS_InteractionWidget* InInteractionWidget);
	
	UFUNCTION()
	void OnObjectiveActivated(UAoS_Objective* ActivatedObjective);
	UFUNCTION()
	void OnObjectiveCompleted(UAoS_Objective* CompletedObjective);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	TArray<UAoS_InteractionWidget*>& GetActiveInteractionWidgets();

	UFUNCTION(BlueprintPure, Category = "Media")
	UAoS_MoviePlayerWidget* GetMoviePlayerWidget() const;
	UFUNCTION(BlueprintPure, Category = "PlayerHUD")
	UAoS_HUD* GetPlayerHUD();

protected:

	virtual void OnGameInstanceInit() override;
	virtual void OnPlayerModeChanged(EPlayerMode NewPlayerMode, EPlayerMode InPreviousPlayerMode) override;
	virtual void OnGameModeBeginPlay() override;

	void DisplayDialogueBox();
	void HideDialogueBox();
	void HideActiveInteractionWidgets();
	void LoadingScreenFadeDelay();


private:

	void BindCaseManagerDelegates();
	
	UPROPERTY()
	AAoS_PlayerController* PlayerController;
	UPROPERTY()
	UAoS_UserWidget* LoadingScreen;
	UPROPERTY()
	UAoS_HUD* PlayerHUD;
	UPROPERTY()
	UAoS_UserWidget* MainMenu;
	UPROPERTY()
	UAoS_SkipWidget* SkipWidget;
	UPROPERTY()
	UAoS_MoviePlayerWidget* MoviePlayerWidget;
	UPROPERTY()
	UAoS_CaseTitleCard* CaseTitleCardWidget;
	UPROPERTY()
	TArray<UAoS_InteractionWidget*> ActiveInteractionWidgets;

	FTimerHandle LoadingScreenFadeDelayHandle;
	FTimerDelegate LoadingScreenFadeDelayDelegate;

	FSimpleDelegate TitleCardDelayDelegate;
	
};
