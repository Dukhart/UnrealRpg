// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"

#include "URpg_PowerUpEffect_Struct.h"
#include "URpg_Character.h"

#include "URpg_StatusEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UNREALRPG_API UURpg_StatusEffect : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
protected:

	UURpg_StatusEffect(const class FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Info")
		FName Name;
	// Character the status is ticking on
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic Info")
		AURpg_Character* Target;
	// Actor that caused the status effect
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic Info")
		AActor* Source;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Params")
		FURpg_PowerUpEffect_Struct Params;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EffectControl")
		bool bIsActive = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EffectControl")
		float Ticks = 0;
	FTimerHandle EffectTimer;
	FTimerDelegate EffectDelegate;

public:

	UFUNCTION(BlueprintCallable, Category = "EffectControl")
	void RunEffect(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "EffectControl")
	void Activate(AURpg_Character* TargetActor);
	UFUNCTION(BlueprintCallable, Category = "EffectControl")
	void Pause();
	UFUNCTION(BlueprintCallable, Category = "EffectControl")
	void Reset();
	UFUNCTION(BlueprintCallable, Category = "EffectControl")
	void Remove();

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	FURpg_PowerUpEffect_Struct GetParams() const { return Params; }
};
