// Copyright Jordan Duncan 2015

#pragma once

#include "Object.h"
#include "URpg_Stat_Struct.generated.h"

UENUM(BlueprintType)
enum class EStatName : uint8 {
	SName_Health UMETA(DisplayName = "Health"),
	SName_Stamina UMETA(DisplayName = "Stamina"),
	SName_Mana UMETA(DisplayName = "Mana"),

	SName_Hunger UMETA(DisplayName = "Hunger"),
	SName_Thirst UMETA(DisplayName = "Thirst"),
	SName_Warmth UMETA(DisplayName = "Warmth"),

	SName_Happiness UMETA(DisplayName = "Happiness"),


	SName_None UMETA(DisplayName = "None")
};

/* Struct hold Stat values
 * StatIndex Set automaticly by StatName
 *
*/

USTRUCT(BlueprintType)
struct UNREALRPG_API FURpg_Stat_Struct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 StatIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		EStatName StatName;

	// Current Value for the Stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float Value;

		// min allowed value for the stat
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 MinValue;
	// max allowed value for the stat
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 MaxValue;

	FURpg_Stat_Struct(EStatName InName = EStatName::SName_None, float InStartValue = 100, int32 InMin = 0, int32 InMax = 100) {
		StatName = InName;
		StatIndex = uint8(InName);

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
	}

};
