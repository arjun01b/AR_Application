// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "CustomARPawn.generated.h"

class UCameraComponent;

UCLASS()
class UE5_AR_API ACustomARPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomARPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos);
	//FVector LineTraceFunction(FVector Loc, FRotator Rot);

	bool WorldHitTest(FVector2d(screenPos),FHitResult(HitTestResult));

	UPROPERTY(EditDefaultsOnly, Category= Projectile)
	TSubclassOf<class AMyActor_Projectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	class ASpawnPlayer* Playerspawn;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
	bool gameState;

	
	bool canShoot;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
//	USceneComponent* SceneComponent;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;

	UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ASpawnPlayer> PlacableToSpawn;

	//UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
	//UCharacterMovementComponent* MoveComponent;

	//Should fire function be declared here?
	UFUNCTION()
	void Fire();
	
	
    UFUNCTION()
	FVector LineTraceFunction(FVector Loc, FRotator Rot);

	//FPSCharactercode

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myCategory")
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myCategory")
	FVector CameraPos;
	
	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
	FRotator RotSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myCategory")
	FRotator MuzzleRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myCategory")
	FVector TargetLoc;

	int TraceDistance;

	//bool shootingDelay;
	

};
