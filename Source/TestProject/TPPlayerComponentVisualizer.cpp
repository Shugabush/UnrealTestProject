// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPlayerComponentVisualizer.h"
#include "TPPlayer.h"
#include "TPPlayerComponent.h"

void FPlayerComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UTPPlayerComponent* PlayerComponent = Cast<UTPPlayerComponent>(Component);
	if (!PlayerComponent) return;

	const ATPPlayer* Player = PlayerComponent->GetPlayer();
	const FVector OwnerLocation = Player->GetActorLocation();

	const FVector PlayerGroundCheckPosition = Player->GetGroundCheckPosition();
	const float PlayerGroundCheckRadius = Player->GetGroundCheckRadius();

	PDI->DrawLine(PlayerGroundCheckPosition, PlayerGroundCheckPosition + FVector::DownVector * PlayerGroundCheckRadius, FLinearColor::Red, 0);
}
