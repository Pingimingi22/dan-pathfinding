#include "NavMap.h"


NavMap::NavMap(int width, int height)
{
	m_Width = width;
	m_Height = height;

	// Create grid.
	for (int i = 0; i < width; i++)
	{
		m_Grid.push_back(std::vector<Node*>());
		for (int j = 0; j < height; j++)
		{
			Node* newNode = new Node(i, j);
			m_Grid[i].push_back(newNode);
		}
	}

	// After filling out the 2D std::vector with nodes, it's time to connect them.
	ConnectNodes();
}

/// <summary>
/// This functions connects nodes in the graph. Connecting nodes is a two way thing, so if node A connects to node B, now node A has a reference to node B
/// and node B has a reference to node A.
/// The idea behind this connection algorith is to connect the nodes to the right, bottom, diagonal top right and diagonal bottom right. If done
/// to the entire grid, all nodes should be connected 8 ways.
/// </summary>
void NavMap::ConnectNodes()
{
	for (int i = 0; i < m_Width; i++)
	{
		for (int j = 0; j < m_Height; j++)
		{
			if (i != 0 && i != m_Width - 1)
			{
				// We have a right connection to add.
				Node* otherNode = m_Grid[i + 1][j];

				if (!m_Grid[i][j]->CheckIfConnected(otherNode))
				{
					m_Grid[i][j]->m_ConnectedNodes.push_back(otherNode);
				}
				if(!otherNode->CheckIfConnected(m_Grid[i][j]))
					otherNode->m_ConnectedNodes.push_back(m_Grid[i][j]); // Giving the other node a reference to this node.
			}
			if (j != m_Height - 1)
			{
				// We have a connection below us to add.
				Node* otherNode = m_Grid[i][j + 1];

				if (!m_Grid[i][j]->CheckIfConnected(otherNode))
				{
					m_Grid[i][j]->m_ConnectedNodes.push_back(otherNode);
				}

				if(!otherNode->CheckIfConnected(m_Grid[i][j]))
					otherNode->m_ConnectedNodes.push_back(m_Grid[i][j]);
			}
			if (j != 0 && i != m_Width - 1)
			{
				// We have a diagonal top-right connection.
				Node* otherNode = m_Grid[i + 1][j - 1];

				if (!m_Grid[i][j]->CheckIfConnected(otherNode))
				{
					m_Grid[i][j]->m_ConnectedNodes.push_back(otherNode);
				}

				if(!otherNode->CheckIfConnected(m_Grid[i][j]))
					otherNode->m_ConnectedNodes.push_back(m_Grid[i][j]);
			}
			if (i != m_Width - 1 && j != m_Height - 1)
			{
				// We have a diagonal connection bottom-right of us.
				Node* otherNode = m_Grid[i + 1][j + 1];

				if (!m_Grid[i][j]->CheckIfConnected(otherNode))
				{
					m_Grid[i][j]->m_ConnectedNodes.push_back(otherNode);
				}

				if(!otherNode->CheckIfConnected(m_Grid[i][j]))
					otherNode->m_ConnectedNodes.push_back(m_Grid[i][j]);
			}
		}
	}
}