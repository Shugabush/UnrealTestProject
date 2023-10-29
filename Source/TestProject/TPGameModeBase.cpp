// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"
#include "TPPlayer.h"
#include "Camera/CameraComponent.h"

ATPGameModeBase::ATPGameModeBase()
{
	DefaultPawnClass = ATPPlayer::StaticClass();

	MainCamera = DefaultPawnClass.GetDefaultObject()->GetComponentByClass<UCameraComponent>();
}

UCameraComponent* ATPGameModeBase::GetMainCamera() const
{
	return MainCamera;
}
