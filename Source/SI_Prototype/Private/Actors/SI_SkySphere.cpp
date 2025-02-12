// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SI_SkySphere.h"

#include "SI_GameInstance.h"
#include "Components/LightComponent.h"
#include "Curves/CurveLinearColor.h"
#include "World/SI_SunLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/SI_WorldManager.h"


// Sets default values
ASI_SkySphere::ASI_SkySphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	SetRootComponent(Base);
	SkySphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkySphereMesh"));
	SkySphereMesh->SetupAttachment(Base);
}

void ASI_SkySphere::UpdateSunDirection()
{
	if (!SkySphereMesh || !SkyMaterial || !DynamicSkyMaterial || !SunLightActor || !HorizonColorCurve || !ZenithColorCurve || !CloudColorColorCurve) {return;}
	const FLinearColor LightDirectionVector = UKismetMathLibrary::Conv_VectorToLinearColor(UKismetMathLibrary::Conv_RotatorToVector(SunLightActor->GetActorRotation()));
	DynamicSkyMaterial->SetVectorParameterValue("Light direction", LightDirectionVector);

	const FLinearColor SunColorVector = UKismetMathLibrary::Conv_ColorToLinearColor(SunLightActor->GetSunLightComponent()->LightColor);
	DynamicSkyMaterial->SetVectorParameterValue("Sun color", SunColorVector);

	SunHeight = UKismetMathLibrary::MapRangeUnclamped(SunLightActor->GetActorRotation().Pitch, 0, -90, 0, 1);

	const FLinearColor HorizonColorVector = HorizonColorCurve->GetClampedLinearColorValue(SunHeight);
	DynamicSkyMaterial->SetVectorParameterValue("Horizon color", HorizonColorVector);

	const FLinearColor ZenithColorVector = ZenithColorCurve->GetClampedLinearColorValue(SunHeight);
	DynamicSkyMaterial->SetVectorParameterValue("Zenith color", ZenithColorVector);

	const FLinearColor CloudColorVector = CloudColorColorCurve->GetClampedLinearColorValue(SunHeight);
	DynamicSkyMaterial->SetVectorParameterValue("Cloud color", CloudColorVector);

	const float HorizonFalloffValue = FMath::Lerp(3, 8, FMath::Abs(SunHeight));
	DynamicSkyMaterial->SetScalarParameterValue("Horizon falloff", HorizonFalloffValue);

	const float SunHeightValue = UKismetMathLibrary::SelectFloat(FMath::Abs(SunHeight), 0, SunHeight < 0);
	DynamicSkyMaterial->SetScalarParameterValue("Sun height", SunHeightValue);

}

void ASI_SkySphere::RefreshMaterial()
{
	if (!SkySphereMesh || !SkyMaterial  || !DynamicSkyMaterial || !HorizonColorCurve || !ZenithColorCurve || !CloudColorColorCurve) {return;}
	if (SunLightActor)
	{
		const FLinearColor LightDirectionVector = UKismetMathLibrary::Conv_VectorToLinearColor(UKismetMathLibrary::Conv_RotatorToVector(SunLightActor->GetActorRotation()));
		DynamicSkyMaterial->SetVectorParameterValue("Light direction", LightDirectionVector);

		const FLinearColor SunColorVector = UKismetMathLibrary::Conv_ColorToLinearColor(SunLightActor->GetSunLightComponent()->LightColor);
		DynamicSkyMaterial->SetVectorParameterValue("Sun color", SunColorVector);

		SunHeight = UKismetMathLibrary::MapRangeUnclamped(SunLightActor->GetActorRotation().Pitch, 0, -90, 0, 1);
	}
	else
	{
		const FLinearColor LightDirectionVector = UKismetMathLibrary::Conv_VectorToLinearColor(UKismetMathLibrary::Conv_RotatorToVector(FRotator(0, UKismetMathLibrary::MapRangeUnclamped(SunHeight, -1, 1, 90, -90), GetActorRotation().Yaw)));
		DynamicSkyMaterial->SetVectorParameterValue("Light direction", LightDirectionVector);

		FLinearColor A = FLinearColor(1.0, 0.221, 0.04, 1.0);
		FLinearColor B = FLinearColor(0.954, 0.901, 0.74412, 1.0);
		const FLinearColor SunColorVector = UKismetMathLibrary::LinearColorLerp(A, B, UKismetMathLibrary::Clamp(SunHeight + .2, 0, 1));
		DynamicSkyMaterial->SetVectorParameterValue("Sun color", SunColorVector);
	}

	if (bColorsDeterminedBySunPosition)
	{
		const FLinearColor HorizonColorVector = HorizonColorCurve->GetClampedLinearColorValue(SunHeight);
		DynamicSkyMaterial->SetVectorParameterValue("Horizon color", HorizonColorVector);

		const FLinearColor ZenithColorVector = ZenithColorCurve->GetClampedLinearColorValue(SunHeight);
		DynamicSkyMaterial->SetVectorParameterValue("Zenith color", ZenithColorVector);

		const FLinearColor CloudColorVector = CloudColorColorCurve->GetClampedLinearColorValue(SunHeight);
		DynamicSkyMaterial->SetVectorParameterValue("Cloud color", CloudColorVector);

		const float HorizonFalloffValue = FMath::Lerp(3, 8, FMath::Abs(SunHeight));
		DynamicSkyMaterial->SetScalarParameterValue("Horizon falloff", HorizonFalloffValue);
	}
	else
	{
		DynamicSkyMaterial->SetVectorParameterValue("Horizon color", HorizonColor);
		DynamicSkyMaterial->SetVectorParameterValue("Zenith color", ZenithColor);
		DynamicSkyMaterial->SetVectorParameterValue("Cloud color", CloudColor);
		DynamicSkyMaterial->SetScalarParameterValue("Horizon falloff", HorizonFalloff);
	}

	DynamicSkyMaterial->SetScalarParameterValue("Cloud speed", CloudSpeed);
	DynamicSkyMaterial->SetScalarParameterValue("Sun brightness", SunBrightness);

	const float SunHeightValue = UKismetMathLibrary::SelectFloat(FMath::Abs(SunHeight), 0, SunHeight < 0);
	DynamicSkyMaterial->SetScalarParameterValue("Sun height", SunHeightValue);
	DynamicSkyMaterial->SetScalarParameterValue("Cloud opacity", CloudOpacity);
	DynamicSkyMaterial->SetScalarParameterValue("Stars brightness", StarsBrightness);
}

void ASI_SkySphere::RotateSun(FRotator InRotation)
{
	if(SunLightActor)
	{
		SunLightActor->SetActorRelativeRotation(InRotation);
		RefreshMaterial();
	}
}

void ASI_SkySphere::SetSunLightActor(ASI_SunLight* SunLightToSet)
{
	SunLightActor = SunLightToSet;
}

// Called when the game starts or when spawned
void ASI_SkySphere::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USI_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		WorldManager = GameInstance->GetSubsystem<USI_WorldManager>();
	}
	if (WorldManager)
	{
		WorldManager->SetSkySphere(this);
	}
}

void ASI_SkySphere::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (!SkySphereMesh) {return;}
	
	if (SkyMaterial)
	{
		DynamicSkyMaterial = SkySphereMesh->CreateDynamicMaterialInstance(0, SkyMaterial);
	}

	if (bRefreshMaterial)
	{
		bRefreshMaterial = false;
	}
	else
	{
		bRefreshMaterial = false;
	}

	RefreshMaterial();
	
}

// Called every frame
void ASI_SkySphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

