// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InteractionInterface.h"
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Camera boom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Enhanced input actions (set in the blueprint)
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Interact;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputMappingContext* IMC_Player;

	//HAndlers
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
UPROPERTY(EditAnywhere,Category="Health")
float HP{};
UFUNCTION(BlueprintCallable)
void PrintHealth();

};
