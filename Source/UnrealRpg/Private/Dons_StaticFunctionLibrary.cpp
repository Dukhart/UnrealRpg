// Copyright Jordan Duncan 2015
#include "Dons_StaticFunctionLibrary.h"

const FAttachmentTransformRules UDons_StaticFunctionLibrary::StandardComponentAttachRules = FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);

// * INITIALIZATION * //
// Constructor
UDons_StaticFunctionLibrary::UDons_StaticFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

}
// * ARRAY SORTING * ///
// Sorts an array of Strings alphabetically
TArray<FString> UDons_StaticFunctionLibrary::SortStringsAlphabetically(TArray<FString> InArray, bool bInverse) {
	if (bInverse) {
		InArray.Sort(&UDons_StaticFunctionLibrary::PredicateStringGreaterThan);
	}
	else {
		InArray.Sort(&UDons_StaticFunctionLibrary::PredicateStringLessThan);
	}
	return InArray;
}
// sorts an array of actors alphabetically by display name
TArray<AActor*> UDons_StaticFunctionLibrary::SortActorsAlphabetically(TArray<AActor*> InArray, bool bInverse) {
	if (bInverse) {
		InArray.Sort(&UDons_StaticFunctionLibrary::PredicateActorNameGreaterThan);
	}
	else {
		InArray.Sort(&UDons_StaticFunctionLibrary::PredicateActorNameLessThan);
	}
	return InArray;
}


// * RAYTRACING * //
// fires a raytrace with an optional debugline
bool UDons_StaticFunctionLibrary::RayTraceSingle(UWorld* World, AActor* IgnoreOriginActor,
	const FVector& Start, const FVector& End, FHitResult& OutHitResult,
	ECollisionChannel ECC, bool bReturnPhysMat,
	bool bDrawDebug, float debugDrawDuration) {

	// if we don't have a valid world ptr just return false
	if (World == nullptr) {
		return false;
	}
	// stores a bool for whether we hit something
	bool bHit = false;
	// the collision params
	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = FName("Ray Trace");
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = bReturnPhysMat;
	// add ignore actor
	if (IgnoreOriginActor != nullptr) {
		QueryParams.AddIgnoredActor(IgnoreOriginActor);
	}

	// fire the trace
	bHit = World->LineTraceSingleByChannel(OutHitResult, Start, End, ECC, QueryParams);

	// if bDrawDebug is set draw the debug line
	if (bDrawDebug) {
		DrawRayTraceDebugLine(World, bHit, Start, End, OutHitResult, debugDrawDuration);
	}
	// return our bool for whether we hit something
	return bHit;

}
// fires a raytrace with actors to ignore with an optional debugline
bool UDons_StaticFunctionLibrary::RayTraceSingle(UWorld* World, TArray<AActor*> IgnoreActors,
	const FVector& Start, const FVector& End, FHitResult& OutHitResult,
	ECollisionChannel ECC, bool bReturnPhysMat,
	bool bDrawDebug, float debugDrawDuration) {

	// if we don't have a valid world ptr just return false
	if (World == nullptr) {
		return false;
	}
	// stores a bool for whether we hit something
	bool bHit = false;
	// the collision params
	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = FName("Ray Trace");
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = bReturnPhysMat;
	// add ignore actors
	QueryParams.AddIgnoredActors(IgnoreActors);

	// fire the trace
	bHit = World->LineTraceSingleByChannel(OutHitResult, Start, End, ECC, QueryParams);
	// if bDrawDebug is set draw the debug line

	if (bDrawDebug) {
		DrawRayTraceDebugLine(World, bHit, Start, End, OutHitResult, debugDrawDuration);
	}

	return false;
}

/*
// fires a raytrace with multiple hits and optional debugline
bool UDons_StaticFunctionLibrary::RayTraceMulti(UWorld* World, AActor* IgnoreOriginActor,
	const FVector& Start, const FVector& End, TArray<FHitResult>& OutHitResults,
	ECollisionChannel ECC, bool bReturnPhysMat,
	bool bDrawDebug, float debugDrawDuration) {

	// if we don't have a valid world ptr just return false
	if (World == nullptr) {
		return false;
	}
	// stores a bool for whether we hit something
	bool bHit = false;
	// the collision params
	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = FName("Ray Trace");
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = bReturnPhysMat;
	// add ignore actor
	if (IgnoreOriginActor != nullptr) {
		QueryParams.AddIgnoredActor(IgnoreOriginActor);
	}

	// fire the trace
	bHit = World->LineTraceMultiByChannel(OutHitResults, Start, End, ECC, QueryParams);

	// if bDrawDebug is set draw the debug line
	if (bDrawDebug) {
		for (int32 i = 0; i < OutHitResults.Num(); ++i)
		{
			DrawRayTraceDebugLine(World, bHit, Start, End, OutHitResults[i], debugDrawDuration);
		}
	}
	// return our bool for whether we hit something
	return bHit;

}
// fires a raytrace with actors to ignore and multiple hits with an optional debugline
bool UDons_StaticFunctionLibrary::RayTraceMulti(UWorld* World, TArray<AActor*> IgnoreActors,
	const FVector& Start, const FVector& End, TArray<FHitResult>& OutHitResults,
	ECollisionChannel ECC, bool bReturnPhysMat,
	bool bDrawDebug, float debugDrawDuration) {

	// if we don't have a valid world ptr just return false
	if (World == nullptr) {
		return false;
	}
	// stores a bool for whether we hit something
	bool bHit = false;
	// the collision params
	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = FName("Ray Trace");
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = bReturnPhysMat;
	// add ignore actors
	QueryParams.AddIgnoredActors(IgnoreActors);

	// fire the trace
	bHit = World->LineTraceSingleByChannel(OutHitResult, Start, End, ECC, QueryParams);
	// if bDrawDebug is set draw the debug line

	if (bDrawDebug) {
		DrawRayTraceDebugLine(World, bHit, Start, End, OutHitResult, debugDrawDuration);
	}

	return false;
}

*/

// fires a raytrace againts one component with an optional debugline
bool UDons_StaticFunctionLibrary::RayTraceComp(UPrimitiveComponent* compRef,
	const FVector& Start, const FVector& End, FHitResult& OutHitResult,
	bool bDrawDebug, float debugDrawDuration) {

	// if we don't have a valid component ptr OR the comp is not valid return false
	if (compRef == nullptr || !compRef->IsValidLowLevel()) {
		return false;
	}
	// stores a bool for whether we hit something
	bool bHit = false;
	// the collision params
	FCollisionQueryParams QueryParams;
	QueryParams.TraceTag = FName("Comp Trace");
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = false;
	// do the trace
	bHit = compRef->LineTraceComponent(OutHitResult, Start, End, QueryParams);
	// if bDrawDebug is set draw the debug line
	if (bDrawDebug && compRef->GetWorld() != nullptr) {
		DrawRayTraceDebugLine(compRef->GetWorld(), bHit, Start, End, OutHitResult, debugDrawDuration);
	}
	// return our bool for whether we hit something
	return bHit;
}

void UDons_StaticFunctionLibrary::DrawRayTraceDebugLine(UWorld* World, bool bSuccessfullHit,
	const FVector& Start, const FVector& End,
	FHitResult& Hit, float drawDuration) {
	
	// if world is not valid return
	if (World == nullptr) {
		return;
	}

	if (bSuccessfullHit) {
		// draw origin to hit
		DrawDebugLine(World,Start, Hit.ImpactPoint, FColor::Cyan, false, drawDuration);
		// draw hit to end
		DrawDebugLine(World, Hit.ImpactPoint, End, FColor::Yellow, false, drawDuration);
		// draw the impact point
		DrawDebugPoint(World, Hit.ImpactPoint, 2.0f, FColor::Red, false, drawDuration);
	}
	else {
		DrawDebugLine(World, Start, End, FColor::Yellow, false, drawDuration);
	}

}
/*
void UDons_StaticFunctionLibrary::DrawRayTraceDebugLine(UWorld* World, bool bBlockingHit,
	const FVector& Start, const FVector& End,
	TArray<FHitResult&> Hits, float drawDuration) {

	// if world is not valid return
	if (World == nullptr) {
		return;
	}
}
*/