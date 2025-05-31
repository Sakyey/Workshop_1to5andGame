// Fill out your copyright notice in the Description page of Project Settings.


#include "AActor.h"

// Sets default values
AAActor::AAActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	RootComponent = TriggerSphere;

}

// Called when the game starts or when spawned
void AAActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this,&AAEventActor::OnOverlapBegin);
	
}

// Called every frame
void AAActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AAEventActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AAActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if(GEngine){
		GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Cyan,FString::Printf(TEXT("Overlapping from CPP!")));
	}
}

