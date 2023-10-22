// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomUtils.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UCustomUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	static bool WithinRange(float value, float minInclusive, float maxExclusive);
};
