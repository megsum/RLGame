// Fill out your copyright notice in the Description page of Project Settings.


#include "GridWorldVisualizer.h"

// Sets default values for this component's properties
UGridWorldVisualizer::UGridWorldVisualizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickInterval = 5;

    numEpisodes = 1;
    learningRate = 0.1;
    currentRewardSum = 0;
    episodeNum = 1;

}


// Called when the game starts
void UGridWorldVisualizer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGridWorldVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    // For debug, convert the array into a string and print it to the screen each tick
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    FString s = "";
    for (int i = 0; i < gridWorld.grid.size(); i++) {
        for (int j = 0; j < gridWorld.grid[i].size(); j++) {
            s += (FString::FromInt(gridWorld.grid[i][j]));
            if (j < grid[i].size() - 1) {
                s += ", ";
            }
        }
        s += "\n";
        if (i < grid.size() - 1) {
            s += "  ";
        }
    }

    if (episodeNum < numEpisodes)
    {
        // Get current state, action values and action
        auto currentState = gridWorld.currentState;
        auto currentActionValues = qLearningAgent.getActionValues(currentState);
        auto currentAction = qLearningAgent.greedy_policy(currentActionValues);

        // Step the grid world
        auto newState = gridWorld.Step(GridWorld::actions(currentAction));

        currentRewardSum += gridWorld.totalReward;

        qLearningAgent.update(currentState, currentAction, newState, gridWorld.totalReward);

        // TODO: Reset the level for next episode
        if (gridWorld.terminal)
        {
            // End run
            // Reset level
            episodeNum += 1;
        }
    }

    GridWorld::actions action = GridWorld::actions(rand() % 3);

    FString actionString = "";
    switch (action)
    {
    case GridWorld::left:
        actionString = "left";
        break;
    case GridWorld::right:
        actionString = "right";
        break;
    case GridWorld::up:
        actionString = "up";
        break;
    default:
        actionString = "down";
        break;
    }

    gridWorld.Step(action);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ("Moving: %s ", actionString));
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, s);

}

