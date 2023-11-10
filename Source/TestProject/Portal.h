// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UCameraComponent;
UCLASS()
class TESTPROJECT_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable)
	virtual void RenderView(UCameraComponent* ViewCamera, const FVector RefPosition, const FQuat RefRotation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector TransformPositionBetweenPortals(const APortal* Sender, const APortal* Target, const FVector& Position);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FQuat TransformRotationBetweenPortals(const APortal* Sender, const APortal* Target, const FQuat& Rotation);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector TransformScaleBetweenPortals(const APortal* Sender, const APortal* Target, const FVector& Scale);

private:

	FTransform NormalVisible;
	FTransform NormalInvisible;

	void UpdateTransforms();

	UPROPERTY()
	class ATPGameModeBase* GameMode;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* RenderPlane;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	class UMaterial* PortalMatReference;

	UPROPERTY()
	class UMaterialInstanceDynamic* PortalMat;

	UPROPERTY()
	class UTextureRenderTarget2D* PortalTex;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	class USceneCaptureComponent2D* PortalCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	APortal* TargetPortal;
};
