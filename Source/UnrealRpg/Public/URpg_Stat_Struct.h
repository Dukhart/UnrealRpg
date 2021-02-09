// Copyright Jordan Duncan 2015

#pragma once

#include "UObject/Object.h"
#include "URpg_Stat_Struct.generated.h"

UENUM(BlueprintType)
enum class EStatName : uint8 {
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Mana UMETA(DisplayName = "Mana"),

	Hunger UMETA(DisplayName = "Hunger"),
	Thirst UMETA(DisplayName = "Thirst"),
	Warmth UMETA(DisplayName = "Warmth"),
	Rest UMETA(DisplayName = "Rest"),

	Happiness UMETA(DisplayName = "Happiness"),


	None UMETA(DisplayName = "None")
};

/* Struct hold Stat values
 * StatIndex Set automaticly by StatName
 *
*/

USTRUCT(BlueprintType)
struct UNREALRPG_API FURpg_Stat_Struct
{
	GENERATED_USTRUCT_BODY()

protected:
	// Current Value for the Stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float Value;
	// Current Buff Debuff for the Stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float BuffValue;

	// min allowed value for the stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float MinValue;
	// max allowed value for the stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float MaxValue;
public:
	// index of the stat
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	//	uint8 StatIndex;
	// enum name of the stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		EStatName StatName;

	FURpg_Stat_Struct(EStatName InName = EStatName::None, float InStartValue = 100, int32 InMin = 0, int32 InMax = 100) {
		StatName = InName;

		MinValue = InMin;
		MaxValue = InMax;

		if (InStartValue > InMax) {
			Value = InMax;
		}
		else if (InStartValue < InMin) {
			Value = InMin;
		}
		else {
			Value = InStartValue;
		}

		BuffValue = 0;
	}
	
	// * GET / SET / ADD * //
	// Sets the stat value clamping between min and max
	void SetValue(float inValue) {
		if (inValue > MaxValue) {
			Value = MaxValue;
		}
		else if (inValue < MinValue) {
			Value = MinValue;
		}
		else {
			Value = inValue;
		}
	} 
	float GetValue() const { return Value; }
	void AddValue(float inValue) { SetValue(Value + inValue); }
	// sets the min value
	// Override max will force max value up with min if a higher number is set
	// otherwise min will only go up as far as min
	void SetMin(float inValue, bool bOverrideMax = false) {
		if (inValue > MaxValue) {
			if (bOverrideMax) {
				MaxValue = inValue;
				MinValue = inValue;
			}
			else {
				MinValue = MaxValue;
			}
		}
		else {
			MinValue = inValue;
		}
		SetValue(Value);
	}
	float GetMin() const { return MinValue; }
	void AddMin(float inValue) { SetMin(inValue + MinValue); }
	// sets the max value
	// Override min will force min value down with max if a lower number is set
	// otherwise max will only go down as far as min
	void SetMax(float inValue, bool bOverrideMin = false) {
		if (inValue < MinValue) {
			if (bOverrideMin) {
				MaxValue = inValue;
				MinValue = inValue;
			}
			else {
				MaxValue = MinValue;
			}
		}
		else {
			MaxValue = inValue;
		}
		// reset base value
		SetValue(Value);
	}
	float GetMax() const { return MaxValue; }
	void AddMax(float inValue) { SetMax(inValue + MaxValue); }

	void SetBuff(float inValue) { BuffValue = inValue; }
	float GetBuff() const { return BuffValue; }
	void AddBuff(float inValue) { SetBuff(inValue + BuffValue); }
};
