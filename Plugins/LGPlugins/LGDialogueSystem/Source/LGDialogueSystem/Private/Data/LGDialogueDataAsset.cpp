// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LGDialogueDataAsset.h"
#include "LGCsvDataProcessorFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void ULGDialogueDataAsset::UpdateDialogue_Internal()
{
	for(const FLGDialogueURL& CurrentURL : DialogueURLs)
	{
		FString FilePath = UKismetSystemLibrary::GetProjectSavedDirectory();
		FilePath.Append(FolderPath + "/");

		FLGCsvInfoImportPayload ImportPayload;
		ImportPayload.Caller = this;
		ImportPayload.FolderName = FolderName;
		ImportPayload.FilePath = FilePath;
		ImportPayload.FileName = CurrentURL.FileName;
		ImportPayload.URL = CurrentURL.URL;
		ImportPayload.CsvArrayTypeTag = CurrentURL.DialogueStructType;
		
		FRDTGetStringDelegate CallbackDelegate;
		CallbackDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ULGDialogueDataAsset, OnSheetStructsDownloaded));
		
		ULGCsvDataProcessorFunctionLibrary::ImportCsvFromURL(ImportPayload, CallbackDelegate);
	}
}

void ULGDialogueDataAsset::UpdateDialogue()
{
	UpdateDialogue_Internal();
}

void ULGDialogueDataAsset::OnInteractComplete_Implementation(UObject* Caller, const FLGCsvInfo& InCvsInfo)
{
	UE_LOG(LogLGDialogue, Warning, TEXT("Dilogue Asset Interaction Complete!"));
}

UStruct* ULGDialogueDataAsset::GetUStructContainer()
{
	return nullptr;
}

void* ULGDialogueDataAsset::GetDialogueStructArrayByTag(const FGameplayTag& InGameplayTag)
{
	return nullptr;
}

FName ULGDialogueDataAsset::GetStructPropertyNameByTag(const FGameplayTag& InGameplayTag)
{
	return FName("NONE");
}

void ULGDialogueDataAsset::OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo)
{
	const FGameplayTag& CsvArrayType = InCallbackInfo.CsvArrayTypeTag;
	const FName& PropertyName = GetStructPropertyNameByTag(CsvArrayType);
	void* DialogueStructArray = GetDialogueStructArrayByTag(CsvArrayType);
	
	ULGCsvDataProcessorFunctionLibrary::OnSheetStructsDownloaded(InCallbackInfo, DialogueStructArray, GetUStructContainer(), PropertyName);
}
