// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"
#include "TPPlayer.h"
#include "Camera/CameraComponent.h"

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
	Player = Cast<ATPPlayer>(DefaultPawnClass->GetDefaultObject());

	MainCamera = Player->GetComponentByClass<UCameraComponent>();
}
