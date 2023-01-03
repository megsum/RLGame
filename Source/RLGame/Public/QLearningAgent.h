// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RLGAME_API QLearningAgent
{
private:
    /* The previous state the agent was in*/
    int prevState;
    /* The previous action the agent took */
    int prevAction;
    /* The previous reward the agent received */
    double prevReward;
    /* The previous Q value the agent had for the previous stateand action */
    double prevQ;
public:
    /* The number of actions the agent can take */
    int numActions;
    /* The number of states the agent can be in */
    int numStates;
    /* The learning rate */
    double learningRate;
    /* The discount factor */
    double discountFactor;
    /* The probability of taking a random action */
    double epsilon;

    /* Returns the action the agent should take in the given state */
    int getAction(int state);
    /* Updates the agents Q function based on the previous state, action, and reward */
    void update(int state, double reward);
    /* Returns the Q value for the given state and action */
    double getQ(int state, int action);

    /* Constructor */
	QLearningAgent(int numActions, int numStates, double learningRate, double discountFactor, double epsilon);
    /* Destructor */
	~QLearningAgent();
};