// Copyright Jordan Duncan 2015

#pragma once

#include "GameFramework/Actor.h"

#include "URpg_IsPowerUp.h"
#include "URpg_StatusEffect.h"

#include "URpg_Character.h"

#include "URpg_BasePowerUp.generated.h"

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
	//virtual void Tick( float DeltaSeconds ) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		//TArray<UURpg_StatusEffect*> PowerUpEffects;
	TArray<TSubclassOf<UURpg_StatusEffect>> PowerUpEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filters")
	TArray<ECharacterType> AffectedCharacterTypes;
	
	//UPROPERTY(EditeAnywhere, BlueprintReadWrite, Category = "Filters")
	//	E
};
