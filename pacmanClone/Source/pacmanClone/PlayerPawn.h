// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UENUM()
enum EDirection
{
	ENull UMETA(DisplayName = "Null"),
	EForward UMETA(DisplayName = "Forward"),
	ESideways UMETA(DisplayName = "Sideway")
};

UCLASS()
class PACMANCLONE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDirection> Direction = EDirection::ENull;	

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void MovePlayer(float Scale, EDirection Dir);

	UFUNCTION()
	void MoveForward();

	UFUNCTION()
	void MoveBackward();

	UFUNCTION()
	void MoveRight();

	UFUNCTION()
	void MoveLeft();
private:
	
	UPROPERTY()
	float ScaleDir = 1.0f;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	UFloatingPawnMovement* Movement;
};
