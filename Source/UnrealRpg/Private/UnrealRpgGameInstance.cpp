// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "UnrealRpgGameInstance.h"




UUnrealRpgGameInstance::UUnrealRpgGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	AssetLoader = new FStreamableManager;
}
/*
UObject* UUnrealRpgGameInstance::LoadAsset(FString aPath, bool bUseSynchronous = false) {
	FStringAssetReference ref(aPath);
	UObject* asset;
	asset = stream->SynchronousLoad(ref);

	return (asset);
}
*/