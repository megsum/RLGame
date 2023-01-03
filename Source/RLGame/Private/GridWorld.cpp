// Fill out your copyright notice in the Description page of Project Settings.


#include "GridWorld.h"

GridWorld::GridWorld(int xbounds, int ybounds, int xstart, int ystart, std::vector<std::vector<int>> grid, int rps, int tpr, int tnr)
{
	this->xbounds = xbounds;
	this->ybounds = ybounds;
	this->xstart = xstart;
	this->ystart = ystart;
	this->grid = grid;

	// State rewards
	this->rps;
	this->tpr;
	this->tnr;

	mapBounds = { xbounds, ybounds };
	startLocation = { xstart, ystart };
	currentState = startLocation;

	grid[currentState[0]][currentState[1]] = 1000;
	terminal = false;
}

GridWorld::~GridWorld()
{
}

int GridWorld::Step(actions action)
{
	std::vector<int> newState = { 0,0 };

	// Move the agent to the next state based off the action taken (Update the x and y coordinates)
	// If we are at the max or min bounds, don't move.
	if (currentState[0] + getActionCoordinates(action)[0] < 0 || currentState[0] + getActionCoordinates(action)[0] > xbounds)
	{
		newState[0] = currentState[0];
	}
	else
	{
		newState[0] = currentState[0] + getActionCoordinates(action)[0];
	}
	if (currentState[1] + getActionCoordinates(action)[1] < 0 || currentState[1] + getActionCoordinates(action)[1] > ybounds)
	{
		newState[1] = currentState[1];
	}
	else
	{
		newState[1] = currentState[1] + getActionCoordinates(action)[1];
	}
	auto reward = rps;

	// Add the grid reward for the new state to the total reward if we have hit a terminal state
	if (grid[newState[0]][newState[1]] == -1)
	{
		reward += tnr;
		terminal = true;
	}
	else if(grid[newState[0]][newState[1]] == 1)
	{
		reward += tpr;
		terminal = true;
	}

	currentState = newState;
	return 0;
}

std::vector<int> GridWorld::getActionCoordinates(actions action)
{
	std::vector<int> actionCoordinate;
	switch (action) {
	case left:
		actionCoordinate = { -1, 0 };
		break;
	case up:
		actionCoordinate = { 0, 1 };
		break;
	case right:
		actionCoordinate = { 1, 0 };
		break;
	case down:
		actionCoordinate = { 0, -1 };
		break;
	default:
		actionCoordinate = { 0, 0 };
	}

	return actionCoordinate;
}