#pragma once
#include "SDL.h"
#include "Node.h"

class Square
{
public:
	float m_XPos;
	float m_YPos;
	float m_HalfExtent;
	SDL_Rect m_Rect;

	SDL_Color m_Colour;

	bool m_Passable = true;

	Node* m_Node;

	Square() {}
	Square(float x, float y, float halfExtent);

	void Draw(SDL_Renderer* renderer);
	void SetPassable(bool toggle);
	void SetColour(float r, float g, float b);

};