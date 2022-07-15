// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Player Mesh");
	MeshComponent->SetupAttachment(RootComponent);
	
	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision Capsule");
	Collision->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");	
	Movement->Acceleration = 10000.0f;
		
	MeshComponent->SetStaticMesh(Mesh);	

	Collision->SetCapsuleSize(60, 60);
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->OnComponentHit.AddDynamic(this, &APlayerPawn::OnCompHit);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	Movement->MaxSpeed = MoveSpeed;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Direction = ENull;
	
	MovePlayer(ScaleDir, Direction);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("FW", IE_Pressed, this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAction("BW", IE_Pressed, this, &APlayerPawn::MoveBackward);
	PlayerInputComponent->BindAction("SL", IE_Pressed, this, &APlayerPawn::MoveLeft);
	PlayerInputComponent->BindAction("SR", IE_Pressed, this, &APlayerPawn::MoveRight);
}

void APlayerPawn::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Direction = ENull;
}

void APlayerPawn::MovePlayer(float Scale, EDirection Dir)
{
	switch (Dir)
	{
	case ENull:
		UE_LOG(LogTemp, Warning, TEXT("Player is Idle"));
		break;
	case EForward:
		AddMovementInput(FVector(1,0,0), Scale);
		SetActorRotation(UKismetMathLibrary::MakeRotFromX(GetActorForwardVector() * Scale));

		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, TEXT("FW"));
		break;
	case ESideways:
		AddMovementInput(FVector(0,1,0), Scale);
		SetActorRotation(UKismetMathLibrary::MakeRotFromX(GetActorRightVector() * Scale));

		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, TEXT("SD"));
		break;
	default: UE_LOG(LogTemp, Warning, TEXT("Player is Idle"));
	}
	
}

void APlayerPawn::MoveForward()
{
	Direction = EForward;
	ScaleDir = 1.0f;
}

void APlayerPawn::MoveBackward()
{
	Direction = EForward;
	ScaleDir = -1.0f;
}

void APlayerPawn::MoveRight()
{
	Direction = ESideways;
	ScaleDir = 1.0f;
}

void APlayerPawn::MoveLeft()
{
	Direction = ESideways;
	ScaleDir = -1.0f;
}

