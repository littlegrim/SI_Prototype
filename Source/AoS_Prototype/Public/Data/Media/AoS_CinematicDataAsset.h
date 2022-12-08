// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSequencePlayer.h"
#include "Data/Media/AoS_MediaDataAsset.h"
#include "AoS_CinematicDataAsset.generated.h"

class ULevelSequencePlayer;
class ALevelSequenceActor;
class ULevelSequence;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicSkipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicEnd);

UCLASS()
class AOS_PROTOTYPE_API UAoS_CinematicDataAsset : public UAoS_MediaDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cinematics")
	ULevelSequence* LevelSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cinematics")
	FMovieSceneSequencePlaybackSettings PlaybackSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cinematics")
	ALevelSequenceActor* LevelSequenceActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cinematics")
	ULevelSequencePlayer* CinematicPlayer;

	UPROPERTY(BlueprintAssignable, Category = "Cinematics")
	FOnCinematicStart OnCinematicStart;
	UPROPERTY(BlueprintAssignable, Category = "Cinematics")
	FOnCinematicSkipped OnCinematicSkipped;
	UPROPERTY(BlueprintAssignable, Category = "Cinematics")
	FOnCinematicEnd OnCinematicEnded;

	virtual void StartMedia() override;
	virtual void SkipMedia() override;

protected:

	virtual void ClearDelegates() override;

private:

	UFUNCTION()
	void OnCinematicEnd();
};
