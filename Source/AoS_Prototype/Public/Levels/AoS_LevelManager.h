// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/AoS_GameInstanceSubsystem.h"
#include "AoS_LevelManager.generated.h"

enum class EMapType : uint8;

class UAoS_UIManager;
class UAoS_MapData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginLevelLoad, UAoS_MapData*, LoadingLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelLoaded, UAoS_MapData*, LoadedLevel, bool, bShouldFade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloaded, UAoS_MapData*, UnloadedLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMapTypeChanged, EMapType, NewMapType);

UCLASS()
class AOS_PROTOTYPE_API UAoS_LevelManager : public UAoS_GameInstanceSubsystem
{
	GENERATED_BODY()

	// This subsystem will handle the loading and unloading of levels inside the persistent level
	
public:

	UAoS_LevelManager();

	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnBeginLevelLoad OnBeginLevelLoad;
	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnLevelLoaded OnLevelLoaded;
	UPROPERTY(BlueprintAssignable, Category = "Levels")
	FOnLevelUnloaded OnLevelUnloaded;
	UPROPERTY(BlueprintAssignable, Category = "MapData")
	FOnMapTypeChanged OnMapTypeChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Levels")
	void LoadLevel(UAoS_MapData* InLevelToLoad, bool bAllowDelay = true, bool bShouldFade = true,  FString InPlayerStartTag = FString(TEXT("")));
	UFUNCTION(BlueprintCallable, Category = "Levels")
	TArray<FString> GetMapNames();
	UFUNCTION(BlueprintCallable, Category = "Levels")
	UAoS_MapData* GetMapFromName(FString MapName);
	UFUNCTION(BlueprintCallable, Category = "Levels")
	EMapType GetCurrentMapType() const;
	UFUNCTION(BlueprintCallable, Category = "Levels")
	UAoS_MapData* GetCurrentMap() const;
	UFUNCTION(BlueprintCallable, Category = "Levels")
	FString GetCurrentMapName() const;
	
	UFUNCTION(BlueprintCallable)
    void UpdateMapType(EMapType InMapType);
	
	UFUNCTION()
	void LevelLoaded();
	UFUNCTION()
	void OnGameLoaded();

	UAoS_MapData* GetCurrentLoadedLevel() const {return CurrentLevel;}

protected:
	
	virtual void OnGameInstanceInit() override;

private:
		
	float LevelLoadDelay;
	bool bLoadShouldFade = true;

	UPROPERTY()
	UAoS_MapData* LevelToLoad;
	UPROPERTY()
	UAoS_MapData* CurrentLevel;
	UPROPERTY()
	UAoS_MapData* MainMenu;
	UPROPERTY()
	EMapType CurrentMapType;

	FString PlayerStartTag;


	FTimerHandle LoadDelayHandle;
	FTimerHandle UnloadDelayHandle;
	FTimerHandle PersistentLevelLoadTimerHandle;

	UFUNCTION()
	void ExecuteLevelLoad();

	UAoS_MapData* GetMapDataFromStreamingLevel(ULevelStreaming* InStreamingLevel);
};