// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
// #include "InteractionInterface.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create and attach spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//ATtach it to the root (capsule component from ACharacter)
	SpringArm->SetupAttachment(GetRootComponent());
	//Distance from the character
	SpringArm->TargetArmLength=300.0f;
	
	//Let the controller rotate the arm
	SpringArm->bUsePawnControlRotation=true;

	//create and attach follow camrera
	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//Attach the camera to socket on the ennd of the springarm
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	//Don't rotate the camera by controller, only the arm
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller)){
		if(ULocalPlayer* LP = PlayerController->GetLocalPlayer()){
			if(UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()){
			Subsystem->AddMappingContext(IMC_Player,0);
			}
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
	if(UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){
		if(IA_Move){
			EIC->BindAction(IA_Move,ETriggerEvent::Triggered,this,&APlayerCharacter::Move);
		}
		if(IA_Look){
			EIC->BindAction(IA_Look,ETriggerEvent::Triggered,this,&APlayerCharacter::Look);
		}
		if(IA_Jump){
			EIC->BindAction(IA_Jump,ETriggerEvent::Triggered,this,&ACharacter::Jump);
			EIC->BindAction(IA_Jump,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
		}
	}

}
//Move handler
void APlayerCharacter::Move(const FInputActionValue& Value){
	//Convert to FVector2
	FVector2D MovementVector = Value.Get<FVector2D>();

	//ADd movement in forward direction (Y) and right direction (X)
	AddMovementInput(GetActorForwardVector(),MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}
//Look handler
void APlayerCharacter::Look(const FInputActionValue& Value){
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerYawInput(LookVector.Y);
}
void APlayerCharacter::PrintHealth(){
	if(GEngine){
		GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Cyan,FString::Printf(TEXT("Current Health: %f"),HP));
	}

	UE_LOG(LogTemp,Warning, TEXT("Current health: %f"), HP);
}
void APlayerCharacter::Interact(){

}

