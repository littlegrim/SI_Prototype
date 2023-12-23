// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "SI_Character.generated.h"

class USI_AbilitySystemComponent;

UCLASS()
class SI_PROTOTYPE_API ASI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASI_Character();

	USI_AbilitySystemComponent* GetAbilitySystemComponent() {return AbilitySystemComponent; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character | Abilities")
	USI_AbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsMainCharacter = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", meta=(EditCondition = "!bIsMainCharacter", EditConditionHides))
	int32 NPC_Version;
};
