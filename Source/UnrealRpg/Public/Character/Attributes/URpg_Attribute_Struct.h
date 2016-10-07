// Copyright Jordan Duncan 2015

#pragma once

#include "Object.h"
#include "URpg_Attribute_Struct.generated.h"

UENUM(BlueprintType)
enum class EAttributeName : uint8 {
	Strength UMETA(DisplayName = "Strength"),
	Constitution UMETA(DisplayName = "Constitution"),
	Dexterity UMETA(DisplayName = "Dexterity"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Wisdom UMETA(DisplayName = "Wisdom"),
	Charisma UMETA(DisplayName = "Charisma"),
	Luck UMETA(DisplayName = "Luck"),


	None UMETA(DisplayName = "None")
};

/* Struct hold Attribute values
* AtriIndex Set automaticly by AtriName
*
*/
USTRUCT(BlueprintType)
struct UNREALRPG_API FURpg_Attribute_Struct
{
	GENERATED_USTRUCT_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
		int32 AtriIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
		EAttributeName AtriName;

	// Current Value for the Attribute
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
		float Value;
	// Current Buff Debuff for the Attribute
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float BuffValue;

	// min allowed value for the Attribute
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
		int32 MinValue;
	// max allowed value for the Attribute
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
		int32 MaxValue;

	FURpg_Attribute_Struct(EAttributeName InName = EAttributeName::None, float InStartValue = 8, int32 InMin = 0, int32 InMax = 30) {
		AtriName = InName;
		AtriIndex = uint8(InName);

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

	
};
