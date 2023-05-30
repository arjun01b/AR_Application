// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_Projectile.h"

#include "Components/AudioComponent.h"

// Sets default values
AMyActor_Projectile::AMyActor_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(!RootComponent)
	{
		RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if(!CollisionComponent)
	{
		CollisionComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent")); //Sphere as a collision component

		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		CollisionComponent->OnComponentHit.AddDynamic(this,&AMyActor_Projectile::OnHit);
		
		CollisionComponent->InitSphereRadius(5.0f); //Setting radius

		RootComponent=CollisionComponent; //Setting root component as collisioncomponent
		
	}

	if(!ProjectileMovementComponent)
	{
		ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed=3000.0f;
		ProjectileMovementComponent->MaxSpeed=3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity=true;
		ProjectileMovementComponent->bShouldBounce=true;
		ProjectileMovementComponent->Bounciness=0.3f;
		ProjectileMovementComponent->ProjectileGravityScale=0.0f;
	}

	if(!ProjectileMeshComponent)
	{
		ProjectileMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Assets/Meshes/Sphere.Sphere'"));
		if(Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Assets/Materials/SphereMaterial.SphereMaterial'"));
	if(Material.Succeeded())
	{
		ProjectileMaterialInstance=UMaterialInstanceDynamic::Create(Material.Object,ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0,ProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09,0.09,0.09));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	InitialLifeSpan=3.0f;


	static ConstructorHelpers::FObjectFinder<USoundCue>ProjectileSoundCueObject(TEXT("SoundCue'/Game/Sounds/Main/435417__v-ktor__shoot02_Cue.435417__v-ktor__shoot02_Cue'"));
	if(ProjectileSoundCueObject.Succeeded())
	{


		ProjectileSoundCue=ProjectileSoundCueObject.Object;



		ProjectileAudioComponent=CreateDefaultSubobject<UAudioComponent>(TEXT("ProjectileAudioComponent"));

		ProjectileAudioComponent->SetupAttachment(RootComponent);
	}

	

}

// Called when the game starts or when spawned
void AMyActor_Projectile::BeginPlay()
{
	Super::BeginPlay();


	if(ProjectileAudioComponent&&ProjectileSoundCue)
	{
		ProjectileAudioComponent->SetSound(ProjectileSoundCue);
	}
}

// Called every frame
void AMyActor_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor_Projectile::FireinDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity=ShootDirection*ProjectileMovementComponent->InitialSpeed;
	ProjectileAudioComponent->Play();
}


void AMyActor_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit)
{
	if(OtherActor!=this&&OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity*100.0f,hit.ImpactPoint);
	}

	Destroy();
}


