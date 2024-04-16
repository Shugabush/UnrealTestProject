// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerComponent.h"
#include "TPPlayer.h"

// Sets default values for this component's properties
UTPPlayerComponent::UTPPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Player = Cast<ATPPlayer>(GetAttachParentActor());
}


// Called when the game starts
void UTPPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTPPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

