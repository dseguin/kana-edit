#include <fstream>
#include <cerrno>

#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
	#include <fcntl.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "defines.h"

std::string to_std_string(const sf::String& original);
