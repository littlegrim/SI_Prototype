// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SI_PlayerController.h"

#include "ATPCCameraComponent.h"
#include "SI_GameInstance.h"
#include "SI_GameplayTagManager.h"
#include "Components/Actor/SI_EnhancedInputComponent.h"
#include "Interfaces/SI_InteractInterface.h"
#include "MediaAssets/Public/MediaSoundComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "Cameras/SI_PlayerCameraManager.h"
#include "Characters/SI_GizboManager.h"
#include "Media/SI_MediaManager.h"
#include "Actors/SI_InteractableActor.h"
#include "Controllers/SI_GizboController.h"
#include "Data/Media/SI_VideoDataAsset.h"
#include "Data/Media/SI_CinematicDataAsset.h"
#include "Dialogue/SI_DialogueManager.h"
#include "Dialogue/SI_DialogueSession.h"
#include "UI/SI_DialogueBox.h"
#include "UI/SI_HUD.h"
#include "UI/SI_UIManager.h"
#include "Data/Input/SI_InputConfig.h"
#include "SI_Prototype/SI_Prototype.h"
#include "SI_NativeGameplayTagLibrary.h"
#include "SI_PlayerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/SI_Nick.h"
#include "Components/Actor/SI_AbilitySystemComponent.h"
#include "EngineUtils.h" // ActorIterator
#include "Abilities/SI_GameplayAbility_Observation.h"
#include "Characters/SI_Gizbo.h"

// todo: delete when gadget system implemented
#include "Actors/Gadgets/SI_Flashlight.h"


using namespace SI_NativeGameplayTagLibrary;

ASI_PlayerController::ASI_PlayerController()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	MediaSoundComponent = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSoundComponent"));
	MediaSoundComponent->SetupAttachment(RootComponent);

	EnhancedInputSettings = CreateDefaultSubobject<USI_EnhancedInputComponent>(TEXT("EnhancedInputSettings"));
}

void ASI_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USI_EnhancedInputComponent* EnhancedInputComponent = Cast<USI_EnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)){return;}

	const USI_InputConfig* InputConfig = EnhancedInputComponent->GetInputConfig();
	if (!IsValid(InputConfig)) {return;}

	// Axis Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_MoveForward, ETriggerEvent::Triggered, this, &ThisClass::RequestMoveForward);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_MoveRight,  ETriggerEvent::Triggered, this, &ThisClass::RequestMoveRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_TurnRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestTurnRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Axis_1D_LookUpRate,  ETriggerEvent::Triggered, this, &ThisClass::RequestLookUp);
	
	// Nick Action Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Interact, ETriggerEvent::Started, this, &ThisClass::RequestInteract);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleObservationMode, ETriggerEvent::Started, this, &ThisClass::RequestToggleObservation);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ToggleSystemMenu, ETriggerEvent::Started, this, &ThisClass::RequestToggleSystemMenu);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_ObserveObject, ETriggerEvent::Started, this, &ThisClass::RequestObserveObject);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Media_Skip, ETriggerEvent::Triggered, this, &ThisClass::RequestSkipCinematic);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Next, ETriggerEvent::Started, this, &ThisClass::RequestNextDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Previous, ETriggerEvent::Started, this, &ThisClass::RequestPreviousDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Dialogue_Exit, ETriggerEvent::Started, this, &ThisClass::RequestExitDialogue);
	EnhancedInputComponent->BindInputByTag(InputConfig, SITag_Input_Action_UseGadget, ETriggerEvent::Started, this, &ThisClass::RequestUseGadget);
	EnhancedInputComponent->BindInputByTag(InputConfig, SITag_Input_Action_UseGadgetSecondary, ETriggerEvent::Started, this, &ThisClass::RequestUseGadgetSecondary);
	
	// Gizbo Commands Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_Follow, ETriggerEvent::Started, this, &ThisClass::RequestToggleGizboFollow); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MoveTo, ETriggerEvent::Started, this, &ThisClass::RequestToggleGizboAdaptableAction); //TODO: Amend later
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_MoveToConfirm, ETriggerEvent::Started, this, &ThisClass::RequestGizboAdaptableActionConfirm);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_UseGadget, ETriggerEvent::Started, this, &ThisClass::RequestGizboUseGadget);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_Gizbo_UseGadgetSecondary, ETriggerEvent::Started, this, &ThisClass::RequestGizboUseGadgetSecondary);

	// Gadget Bindings
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Down, ETriggerEvent::Started, this, &ThisClass::RequestMutliOptionDown);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Left, ETriggerEvent::Started, this, &ThisClass::RequestMultiOptionLeft);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Right, ETriggerEvent::Started, this, &ThisClass::RequestMultiOptionRight);
	EnhancedInputComponent->BindInputByTag(InputConfig,SITag_Input_Action_MultiOption_Up, ETriggerEvent::Started, this, &ThisClass::RequestMultiOptionUp);
}

void ASI_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	const USI_PlayerManager* PlayerManager = GetLocalPlayer()->GetSubsystem<USI_PlayerManager>();
	if(!IsValid(PlayerManager) || !PlayerManager->GetCurrentPlayerState().IsValid()) {return;}

	if(PlayerManager->GetCurrentPlayerState() == SITag_Player_State_Menu)
	{
		SetMenuMode(true);
	}
	else
	{
		SetMenuMode(false);
	}

	AddInputMappingByTag(PlayerManager->GetCurrentPlayerState());
	if(PlayerManager->GetPreviousPlayerState().IsValid())
	{
		RemoveInputMappingByTag(PlayerManager->GetPreviousPlayerState());
	}

	Nick = Cast<ASI_Nick>(GetCharacter());

	GizboManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_GizboManager>();
	if (IsValid(GizboManager))
	{
		GizboManager->Nick = Cast<ASI_Nick>(GetCharacter());
	}
}

void ASI_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASI_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	USI_GameInstance* GameInstance = Cast<USI_GameInstance>(GetGameInstance());
	if (!IsValid(GameInstance) || !IsValid(PlayerCameraManager)){return;}

	/*if (GameInstance->GetPlayerMode() != EPlayerMode::PM_NONE)
	{
		PlayerCameraManager->StartCameraFade(0, 1, 0.001, FLinearColor::Black, false, true);
	}*/
}

void ASI_PlayerController::RequestMoveForward(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanMove || !GetPawn()) return;

	const float Value = ActionValue.Get<FInputActionValue::Axis1D>();
	
	if ((Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void ASI_PlayerController::RequestMoveRight(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanMove || !GetPawn()) return;

	const float Value = ActionValue.Get<FInputActionValue::Axis1D>();

	if ((Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void ASI_PlayerController::RequestLookUp(const FInputActionValue& ActionValue)
{
	if (!bPlayerCanTurn || !GetPawn()) return;

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();
	
	AddPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASI_PlayerController::RequestTurnRight(const FInputActionValue& ActionValue)
{
	if  (!bPlayerCanTurn || !GetPawn()) return;

	const float AxisValue = ActionValue.Get<FInputActionValue::Axis1D>();

	AddYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASI_PlayerController::RequestInteract()
{
	if (!GetPawn()) {return;}

	if(Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Interact.GetTag().GetSingleTagContainer(), false))
	{
		OnInteractPressed.Broadcast(InteractableActor, this);
	}

	if(InteractableActor)
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteract(InteractableActor, InteractableActor);
			OnInteractPressed.Broadcast(InteractableActor, this);
		}
	}
}

void ASI_PlayerController::RequestToggleObservation()
{
	if(!IsValid(SITagManager)) {return;}
	
	if(SITagManager->HasGameplayTag(SITag_Player_State_Observation))
	{
		Nick->GetSIAbilitySystemComponent()->CancelAbility(Nick->GetSIAbilitySystemComponent()->GetGameplayAbilityFromTag(SITag_Ability_Observation));
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Exploration, SITag_Player_State);
		Nick->HideMeshes(true);
	}
	else
	{
		Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Observation.GetTag().GetSingleTagContainer(), false);
		SITagManager->ReplaceTagWithSameParent(SITag_Player_State_Observation, SITag_Player_State);
		Nick->HideMeshes(false);
	}
}

void ASI_PlayerController::RequestObserveObject()
{
	if (Nick->GetCurrentInteractableActor() != nullptr)
	{
		Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_ObserveObject.GetTag().GetSingleTagContainer(), false);
		if (Nick->GetCurrentInteractableActor() != nullptr)
		{
			Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Interact.GetTag().GetSingleTagContainer(), false);
		}
	}
}

void ASI_PlayerController::RequestSkipCinematic()
{
	if (USI_MediaManager* MediaManager = GetWorld()->GetSubsystem<USI_MediaManager>())
	{
		if (IsValid(MediaManager->GetLoadedVideo()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedVideo());	
		}
		else if (IsValid(MediaManager->GetLoadedCinematic()))
		{
			MediaManager->SkipMedia(MediaManager->GetLoadedCinematic());
		}
	}	
}

void ASI_PlayerController::RequestNextDialogue()
{
	USI_UIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_UIManager>();
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (UIManager && DialogueManager)
	{
		if (DialogueManager->HasNextOption())
		{
			UIManager->GetPlayerHUD()->GetDialogueBox()->OnNextClicked();
		}
	}
}

void ASI_PlayerController::RequestPreviousDialogue()
{
	USI_UIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<USI_UIManager>();
	USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>();
	if (UIManager && DialogueManager)
	{
		if (DialogueManager->HasPreviousOption())
		{
			UIManager->GetPlayerHUD()->GetDialogueBox()->OnPreviousClicked();
		}
	}
}

void ASI_PlayerController::RequestExitDialogue()
{
	if (USI_DialogueManager* DialogueManager = GetWorld()->GetSubsystem<USI_DialogueManager>())
	{
		DialogueManager->GetCurrentDialogue()->ExitDialogue();
	}
	if (InteractableActor)
	{
		if (const ISI_InteractInterface* InterfaceActor = Cast<ISI_InteractInterface>(InteractableActor))
		{
			InterfaceActor->Execute_OnInteractEnd(Cast<UObject>(InteractableActor), InteractableActor);
		}
	}
}

void ASI_PlayerController::RequestToggleSystemMenu()
{
	USI_UIManager* UIManager = GetGameInstance()->GetSubsystem<USI_UIManager>();
	if (IsValid(UIManager))
	{
		UIManager->ToggleSystemMenu();
	}
}

void ASI_PlayerController::RequestUseGadget()
{
	if(!IsValid(SITagManager)) {return;}
	
	if(SITagManager->HasGameplayTag(SITag_Player_State_Exploration))
	{
		Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Gadget_UsePrimary.GetTag().GetSingleTagContainer(), false);
	}
	
	// todo: Delete when gadget system implemented
	TArray<AActor*> AttachedFlashlights;
	Nick->GetAttachedActors(AttachedFlashlights, true, false);

	for (auto AttachedFlashlight : AttachedFlashlights)
	{
		ASI_Flashlight* EquippedFlashlight = Cast<ASI_Flashlight>(AttachedFlashlight);
		EquippedFlashlight->UsePrimary();			
	}	
}

void ASI_PlayerController::RequestUseGadgetSecondary()
{
	if(!IsValid(SITagManager)) {return;}
	
	if(SITagManager->HasGameplayTag(SITag_Player_State_Exploration))
	{
		Nick->GetSIAbilitySystemComponent()->TryActivateAbilitiesByTag(SITag_Ability_Gadget_UseSecondary.GetTag().GetSingleTagContainer(), false);
	}

	// todo: Delete when gadget system implemented
	TArray<AActor*> AttachedFlashlights;
	Nick->GetAttachedActors(AttachedFlashlights, true, false);

	for (auto AttachedFlashlight : AttachedFlashlights)
	{
		ASI_Flashlight* EquippedFlashlight = Cast<ASI_Flashlight>(AttachedFlashlight);
		EquippedFlashlight->UseSecondary();			
	}
}

void ASI_PlayerController::RequestToggleGizboFollow()
{
	GizboManager->GetGizboController()->ToggleFollow();
}

void ASI_PlayerController::RequestToggleGizboAdaptableAction()
{
	bAdaptableActionMode = !bAdaptableActionMode;
	
	if(bAdaptableActionMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Gizbo: AdaptableAction")));
		UE_LOG(LogSIAI, Log, TEXT("%s : SI_PlayerController::RequestToggleGizboAdaptableAction Initiated"), *GetNameSafe(GetPawn()));

		InitializeGizboAdaptableAction();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Gizbo: AdaptableAction")));
		UE_LOG(LogSIAI, Log, TEXT("%s : SI_PlayerController::RequestToggleGizboAdaptableAction Cancelled"), *GetNameSafe(GetPawn()));

		CancelGizboAdaptableAction();
	}
}

void ASI_PlayerController::RequestGizboAdaptableActionConfirm()
{
	bAdaptableActionMode = false;
	GizboManager->GetGizboController()->ToggleMoveTo();
}

void ASI_PlayerController::InitializeGizboAdaptableAction()
{
	ASI_PlayerCameraManager* AOSCamera = Cast<ASI_PlayerCameraManager>(this->PlayerCameraManager);
	if(!IsValid(AOSCamera)) return;
}

void ASI_PlayerController::CancelGizboAdaptableAction()
{
	GizboManager->GetGizboController()->ToggleWait();
}

void ASI_PlayerController::RequestGizboUseGadget()
{
	// todo:
	GizboManager->GetGizboController()->ToggleFollow();
}

void ASI_PlayerController::RequestGizboUseGadgetSecondary()
{
	// todo:
	GizboManager->GetGizboController()->ToggleFollow();
}

void ASI_PlayerController::RequestGadget(AActor* InActor, FGameplayTag InGadgetTag)
{
	FGameplayEventData Payload;
	Payload.Target = InActor;
	Payload.EventTag = InGadgetTag;
	Gizbo->GetSIAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
}

void ASI_PlayerController::RequestMultiOptionUp()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,"Called: RequestMultiOptionUp");

	//TODO: Add functionality to collect gadget GameplayTag from quickbind widget
	RequestGadget(GetPawn(),SITag_Gadget_Flashlight);
}

void ASI_PlayerController::RequestMutliOptionDown()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,"Called: RequestMutliOptionDown");

	//TODO: Add functionality to collect gadget GameplayTag from quickbind widget
	RequestGadget(GetPawn(),SITag_Ability_Construct_Lockpicks);
}

void ASI_PlayerController::RequestMultiOptionLeft()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,"Called: RequestMultiOptionLeft");
}

void ASI_PlayerController::RequestMultiOptionRight()
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,"Called: RequestMultiOptionRight");
}

void ASI_PlayerController::SetInteractableActor(AActor* InInteractableActor)
{
	InteractableActor = Cast<ASI_InteractableActor>(InInteractableActor);
}

AActor* ASI_PlayerController::GetInteractableActor()
{
	return InteractableActor;
}

void ASI_PlayerController::SetObservableActor(AActor* InObservableActor)
{
	ObservableActor = InObservableActor;
}

void ASI_PlayerController::AddInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToAdd = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	const FModifyContextOptions ModifyContextOptions;
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MappingToAdd, 0, ModifyContextOptions);
}

void ASI_PlayerController::RemoveInputMappingByTag(const FGameplayTag InMappingTag, const FGameplayTag InSecondaryTag)
{
	if (!InMappingTag.IsValid()) {return;}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	const UInputMappingContext* MappingToRemove = EnhancedInputSettings->GetInputConfig()->GetInputMappingByTag(InMappingTag, InSecondaryTag);
	EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(MappingToRemove);
}

void ASI_PlayerController::SetFocusedWidget(USI_UserWidget* InWidgetToFocus)
{
	FocusedWidget = InWidgetToFocus;
}

void ASI_PlayerController::SetMenuMode(bool bSetMenuMode)
{
	if (bSetMenuMode)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, FocusedWidget);
		SetShowMouseCursor(true);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
	}
	
	bInMenuMode = bSetMenuMode;
}

UMediaSoundComponent* ASI_PlayerController::GetMediaSoundComponent() const
{
	return MediaSoundComponent;
}

bool ASI_PlayerController::IsInMenuMode() const
{
	return bInMenuMode;
}
