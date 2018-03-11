#pragma once

#include <SFML/Graphics.hpp>

class Animator
{
public:
	Animator();

	void AddFrame( sf::IntRect frame );
	void Play( sf::Time duration, bool loop );
	bool IsPlaying() const;

	void Update( sf::Time delta );
	void Animate( sf::Sprite & sprite );

private:
	std::vector< sf::IntRect > m_frames;

	bool m_isPlaying;
	sf::Time m_duration;
	bool m_loop;

	unsigned int m_currentFrame;
};