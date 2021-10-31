#include "Square.h"
#include "Node.h"

Square::Square(float x, float y, float halfExtent)
{
	m_XPos = x;
	m_YPos = y;
	m_HalfExtent = halfExtent;

	m_Colour = { 125, 125, 255 };

	m_Rect.x = m_XPos;
	m_Rect.y = m_YPos;
	m_Rect.w = m_HalfExtent * 2;
	m_Rect.h = m_HalfExtent * 2;
}

void Square::Draw(SDL_Renderer* renderer)
{
	SDL_RenderDrawRect(renderer, &m_Rect);

	SDL_SetRenderDrawColor(renderer, m_Colour.r, m_Colour.g, m_Colour.b, 255);

	if (!m_Passable)
		SDL_SetRenderDrawColor(renderer, 255, 0, 10, 255);

	SDL_RenderFillRect(renderer, &m_Rect);

	// Returning squares back to normal square colour.
	SDL_SetRenderDrawColor(renderer, 0, 125, 125, 255);
}

void Square::SetPassable(bool toggle)
{
	m_Passable = toggle;
	m_Node->m_Passable = toggle;
}

void Square::SetColour(float r, float g, float b)
{
	m_Colour.r = r;
	m_Colour.g = g;
	m_Colour.b = b;
}