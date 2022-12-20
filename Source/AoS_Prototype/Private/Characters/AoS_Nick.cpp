// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_Nick.h"

#include "AI/AoS_AIPerceptionStimuliSource.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Data/Characters/AoS_NickCharacterData.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "UI/AoS_HUD.h"

AAoS_Nick::AAoS_Nick()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create an observation camera
	ObservationCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ObservationCamera"));
	ObservationCamera->SetupAttachment(RootComponent);
	
	// Create an AI Perception Stimuli Source component
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAoS_AIPerceptionStimuliSource>(TEXT("Perception Stimuli Source Component"));
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Sight::StaticClass());
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Hearing::StaticClass());
}


void AAoS_Nick::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(NickCharacterData)) {return;}
	
	FString MapName = GetWorld()->GetMapName();
	
	if (MapName == "M_NicksOffice")
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("NoJacketNick"))));
	}
	else
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("JacketNick"))));
	}
}


