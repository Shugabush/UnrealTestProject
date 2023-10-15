// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"

ATPGameModeBase::ATPGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_TPPlayer"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
