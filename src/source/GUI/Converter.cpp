#include "stdafx.h"

#include "Converter.h"

using namespace GUI;

//XY manip
float Converter::Сalc(const float perc, const float size)
{
	return std::floor(static_cast<float>(size) * (perc / 100.f));
}

float Converter::Сalc(const float perc, const unsigned size)
{
	return std::floor(static_cast<float>(size) * (perc / 100.f));
}

float Converter::СalcX(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

float Converter::СalcX(const float perc, const sf::Vector2f& size_xy)
{
	return std::floor(static_cast<float>(size_xy.x) * (perc / 100.f));
}

float Converter::СalcY(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

float Converter::СalcY(const float perc, const sf::Vector2f& size_xy)
{
	return std::floor(static_cast<float>(size_xy.y) * (perc / 100.f));
}

sf::Vector2f Converter::СalcVecf(const sf::Vector2f& perc, const sf::VideoMode& vm)
{
	return sf::Vector2f(
		std::floor(static_cast<float>(vm.width)  * (perc.x / 100.f)),
		std::floor(static_cast<float>(vm.height) * (perc.y / 100.f))
	);
}

sf::Vector2f Converter::СalcVecf(const sf::Vector2f& perc, const sf::Vector2f& size_xy)
{
	return sf::Vector2f(
		std::floor(static_cast<float>(size_xy.x) * (perc.x / 100.f)),
		std::floor(static_cast<float>(size_xy.y) * (perc.y / 100.f))
	);
}

//Char size
const unsigned Converter::СalcCharSize(const unsigned modifier, const sf::VideoMode& vm)
{

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

const unsigned Converter::СalcCharSize(const unsigned modifier, const sf::Vector2f& size_xy)
{
	return static_cast<unsigned>((size_xy.x + size_xy.y) / modifier);
}