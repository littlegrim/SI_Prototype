// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AoS_Nick.h"

<<<<<<< HEAD
#include "AI/AoS_AIPerceptionStimuliSource.h"
=======
#include "AoS_GameInstance.h"
#include "Camera/CameraActor.h"
>>>>>>> cce4cdcfa9286d95bddaf46848769a82dd2c851b
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Data/Characters/AoS_NickCharacterData.h"
<<<<<<< HEAD
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "UI/AoS_HUD.h"
=======
#include "Data/Maps/AoS_MapData.h"
#include "Levels/AoS_LevelManager.h"
>>>>>>> cce4cdcfa9286d95bddaf46848769a82dd2c851b

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
	FollowCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetChildActorClass(ACameraActor::StaticClass());
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create an observation camera
	ObservationCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("ObservationCamera"));
	ObservationCamera->SetupAttachment(RootComponent);
<<<<<<< HEAD
	
	// Create an AI Perception Stimuli Source component
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAoS_AIPerceptionStimuliSource>(TEXT("Perception Stimuli Source Component"));
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Sight::StaticClass());
	PerceptionStimuliSourceComponent->RegisterSense(UAISense_Hearing::StaticClass());
=======
	ObservationCamera->SetChildActorClass(ACameraActor::StaticClass());
}

void AAoS_Nick::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(FollowCamera))
	{
		FollowCameraActor = Cast<ACameraActor>(FollowCamera->GetChildActor());
		FollowCameraActor->GetCameraComponent()->SetConstraintAspectRatio(false);
	}
	if (IsValid(FollowCamera))
	{
		ObservationCameraActor = Cast<ACameraActor>(ObservationCamera->GetChildActor());
		ObservationCameraActor->GetCameraComponent()->SetConstraintAspectRatio(false);
	}
>>>>>>> cce4cdcfa9286d95bddaf46848769a82dd2c851b
}


void AAoS_Nick::BeginPlay()
{
	Super::BeginPlay();

	UAoS_GameInstance* GameInstance = Cast<UAoS_GameInstance>(GetWorld()->GetGameInstance());
	if (!IsValid(GameInstance)) {return;}

	LevelManager = GameInstance->GetLevelManager();
	if (!IsValid(LevelManager)){return;}

	if(LevelManager->GetLevelHasLoaded())
	{
		OnLevelLoaded(LevelManager->GetCurrentMap());
	}
	else
	{
		LevelManager->OnLevelLoaded.AddDynamic(this, &ThisClass::OnLevelLoaded);	
	}
}


void AAoS_Nick::OnLevelLoaded(UAoS_MapData* LoadedLevel, bool bShouldFade)
{
	FString MapName;
	
	if (LoadedLevel)
	{
		MapName = LoadedLevel->GetName();
	}
	else
	{
		MapName = "DA_MainMenu";
	}
	
	if (MapName == "DA_NicksOffice")
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("NoJacketNick"))));
	}
	else
	{
		GetMesh()->SetSkeletalMesh(NickCharacterData->GetClothingMeshFromName(FName(TEXT("JacketNick"))));
	}
}


