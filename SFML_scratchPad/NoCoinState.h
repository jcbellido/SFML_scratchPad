#pragma once

#include "GameState.h"

class NoCoinState : public GameState
{
public:
	NoCoinState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );

	void PreEnter() override;

protected:
	sf::Text m_text;
	sf::Sprite m_sprite;
	bool m_showInsertCoin;
	int m_coinsInserted;

private:
	void UpdateText();
};
