// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AoS_GizboController.h"

#include "Characters/AoS_Nick.h"
#include "Characters/AoS_NPC.h"
#include "AoS_Prototype/AoS_Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AAoS_GizboController::AAoS_GizboController() : AAoS_NPCController_Interactable()
{
	ConfigurePerception();
}

void AAoS_GizboController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAoS_GizboController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAoS_GizboController::UpdateBehaviorTree()
{
	Super::UpdateBehaviorTree();
}

void AAoS_GizboController::ConfigurePerception()
{
	//TODO: Play around with / discuss values with Jeff, Manuel etc.
	if (SightConfig)
	{
		SightConfig->SightRadius = 2000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		//SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	}

	if (HearingConfig)
	{
		HearingConfig->HearingRange = 2000.0f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	}

	if (PerceptionComp && SightConfig && HearingConfig)
	{
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->ConfigureSense(*HearingConfig);
		PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AAoS_GizboController::SetSeenTarget(AActor* Actor)
{
	Super::SetSeenTarget(Actor);
}

void AAoS_GizboController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && Stimulus.IsValid() && Stimulus.IsActive())
	{
		if (Nick)
		{
			switch (Stimulus.Type)
			{
				case 0: //Sight
					{
						//TODO: Amend accordingly
						if (bCanFollow)
						{
							SetSeenTarget(Actor);
							UpdateBehaviorTree();
						}
						break;
					}
				case 1: //Hearing
					{
						//TODO: Implement
						break;
					}
				default:
					{
						//TODO: Implement
						break;
					}
			}
		}
		else
		{
			switch (Stimulus.Type)
			{
				case 0: //Sight
					{
						//TODO: Amend accordingly
						if (bCanMoveTo)
						{
							SetSeenTarget(Actor);
							UpdateBehaviorTree();
						}
						break;
					}
				case 1: //Hearing
					{
						//TODO: Implement
						break;
					}
				default:
					{
						//TODO: Implement
						break;
					}
			}
		}
	}
}

void AAoS_GizboController::ToggleFollow()
{
	bCanFollow = !bCanFollow;
	bCanMoveTo = false;
	
	if (!bCanFollow && PossessedNPC->IsPerformingMainAction())
	{
		// Stop Gizbo from following Nick
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_Nothing);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: Follow Action Disabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleFollow Follow Action Disabled"), *GetNameSafe(GetPawn()));
	}
	else
	{
		// Allow Gizbo to follow Nick
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_PerformingMainAction);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: Follow Action Enabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleFollow Follow Action Enabled"), *GetNameSafe(GetPawn()));
	}
	
	UpdateBehaviorTree();
}

void AAoS_GizboController::ToggleMoveTo()
{
	bCanMoveTo = !bCanMoveTo;
	bCanFollow = false;

	if (!bCanMoveTo && PossessedNPC->IsMovingToTarget())
	{
		// Stop Gizbo from moving to a target
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_Nothing);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: MoveTo Action Disabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleMoveTo MoveTo Action Disabled"), *GetNameSafe(GetPawn()));
	}
	else
	{
		// Allow Gizbo to move to a target
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_MovingToTarget);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: MoveTo Action Enabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleMoveTo MoveTo Action Enabled"), *GetNameSafe(GetPawn()));
	}
	
	UpdateBehaviorTree();
}

void AAoS_GizboController::ToggleWait()
{
	bCanFollow = false;
	bCanMoveTo = false;

	if (!PossessedNPC->IsDoingNothing())
	{
		// Make Gizbo wait for further action
		PossessedNPC->SetCurrentBehavior(ECurrentBehavior::CB_Nothing);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Gizbo: Waiting Action Enabled")));
		UE_LOG(LogAoSAI, Log, TEXT("%s : AoS_GizboController::ToggleWait Waiting Action Enabled"), *GetNameSafe(GetPawn()));
	}

	SetLostTarget();
	UpdateBehaviorTree();
}

