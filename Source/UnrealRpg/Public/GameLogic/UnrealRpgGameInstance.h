// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "Engine/GameInstance.h"
#include "UnrealRpgGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class UNREALRPG_API UURpg_GameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	
public:
	UURpg_GameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	FStreamableManager* AssetLoader;
	//UObject* LoadAsset(FString aPath, bool bUseSynchronous = false);
	
};
