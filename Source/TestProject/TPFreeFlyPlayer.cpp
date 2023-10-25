// Fill out your copyright notice in the Description page of Project Settings.


#include "TPFreeFlyPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

void ATPFreeFlyPlayer::Tick(float DeltaTime)
{
	Super::Super::Tick(DeltaTime);

	// Transform movement to be relative to camera's direction
	FVector camEulers = GetLookRotationZ().Euler();

	// I'm not sure why we have to add this offset, but it's the only way it will work properly
	camEulers.Z -= 90;

	FVector transformedMovement = FQuat::MakeFromEuler(camEulers).RotateVector(FVector(Movement.X, Movement.Y, 0));
	transformedMovement.Z += Movement.Z;

	Collision->SetAllPhysicsLinearVelocity((transformedMovement) * MovementSpeed);

	FQuat Rotation = GetLookRotation();

	SetActorRotation(Rotation);
}
