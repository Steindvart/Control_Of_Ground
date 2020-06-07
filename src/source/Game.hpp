#ifndef GAME_H
#define GAME_H

#include "State.hpp"
#include "GameState.hpp"

namespace Core
{
class Game final
{
public:
	//Constructors
	Game();
	~Game();

	//Core
	void run();

private:
////////////////////////////////////////////////////////////
// Members
////////////////////////////////////////////////////////////
	//Window
		sf::RenderWindow*          m_window;
		sf::ContextSettings        m_window_settings;
		std::vector<sf::VideoMode> m_video_modes;
		bool m_fullscreen_enabled;

	//Supported keys
		std::map<const std::string, int> m_supported_keys;

	//Time
		sf::Clock m_delta_time_clock;
		float m_delta_time;

	//States
		std::stack<States::State*> m_states;

	//Fonts
		std::map<const std::string, sf::Font*> m_supported_fonts;

	//Info
		std::stringstream m_tech_info;
		bool m_enable_info;

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
	void inline initWindow();
	void inline initSupportedKeys();
	void inline initSupportedFonts();
	void inline initFirstState();

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
	void updateInfo();
	sf::Text getTextInfo(const sf::Font& font);

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
	//Update
		void updateDeltaTime();
		void update();

		void applicationEnd();

	//Render
		void render();

////////////////////////////////////////////////////////////
// Tech functions
////////////////////////////////////////////////////////////
	//Support_cleaner
		void inline delete_states();
		void inline delete_fonts();
};
} // !namespace cog
#endif // !GAME_H