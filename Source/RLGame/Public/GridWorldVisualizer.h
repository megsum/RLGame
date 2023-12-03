// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridWorld.h"
#include "QLearningAgent.h"
#include "GridWorldVisualizer.generated.h"

UCLASS(Blueprintable)
class RLGAME_API UGridWorldVisualizer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridWorldVisualizer();

	float learningRate;
	int numEpisodes;
	std::vector<int> rewardPerEpisode;
	int currentRewardSum;
	int episodeNum;
	int RowWidth = 29;
	bool gridGenerated = false;

	std::vector < std::vector<int>> grid = { {} };

	GridWorld gridWorld = GridWorld(RowWidth, 34, 11, 18, grid, -1, 100, -100);

	UPROPERTY(BlueprintReadOnly) 
	FVector CurrentLocation;

	UFUNCTION(BlueprintCallable)
	void GenerateGrid(TArray<int> UnrealGrid);

	QLearningAgent qLearningAgent = QLearningAgent(4, 1, learningRate, 29, 34);

	void MovePlayerToLocation(std::vector<int> state);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
