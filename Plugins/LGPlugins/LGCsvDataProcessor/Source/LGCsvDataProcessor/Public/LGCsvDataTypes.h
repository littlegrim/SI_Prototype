// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EasyCsvTypes.h"
#include "GameplayTagContainer.h"
#include "LGCsvDataTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCsvDataProcessor, Log, All);

USTRUCT(BlueprintType)
struct LGCSVDATAPROCESSOR_API FLGCsvInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString CSVToWrite;

	UPROPERTY()
	FEasyCsvInfo CSVInfoResults;

	UPROPERTY()
	TArray<FString> ExportKeys;

	UPROPERTY()
	TArray<FString> DialogueStringArray;
};

USTRUCT()
struct LGCSVDATAPROCESSOR_API FLGCsvInfoImportPayload
{
	GENERATED_BODY()

	UPROPERTY()
	FString URL;

	UPROPERTY()
	FGuid DialogueStructID;

	UPROPERTY()
	FGuid DataTableOwnerID;

	UPROPERTY()
	FGuid DialogueArrayID;
		
	UPROPERTY()
	FString FileName;

	UPROPERTY()
	FString FilePath;

	UPROPERTY()
	UObject* Caller;

	UPROPERTY()
	FGameplayTag CsvArrayTypeTag;

	UPROPERTY()
	FName DialogueTag;

	UPROPERTY()
	TSoftObjectPtr<UDataTable> DataTableSoftPtr;
};


USTRUCT()
struct LGCSVDATAPROCESSOR_API FLGDialogueArray
{
	GENERATED_BODY()

	FLGDialogueArray();
	virtual ~FLGDialogueArray(){}
	
	UPROPERTY()
	FGameplayTag DialogueStructTypeTag;

	UPROPERTY()
    FName DialogueTag;
	
	UPROPERTY()
	FName PropertyName;

	UPROPERTY()
	FGuid DialogueArrayID;

	UPROPERTY()
	FString DialogueArrayLabel;

	void GenerateDialogueTagFromTypeName(FName& OutDialogueTag, const FGameplayTag& InStructType);

	virtual void SetDataTable(UDataTable* InDataTable);
		
	virtual UScriptStruct* GetStructContainer();
	virtual UDataTable* GetDialogueDataTable();
	virtual void InitializeDialogueDataTable(UDataTable* InDataTable);
	virtual void InitializeContainedDialogueTags();
	
	bool operator==(const FLGDialogueArray& OtherDialogue) const;
	bool operator!=(const FLGDialogueArray& OtherDialogue) const;
};

USTRUCT()
struct LGCSVDATAPROCESSOR_API FLGDialogueArrayData
{
	GENERATED_BODY()

	FLGDialogueArrayData();
	virtual ~FLGDialogueArrayData(){}

	FGuid DialogueDataID;
	FString DialogueLabel;
	TArray<FLGDialogueArray*> DialogueArrays;

	virtual void AddNewArrayByTag(const FGameplayTag& InStructTypeTag, FLGCsvInfoImportPayload& OutPayload, const FName& InDialogueTag = FName());
	virtual FLGDialogueArray* GetDialogueArrayByID(const FGuid& InDialogueArrayID);
};