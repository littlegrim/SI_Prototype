// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AoS_UserWidget.h"
#include "AoS_HUD.generated.h"

class UAoS_DialogueBox;
class UAoS_CaseManager;
class UAoS_Case;
class UAoS_Part;
class UAoS_Objective;

UCLASS()
class AOS_PROTOTYPE_API UAoS_HUD : public UAoS_UserWidget
{
	GENERATED_BODY()

public:
	
	UAoS_HUD();

	UFUNCTION(BlueprintCallable)
	UAoS_DialogueBox* GetDialogueBox() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnObjectiveComplete(UAoS_Objective* CompletedObjective);
	void OnObjectiveComplete_Implementation(UAoS_Objective* CompletedObjective);

protected:

	UPROPERTY(meta=(BindWidget))
	UAoS_DialogueBox* DialogueBox;
	
private:

	UPROPERTY()
	UAoS_CaseManager* CaseManagerRef;
	bool bBindingsSetup;
	
	virtual void NativeConstruct() override;
	void SetupBindings();
	
};
