#include "stdHeader.hpp"

#include "Player.hpp"

using namespace Entities;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Player::Player(const sf::Vector2f& position_xy, sf::Texture& texture,
			   const float& max_speed, const float& acceleration, const float& deceleration,
			   const sf::Vector2f& scale)
	: Entity{ texture, scale }, m_scale_x { scale.x }, m_scale_y{ scale.y }
{
	//Creating components
	createMovementComponent (*m_sprite, max_speed, acceleration, deceleration);
	createAnimationComponent(*m_sprite, texture);
	sf::Vector2f hitbox_size{ 11.f, 29.f };
	createHitboxComponent   (*m_sprite, sf::Vector2f(80.f, 30.f), hitbox_size, scale);

	initAnimations();

	setPosition(position_xy);
}

Player::~Player()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void Player::initAnimations()
{
	//addAnimation(NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animation_component->addAnimation("BREAKING", 0.35f, 3, 3, 4, 1, 50, 37);
	m_animation_component->addAnimation("WALK", 0.35f, 1, 1, 5, 1, 50, 37);
	m_animation_component->addAnimation("IDLE", 0.35f, 0, 0, 3, 0, 50, 37); //Need last, because it's a start Rect
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string Player::getStringInfo()
{
	std::stringstream result;

	result << "Player_pos: " << m_sprite->getPosition().x << ' ' << m_sprite->getPosition().y << '\n';
	result << "MovementComponent:\n";
	result << m_movement_component->getStringInfo();

	return result.str();
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

void Player::move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_movement_component->move(dir_xy, dt);
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void Player::updateAnimations(const float& dt)
{
	using MoveState  = Components::MovementComponent::MovingStates;
	using SpeedStage = Components::MovementComponent::SpeedStages;

	MoveState movement_state = m_movement_component->getMovingState();
	SpeedStage speed_stage   = m_movement_component->getSpeedStage();

	float grow_speed_anim = 0.f;
	if (speed_stage == SpeedStage::FIRST)
		grow_speed_anim = 0.1f;
	else if (speed_stage == SpeedStage::SECOND)
		grow_speed_anim = 0.15f;
	else if (speed_stage == SpeedStage::THIRD)
		grow_speed_anim = 0.18f;

	switch (movement_state)
	{
	case MoveState::IDLE:
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setRotation(0.f);
		m_animation_component->play("IDLE", dt);
		break;
	case MoveState::RIGHT:
		m_sprite->setOrigin(0.f, 0.f);
		m_sprite->setScale(m_scale_x, m_scale_y);
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(23.f, 0.f));
		m_hitbox_component->setRotation(7.f);
		m_animation_component->play("WALK", dt, grow_speed_anim);
		break;
	case MoveState::LEFT:
		m_sprite->setOrigin(50.f, 0.f);
		m_sprite->setScale(-m_scale_x, m_scale_y);
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(-23.f, 0.f));
		m_hitbox_component->setRotation(-7.f);
		m_animation_component->play("WALK", dt, grow_speed_anim);
		break;
	case MoveState::UP:
		m_sprite->setOrigin(0.f, 0.f);
		m_sprite->setScale(m_scale_x, m_scale_y);
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(23.f, 0.f));
		m_hitbox_component->setRotation(7.f);
		m_animation_component->play("WALK", dt, grow_speed_anim);
		break;
	case MoveState::DOWN:
		m_sprite->setOrigin(0.f, 0.f);
		m_sprite->setScale(m_scale_x, m_scale_y);
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(23.f, 0.f));
		m_hitbox_component->setRotation(7.f);
		m_animation_component->play("WALK", dt, grow_speed_anim);
		break;
	case MoveState::BREAKING:
		m_hitbox_component->setSize(sf::Vector2f(29.f, 13.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(-34.f, 65.f));
		m_hitbox_component->setRotation(0.f);
		m_animation_component->play("BREAKING", dt, grow_speed_anim);
		break;
	}		
}

void Player::updateInput()
{
}

void Player::update(const float& dt)
{
	m_movement_component->update(dt);
	updateAnimations(dt);
	m_hitbox_component->update(dt);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*m_sprite);
	m_hitbox_component->render(target);
}