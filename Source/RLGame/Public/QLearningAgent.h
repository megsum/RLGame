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
    QLearningAgent(int numActions, float gamma, float lr, int xbounds, int ybounds);

    /* Destructor */
    ~QLearningAgent();

    std::vector<std::vector<std::vector<int>>> approxActionValues;
    int numActions;
    float gamma;
    float lr;
    int xbounds;
    int ybounds;

    int greedy_policy(std::vector<int> action_values);

    std::vector<int> getActionValues(std::vector<int> state);

    int update(std::vector<int> s, int a, std::vector<int> ns, int r);


};