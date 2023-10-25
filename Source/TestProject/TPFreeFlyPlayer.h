// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPPlayer.h"
#include "TPFreeFlyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATPFreeFlyPlayer : public ATPPlayer
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaTime) override;
};
