#include "FLowController.h"

#include "AITestsCommon.h"
#include "Kismet/GameplayStatics.h"

UFLowController::UFLowController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Constructor implementation
}

void UFLowController::LoadLevel(ELevelNames const LevelName)
{
	FString const LevelToLoad = GetLevelName(LevelName);
	UE_LOG(LogTemp, Warning, TEXT("Loading level: %s"), *LevelToLoad);
	UGameplayStatics::OpenLevel(FAITestHelpers::GetWorld(), FName(*LevelToLoad));
}




