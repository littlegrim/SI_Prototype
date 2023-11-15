// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGDialogueTypes.generated.h"

class ULGDialogueDataAsset;

DECLARE_LOG_CATEGORY_EXTERN(LogLGDialogue, Log, All);

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGDialogueURL
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString URL_Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString URL;
};

USTRUCT(BlueprintType)
struct LGDIALOGUESYSTEM_API FLGCharacterDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ULGDialogueDataAsset*> DialogueData; 
};