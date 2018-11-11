#include "Actions.hpp"
#include "CommonMini.hpp"

void Actions::addAction(Action action)
{
	actions.push_back(action);
}

void Actions::setStartAction(std::vector<int> storyId, double simulationTime)
{
	for (size_t i = 0; i < actions.size(); i++)
	{
		if (actions[i].getStoryId() == storyId)
		{
			actions[i].setStartAction();
			actions[i].setStartTime(simulationTime);
		}
	}
}

void Actions::executeActions(double simulationTime)
{
	double timeStep = simulationTime - oldSimulationTime;

	int numberOfActions = (int)actions.size();
	int i = 0;

	while (i<numberOfActions)
	{
		if (actions[i].getStartAction())
		{
			actions[i].ExecuteAction(simulationTime, timeStep);
		}

		if (actions[i].getActionCompleted())
		{
			LOG("Action %s is removed from actions", actions[i].getActionType().c_str());
			actions.erase(actions.begin() + i);

			numberOfActions = (int)actions.size();
			i = i - 1;
		}
		i = i + 1;
	}

	oldSimulationTime = simulationTime;
}