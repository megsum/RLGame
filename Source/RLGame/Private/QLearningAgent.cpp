// Fill out your copyright notice in the Description page of Project Settings.


#include "QLearningAgent.h"
#include "GridWorld.h"


/* Constructor */
QLearningAgent::QLearningAgent(int numActions, float gamma, float lr, int xbounds, int ybounds)
{
    this->numActions = numActions;
    this->gamma = gamma;
    this->lr = lr;
    this->xbounds = xbounds;
    this->ybounds = ybounds;

    // Initialize all states with the number of actions for each state
    for (int i = 0; i < xbounds; i++)
    {
        std::vector<std::vector<int>> u;
        for (int j = 0; j < ybounds; j++)
        {
            std::vector<int> v;
            for (int a = 0; a < numActions; a++)
            {
                v.push_back(0);
            }

            u.push_back(v);
        }
        approxActionValues.push_back(u);
    }
}

/* Destructor */
QLearningAgent::~QLearningAgent() {
}

/* Returns the action the agent should take in the given state */
std::vector<int> QLearningAgent::getActionValues(std::vector<int> state)
{
    return approxActionValues[state[0]][state[1]];
}

int QLearningAgent::greedy_policy(std::vector<int> action_values)
{
    std::vector<int> max_indices;
    int max_value = -1;
    for (int i = 0; i < numActions; i++)
    { 
        if (action_values[i] > max_value)
        {
            max_value = action_values[i];
            max_indices.clear();
            max_indices.push_back(i);
        }
        else if (action_values[i] == max_value)
        {
            max_indices.push_back(i);
        }
    }

    return max_indices[rand() % max_indices.size()];
}

int QLearningAgent::update(std::vector<int> s, int a, std::vector<int> ns, int r)
{
    // Get action value for current state
    int action = getActionValues(s)[a];

    auto next_actions = getActionValues(ns);

    // Get max over the action values at the next state
    int next_action = *max_element(next_actions.begin(), next_actions.end());

    // Compute TD-error
    float td = (r + gamma * next_action) - action;

    // Update Approx_Av for (s,a)
    approxActionValues[s[0]][s[1]][a] = action + lr * td;
    return action;
}