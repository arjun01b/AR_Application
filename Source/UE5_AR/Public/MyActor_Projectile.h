// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Sound/SoundCue.h"
#include "MyActor_Projectile.generated.h"


UCLASS()
class UE5_AR_API AMyActor_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_Projectile();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor, UPrimitiveComponent*OtherComponent,FVector NormalImpulse,const FHitResult& hit);
	

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile);
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Projectile")
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly,Category=Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	

	void FireinDirection(const FVector& ShootDirection);

	


	
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile);
	class USoundCue* ProjectileSoundCue;


	UPROPERTY(VisibleDefaultsOnly, Category=Projectile);
	UAudioComponent* ProjectileAudioComponent;
};
