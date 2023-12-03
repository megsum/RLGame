// Copyright Megan Sumner. All rights reserved.


#include "GridWorldVisualizer.h"


// Map size is 2900/100 by 3400/100
// 
// Sets default values for this component's properties
UGridWorldVisualizer::UGridWorldVisualizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickInterval = 0.5;

    numEpisodes = 5;
    learningRate = 0.1;
    currentRewardSum = 0;
    episodeNum = 1;
}

void UGridWorldVisualizer::MovePlayerToLocation(std::vector<int> state)
{
    CurrentLocation = FVector{ state[0] * 100.0, state[1] * 100.0, 0.0 };
}

// Called when the game starts
void UGridWorldVisualizer::BeginPlay()
{
	Super::BeginPlay();

    CurrentLocation = FVector{ gridWorld.xstart * 100.0, gridWorld.ystart * 100.0, 0.0 };
	
}

void UGridWorldVisualizer::GenerateGrid(TArray<int> UnrealGrid)
{

    std::vector<int> gridRow;
    for (int i = 0; i < UnrealGrid.Num(); i++)
    {
        gridRow.push_back(UnrealGrid[i]);
        if (i % RowWidth == 0)
        {
            grid.push_back(gridRow);
            gridRow = {};
        }
    }
    gridWorld.grid = grid;
    gridGenerated = true;
}

// Called every frame
void UGridWorldVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    // For debug, convert the array into a string and print it to the screen each tick
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (episodeNum < numEpisodes && gridGenerated)
    {
        // Get current state, action values and action
        std::vector<int> currentState = gridWorld.currentState;
        std::vector<int> currentActionValues = qLearningAgent.getActionValues(currentState);
        auto currentAction = qLearningAgent.greedy_policy(currentActionValues);

        // Step the grid world
        auto newState = gridWorld.Step(GridWorld::actions(currentAction));

        currentRewardSum += gridWorld.totalReward;

        auto action = qLearningAgent.update(currentState, currentAction, newState, gridWorld.totalReward);

        // Need to set this up to move the player with the grid world in game
        MovePlayerToLocation(newState);

        // TODO: Reset the level for next episode
        if (gridWorld.terminal)
        {
            // End run
            // Reset level
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Episode ended!");
            rewardPerEpisode.push_back(currentRewardSum);
            currentRewardSum = 0;
            episodeNum += 1;
        }

        // Allows us to pick a random action
        // GridWorld::actions action = GridWorld::actions(rand() % 3);

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

        // Debug action taken
        FString actionString = "";
        switch (GridWorld::actions(action))
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

        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ("Moving: %s ", actionString));
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, s);
    }
}

