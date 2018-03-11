#include "Character.h"

Character::Character()
:m_speed(1.f)
{
}

void Character::SetSpeed(float speed)
{
	m_speed = speed;
}

float Character::GetSpeed() const 
{
	return m_speed;
}
