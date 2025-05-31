// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "COverlapActor.h"

// Sets default values
ACOverlapActor::ACOverlapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	RootComponent=TriggerSphere;

	TriggerSphere->InitSphereRadius(200.0f);

	TriggerSphere->SetCollisionProfileName(TEXT("Trigger"));

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this,&ACOverlapActor::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ACOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOverlapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACOverlapActor::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult){

		if(OtherActor  && OtherActor->IsA<PlayerCharacter>()){
			if(GEngine){
				GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Green,TEXT("C++ Overlap with player"));
			}
		}
}

