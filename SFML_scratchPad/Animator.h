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
	bool m_loop;
	
	sf::Time m_duration;
	sf::Time m_frameDuration;
	sf::Time m_timeBuffer; 

	unsigned int m_currentFrame;
};