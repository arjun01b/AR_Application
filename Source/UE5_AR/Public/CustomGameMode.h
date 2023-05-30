// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

//Forward Declarations
class APlaceableActor;
class AEnemyNew;
/**
 * 
 */

UCLASS()
class UE5_AR_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()



private:

	FTimerHandle Ticker;
	APlaceableActor* SpawnedActor;
	//AEnemyNew* SpawnedEnemy;

public:
	ACustomGameMode();
	virtual ~ACustomGameMode() = default;


	virtual void StartPlay() override;


	/**
	 * @brief An example of an event as generally seen within the Event Graph of Blueprints
	 *  You can have different implementations of this event which will be called when you call this as a delegate.
	 *	See the CPP For more information on the implementation
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "GameModeBase", DisplayName = "Start Play")
		void StartPlayEvent();

	UFUNCTION(BlueprintCallable, Category = "Score")
		int32 GetScore();

	UFUNCTION(BlueprintCallable, Category="Score")
		void SetScore(const int32 NewScore);
	/**
	 * @brief A Dummy event for spawning ACustomActor.
	 */
	UFUNCTION(BlueprintCallable, Category="Spawn")
		virtual void SpawnCube();

    //UFUNCTION()
	//virtual void SpawnEnemy();
	
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief Perform a line trace at the screen position provided and place a default Placeable actor on it.
	 * Create another actor class that inherits from APlaceableActor and is spawned here instead of the default one. Make sure this new object is placed on the Plane rather than halfway through a plane
	 * @param ScreenPos Pass the Screen Position as an FVector
	 */
	virtual void LineTraceSpawnActor(FVector ScreenPos);
	

	/**
	 * @brief This function is virtual - you can inherit this class to override this function
	 * Each level can have their own unique spawned actors but with similar base qualities using inheritance
	 */
	virtual void SpawnInitialActors();

	 UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	 TSubclassOf<APlaceableActor> PlacableToSpawn;

	UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AEnemyNew> EnemyPlacableToSpawn;
	

	UPROPERTY(Category="Placeable",EditAnywhere,BlueprintReadWrite)
	FVector EnemyPlaceLoc;


	FTransform TrackedTF;

	//bool delayShoot;
//
	//UFUNCTION()
	//void ShootingDelay();
//
	//bool GetDelay();
//
	//void SetDelay(bool newShoot);

//	bool newShoot;
	
};
