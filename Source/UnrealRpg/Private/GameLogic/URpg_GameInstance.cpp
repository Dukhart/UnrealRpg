// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "URpg_GameInstance.h"



// * INTITIALIZATION * //
// Constructor
UURpg_GameInstance::UURpg_GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	AssetLoader = new FStreamableManager;
}


// * LOADING OPERATIONS * //
/*
 UObject* UURpg_GameInstance::LoadAsset(FString aPath, bool bUseSynchronous = false) {
	FStringAssetReference ref(aPath);
	UObject* asset;
	asset = stream->SynchronousLoad(ref);

	return (asset);
}
*/