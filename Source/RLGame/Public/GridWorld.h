// Copyright Megan Sumner. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include <vector>

/**
 * Define a grid world with obstacles and a goal.
 * The agent can move in four directions: up, down, left, right.
 * The agent receives a reward of 1 for reaching an objective and -1 for hitting an obstacle.
 * The agent receives a reward of 0 for all other actions.
 * The agent recieves a reward of 10 for reaching the goal.
 */
class RLGAME_API GridWorld
{
public:
	GridWorld(int xbounds, int ybounds, int xstart, int ystart, std::vector<std::vector<int>> grid, int rps, int tpr, int tnr);
	~GridWorld();

	// The max bounds of the grid (mapped from 0 to bounds)
	int xbounds;
	int ybounds;
	std::vector<int> mapBounds;

	// Define where the agent starts in the world
	int xstart;
	int ystart;
	std::vector<int> startLocation;

	// Current location of the agent
	std::vector<int> currentState;

	// Input the grid with the rewards of each grid location as stated above
	std::vector<std::vector<int>> grid;

	// Have we hit an end condition
	bool terminal;

	// All the actions the agent can take in the world
	// 0 = move left, 1 = move up, 2 = move right, 3 = move down
	enum actions
	{
		left,
		up,
		right,
		down
	};

	// Rewards
	int rps; // Reward per step
	int tpr; // Positive terminal reward
	int tnr; // Negative terminal reward
	int totalReward;

	// Get the next state based off the action taken
	 std::vector<int> Step(actions action);

	std::vector<int> getActionCoordinates(actions action);

	// Create the grid world with the bounds of the world and represent it as the rewards for each spot
	// -1 is an obstacle, +1 is an objective and +10 is the final reward.
	// TODO: Future need when we input the grid from 
	int GenerateGrid(int xbounds, int ybounds);

	// Reset the grid world to the starting state.
	void reset();
};
