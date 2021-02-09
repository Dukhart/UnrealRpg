// Copyright Jordan Duncan 2015

#pragma once

#include "URpg_Base_UserWidget.h"

// include for stat data
#include "URpg_Stat_Struct.h"

#include "URpg_StatDisplay_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_StatDisplay_UserWidget : public UURpg_Base_UserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
		EStatName StatName;
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Update")
		void UpdateStatData(FURpg_Stat_Struct statData);
	
};
