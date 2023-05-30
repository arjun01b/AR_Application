// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "ARBlueprintLibrary.h"
#include "CustomActor.h"
#include "Camera/CameraComponent.h"
#include "CustomGameMode.h"
#include "SpawnPlayer.h"
#include "MyActor_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACustomARPawn::ACustomARPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SetRootComponent(CameraComponent);

	
	
	

	gameState=false;
	canShoot=false;
}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();
	UARSessionConfig* Config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(Config);

	const FActorSpawnParameters spawnVar;

	CameraPos = FVector(CameraComponent->GetRelativeLocation().X+25.0,CameraComponent->GetRelativeLocation().Y,CameraComponent->GetRelativeLocation().Z-25);

	RotSpawn = FRotator(0.0f,-90.0f,0.0f);

	Playerspawn  = GetWorld()->SpawnActor<ASpawnPlayer>(CameraPos,RotSpawn,spawnVar);

	Playerspawn->SetActorScale3D(FVector(1.0,1.0,1.0));

	FAttachmentTransformRules AttachRule=FAttachmentTransformRules(EAttachmentRule::KeepRelative,true);

	FName  SocketName ="None";

	
	Playerspawn->AttachToComponent(RootComponent,AttachRule,SocketName);
	
}

// Called every frame
void ACustomARPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetWorldTimerManager().SetTimer();
	Fire();
}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind various player inputs to functions
	// There are a few types - BindTouch, BindAxis, and BindEvent.  
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);
}

FVector ACustomARPawn::LineTraceFunction(FVector Loc, FRotator Rot)
{

	FHitResult Hit;


	


	FVector Start = Loc+FVector(-100.0,0.0,0.0);
	FVector End=Start+(Rot.Vector()*TraceDistance);

	FCollisionQueryParams TraceParams;

	bool isHit=GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_Visibility,TraceParams);
	DrawDebugLine(GetWorld(),Start,End,FColor::Orange,false,200.0);


	if(isHit)
	{
		DrawDebugBox(GetWorld(),Hit.ImpactPoint,FVector(5,5,5),FColor::Emerald,false,2.0f);
	}

	return Hit.ImpactPoint;
}




void ACustomARPawn::OnScreenTouch(const ETouchIndex::Type FingerIndex, const FVector ScreenPos)
{
	auto Temp = GetWorld()->GetAuthGameMode();
	auto GM = Cast<ACustomGameMode>(Temp);

	

	FHitResult hitTestResult;

	
	

	if (GM)
	{

		if (!gameState)
		{
			if (!WorldHitTest(FVector2d(ScreenPos), hitTestResult))
			{
				

				GM->LineTraceSpawnActor(ScreenPos);
				gameState = true;
			}


			else if (WorldHitTest(FVector2d(ScreenPos), hitTestResult))
			{
				auto* hitActorClass = UGameplayStatics::GetObjectClass(hitTestResult.GetActor());

				if (UKismetMathLibrary::ClassIsChildOf(hitActorClass, ACustomActor::StaticClass()))
				{
					//UKismetSystemLibrary::PrintString(this, "Cube Clicked", true, true, FLinearColor(0, 0.66, 1, 1), 2);
				}
			}
		}



		else if (gameState)
		{

			
			
			canShoot=true;

			
			

		}
	}
}

bool ACustomARPawn::WorldHitTest(FVector2d(screenPos),FHitResult(HitTestResult))
{
	APlayerController* PlayerController=UGameplayStatics::GetPlayerController(this,0);
	
	FVector worldPosition;
	FVector worldDirection;
	bool deprojectionSuccess=UGameplayStatics::DeprojectScreenToWorld(PlayerController,screenPos,worldPosition,worldDirection);

	FVector traceEndVector=worldDirection* 1000.0;
	traceEndVector =worldPosition+traceEndVector;


	bool traceSuccess = GetWorld()->LineTraceSingleByChannel(HitTestResult,worldPosition,traceEndVector,ECollisionChannel::ECC_WorldDynamic);
	
	return traceSuccess;

	
	
}

void ACustomARPawn::Fire()
{

	auto Temp = GetWorld()->GetAuthGameMode();
	auto GM = Cast<ACustomGameMode>(Temp);
	
	if(canShoot)
	{
		if (ProjectileClass)
		{
			

			const FVector2d ScreenSize = FVector2d(GEngine->GameViewport->Viewport->GetSizeXY());

			FVector CameraDir;

			
			
			bool deprojectionSuccess = UGameplayStatics::DeprojectScreenToWorld(GetWorld()->GetFirstPlayerController(),  FVector2d(ScreenSize.X/2,ScreenSize.Y/2-(10.0f)), /*out*/CameraPos, /*out*/ CameraDir);


			TargetLoc = CameraPos + (CameraDir*45.f); //FTransform(RotSpawn).TransformVector(MuzzleOffset);

			
			UWorld* World = GetWorld();
			if (World)
			
			{
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("World is valid"));

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				AMyActor_Projectile* Projectile = World->SpawnActor<AMyActor_Projectile>(ProjectileClass, TargetLoc, FRotator(), SpawnParams);

				if (Projectile)
				{

				

					FVector LaunchDirection = CameraDir;
					Projectile->FireinDirection(LaunchDirection);
					
				}

			}
		}
		canShoot=false;
	}
}
