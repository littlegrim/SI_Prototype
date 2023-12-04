﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SI_GameplayTagTypes.h"

void FSI_GameplayTagContainer::SetParentTag(const FGameplayTag& InParentTag)
{
	ParentTag = InParentTag;
}

const FGameplayTag& FSI_GameplayTagContainer::GetParentTag() const
{
	return ParentTag;
}

FSITagPayload::FSITagPayload(AActor* InCaller, AActor* InTarget):
	Instigator(InCaller),
	Target(InTarget)
{
}

bool FSITagPayload::operator==(const FSITagPayload& Other) const
{
	return Instigator == Other.Instigator && Target == Other.Target;
}

bool FSITagPayload::operator!=(const FSITagPayload& Other) const
{
	return Instigator != Other.Instigator || Target != Other.Target;
}
