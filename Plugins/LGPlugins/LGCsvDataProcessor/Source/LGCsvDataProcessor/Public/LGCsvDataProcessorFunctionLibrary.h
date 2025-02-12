// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RuntimeDataTable.h"
#include "LGCsvDataTypes.h"
#include "LGCsvDataProcessorFunctionLibrary.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestCheckForEmbeddedCsv, const void* InArrayPtr);

UCLASS()
class LGCSVDATAPROCESSOR_API ULGCsvDataProcessorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION()
	static void ImportCsvFromURL(const FLGCsvInfoImportPayload& InImportPayload, FRDTGetStringDelegate InCallbackDelegate);

	static void OnSheetStructsDownloaded(FRuntimeDataTableCallbackInfo InCallbackInfo, void* InArrayPtr, UScriptStruct* InStructPtr, const FName& InPropertyName);
};
