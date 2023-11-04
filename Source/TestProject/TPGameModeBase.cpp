// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"
#include "TPPlayer.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATPGameModeBase::ATPGameModeBase()
{
	DefaultPawnClass = ATPPlayer::StaticClass();
}

UCameraComponent* ATPGameModeBase::GetMainCamera() const
{
	return MainCamera;
}

void ATPGameModeBase::BeginPlay()
{
	Player = Cast<ATPPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	MainCamera = Player->GetComponentByClass<UCameraComponent>();
}
