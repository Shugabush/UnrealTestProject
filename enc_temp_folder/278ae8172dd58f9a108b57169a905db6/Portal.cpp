// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "TPPlayer.h"
#include "TPGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Camera/CameraComponent.h"
#include "PortalRenderer.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RenderPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RenderPlane"));
	RenderPlane->SetupAttachment(RootComponent);

	PortalCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	PortalCapture->SetupAttachment(RootComponent);
	PortalCapture->bUseCustomProjectionMatrix = true;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	UpdateTransforms();

	GameMode = Cast<ATPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortal::Render(UPortalRenderer* ViewCamera, float DeltaTime)
{
	if (ViewCamera == nullptr) { return; }

	if (alwaysUpdateTransforms)
	{
		UpdateTransforms();
	}

	// Calculate portal capture position and rotation

	FVector VirtualPosition = TransformPositionBetweenPortals(this, TargetPortal, ViewCamera->GetComponentLocation());
	FQuat VirtualRotation = TransformRotationBetweenPortals(this, TargetPortal, ViewCamera->GetComponentQuat());

	// Position portal capture
	PortalCapture->SetWorldLocationAndRotation(VirtualPosition, VirtualRotation);

	FMinimalViewInfo ViewInfo;

	ViewCamera->GetCameraView(DeltaTime, ViewInfo);

	FMatrix ViewMatrix;
	FMatrix ProjectionMatrix;
	FMatrix ViewProjectionMatrix;

	UGameplayStatics::GetViewProjectionMatrix(ViewInfo, ViewMatrix, ProjectionMatrix, ViewProjectionMatrix);

	PortalCapture->CustomProjectionMatrix = ProjectionMatrix;
}

void APortal::Destroyed()
{

}

FVector APortal::TransformPositionBetweenPortals(APortal* Sender, APortal* Target, FVector Position)
{
	FVector LocalPosition = Sender->NormalVisible.InverseTransformPosition(Position);
	return Target->NormalInvisible.TransformPosition(LocalPosition);
}

FQuat APortal::TransformRotationBetweenPortals(APortal* Sender, APortal* Target, FQuat Rotation)
{
	FQuat LocalRotation = Sender->NormalVisible.InverseTransformRotation(Rotation);
	return Target->NormalInvisible.TransformRotation(LocalRotation);
}

FRotator APortal::TransformRotationBetweenPortals(APortal* Sender, APortal* Target, FRotator Rotation)
{
	FQuat LocalRotation = Sender->NormalVisible.InverseTransformRotation(Rotation.Quaternion());
	return Target->NormalInvisible.TransformRotation(LocalRotation).Rotator();
}

void APortal::UpdateTransforms()
{
	NormalInvisible.SetTranslation(GetActorLocation());
	NormalInvisible.SetRotation(GetActorRotation().Quaternion());
	NormalInvisible.SetScale3D(GetActorScale3D());

	NormalVisible.SetTranslation(GetActorLocation());
	NormalVisible.SetRotation(GetActorRotation().Quaternion() * FQuat::MakeFromEuler(FVector(0, 0, 180)));
	NormalVisible.SetScale3D(GetActorScale3D());
}
