// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "TPPlayer.h"
#include "TPGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"

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

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(nullptr);
	Mesh->SetupAttachment(RootComponent);

	PortalCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PortalCamera"));
	PortalCamera->SetupAttachment(RootComponent);
	PortalCamera->bUseCustomProjectionMatrix = true;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ATPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	SetTickGroup(ETickingGroup::TG_PostUpdateWork);
	PortalMat = UMaterialInstanceDynamic::Create(PortalMatReference, this);

	RenderPlane->SetMaterial(0, PortalMat);

	PortalTex = UKismetRenderingLibrary::CreateRenderTarget2D(this);

	PortalMat->SetTextureParameterValue("BaseTexture", PortalTex);

	TargetPortal->PortalCamera->TextureTarget = PortalTex;

	UpdateTransforms();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortal::Destroyed()
{

}

void APortal::RenderView(UCameraComponent* ViewCamera, const FVector RefPosition, const FQuat RefRotation)
{
	FVector TargetPosition = TransformPositionBetweenPortals(this, TargetPortal, RefPosition);
	FQuat TargetRotation = TransformRotationBetweenPortals(this, TargetPortal, RefRotation);

	FMinimalViewInfo ViewInfo;
	FMatrix ViewMatrix;
	FMatrix ProjectionMatrix;
	FMatrix ViewProjectionMatrix;
	TargetPortal->PortalCamera->SetWorldLocationAndRotation(TargetPosition, TargetRotation);
	ViewCamera->GetCameraView(0.1f, ViewInfo);
	UGameplayStatics::GetViewProjectionMatrix(ViewInfo, ViewMatrix, ProjectionMatrix, ViewProjectionMatrix);
	TargetPortal->PortalCamera->CustomProjectionMatrix = ProjectionMatrix;
}

FVector APortal::TransformPositionBetweenPortals(const APortal* const Sender, const APortal* const Target, const FVector& Position)
{
	FVector LocalPosition = Sender->NormalVisible.InverseTransformPosition(Position);
	return Target->NormalInvisible.TransformPosition(LocalPosition);
}

FQuat APortal::TransformRotationBetweenPortals(const APortal* const Sender, const APortal* const Target, const FQuat& Rotation)
{
	FQuat LocalRotation = Sender->NormalVisible.InverseTransformRotation(Rotation);
	return Target->NormalInvisible.TransformRotation(LocalRotation);
}

FVector APortal::TransformScaleBetweenPortals(const APortal* const Sender, const APortal* const Target, const FVector& Scale)
{
	FVector LocalScale = Scale / Sender->NormalVisible.GetScale3D();
	return Target->NormalInvisible.GetScale3D() * LocalScale;
}

void APortal::UpdateTransforms()
{
	NormalVisible.SetLocation(GetActorLocation());
	NormalVisible.SetRotation(GetActorQuat() * FQuat::MakeFromEuler({ 0, 0, 180 }));
	NormalVisible.SetScale3D(GetActorRelativeScale3D());

	NormalInvisible.SetLocation(GetActorLocation());
	NormalInvisible.SetRotation(GetActorQuat());
	NormalInvisible.SetScale3D(GetActorRelativeScale3D());
}