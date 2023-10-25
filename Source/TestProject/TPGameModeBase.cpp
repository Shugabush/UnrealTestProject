// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"
#include "TPPlayer.h"

ATPGameModeBase::ATPGameModeBase()
{
	DefaultPawnClass = ATPPlayer::StaticClass();
}
