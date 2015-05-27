#ifndef RENDERVARS_H
#define RENDERVARS_H

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

#endif // RENDERVARS_H
