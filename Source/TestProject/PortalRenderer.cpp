// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalRenderer.h"
#include "Portal.h"

void UPortalRenderer::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)
{
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);

	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("Here"));
	for (auto Portal : PortalsToRender)
	{
		//Portal->Render(this);
	}
}
