// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "Engine/GameInstance.h"
#include "UnrealRpgGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class UNREALRPG_API UUnrealRpgGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	
public:
	UUnrealRpgGameInstance(const FObjectInitializer& ObjectInitializer);
	FStreamableManager* AssetLoader;
	//UObject* LoadAsset(FString aPath, bool bUseSynchronous = false);
	
};
