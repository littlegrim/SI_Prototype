// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SI_MoveToIndicator.generated.h"

class USI_AIPerceptionStimuliSource;

UCLASS()
class SI_PROTOTYPE_API ASI_MoveToIndicator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASI_MoveToIndicator();
	
	void SetPerceptionStimuliSource();
	void UpdateActiveMesh(UStaticMesh* InMesh);
	void SetActiveMeshToDefault();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MoveToMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMesh* DefaultMesh;

private:
	UPROPERTY(VisibleAnywhere)
	USI_AIPerceptionStimuliSource* StimuliSource;
};