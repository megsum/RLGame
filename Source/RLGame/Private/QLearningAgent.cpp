// Fill out your copyright notice in the Description page of Project Settings.


#include "QLearningAgent.h"
#include "GridWorld.h"

// Map size is 2900/100 by 3400/100


/* Constructor */
QLearningAgent::QLearningAgent(std::vector<std::vector<std::vector<int>>> approxActionValue, int numActions, float gamma, float lr) 
{
    this->approxActionValue = approxActionValue;
    this->numActions = numActions;
    this->gamma = gamma;
    this->lr = lr;
}

/* Destructor */
QLearningAgent::~QLearningAgent() {
}

/* Returns the action the agent should take in the given state */
std::vector<int> QLearningAgent::getActionValues(std::vector<int> state)
{
    return approxActionValue[state[0]][state[1]];
}

int QLearningAgent::greedy_policy(std::vector<int> action_values)
{
    return std::distance(action_values.begin(), std::max_element(action_values.begin(), action_values.end()));
}

void QLearningAgent::update(std::vector<int> s, int a, std::vector<int> ns, int r)
{
    // Get action value for (s, a)std::vector<int>
    int action = getActionValues(s)[a];

    // Get max over the action values at the next state
    int next_action = std::distance(getActionValues(ns).begin(), std::max_element(getActionValues(ns).begin(), getActionValues(ns).end()));

    // Compute TD-error
    float td = (r + gamma * next_action) - action;

    // Update Approx_Av for (s,a)
    approxActionValue[s[0]][s[1]][a] = action + lr * td;
}