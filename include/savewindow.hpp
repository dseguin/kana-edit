#include <fstream>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "defines.h"

std::string to_std_string(const sf::String& original);
