// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "pacmanCloneGameModeBase.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	MeshComponent = CreateDefaultSubobject<UMeshComponent>("Mesh Component");

	CapsuleComponent->SetCapsuleSize(32,32);
	CapsuleComponent->SetGenerateOverlapEvents(true);

	
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ACoin::OnOverlapEnd);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0,0, RotationSpeed));
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,-1, FColor::Blue, TEXT("Coin"));

	if (Cast<APlayerPawn, AActor>(OtherActor))
	{

		AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
		ApacmanCloneGameModeBase* PacGM = Cast<ApacmanCloneGameModeBase, AGameModeBase>(GM);
		PacGM->AddScore(Value);
		GEngine->AddOnScreenDebugMessage(-1,-1, FColor::Blue, TEXT("Coin"));
		K2_DestroyActor();
	}
}

void ACoin::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

