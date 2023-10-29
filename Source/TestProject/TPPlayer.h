// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "TPPlayer.generated.h"

UCLASS()
class TESTPROJECT_API ATPPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FVector Movement;

	float LookRotationZ;
	float LookRotationY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MovementSpeed = 500;

	UFUNCTION()
	virtual void HandleMoveRight(float axisValue);

	UFUNCTION()
	virtual void HandleMoveForward(float axisValue);

	UFUNCTION()
	virtual void HandleMoveUp(float axisValue);

	UFUNCTION()
	virtual void HandleLookUp(float axisValue);

	UFUNCTION()
	virtual void HandleLookRight(float axisValue);

	// Left / Right rotation
	virtual FQuat GetLookRotationY() const;
	// Up / Down rotation
	virtual FQuat GetLookRotationZ() const;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	virtual FQuat GetLookRotation() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FVector GetMovement() const;
	
	virtual FVector GetVelocity() const override;
};
