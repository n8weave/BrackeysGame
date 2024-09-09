#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELevelNames : uint8
{
	MainMenuLevel UMETA(DisplayName = "MainMenuLevel"),
	MainLevel UMETA(DisplayName = "MainLevel"),
	EndGameLevel UMETA(DisplayName = "EndGameLevel")
};

inline FString GetLevelName(ELevelNames const LevelName)
{
	switch (LevelName)
	{
	case ELevelNames::MainMenuLevel:
		return TEXT("MainMenuLevel");
	case ELevelNames::MainLevel:
		return TEXT("MainLevel");
	case ELevelNames::EndGameLevel:
		return TEXT("EndGameLevel");
	default:
		return TEXT("Invalid");
	}
}