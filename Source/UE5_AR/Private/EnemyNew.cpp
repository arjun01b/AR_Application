// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNew.h"
#include "CustomARPawn.h"
#include "SpawnPlayer.h"
#include "Camera/CameraComponent.h"

// Sets default values
AEnemyNew::AEnemyNew()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyNew::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Camlocation = ARPawnRef->CameraComponent->GetRelativeLocation();

	FVector AndroidLocation = AndroidLoc->StaticMeshComponent->GetRelativeLocation();
	

}

