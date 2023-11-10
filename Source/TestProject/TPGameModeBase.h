// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATPGameModeBase();

	class UCameraComponent* GetMainCamera() const;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UCameraComponent* MainCamera;
	UPROPERTY()
	class ATPPlayer* Player;

	UPROPERTY()
	TArray<class APortal*> Portals;

	UFUNCTION()
	virtual void OnPreRender();
};
