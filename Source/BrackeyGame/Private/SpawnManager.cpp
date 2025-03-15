// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

USpawnBatch::USpawnBatch()
{
	// Default constructor implementation
}


ASpawnManager::ASpawnManager()
{
}

void ASpawnManager::InitManager(const FUWavesConfig& InWavesConfig, const int32 StartWaveIndex,
                                const int32 StartStageIndex)
{
	WavesConfig = InWavesConfig;
	CurrentWaveIndex = StartWaveIndex;
	CurrentStageIndex = StartStageIndex;

	// Check if wave and stage indices are valid
	// try extracting WavesConfig.Waves[CurrentWaveIndex].Stages[CurrentStageIndex]
	// if it fails, throw an error
	if (CurrentWaveIndex >= WavesConfig.Waves.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid wave index: %d"), CurrentWaveIndex);
		return;
	}
	if (CurrentStageIndex >= WavesConfig.Waves[CurrentWaveIndex].Stages.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid stage index: %d"), CurrentStageIndex);
		return;
	}
}


void ASpawnManager::GetNextBatch(USpawnBatch* & Batch)
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Wave/Stage: %d/%d"), CurrentWaveIndex, CurrentStageIndex);
	if (!Batch)
	{
		Batch = NewObject<USpawnBatch>();
	}


	if (CurrentWaveIndex < WavesConfig.Waves.Num())
	{
		bool bIsLastWave = CurrentWaveIndex >= WavesConfig.Waves.Num() - 1;
		if (CurrentStageIndex < WavesConfig.Waves[CurrentWaveIndex].Stages.Num())
		{
			bool bIsLastStage = CurrentStageIndex >= WavesConfig.Waves[CurrentWaveIndex].Stages.Num() - 1;

			Batch->StageConfig = WavesConfig.Waves[CurrentWaveIndex].Stages[CurrentStageIndex];
			Batch->NextStageDelay = WavesConfig.Waves[CurrentWaveIndex].NextStageDelay;
			Batch->DamageMultiplier = WavesConfig.Waves[CurrentWaveIndex].DamageMultiplier;
			Batch->HealthMultiplier = WavesConfig.Waves[CurrentWaveIndex].HealthMultiplier;
			Batch->SpeedMultiplier = WavesConfig.Waves[CurrentWaveIndex].SpeedMultiplier;
			Batch->bIsLastWave = bIsLastWave;
			Batch->bIsLastStage = bIsLastStage;

			if (bIsLastStage)
			{
				CurrentWaveIndex++;
				CurrentStageIndex = 0;
			}
			else
			{
				CurrentStageIndex++;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid stage index: %d"), CurrentStageIndex);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid wave index: %d"), CurrentWaveIndex);
	}
}
