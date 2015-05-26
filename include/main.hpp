// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/* MS Windows
#include <windows.h>	// Windows objects (WinMain, etc...)
#include <shlobj.h>		// Contains SHGetFolderPath() (link with shell32.lib)
*/

/*
// Standard
#include <ctime>		// For animation and blinking of cursor object
#include <iostream>
#include <fstream>		// Save window function
#include <string>		// For standard string output
#include <stdexcept>	// For standard exceptions
*/

// Local
#include "../include/icon.h"

/* MS Windows
// Linking libraries
#pragma comment(lib, "C:/path/to/SFML-2.x/lib/sfml-window.lib")
#pragma comment(lib, "C:/path/to/SFML-2.x/lib/sfml-system.lib")
#pragma comment(lib, "C:/path/to/SFML-2.x/lib/sfml-graphics.lib")
#pragma comment(lib, "shell32.lib")
*/

// --------------------------------------------------------------------------
// ---   ---   ---   -  STATIC MEMBER DECLARATION  -   ---   ---   ---   ---
// --------------------------------------------------------------------------

sf::Mutex renderMutex;

#include "threadvars.h"

/*
// Structure containing references to I/O variables
struct threadVariables
{
	sf::String *InputString;
	sf::String *OutputString;
	bool *inHiragana;
	bool *wrapToNewline;
};
*/

#include "rendervars.h"

/*
sf::Mutex renderMutex;

// Structure containing references to render objects (THREADED)
struct renderVariables
{
	sf::RectangleShape *InField;
	sf::RectangleShape *OutField;
	sf::Text *InText;
	sf::Text *OutText;
	sf::RectangleShape *InCursor;
	sf::RectangleShape *OutCursor;
	sf::RenderWindow *XGui;
	// Menu items:
	char *MouseInArea;
	char *MouseInSubarea;
	char *ThisSubmenu;
	sf::Text *MenuFile;
	sf::VertexArray *MenuFileButtonBox;
	sf::RectangleShape *MenuFileButton;
	sf::RectangleShape *MenuFileSubmenu;
	sf::RectangleShape *SubmenuButton01;
	sf::RectangleShape *SubmenuButton02;
	sf::RectangleShape *SubmenuButton03;
	sf::RectangleShape *SubmenuButton04;
	sf::RectangleShape *SubmenuButton05;
	sf::Text *SubmenuSwitchKana;
	sf::Text *SubmenuClear;
	sf::Text *SubmenuSave;
	sf::Text *SubmenuBlank;
	sf::Text *SubmenuExit;
	// Disclamer:
	sf::Text *BottomText;
};
*/

// Function declarations
// sf::String toHiragana (sf::String InputString);			// Accepts input (stringin) and returns sf::String with corresponding kana
// sf::String toKatakana (sf::String InputString);
void concatenateKana (threadVariables variablestruct);	// Concatenates input to stringout if stringin is not NULL
void kanaBackspace (threadVariables variablestruct);	// Erases previous kana if conditions are met
void renderObjects (renderVariables *variablestruct);	// Contains all draw functions for rendering objects (clear, draw, display)
void saveOutput (sf::String OutputString, sf::Font font); // Creates and draws save window
// std::string to_std_string(const sf::String& original);	// Takes sf::String (UTF-32) and returns std::string (UTF-8)

/*
#include "hiragana.cpp"
#include "katakana.cpp"
#include "concatenate.cpp"
#include "backspace.cpp"
#include "renderdraw.cpp"
#include "savewindow.cpp"
#include "stringconvert.cpp"
*/
