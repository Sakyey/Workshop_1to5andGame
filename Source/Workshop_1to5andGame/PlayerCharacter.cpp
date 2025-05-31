// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create and attach spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")):
	//ATtach it to the root (capsule component from ACharacter)
	SpringArm->SetupAttachment(GetRootComponent());
	//Distance from the character
	SpringArm->TargetArmLength=300.0f;
	//Let the controller rotate the arm
	SpringArm->bUsePawnControlRotation=true;

	//create and attach follow camrera
	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//Attach the camera to socker on the ennd of the springarm
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	//Don't rotate the camera by controller, only the arm
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller)){
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(IMC_Player,0);
		}
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

