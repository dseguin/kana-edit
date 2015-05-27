// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// Local
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
