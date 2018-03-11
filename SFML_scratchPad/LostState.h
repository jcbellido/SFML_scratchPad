#pragma once

#include "GameState.h"

class LostState : public GameState
{
public:
	LostState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );

	void PreEnter() override;

private:
	void UpdateText();

	int m_remainingSeconds;

	sf::Time m_timeBuffer;

	sf::Text m_textBanner;
	sf::Text m_textCounter;
};
