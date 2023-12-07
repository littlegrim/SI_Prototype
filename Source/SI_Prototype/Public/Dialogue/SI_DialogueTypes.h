// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SI_DialogueTypes.generated.h"

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_PrimaryDialogue
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Line;

	UPROPERTY(BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(BlueprintReadOnly)
	FText Dialogue;

	UPROPERTY(BlueprintReadOnly)
	FString PressURL;
	
	UPROPERTY(BlueprintReadOnly)
	FString ResponseURL;

	UPROPERTY(BlueprintReadOnly)
    bool IsTrueStatement;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_CorrectedDialogue
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 CorrectedLine;

	UPROPERTY(BlueprintReadOnly)
	int32 SpeakerLine;

	UPROPERTY(BlueprintReadOnly)
	FText SpeakerName;
	
	UPROPERTY(BlueprintReadOnly)
	FText Dialogue;
};

USTRUCT(BlueprintType)
struct SI_PROTOTYPE_API FSI_DefaultResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 CorrectedLine;

	UPROPERTY(BlueprintReadOnly)
	int32 SpeakerLine;

	UPROPERTY(BlueprintReadOnly)
	FText SpeakerName;
	
	UPROPERTY(BlueprintReadOnly)
	FText Dialogue;	
};