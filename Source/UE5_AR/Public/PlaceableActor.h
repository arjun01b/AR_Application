// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "Enemy.h"
#include "EnemyNew.h"
#include "GameFramework/Actor.h"
#include "PlaceableActor.generated.h"

class UARPin;

UCLASS()
class UE5_AR_API APlaceableActor : public AActor
{
	GENERATED_BODY()
private:
	///FTimerHandle Ticker;
	//AEnemyNew* SpawnedEnemy;
public:	
	// Sets default values for this actor's properties
	APlaceableActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION()
	//void ();
  // UFUNCTION()
  // void MoveActor();

	float t;
	////
	float scale;
	//
	float x;
	//
	float y;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
///
	//
	//UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	//TSubclassOf<ACharacter> EnemyToSpawn;

	//UFUNCTION(BlueprintNativeEvent, Category = "GameModeBase", DisplayName = "Start Play")
	//	void StartPlayEvent();

	//UFUNCTION(BlueprintCallable, Category="Spawn")
	//	virtual void SpawnEnemy();


	//UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	//TSubclassOf<AEnemyNew> PlacableToSpawnEnemy;

	UARPin* PinComponent;

	FVector PlacableLoc;
//


	UFUNCTION()
	void LocationForActor();

	

};
