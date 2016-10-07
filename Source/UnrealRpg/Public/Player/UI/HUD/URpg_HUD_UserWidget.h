// Copyright Jordan Duncan 2015

#pragma once

#include "Player/UI/URpg_Base_UserWidget.h"

// include for stat data
#include "URpg_Stat_Struct.h"
// include for attribute data
#include "URpg_Attribute_Struct.h"

#include "URpg_HUD_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_HUD_UserWidget : public UURpg_Base_UserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Stats)
		void UpdateStat(EStatName StatToChange);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Attributes)
		void UpdateAttribute(EAttributeName AttributeToChange);
	
};
