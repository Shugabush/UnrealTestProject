// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPPlayer::ATPPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collision->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	
	Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	RootComponent = Collision;
}

// Called when the game starts or when spawned
void ATPPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Transform movement to be relative to camera's direction
	FVector camEulers = Camera->GetComponentRotation().Euler();

	// I'm not sure why we have to add this offset, but it's the only way it will work properly
	camEulers.Z -= 90;

	FVector transformedMovement = FRotator::MakeFromEuler(camEulers).RotateVector(Movement);
	transformedMovement.Z = 0;

	Collision->SetAllPhysicsLinearVelocity((transformedMovement + Velocity) * MovementSpeed);
}

// Called to bind functionality to input
void ATPPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ATPPlayer::HandleMoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &ATPPlayer::HandleMoveRight);

}

void ATPPlayer::HandleMoveRight(float axisValue)
{
	Movement.X = -axisValue;
}

void ATPPlayer::HandleMoveForward(float axisValue)
{
	Movement.Y = axisValue;
}

FVector ATPPlayer::GetMovement() const
{
	return Movement;
}

FVector ATPPlayer::GetVelocity() const
{
	return Velocity;
}

