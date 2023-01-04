// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RLGAME_API QLearningAgent
{
public:
    /* Constructor */
    QLearningAgent(std::vector<std::vector<std::vector<int>>> approxActionValue, int numActions, float gamma, float lr);

    /* Destructor */
    ~QLearningAgent();

    std::vector<std::vector<std::vector<int>>> approxActionValue;
    int numActions;
    float gamma;
    float lr;

    int greedy_policy(std::vector<int> action_values);

    std::vector<int> getActionValues(std::vector<int> state);

    void update(std::vector<int>, int a, std::vector<int> ns, int r);


};