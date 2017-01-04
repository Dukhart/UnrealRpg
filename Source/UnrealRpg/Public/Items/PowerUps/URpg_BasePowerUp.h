// Copyright Jordan Duncan 2015

#pragma once

#include "GameFramework/Actor.h"

#include "URpg_IsPowerUp.h"
#include "URpg_StatusEffect.h"

#include "URpg_Character.h"

#include "URpg_BasePowerUp.generated.h"

UENUM(BlueprintType)
enum class EPowerUpStyle : uint8 {
	// PowerUp Permentantly in place
	Perment,
	// Powerup will respawn after a time
	Respawn,
	// PowerUp will be destroyed after all its charges are used
	Charges,
	// PowerUp will be destroyed after all its charges are used
	// Then respawn after a time
	Hybrid
};
/*
USTRUCT(BlueprintType)
struct UNREALRPG_API FRecentActorData {
protected:
	GENERATED_USTRUCT_BODY()
public:
	float duration;
	AActor* actor;

	FRecentActorData(AActor* InActor){
		duration = 0.0f;
		actor = InActor;
	}
};
*/
UCLASS()
class UNREALRPG_API AURpg_BasePowerUp : public AActor, public IURpg_IsPowerUp
{
	GENERATED_BODY()
	
public:	
	// * INIT * //
	// Sets default values for this actor's properties
	AURpg_BasePowerUp(const class FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// * TICK * //
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// * INTERFACES * //
	// IsPowerUp
	// Handles power up activation
	UFUNCTION()
	virtual void ActivatePowerUp_Implementation(AURpg_Character* TargetActor);

	// * COMPONENTS * //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	// * EVENTS * //
	// * Binds Hit Events to power up activation
	void BindHitEvents();
	// fired when an actor overlapse the collision component
	// checks is an interacting actor is valid to use the power up before activating the power up
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	// Affects the behavior of the power up after it is used
	// mostly determins wether or not to destroy the power up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prefrences")
		EPowerUpStyle PowerUpStyle;
	// Array of Stattus Effect types the power up uses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TArray<TSubclassOf<UURpg_StatusEffect>> PowerUpEffects;
	// Array to store the types of characters that can use the powerup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")
	TArray<ECharacterType> AffectedCharacterTypes;
	
	// * ACTIVATION DELAY * //
	// Contains a list of actors that recently used the powerup 
	// used to prevent rapid activation of power up nodes
	TArray<AURpg_Character*> RecentActors;
	

};
