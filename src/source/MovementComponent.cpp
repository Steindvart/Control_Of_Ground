#include "MovementComponent.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_speed)
	: m_sprite {sprite},
	m_max_speed(max_speed)
{
}

MovementComponent::~MovementComponent()
{
}

////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
const sf::Vector2f& cog::MovementComponent::get_speed() const
{
	return m_speed;
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void MovementComponent::move(sf::Vector2f dir_xy, const float& dt)
{
	m_speed = m_max_speed * dir_xy;
}

void MovementComponent::update(const float& dt)
{
}
