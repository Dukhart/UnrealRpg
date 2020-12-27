// Copyright Jordan Duncan 2015

#pragma once

#include "Player/UI/URpg_Base_UserWidget.h"

// include for stat data
#include "URpg_Stat_Struct.h"

#include "URpg_StatBox_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_StatBox_UserWidget : public UURpg_Base_UserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Update")
		void UpdateStatDisplay(EStatName inStat);
	
	
};
