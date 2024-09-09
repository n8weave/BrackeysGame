#pragma once

#include "CoreMinimal.h"
#include "LevelNames.h"
#include "FLowController.generated.h"
/**
 * 
 */
UCLASS()
class BRACKEYGAME_API UFLowController : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	static void LoadLevel(ELevelNames LevelName);
};
