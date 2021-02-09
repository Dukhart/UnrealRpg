// Copyright Jordan Duncan 2015

#pragma once
#include "UObject/Object.h"
// for debugging
#include "DrawDebugHelpers.h"

#include "Dons_StaticFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UDons_StaticFunctionLibrary : public UObject
{
	GENERATED_BODY()

public:
	// * INITIALIZATION * //
	// Constructor
	UDons_StaticFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// * Static class * //
	static const FAttachmentTransformRules StandardComponentAttachRules;

	// * ARRAY SORTING * //
	// Sorts an array of Strings alphabetically
	UFUNCTION(BlueprintCallable, Category = DonStatics)
	static TArray<FString> SortStringsAlphabetically (TArray<FString> InArray, bool bInverse = false);
	// sorts an array of actors alphabetically by display name
	UFUNCTION(BlueprintCallable, Category = DonStatics)
	static TArray<AActor*> SortActorsAlphabetically (TArray<AActor*> InArray, bool bInverse = false);
	
	// * RAYTRACING * //
	// fires a raytrace with an optional debugline
	static bool RayTraceSingle(UWorld* World, AActor* IgnoreOriginActor,
		const FVector& Start, const FVector& End, FHitResult& OutHitResult,
		ECollisionChannel ECC = ECC_Visibility, bool bReturnPhysMat = false,
		bool bDrawDebug = false, float debugDrawDuration = 10.0f);
	// fires a raytrace with actors to ignore with an optional debugline
	static bool RayTraceSingle(UWorld* World, TArray<AActor*> IgnoreActors,
		const FVector& Start, const FVector& End, FHitResult& OutHitResult,
			ECollisionChannel ECC = ECC_Visibility, bool bReturnPhysMat = false,
			bool bDrawDebug = false, float debugDrawDuration = 10.0f);

	// TODO MultiLine trace
	// fires a raytrace with multiple hits and optional debugline
	/*
	static bool RayTraceMulti(UWorld* World, AActor* IgnoreOriginActor,
		const FVector& Start, const FVector& End, TArray<FHitResult>& OutHitResults,
		ECollisionChannel ECC = ECC_Visibility, bool bReturnPhysMat = false,
		bool bDrawDebug = false, float debugDrawDuration = 10.0f);
	// fires a raytrace with actors to ignore and multiple hits with an optional debugline
	static bool RayTraceMulti(UWorld* World, TArray<AActor*> IgnoreActors,
		const FVector& Start, const FVector& End, TArray<FHitResult>& OutHitResults,
		ECollisionChannel ECC = ECC_Visibility, bool bReturnPhysMat = false,
		bool bDrawDebug = false, float debugDrawDuration = 10.0f);
		*/
	
	// fires a raytrace againts one component with an optional debugline
	static bool RayTraceComp(UPrimitiveComponent* TheComp,
		const FVector& Start, const FVector& End, FHitResult& OutHitResult,
		bool bDrawDebug = false, float debugDrawDuration = 10.0f);
	/* draws a debug line for a ray trace with a red line for start to hit
	 * yellow line for hit to end trace point or start to end if their was no hit
	 * and a red dot at the hit point
	*/
	static void DrawRayTraceDebugLine(UWorld* World, bool bSuccessfullHit,
		const FVector& Start, const FVector& End,
		FHitResult& Hit, float DrawDuration = 10.0f);
	/*
	void UDons_StaticFunctionLibrary::DrawRayTraceDebugLine(UWorld* World, bool bBlockingHit,
	const FVector& Start, const FVector& End,
	TArray<FHitResult&> Hits, float drawDuration);
	*/


	// * PREDICATES * //
	// predicate used to sort an array of strings alphabetically 
	FORCEINLINE static bool PredicateStringLessThan(const FString& x, const FString& y) {
		return (x < y);
	};
	// predicate used to sort an array of strings inverse alphabetically 
	FORCEINLINE static bool PredicateStringGreaterThan(const FString& x, const FString& y) {
		return (x > y);
	};
	// predicate used to sort an array of actors alphabetically by name
	FORCEINLINE static bool PredicateActorNameLessThan(const AActor& x, const AActor& y) {
		return (x.GetName() < y.GetName());
	};
	// predicate used to sort an array of actors inverse alphabetically by name
	FORCEINLINE static bool PredicateActorNameGreaterThan(const AActor& x, const AActor& y) {
		return (x.GetName() > y.GetName());
	};
};