// Copyright Jordan Duncan 2015

#pragma once

#include "UObject/Object.h"

#include "URpg_Stat_Struct.h"
#include "URpg_Attribute_Struct.h"

#include "URpg_PowerUpEffect_Struct.generated.h"

UENUM(BlueprintType)
enum class EPowerUpEffectStyle : uint8
{
	// always will be active after getting
	Permanent,
	// last until the set time elapses
	TimedBuff,
	// lasts until the next time the character dies
	NextDeath,
	// last until the character attacks
	NextAttack,
	// last until the character lands an attack on an enemy
	NextSuccessfulAttack,
	// last until the character is hit
	NextHit,
	// lasts until the character takes health damage
	NextDamaged,

	None
};

UENUM(BlueprintType)
enum class EAffectedProperty : uint8
{
	// the base value of the stat/attribute
	Base,
	// The min value of the stat/attribute
	Min,
	// The max value of the stat/attribute
	Max,
	// the buff value of the stat
	Buff,

	None
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct UNREALRPG_API FURpg_PowerUpEffect_Struct
{
	GENERATED_USTRUCT_BODY()

protected:
	// rate at which the effct is applied for its duration
	// 0 will result in a continuous rate
	// 1 will trigger the effect once 5 five times evenly distrubuted for the duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (ClampMin = 0))
		float TickRate;
public:
	// list of stats to alter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (DisplayName = "Effected Stat Names"))
		TArray<EStatName> SNames;
	// list of attributes to alter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (DisplayName = "Effected Attribute Names"))
		TArray<EAttributeName> ANames;
	// value to alter stats/attributes by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Value;
	// the property of the stat/attributte to alter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EAffectedProperty AffectedProperty;
	// Effects how long the power up will last
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EPowerUpEffectStyle PowerUpEffectStyle;
	// Length of time for a timed buff
	// no effect for a permenant buff 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		float Duration;
	// number of stacks / duplicates currently active of the effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stacking")
		int32 Stacks;
	// whether power up effects can stack with other powerups
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stacking")
		bool bStacksOther;
	// whether power up effects can stack with same powerups
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stacking")
		bool bStacksSelf;

	// EStatName inSNames = EStatName::None
	FURpg_PowerUpEffect_Struct(float inValue = 0, float inDuration = 0, int32 inTickRate = 1,
		int32 inStacks = 0, bool inStacksOther = true, bool inStacksSelf = true,
		EAffectedProperty inAffectedProperty = EAffectedProperty::Base, EPowerUpEffectStyle inPowerUpEffectStyle = EPowerUpEffectStyle::Permanent) {
		
		Value = inValue;
		Duration = inDuration;
		TickRate = inTickRate;

		Stacks = inStacks;
		bStacksOther = inStacksOther;
		bStacksSelf = inStacksSelf;

		AffectedProperty = inAffectedProperty;
		PowerUpEffectStyle = inPowerUpEffectStyle;

		//SNames = inSNames;
		//ANames = inANames;
	}

	void SetTickRate(float newRate) {
		TickRate = newRate <= 0 ? 0 : newRate;
	}
	float GetTickRate() const { return TickRate; }
};
