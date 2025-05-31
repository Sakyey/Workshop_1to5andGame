// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class WORKSHOP_1TO5ANDGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetUpPlayerInputComponent(UInputComponent* InputComponent) override;

	//Camera boom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Catergory="Camera")
	class UCameraComponent* FollowCamera;

	//Enhanced input actions (set in the blueprint)
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Look;

	//HAndlers
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
