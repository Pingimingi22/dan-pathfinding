#include "Dijkstra.h"
#include <algorithm>
Node* Dijkstra::GetShortestPath(Node* start, Node* destination)
{
	std::vector<Node*> open;
	std::vector<Node*> closed;

	open.push_back(start); // Adding first node to the open list, which is the node we are starting on.

	Node* currentNode = open[0]; // Current node is the first node in the open list.
	currentNode->ResetGScore();


	while (open.size() > 0) // While the open list is not empty, we have some Dijkstra search to do!
	{

		closed.push_back(open[0]); // Add the first element from the open list to the closed list.
		open.erase(open.begin()); // Remove it from the open list.

		for (int i = 0; i < currentNode->m_ConnectedNodes.size(); i++)
		{
			Node* connectedNode = currentNode->m_ConnectedNodes[i];

			if (CheckIfInList(connectedNode, closed))
			{
				continue; // Do nothing because this node has already been closed.
			}

			// If the node is already in the open list, we will only update it's gScore and previous if the gScore is better than the previous gScore.
			if (CheckIfInList(connectedNode, open))
			{
				if (connectedNode->m_GScore < currentNode->m_GScore + connectedNode->m_Cost)
				{
					// This way is cheaper, so lets set the gScore and previous according to this cheaper route.
					connectedNode->ResetPrevious();
					connectedNode->ResetGScore(); // Reset old g score.
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

			open.push_back(connectedNode); // Adding connected to the open list for processing.
		}

		// Sort open list so that node with lowest G score is first.
		std::sort(open.begin(), open.end(), [](Node* first, Node* second) {return first->m_GScore > second->m_GScore; });

		if (open.size() > 0) // If we still have anything in the open list, set current node to it.
			currentNode = open[0];

	}



	// If this returns a nullptr, it means we couldn't find a path to the destination node.
	return nullptr;
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