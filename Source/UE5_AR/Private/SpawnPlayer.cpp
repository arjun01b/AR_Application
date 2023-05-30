// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPlayer.h"

// Sets default values
ASpawnPlayer::ASpawnPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);


	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Meshes/Andy_Mesh.Andy_Mesh'"));
	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

	//StaticMeshComponent->SetRelativeScale3D(FVector (1.0,1.0,1.0));
	

}

// Called when the game starts or when spawned
void ASpawnPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

