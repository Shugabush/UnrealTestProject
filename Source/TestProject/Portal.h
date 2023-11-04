// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class TESTPROJECT_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true))
	APortal* TargetPortal;

	FTransform NormalVisible;

	FTransform NormalInvisible;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Render(class UPortalRenderer* ViewCamera, float DeltaTime);

	virtual void Destroyed() override;

	static FVector TransformPositionBetweenPortals(APortal* Sender, APortal* Target, FVector Position);
	static FQuat TransformRotationBetweenPortals(APortal* Sender, APortal* Target, FQuat Rotation);
	static FRotator TransformRotationBetweenPortals(APortal* Sender, APortal* Target, FRotator Rotation);

private:
	void UpdateTransforms();

	class ATPGameModeBase* GameMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	// Should this portal always update its translations?
	// Leave this false if the portal will never move
	bool alwaysUpdateTransforms = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	class USceneCaptureComponent2D* PortalCapture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	class UCameraComponent* MainCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* RenderPlane;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	class UTextureRenderTarget2D* ViewthroughRenderTexture;

};
