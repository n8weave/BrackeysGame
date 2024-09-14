#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SpawnManager.generated.h"

/**
 * Maps an enemy class to a count
 */
USTRUCT()
struct FUEnemyConfig : public FTableRowBase
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	int32 Count;

	GENERATED_BODY()

	FUEnemyConfig()
	{
		EnemyClass = nullptr;
		Count = 0;
	}
};


/**
 * Contains a stage of enemies
 */
USTRUCT()
struct FUSpawnStageConfig : public FTableRowBase
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	TArray<FUEnemyConfig> Enemies;

	GENERATED_BODY()

	FUSpawnStageConfig()
	{
		Enemies.Empty();
	}
};

/**
 * Contains a wave of enemies with difficulty modifiers
 */
USTRUCT()
struct FUSpawnWaveConfig : public FTableRowBase
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	TArray<FUSpawnStageConfig> Stages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	float NextStageDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	float DamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	float HealthMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	float SpeedMultiplier;

	GENERATED_BODY()

	FUSpawnWaveConfig()
	{
		Stages.Empty();
		NextStageDelay = 0.0f;
		DamageMultiplier = 1.0f;
		HealthMultiplier = 1.0f;
		SpeedMultiplier = 1.0f;
	}
};


/**
 * Contains a list of waves
 */
USTRUCT()
struct FUWavesConfig : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	TArray<FUSpawnWaveConfig> Waves;

	FUWavesConfig()
	{
		Waves.Empty();
	}
};


UCLASS(Blueprintable, BlueprintType)
class USpawnBatch : public UObject
{
	GENERATED_BODY()

public:
	// Default constructor
	USpawnBatch();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Manager")
	FUSpawnStageConfig StageConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn manager")
	float NextStageDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn manager")
	float DamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn manager")
	float HealthMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn manager")
	float SpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn manager")
	bool bIsLastStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn manager")
	bool bIsLastWave;
};


/**
 * Contains waves of enemies for a level
 */
UCLASS()
class BRACKEYGAME_API ASpawnManager : public AActor
{
	GENERATED_BODY()

public:
	ASpawnManager();

private:
	FUWavesConfig WavesConfig;
	int CurrentWaveIndex;
	int CurrentStageIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawn manager")
	void InitManager(const FUWavesConfig& InWavesConfig, int32 StartWaveIndex = 0, int32 StartStageIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "Spawn manager")
	void GetNextBatch(USpawnBatch* &Batch);
};
