#include "stdHeader.hpp"

#include "TileMap.hpp"

TileMap::TileMap(const sf::Vector2f& grid_size, const sf::Vector2u& max_size, const size_t layers)
	: m_grid_size_f { grid_size },
	m_grid_size_u   { static_cast<sf::Vector2u>(grid_size) },
	m_max_size      { max_size },
	m_layers        { layers }
{
	m_map.resize(max_size.x);
	for (size_t x = 0; x < max_size.x; x++)
	{
		m_map.push_back(std::vector< std::vector<Tile> >());

		for (size_t y = 0; y < max_size.y; y++)
		{
			m_map[x].resize(max_size.y);
			m_map[x].push_back(std::vector<Tile>());

			for (size_t z = 0; z < layers; z++)
			{
				m_map[x][y].resize(layers);
				m_map[x][y].push_back(Tile(sf::Vector2f(m_grid_size_f.x * x, m_grid_size_f.y * y), grid_size));
			}
		}
	}
}

TileMap::~TileMap()
{
}

//Update
void TileMap::update(const float& dt)
{
}

//Render
void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : m_map)
		for (auto& y : x)
			for (auto& z : y)
				z.render(target);
}