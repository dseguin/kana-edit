// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#ifdef _WIN32
	#include <Windows.h>
#endif

// Local
#if defined HAVE_CONFIG_H && !defined CONFIG_H
	#define CONFIG_H
	#include "config.h"
#endif
#include "../include/icon.h"
#include "../include/defines.h"

// Start mutex
sf::Mutex renderMutex;

#include "threadvars.h"
#include "rendervars.h"

void concatenateKana (threadVariables variablestruct);
void kanaBackspace (threadVariables variablestruct);
void renderObjects (renderVariables *variablestruct);
void saveOutput (sf::String OutputString, sf::Font font);

#include "unifont.h"
#include "dejavu.h"
