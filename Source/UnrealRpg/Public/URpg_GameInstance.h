// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "URpg_GameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayCharSelectSequence);

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
	//UFUNCTION(BlueprintCallable, Category = Loading)
		FStreamableManager&	GetAssetLoader() { return *AssetLoader; }
	// 
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Play Sequence")
	FPlayCharSelectSequence PlayCharSelectSequence;
};

