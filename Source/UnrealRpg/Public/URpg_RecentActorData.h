// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include "URpg_RecentActorData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UNREALRPG_API FURpg_RecentActorData
{
	GENERATED_USTRUCT_BODY()
public:
	float duration;
	AActor* actor;

	FURpg_RecentActorData(AActor* InActor = nullptr) {
		duration = 0.0f;
		actor = InActor;
	}
	
	
};
