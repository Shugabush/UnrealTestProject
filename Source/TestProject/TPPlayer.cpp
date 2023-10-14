// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayer.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATPPlayer::ATPPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	
	Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);

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

}

// Called to bind functionality to input
void ATPPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

