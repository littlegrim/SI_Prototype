// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Characters/SI_NPC_Interactable.h"
#include "Abilities/SI_GameplayAbility.h"
#include "SI_Gizbo.generated.h"

class UPhysicsHandleComponent;
class USI_AbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SI_PROTOTYPE_API ASI_Gizbo : public ASI_NPC_Interactable , public IAbilitySystemInterface 
{
	GENERATED_BODY()
public:
	ASI_Gizbo();
	USI_AbilitySystemComponent* GetSIAbilitySystemComponent() const;
protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldingItem;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Abilities)
	USI_AbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USI_GameplayAbility>> DefaultAbilities;
	
private:
	void HeldItemPosition();
	void PickupObject(AActor* InHitActor);
	void PushObject(AActor* InHitActor);
	UFUNCTION(BlueprintCallable)
	void DropItem();
	UFUNCTION(BlueprintCallable)
	void LocateInteractable();
	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere, Category = "Gizbo Item Interaction")
	float InteractDistance;
	UPROPERTY(EditAnywhere, Category = "Gizbo Item Interaction")
	float CarryOffset;
	UPROPERTY(EditAnywhere, Category = "Gizbo Item Interaction")
	float AdjustedDampening;
	// Used to restore item state after Gizbo drops it
	float DefaultDampening;
	
	UPROPERTY()
	UPrimitiveComponent* ObjectBeingCarried;
	UPROPERTY()
	AActor* HeldActor;
	FRotator CarriedObjectRotation;
	FName PickupSocket = TEXT("Socket_Chest");

	void ConstructGadget(FGameplayTag InGadgetTag, APawn* InPawnRequestingGadget);
	
	void GiveAbilities();
};
