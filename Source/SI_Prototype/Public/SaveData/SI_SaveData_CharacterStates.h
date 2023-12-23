// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SI_CharacterTypes.h"
#include "GameFramework/SaveGame.h"
#include "SI_SaveData_CharacterStates.generated.h"

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API USI_SaveData_CharacterStates : public USaveGame
{
	GENERATED_BODY()

	USI_SaveData_CharacterStates();

public:

	void UpdateCharacterState(const FSI_CharacterState& InCharacterState);

private:

	TMap<FGameplayTag, FSI_CharacterState> CharacterStates;

	void AddNewCharacterState(const FSI_CharacterState& InCharacterState);
};
