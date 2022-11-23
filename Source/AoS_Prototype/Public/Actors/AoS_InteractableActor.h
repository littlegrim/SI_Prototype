// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/AoS_InteractInterface.h"
#include "AoS_InteractableActor.generated.h"

<<<<<<< Updated upstream
class AAoS_Nick;
=======
class UAoS_InteractableComponent;
class UBoxComponent;
>>>>>>> Stashed changes
class UWidgetComponent;

UCLASS()
class AOS_PROTOTYPE_API AAoS_InteractableActor : public AActor, public IAoS_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAoS_InteractableActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UAoS_InteractableComponent* InteractableComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
<<<<<<< Updated upstream
	class UBoxComponent* OverlapBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionPrompt;	
=======
	UBoxComponent* OverlapBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* InteractionPrompt;
>>>>>>> Stashed changes

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
<<<<<<< Updated upstream
=======



public:	
>>>>>>> Stashed changes
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnBeginOverlap(AAoS_Nick* InNickActor);
	UFUNCTION()
	void OnEndOverlap(AAoS_Nick* InNickActor);

};
