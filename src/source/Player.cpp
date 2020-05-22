#include "stdHeader.hpp"

#include "Player.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Player::Player(sf::Vector2f position_xy, sf::Texture* texture, const float& max_speed)
	: Entity(texture, max_speed)
{
	set_position(position_xy);
	//m_sprite->setTextureRect(sf::IntRect(0, 0, 200, 200));
	m_sprite->setScale(sf::Vector2f(0.12f, 0.15f));
}

Player::~Player()
{
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void update_input()
{

}