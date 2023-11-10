// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalRenderer.h"
#include "Portal.h"
#include "Kismet/GameplayStatics.h"

void UPortalRenderer::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)
{
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);

	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("Here"));
	for (auto Portal : PortalsToRender)
	{
		Portal->RenderView(this, GetComponentLocation(), GetComponentQuat());
	}
}

void UPortalRenderer::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> PortalActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APortal::StaticClass(), PortalActors);

	for (auto PortalActor : PortalActors)
	{
		PortalsToRender.Add(Cast<APortal>(PortalActor));
	}
}

void UPortalRenderer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (auto Portal : PortalsToRender)
	{
		Portal->RenderView(this, GetComponentLocation(), GetComponentQuat());
	}
}
