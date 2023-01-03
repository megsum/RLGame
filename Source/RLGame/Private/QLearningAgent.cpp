// Fill out your copyright notice in the Description page of Project Settings.


#include "QLearningAgent.h"
#include "GridWorld.h"

// Map size is 2900/100 by 3400/100

/* Constructor */
QLearningAgent::QLearningAgent(int numActions, int numStates, double learningRate, double discountFactor, double epsilon) {
    this->numActions = numActions;
    this->numStates = numStates;
    this->learningRate = learningRate;
    this->discountFactor = discountFactor;
    this->epsilon = epsilon;
    prevState = -1;
    prevAction = -1;
    prevReward = 0;
    prevQ = 0;
}

/* Destructor */
QLearningAgent::~QLearningAgent() {
}

/* Returns the action the agent should take in the given state */
int QLearningAgent::getAction(int state) {
    int action = 0;
    return action;
}
