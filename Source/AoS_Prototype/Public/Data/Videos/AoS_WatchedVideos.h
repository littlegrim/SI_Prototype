// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoS_WatchedVideos.generated.h"

class UAoS_VideoDataAsset;

UCLASS()
class AOS_PROTOTYPE_API UAoS_WatchedVideos : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Videos")
	void AddToWatchedVideos(UAoS_VideoDataAsset* InVideoToAdd);
	
	UFUNCTION(BlueprintPure, Category = "Videos")
	TArray<UAoS_VideoDataAsset*>& GetWatchedVideos();	
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Videos")
	TArray<UAoS_VideoDataAsset*> WatchedVideos;
	
};
