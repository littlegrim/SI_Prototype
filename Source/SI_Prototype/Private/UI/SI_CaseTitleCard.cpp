// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SI_CaseTitleCard.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


void USI_CaseTitleCard::ShowTitleCard(UTexture2D* InCaseBackground, USoundBase* InTitleMusic, float InDisplayTime, bool bInShouldFade)
{
	if (!IsValid(InCaseBackground)) {return;}
	
	IMG_CaseBackground->SetBrushFromTexture(InCaseBackground);
	TitleMusic = InTitleMusic;
	bShouldFadeIn = bInShouldFade;

	CardDisplayTimerDelegate.BindUObject(this, &USI_CaseTitleCard::HideTitleCard);
	GetWorld()->GetTimerManager().SetTimer(CardDisplayTimerHandle, CardDisplayTimerDelegate, InDisplayTime, false);
	
	OnShowTitleCard();
}

void USI_CaseTitleCard::HideTitleCard()
{
	CardDisplayTimerDelegate.Unbind();
	OnHideTitleCard();
}
