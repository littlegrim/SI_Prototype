// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SI_GameplayAbility_Wait.h"

#include "Characters/SI_NPC.h"

void USI_GameplayAbility_Wait::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	LG_LOG_LOG(LogLG_Ability," Ability Activated");


	ASI_NPC* Actor = Cast<ASI_NPC>(ActorInfo->OwnerActor);
	if(!IsValid(Actor)) {LG_LOG(LogLG_Ability, Error, "Actor is not valid"); return;}

	Actor->SetCurrentBehavior(SITag_Behavior_Waiting);
}

void USI_GameplayAbility_Wait::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
