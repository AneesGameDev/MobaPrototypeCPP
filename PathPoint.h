// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PathPoint.generated.h"

USTRUCT(BlueprintType)
struct FPathPoint {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
		TArray<FVector> VectorArray;
}; 
