// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomUtils.h"

bool UCustomUtils::WithinRange(float value, float minInclusive, float maxExclusive)
{
    return value >= minInclusive && value < maxExclusive;
}
