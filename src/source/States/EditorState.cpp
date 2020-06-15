#include "stdHeader.hpp"

#include "EditorState.hpp"

#include "States/SettingsState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

EditorState::EditorState(StateData& Sdata)
	: State{ Sdata },
	m_tile_map { sf::Vector2f(100.f, 100.f), sf::Vector2u(3, 3) },
	m_pause_menu { m_Sdata.window, *m_Sdata.supported_fonts["DOSIS"], m_Sdata.supported_fonts}
{
	initTextures();
	initKeybinds();
}

EditorState::~EditorState()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void EditorState::initTextures()
{
}

void EditorState::initKeybinds()
{
#ifdef DEBUG
	std::cout << "EditorState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keys_ifs("config/EditorState_keybinds.ini");
	if (keys_ifs.is_open())
	{
		std::string key{ "" };
		std::string key_value{ "" };

		while (keys_ifs >> key >> key_value)
		{
			m_keybinds[key] = m_Sdata.supported_keys.at(key_value);
		}
	}
	else
	{
		std::cerr << "config/EditorState.ini - cannot open!"
			<< std::endl
			<< "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_Sdata.supported_keys.at("Escape");
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "EditorState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}


////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string EditorState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();
	result << m_pause_menu.getStringInfo();

	return result.str();
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void EditorState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::LostFocus)
	{
		if (!m_paused)
			pause();
	}

	if (event.type == sf::Event::KeyPressed)
	{

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["CLOSE"])))
		{
			if (!m_paused)
				pause();
			else
				unpause();
		}

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["SWITCH_TILE_BORDER_VISIBLE"])))
		{
			if (!m_tile_map.getTilesBorderVisible())
				m_tile_map.setTilesBorderVisible(true);
			else
				m_tile_map.setTilesBorderVisible(false);
		}
	}
}

void EditorState::updateInput(const float& dt)
{
}

void EditorState::updatePauseInput(const float& dt)
{
	if (m_pause_menu.isButtonPressed("SETTINGS_STATE"))
		m_Sdata.states.push(new SettingsState{ m_Sdata });

	if (m_pause_menu.isButtonPressed("EXIT"))
		quitState();
}

void EditorState::update(const float& dt)
{
	updateMousePos();

	if (!m_paused)
	{
	}
	else
	{
		updatePauseInput(dt);

		m_pause_menu.update(m_mouse_pos_view, dt);
	}
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void EditorState::render(sf::RenderTarget& target)
{
	m_tile_map.render(target);

	if (m_paused)
	{
		m_pause_menu.render(target);
	}
}