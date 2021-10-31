#include "Node.h"


Node::Node()
{}

Node::Node(int x, int y)
{
	m_XIndex = x;
	m_YIndex = y;
}

void Node::ResetGScore()
{
	m_GScore = 0;
}

void Node::ResetPrevious()
{
	m_Previous = nullptr;
}

bool Node::Compare(Node* otherNode)
{
	return(m_XIndex == otherNode->m_XIndex && m_YIndex == otherNode->m_YIndex);
}

void Node::SetPassable(bool toggle)
{
	m_Passable = toggle;
}