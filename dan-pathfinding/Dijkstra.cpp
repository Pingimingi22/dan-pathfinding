#include "Dijkstra.h"
#include <algorithm>
std::vector<Node*> Dijkstra::GetShortestPath(Node* start, Node* destination)
{
	std::vector<Node*> open;
	std::vector<Node*> closed;

	open.push_back(start); // Adding first node to the open list, which is the node we are starting on.

	Node* currentNode = open[0]; // Current node is the first node in the open list.
	currentNode->ResetGScore();
	currentNode->ResetPrevious();

	bool searchComplete = false;


	while (/*open.size() > 0 || */!searchComplete) // While the open list is not empty, we have some Dijkstra search to do!
	{

		closed.push_back(open[0]); // Add the first element from the open list to the closed list.
		open.erase(open.begin()); // Remove it from the open list.

		if (closed[closed.size() - 1] == destination)
			searchComplete = true;

		for (int i = 0; i < currentNode->m_ConnectedNodes.size(); i++)
		{
			Node* connectedNode = currentNode->m_ConnectedNodes[i];
			// Making diagonals more expensive.
			if (connectedNode->m_XIndex != currentNode->m_XIndex && connectedNode->m_YIndex != currentNode->m_YIndex) // diagonals more expensive.
				connectedNode->m_Cost = 1.141f;
			else
				connectedNode->m_Cost = 1;

			if (CheckIfInList(connectedNode, closed) || !connectedNode->m_Passable)
			{
				continue; // Do nothing because this node has already been closed or the node is inpassable.
			}

			// If the node is already in the open list, we will only update it's gScore and previous if the gScore is better than the previous gScore.
			if (CheckIfInList(connectedNode, open))
			{
			
				if (connectedNode->m_GScore > currentNode->m_GScore + connectedNode->m_Cost)
				{
					// This way is cheaper, so lets set the gScore and previous according to this cheaper route.
					connectedNode->ResetPrevious();
					//connectedNode->ResetGScore(); // Reset old g score.
					connectedNode->m_GScore = connectedNode->m_Cost + currentNode->m_GScore; // Adding GScore to connected node based on cost.
					connectedNode->m_Previous = currentNode;
				}
				else
				{
					// This way is more expensive, so we wont update the gScore or previous.
					// Do nothing.
					continue;
				}
			}
			else
			{
				// Otherwise, the node is not in the open list so just set the gScore and previous.
				// This way is cheaper, so lets set the gScore and previous according to this cheaper route.
				connectedNode->ResetPrevious();
				//connectedNode->ResetGScore(); // Reset old g score.
				connectedNode->m_GScore = connectedNode->m_Cost + currentNode->m_GScore; // Adding GScore to connected node based on cost.
				connectedNode->m_Previous = currentNode;
			}

			open.push_back(connectedNode); // Adding connected to the open list for processing.
		}

		// Sort open list so that node with lowest G score is first.
		std::sort(open.begin(), open.end(), [](Node* first, Node* second) {return first->m_GScore < second->m_GScore; });

		if (open.size() > 0) // If we still have anything in the open list, set current node to it.
			currentNode = open[0];

	}


	// Get the path and return it.
	std::vector<Node*> path;
	Node* currentPathNode = destination;
	path.push_back(currentPathNode);
	while (currentPathNode->m_Previous)
	{
		currentPathNode = currentPathNode->m_Previous;
		path.insert(path.begin(), currentPathNode); // Adding it to the front of the container since we're are going through the path backwards by using m_Previous.
	}

	return path;

	// It will return a path of 1 if it failed. A path of 1 because it will always add the destination node to the path.
}

bool Dijkstra::CheckIfInList(Node* node, std::vector<Node*> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (node->m_XIndex == list[i]->m_XIndex && node->m_YIndex == list[i]->m_YIndex)
			return true;
	}

	return false;
}

std::vector<Node*> Dijkstra::GetNodesUnderGScore(float maxGScore, Node* start)
{
	std::vector<Node*> open;
	std::vector<Node*> closed;

	open.push_back(start); // Adding first node to the open list, which is the node we are starting on.

	Node* currentNode = open[0]; // Current node is the first node in the open list.
	currentNode->ResetGScore();
	currentNode->ResetPrevious();

	while (open.size() > 0) // While the open list is not empty, we have some Dijkstra search to do!
	{

		closed.push_back(open[0]); // Add the first element from the open list to the closed list.
		open.erase(open.begin()); // Remove it from the open list.

		for (int i = 0; i < currentNode->m_ConnectedNodes.size(); i++)
		{
			Node* connectedNode = currentNode->m_ConnectedNodes[i];
			// Making diagonals more expensive.
			if (connectedNode->m_XIndex != currentNode->m_XIndex && connectedNode->m_YIndex != currentNode->m_YIndex) // diagonals more expensive.
				connectedNode->m_Cost = 1.141f;
			else
				connectedNode->m_Cost = 1;

			if (CheckIfInList(connectedNode, closed) || !connectedNode->m_Passable)
			{
				continue; // Do nothing because this node has already been closed or the node is inpassable.
			}

			// If the node is already in the open list, we will only update it's gScore and previous if the gScore is better than the previous gScore.
			if (CheckIfInList(connectedNode, open))
			{

				if (connectedNode->m_GScore > currentNode->m_GScore + connectedNode->m_Cost)
				{
					// This way is cheaper, so lets set the gScore and previous according to this cheaper route.
					connectedNode->ResetPrevious();

					connectedNode->m_GScore = connectedNode->m_Cost + currentNode->m_GScore; // Adding GScore to connected node based on cost.
					connectedNode->m_Previous = currentNode;
				}
				else
				{
					// This way is more expensive, so we wont update the gScore or previous.
					// Do nothing.
					continue;
				}
			}
			else
			{
				// Otherwise, the node is not in the open list so just set the gScore and previous.
				// This way is cheaper, so lets set the gScore and previous according to this cheaper route.
				connectedNode->ResetPrevious();

				connectedNode->m_GScore = connectedNode->m_Cost + currentNode->m_GScore; // Adding GScore to connected node based on cost.
				connectedNode->m_Previous = currentNode;
			}

			open.push_back(connectedNode); // Adding connected to the open list for processing.
		}

		// Sort open list so that node with lowest G score is first.
		std::sort(open.begin(), open.end(), [](Node* first, Node* second) {return first->m_GScore < second->m_GScore; });

		if (open.size() > 0) // If we still have anything in the open list, set current node to it.
			currentNode = open[0];

	}


	// Store all nodes with GScore under the passed in parameter into a std::vector.
	std::vector<Node*> nodesUnderGScore;
	for (int i = 0; i < closed.size(); i++)
	{
		if (closed[i]->m_GScore < maxGScore)
			nodesUnderGScore.push_back(closed[i]);
	}

	return nodesUnderGScore;	



	// --------------------------- unused code --------------------------- //

	//// Get the path and return it.
	//std::vector<Node*> path;
	//Node* currentPathNode = destination;
	//path.push_back(currentPathNode);
	//while (currentPathNode->m_Previous)
	//{
	//	currentPathNode = currentPathNode->m_Previous;
	//	path.insert(path.begin(), currentPathNode); // Adding it to the front of the container since we're are going through the path backwards by using m_Previous.
	//}

	//return path;

	// It will return a path of 1 if it failed. A path of 1 because it will always add the destination node to the path.
}
