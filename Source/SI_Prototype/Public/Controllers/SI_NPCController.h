// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "SI_NPCController.generated.h"

class ASI_NPC;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

/**
 * Base NPC Controller for SI Prototype
 */
UCLASS()
class SI_PROTOTYPE_API ASI_NPCController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASI_NPCController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	//TODO: Should also define what to do OnUnPossess
	virtual void UpdateBehaviorTree();
	virtual void ConfigurePerception();
	virtual void SetSeenTarget(AActor* Actor);
	virtual void SetLostTarget();
	//TODO: Will need to add support for AI Perception Teams, if we want NPCs to belong to specific factions, and have interactions between each other.
	
	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAIPerceptionComponent> PerceptionComp = nullptr;
	TObjectPtr<UAISenseConfig_Sight> SightConfig = nullptr;
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<ASI_NPC> PossessedNPC = nullptr;

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	FName BlackboardTargetKey = "Target";

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "AI", meta = (AllowPrivateAccess = true))
	FName BlackboardCanSeeTargetKey = "CanSeeTarget";
};
