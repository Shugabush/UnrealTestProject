// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameModeBase.h"
#include "TPPlayer.h"
#include "Portal.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CoreDelegates.h"

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

	TArray<AActor*> PortalActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APortal::StaticClass(), PortalActors);

	for (auto Portal : PortalActors)
	{
		Portals.Add(Cast<APortal>(Portal));
	}

	FCoreDelegates::OnBeginFrameRT.AddUFunction(this, "OnPreRender");
}

void ATPGameModeBase::OnPreRender()
{
	/*for (auto Portal : Portals)
	{
		Portal->RenderView(MainCamera, MainCamera->GetComponentLocation(), MainCamera->GetComponentQuat());
	}*/
}
