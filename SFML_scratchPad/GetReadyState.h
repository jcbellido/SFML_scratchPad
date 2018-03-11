#pragma once

#include "GameState.h"

class GetReadyState : public GameState
{
public:
	GetReadyState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );

	void PreLeave() override;
	
protected:
	sf::Text m_text;
	sf::Time m_timeBuffer;
	bool m_showText;
};