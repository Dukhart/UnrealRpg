// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "Engine/GameInstance.h"
#include "URpg_GameInstance.generated.h"


UCLASS()
class UNREALRPG_API UURpg_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	// * INTITIALIZATION * //
	// Constructor
	UURpg_GameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	// * LOADING OPERATIONS * //
private:
	// Used to load assets at runtime
	FStreamableManager* AssetLoader;
	//UObject* LoadAsset(FString aPath, bool bUseSynchronous = false);
public:
	// * GETTERS and SETTERS * //
	UFUNCTION(BlueprintCallable, Category = Loading)
		FStreamableManager&	GetAssetLoader() { return *AssetLoader; }
};

