/*
// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// MS Windows
//#include <windows.h>	// Windows objects (WinMain, etc...)
//#include <shlobj.h>		// Contains SHGetFolderPath() (link with shell32.lib)

// Standard
#include <ctime>		// For animation and blinking of cursor object
#include <iostream>
#include <fstream>		// Save window function
#include <string>		// For standard string output
#include <stdexcept>	// For standard exceptions

// Local
#include "../include/icon.h"

// MS Windows
// Linking libraries
//#pragma comment(lib, "C:/path/to/SFML-2.x/lib/sfml-window.lib")
//#pragma comment(lib, "C:/path/to/SFML-2.x/lib/sfml-system.lib")
//#pragma comment(lib, "C:/path/to/SFML-2.x/lib/sfml-graphics.lib")
//#pragma comment(lib, "shell32.lib")

// --------------------------------------------------------------------------
// ---   ---   ---   -  STATIC MEMBER DECLARATION  -   ---   ---   ---   ---
// --------------------------------------------------------------------------

sf::Mutex renderMutex;

// Structure containing references to I/O variables
struct threadVariables
{
	sf::String *InputString;
	sf::String *OutputString;
	bool *inHiragana;
	bool *wrapToNewline;
};

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

// Function declarations
sf::String toHiragana (sf::String InputString);			// Accepts input (stringin) and returns sf::String with corresponding kana
sf::String toKatakana (sf::String InputString);
void concatenateKana (threadVariables variablestruct);	// Concatenates input to stringout if stringin is not NULL
void kanaBackspace (threadVariables variablestruct);	// Erases previous kana if conditions are met
void renderObjects (renderVariables *variablestruct);	// Contains all draw functions for rendering objects (clear, draw, display)
void saveOutput (sf::String OutputString, sf::Font font); // Creates and draws save window
std::string to_std_string(const sf::String& original);	// Takes sf::String (UTF-32) and returns std::string (UTF-8)

#include "hiragana.cpp"
#include "katakana.cpp"
#include "concatenate.cpp"
#include "backspace.cpp"
#include "renderdraw.cpp"
#include "savewindow.cpp"
#include "stringconvert.cpp"
*/

// --------------------------------------------------------------------------
// ---   ---   ---   ---   -  MAIN FUNCTION  -   ---   ---   ---   ---   ---
// --------------------------------------------------------------------------

/* MS Windows
// Replaces main() to run without console
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
*/

#include "../include/main.hpp"

int main()
{

// --------------------------------------------------------------------------
// ---   ---   ---   ---   -  USER SET PARAMETERS  -   ---   ---   ---   ---
// --------------------------------------------------------------------------

	bool usingHiragana = true;			// Sets output to hiragana if true and katakana is false
	bool userSetResolution = false;		// Determines if user has changed resolution (resize)
	unsigned int userTextSize = 12;		// Defines size of input and output text
	unsigned int userResolutionX = 800;	// Defines width of resolution set by user
	unsigned int userResolutionY = 600;	// Defines height of resolution set by user
	
	sf::String inputStorage;			// Stores input text during resize event
	sf::String outputStorage;			// Stores output text during resize event
	sf::Vector2i currentMousePosition(0,0); // Contains position of mouse pointer
	char mouseInMenu;					// Determines which menu option mouse is hovering over
	char mouseInSubmenu;				// Determines which submenu option mouse is hovering over
	char whichSubmenu;					// Determines which submenu has been opened
	bool submenuIsOpen = false;			// Sets events to "in submenu" mode if true and "normal" mode if false

// --------------------------------------------------------------------------
//   ---   ---   ---   ---   -  RESOURCE LOADING  -   ---   ---   ---   ---
// --------------------------------------------------------------------------

// **************************** FONT LOADING ********************************
	
	sf::Font arial;
	if (!arial.loadFromFile(FONT_ARIAL))
	{
		return -1;
	}
	
	sf::Font mangal;
	if (!mangal.loadFromFile(FONT_MANGAL))
	{
		return -1;
	}

// **************************************************************************

// --------------------------------------------------------------------------
// ---   ---   ---   ---   -  TEXT OBJECTS  -   ---   ---   ---   ---   ---
// --------------------------------------------------------------------------

	// While userSetResolution is true (Repeats window creation)	
	do
	{
	
// ************************ INPUT TEXT OBJECT *******************************

		// Text input string
		sf::String stringin;
	
		// Text input object
		sf::Text textin;
		textin.setFont(arial);
		textin.setCharacterSize(userTextSize);
		textin.setColor(sf::Color::Black);
		textin.setPosition(30, 50);
	
		// Bounds of input text
		sf::FloatRect textinbounds = textin.getGlobalBounds();

// **************************************************************************

// ************************ OUTPUT TEXT OBJECT ******************************

		// Text output string
		sf::String stringout;
	
		// Text output object
		sf::Text textout;
		textout.setFont(arial);
		textout.setCharacterSize(userTextSize);
		textout.setColor(sf::Color::Black);
		textout.setPosition( 30, ((userResolutionY / 2) + 25) );
	
		// Bounds of output text
		sf::FloatRect textoutbounds = textout.getGlobalBounds();

// **************************************************************************

// ************************* MENU TEXT OBJECTS ******************************
	
		// File menu option
		sf::Text menu_file("Options", mangal, 12);
		menu_file.setColor(sf::Color::Black);
		menu_file.setPosition(5, 3);
		sf::FloatRect menu_file_bounds = menu_file.getGlobalBounds();
	
		// File submenu option for switching between hiragana and katakana
		sf::Text menu_file_switchkana(" ", mangal, 12);

		menu_file_switchkana.setColor(sf::Color::Black);
		menu_file_switchkana.setPosition(5, 21);
	
		// File submenu option for clearing all text fields
		sf::Text menu_file_clear("Clear all text", mangal, 12);
		menu_file_clear.setColor(sf::Color::Black);
		menu_file_clear.setPosition(5, 41);
	
		// File submenu option for saving stringout to text file
		sf::Text menu_file_save("Save to text file", mangal, 12);
		menu_file_save.setColor(sf::Color::Black);
		menu_file_save.setPosition(5, 61);
	
		// File submenu blank option (temporary)
		sf::Text menu_file_blank("---   ---   ---", mangal, 12);
		menu_file_blank.setColor(sf::Color::Black);
		menu_file_blank.setPosition(5, 81);
	
		// File submenu option for Exit
		sf::Text menu_file_exit("Exit", mangal, 12);
		menu_file_exit.setColor(sf::Color::Black);
		menu_file_exit.setPosition(5, 101);

// **************************************************************************

// *********************** BOTTOM TEXT OBJECT *******************************
	
		// Disclaimer
		sf::Text bottomtext("Work in progress. Maintained by dseguin @ github.com.", arial, 10);
		bottomtext.setColor(sf::Color::Black);
		sf::FloatRect bottomtextbounds = bottomtext.getGlobalBounds();
		bottomtext.setPosition( (userResolutionX - bottomtextbounds.width - 2), (userResolutionY - bottomtextbounds.height - 5) );

// **************************************************************************

// --------------------------------------------------------------------------
// --   ---   ---   ---   -  GRAPHICS OBJECTS  -   ---   ---   ---   ---   --
// --------------------------------------------------------------------------

// ************************ INPUT TEXT FIELD ********************************

		sf::RectangleShape textinfield(sf::Vector2f( (userResolutionX - 50) , ((userResolutionY / 2) - 50) ));
		textinfield.setPosition(25, 50);
		textinfield.setFillColor(sf::Color::White);
		textinfield.setOutlineThickness(1);
		textinfield.setOutlineColor(sf::Color(200, 200, 200));

// **************************************************************************

// ************************* OUTPUT TEXT FIELD ******************************

		sf::RectangleShape textoutfield(sf::Vector2f( (userResolutionX - 50) , ((userResolutionY / 2) - 50) ));
		textoutfield.setPosition( 25, ((userResolutionY / 2) + 25) );
		textoutfield.setFillColor(sf::Color::White);
		textoutfield.setOutlineThickness(1);
		textoutfield.setOutlineColor(sf::Color(200, 200, 200));

// **************************************************************************

// ************************** FILE MENU BUTTON ******************************

		// Button outline
		sf::VertexArray menu_file_button_l(sf::LinesStrip, 5);
	
		menu_file_button_l[0].position = sf::Vector2f( (menu_file_bounds.width + 12) , 2 );
		menu_file_button_l[1].position = sf::Vector2f( (menu_file_bounds.width + 12) , 20 );
		menu_file_button_l[2].position = sf::Vector2f(2,20);
		menu_file_button_l[3].position = sf::Vector2f(2,2);
		menu_file_button_l[4].position = sf::Vector2f( (menu_file_bounds.width + 12) , 2 );
	
		menu_file_button_l[0].color = sf::Color(180,180,180);
		menu_file_button_l[1].color = sf::Color(180,180,180);
		menu_file_button_l[2].color = sf::Color(255,255,255);
		menu_file_button_l[3].color = sf::Color(255,255,255);
		menu_file_button_l[4].color = sf::Color(255,255,255);
	
		// Button backshadow
		sf::RectangleShape menu_file_button_b(sf::Vector2f( (menu_file_bounds.width + 10), 18 ));
		menu_file_button_b.setPosition(2,2);
		menu_file_button_b.setFillColor(sf::Color(200,200,200));
	
		// Submenu box
		sf::RectangleShape menu_file_submenu_b(sf::Vector2f(200,100));
		menu_file_submenu_b.setPosition(2,20);
		menu_file_submenu_b.setFillColor(sf::Color(200,200,200));
		menu_file_submenu_b.setOutlineThickness(1);
		menu_file_submenu_b.setOutlineColor(sf::Color(180, 180, 180));
		sf::FloatRect menu_file_submenu_bounds = menu_file_submenu_b.getGlobalBounds();
	
		// Submenu button01 backshadow
		sf::RectangleShape menu_file_submenu_button01_b(sf::Vector2f(menu_file_submenu_bounds.width , 20));
		menu_file_submenu_button01_b.setPosition(2,20);
		menu_file_submenu_button01_b.setFillColor(sf::Color(150,150,180));
	
		// Submenu button02 backshadow
		sf::RectangleShape menu_file_submenu_button02_b(sf::Vector2f(menu_file_submenu_bounds.width , 20));
		menu_file_submenu_button02_b.setPosition(2,40);
		menu_file_submenu_button02_b.setFillColor(sf::Color(150,150,180));
	
		// Submenu button03 backshadow
		sf::RectangleShape menu_file_submenu_button03_b(sf::Vector2f(menu_file_submenu_bounds.width , 20));
		menu_file_submenu_button03_b.setPosition(2,60);
		menu_file_submenu_button03_b.setFillColor(sf::Color(150,150,180));
	
		// Submenu button04 backshadow
		sf::RectangleShape menu_file_submenu_button04_b(sf::Vector2f(menu_file_submenu_bounds.width , 20));
		menu_file_submenu_button04_b.setPosition(2,80);
		menu_file_submenu_button04_b.setFillColor(sf::Color(150,150,180));
	
		// Submenu button05 backshadow
		sf::RectangleShape menu_file_submenu_button05_b(sf::Vector2f(menu_file_submenu_bounds.width , 20));
		menu_file_submenu_button05_b.setPosition(2,100);
		menu_file_submenu_button05_b.setFillColor(sf::Color(150,150,180));

// **************************************************************************

// ********************** TEXT CURSOR OBJECTS *******************************

		sf::RectangleShape intextcursor(sf::Vector2f(1, 20));
		intextcursor.setFillColor(sf::Color::Black);
	
		sf::RectangleShape outtextcursor(sf::Vector2f(1, 20));
		outtextcursor.setFillColor(sf::Color::Black);

// **************************************************************************

// --------------------------------------------------------------------------
//   ---   ---   ---   -  GUI WINDOW DECLARATION  -   ---   ---   ---   ---
// --------------------------------------------------------------------------

		/* MS Windows
		sf::RenderWindow gui ( sf::VideoMode( userResolutionX , userResolutionY ) , "Simple Kana Editor" );
		*/
		sf::RenderWindow gui ( sf::VideoMode( userResolutionX , userResolutionY ) , "Simple Kana Editor" , sf::Style::Close );
		
		gui.setIcon ( kana_icon.width,  kana_icon.height,  kana_icon.pixel_data );
	
// --------------------------------------------------------------------------
// ---   ---   ---   ---   -  THREAD OBJECTS  -   ---   ---   ---   ---   ---
// --------------------------------------------------------------------------

		// Struct for use with concatenateKana()
		threadVariables threadVarInstance;
		threadVarInstance.InputString = &stringin;
		threadVarInstance.OutputString = &stringout;
		threadVarInstance.inHiragana = &usingHiragana;
	
		// Structure containing references to render objects
		renderVariables renderVarInstance;
		renderVarInstance.InField = &textinfield;
		renderVarInstance.OutField = &textoutfield;
		renderVarInstance.InText = &textin;
		renderVarInstance.OutText = &textout;
		renderVarInstance.InCursor = &intextcursor;
		renderVarInstance.OutCursor = &outtextcursor;
		renderVarInstance.XGui = &gui;
		// Menu items:
		renderVarInstance.MouseInArea = &mouseInMenu;
		renderVarInstance.MouseInSubarea = &mouseInSubmenu;
		renderVarInstance.ThisSubmenu = &whichSubmenu;
		// File:
		renderVarInstance.MenuFile = &menu_file;
		renderVarInstance.MenuFileButtonBox = &menu_file_button_l;
		renderVarInstance.MenuFileButton = &menu_file_button_b;
		renderVarInstance.MenuFileSubmenu = &menu_file_submenu_b;
		// Submenu:
		renderVarInstance.SubmenuButton01 = &menu_file_submenu_button01_b;
		renderVarInstance.SubmenuButton02 = &menu_file_submenu_button02_b;
		renderVarInstance.SubmenuButton03 = &menu_file_submenu_button03_b;
		renderVarInstance.SubmenuButton04 = &menu_file_submenu_button04_b;
		renderVarInstance.SubmenuButton05 = &menu_file_submenu_button05_b;
		renderVarInstance.SubmenuSwitchKana = &menu_file_switchkana;
		renderVarInstance.SubmenuClear = &menu_file_clear;
		renderVarInstance.SubmenuSave = &menu_file_save;
		renderVarInstance.SubmenuBlank = &menu_file_blank;
		renderVarInstance.SubmenuExit = &menu_file_exit;
		// Disclamer:
		renderVarInstance.BottomText = &bottomtext;
	
		// Thread instance ( launch() executes renderObjects() )
		sf::Thread renderThread (&renderObjects, &renderVarInstance);

// --------------------------------------------------------------------------
// ---   ---   ---   ---   -  GUI LOOP START  -   ---   ---   ---   ---   ---
// --------------------------------------------------------------------------
		
		// Unsets the main thread as the active window
		gui.setActive(false);

		// Calls renderObjects() through renderThread
		renderThread.launch();
	
		sf::Mouse usermouse;
		sf::Event useraction;

		// Resets userSetResolution if a resize event occurred
		if (userSetResolution)
		{
			stringin = inputStorage;
			stringout = outputStorage;
			userSetResolution = false;
		}
		
		renderMutex.lock();

		while (gui.isOpen())
		{

			renderMutex.unlock();
			
// **************************** EVENT LOOP **********************************
			
			renderMutex.lock();

			while (gui.pollEvent(useraction))
			{
				renderMutex.unlock();

				/* MS Windows
				// Resize event (updates resolution variables)
				if (useraction.type == sf::Event::Resized)
				{
					userResolutionX = useraction.size.width;
					userResolutionY = useraction.size.height;
					userSetResolution = true;
					inputStorage = stringin;
					outputStorage = stringout;
					gui.close();
				}
				*/

				// Close button event
				if (useraction.type == sf::Event::Closed)
				{
					gui.close();
				}
				renderMutex.lock();
				if(!submenuIsOpen)
				{
					renderMutex.unlock();
					// Unicode input events
					if (useraction.type == sf::Event::TextEntered)
					{
						// Text input event
						if (useraction.text.unicode > 31 && useraction.text.unicode < 127)
						{
							
							renderMutex.lock();
							sf::Vector2f lastCharPos = textin.findCharacterPos(stringin.getSize());
							sf::Vector2f outlastCharPos = textout.findCharacterPos(stringout.getSize());
							renderMutex.unlock();
							
							if ( lastCharPos.x < (userResolutionX - 50) )
							{
								// Concatenate input to stringin
								stringin += useraction.text.unicode;
								
								if ( outlastCharPos.x < (userResolutionX - 50) )
								{
									// Concatenates corresponding character to stringout
									concatenateKana (threadVarInstance);
								}
								// Newline once output text reaches bounds
								else if (outlastCharPos.x >= (userResolutionX - 50) && textoutbounds.height < ( (userResolutionY / 2) - 80 ))
								{
									stringout += '\n';
									// Concatenates corresponding character to stringout
									concatenateKana (threadVarInstance);
								}
							}
							else if (lastCharPos.x >= (userResolutionX - 50) && textinbounds.height < ( (userResolutionY / 2) - 80 ))
							{
								// Newline once input text reaches bounds
								stringin += '\n';
								stringin += useraction.text.unicode;
								
								if ( outlastCharPos.x < (userResolutionX - 50) )
								{
									// Concatenates corresponding character to stringout
									concatenateKana (threadVarInstance);
								}
								// Newline once output text reaches bounds
								else if (outlastCharPos.x >= (userResolutionX - 50) && textoutbounds.height < ( (userResolutionY / 2) - 80 ))
								{
									stringout += '\n';
									// Concatenates corresponding character to stringout
									concatenateKana (threadVarInstance);
								}
							}
						}
						// Backspace event
						if (useraction.text.unicode == 8 && stringin.getSize() > 0)
						{
							if (stringout[(stringout.getSize() - 1)] == '\n')
							{
								stringout.erase((stringout.getSize() - 1), 1);
							}
							kanaBackspace (threadVarInstance);
							stringin.erase((stringin.getSize() - 1), 1);
						}
						// Escape event
						if (useraction.text.unicode == 27)
						{
							gui.close();
						}
					}
					// Enter key event
					if (useraction.type == sf::Event::KeyPressed && textinbounds.height < ( (userResolutionY / 2) - 40 ))
					{
						if (useraction.key.code == sf::Keyboard::Return)
						{
							stringin += '\n';
							stringout += '\n';
						}
					}
					renderMutex.lock();
					if(mouseInMenu == 'f')
					{
						if (useraction.type == sf::Event::MouseButtonPressed)
						{
							if (useraction.mouseButton.button == sf::Mouse::Left)
							{
								submenuIsOpen = true;
							}
						}
					}
					renderMutex.unlock();
				}
				// Submenu is open
				else
				{
					renderMutex.unlock();
					// Mouse button event
					if (useraction.type == sf::Event::MouseButtonPressed)
					{
						if (useraction.mouseButton.button == sf::Mouse::Left)
						{
							renderMutex.lock();
							if (mouseInSubmenu == '1')
							{
								if (usingHiragana == true)
								{
									usingHiragana = false;
								}
								else
								{
									usingHiragana = true;
								}
							}
							else if (mouseInSubmenu == '2')
							{
								stringin.clear();
								stringout.clear();
							}
							else if (mouseInSubmenu == '3')
							{
								saveOutput(stringout, arial);
							}
							else if (mouseInSubmenu == '5')
							{
								gui.close();
							}
							submenuIsOpen = false;
							renderMutex.unlock();
						}
					}
				}

				renderMutex.lock();
			}

			renderMutex.unlock();

// **************************************************************************
			
// ************************ VARIABLE UPDATES ********************************
			
			renderMutex.lock();

			currentMousePosition = usermouse.getPosition(gui);
			
			// Changes mouseInMenu to 'f' if mouse is within "File" menu box area
			if ( (currentMousePosition.x >= 2 && currentMousePosition.x <= (menu_file_bounds.width + 12) ) && (currentMousePosition.y >= 2 && currentMousePosition.y <= 20) )
			{
				mouseInMenu = 'f';
			}
			else
			{
				mouseInMenu = '0';
			}
			if (submenuIsOpen)
			{
				// Changes whichSubmenu to 'f' if mouse is within "File" while submenuIsOpen is true
				if (mouseInMenu == 'f')
				{
					whichSubmenu = 'f';
				}
				// Changes mouseInSubmenu to '1' if mouse is within bounds of first submenu option
				if ( (currentMousePosition.x >= 2 && currentMousePosition.x <= (menu_file_submenu_bounds.width + 2)) &&(currentMousePosition.y >= 20 && currentMousePosition.y <= 40) )
				{
					mouseInSubmenu = '1';
				}
				else if ( (currentMousePosition.x >= 2 && currentMousePosition.x <= (menu_file_submenu_bounds.width + 2)) &&(currentMousePosition.y >= 40 && currentMousePosition.y <= 60) )
				{
					mouseInSubmenu = '2';
				}
				else if ( (currentMousePosition.x >= 2 && currentMousePosition.x <= (menu_file_submenu_bounds.width + 2)) &&(currentMousePosition.y >= 60 && currentMousePosition.y <= 80) )
				{
					mouseInSubmenu = '3';
				}
				else if ( (currentMousePosition.x >= 2 && currentMousePosition.x <= (menu_file_submenu_bounds.width + 2)) &&(currentMousePosition.y >= 80 && currentMousePosition.y <= 100) )
				{
					mouseInSubmenu = '4';
				}
				else if ( (currentMousePosition.x >= 2 && currentMousePosition.x <= (menu_file_submenu_bounds.width + 2)) &&(currentMousePosition.y >= 100 && currentMousePosition.y <= 120) )
				{
					mouseInSubmenu = '5';
				}
				else
				{
					mouseInSubmenu = '0';
				}
			}
			else
			{
				whichSubmenu = '0';
			}
			
			if (usingHiragana)
			{
				menu_file_switchkana.setString("Katakana");
			}
			else
			{
				menu_file_switchkana.setString("Hiragana");
			}
			
			// Associate sf::String stringin with sf::Text textin
			textin.setString(stringin);
			// Define bounds of input text
			textinbounds = textin.getGlobalBounds();
			
			// Associate sf::String stringout with sf::Text textout
			textout.setString(stringout);
			// Define bounds of output text
			textoutbounds = textout.getGlobalBounds();
			
			// Update position of input text cursor
			intextcursor.setPosition(textin.findCharacterPos(stringin.getSize()));
			// Update position of output text cursor
			outtextcursor.setPosition(textout.findCharacterPos(stringout.getSize()));
			
			renderMutex.unlock();
			
// **************************************************************************

			// Allows the CPU to "breathe" (looping in thread is demanding)
			sf::sleep(sf::milliseconds(1));

			renderMutex.lock();
		}

		renderMutex.unlock();
	
	}
	while (userSetResolution);
	
	return 1;
}

// --------------------------------------------------------------------------
//    ---   ---   ---   -  FUNCTION DEFINITIONS  -   ---   ---   ---   ---
// --------------------------------------------------------------------------

// Contains all drawing functions
void renderObjects (renderVariables *variablestruct)
{
//	renderVarInstance.InField = &textinfield;
//	renderVarInstance.OutField = &textoutfield;
//	renderVarInstance.InText = &textin;
//	renderVarInstance.OutText = &textout;
//	renderVarInstance.InCursor = &intextcursor;
//	renderVarInstance.OutCursor = &outtextcursor;
//	renderVarInstance.XGui = &gui;
//	Menu items:
//	renderVarInstance.MouseInArea = &mouseInMenu;
//	renderVarInstance.MouseInSubarea = &mouseInSubmenu;
//	renderVarInstance.ThisSubmenu = &whichSubmenu;
//		File:
//		renderVarInstance.MenuFile = &menu_file;
//		renderVarInstance.MenuFileButtonBox = &menu_file_button_l;
//		renderVarInstance.MenuFileButton = &menu_file_button_b;
//		renderVarInstance.MenuFileSubmenu = &menu_file_submenu_b;
//		Submenu:
//		renderVarInstance.SubmenuButton01 = &menu_file_submenu_button01_b;
//		renderVarInstance.SubmenuButton02 = &menu_file_submenu_button02_b;
//		renderVarInstance.SubmenuButton03 = &menu_file_submenu_button03_b;
//		renderVarInstance.SubmenuButton04 = &menu_file_submenu_button04_b;
//		renderVarInstance.SubmenuButton05 = &menu_file_submenu_button05_b;
//		renderVarInstance.SubmenuSwitchKana = &menu_file_switchkana;
//		renderVarInstance.SubmenuClear = &menu_file_clear;
//		renderVarInstance.SubmenuSave = &menu_file_save;
//		renderVarInstance.SubmenuBlank = &menu_file_blank;
//		renderVarInstance.SubmenuExit = &menu_file_exit;
//	Disclaimer:
//	renderVarInstance.BottomText = &bottomtext;
	
	renderMutex.lock();

	while ( variablestruct->XGui->isOpen() )
	{
		variablestruct->XGui->clear(sf::Color(220,220,220));
		// Draw input text field
		variablestruct->XGui->draw(*(variablestruct->InField));
		// Draw output text field
		variablestruct->XGui->draw(*(variablestruct->OutField));
		// Draw disclamer text
		variablestruct->XGui->draw(*(variablestruct->BottomText));
		

		// If mouse is within "File" menu box area
		if( *(variablestruct->MouseInArea) == 'f' )
		{
			// Draw menu button "File" backshadow
			variablestruct->XGui->draw(*(variablestruct->MenuFileButton));
			// Draw menu button "File" borders
			variablestruct->XGui->draw(*(variablestruct->MenuFileButtonBox));
		}
		
		// Draw input text
		variablestruct->XGui->draw(*(variablestruct->InText));
		// Draw output text
		variablestruct->XGui->draw(*(variablestruct->OutText));
		
		// Fetch MOD10 of current time
		int timemodulus = time(NULL) % 2;
		if (timemodulus == 0 )
		{
			// Draw input text cursor
			variablestruct->XGui->draw(*(variablestruct->InCursor));
			// Draw output text cursor
			variablestruct->XGui->draw(*(variablestruct->OutCursor));
		}
		// If "File" submenu is open
		if( *(variablestruct->ThisSubmenu) == 'f' )
		{
			// Draw "File" submenu box
			variablestruct->XGui->draw(*(variablestruct->MenuFileSubmenu));
			// If mouse is within bounds of button 1 of submenu
			if( *(variablestruct->MouseInSubarea) == '1' )
			{
				// Draw submenu button 1 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton01));
			}
			// If mouse is within bounds of button 2 of submenu
			else if( *(variablestruct->MouseInSubarea) == '2' )
			{
				// Draw submenu button 2 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton02));
			}
			// If mouse is within bounds of button 3 of submenu
			else if( *(variablestruct->MouseInSubarea) == '3' )
			{
				// Draw submenu button 3 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton03));
			}
			// If mouse is within bounds of button 4 of submenu
			else if( *(variablestruct->MouseInSubarea) == '4' )
			{
				// Draw submenu button 4 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton04));
			}
			// If mouse is within bounds of button 5 of submenu
			else if( *(variablestruct->MouseInSubarea) == '5' )
			{
				// Draw submenu button 5 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton05));
			}
			// Draw submenu text for Hiragana/Katakana
			variablestruct->XGui->draw(*(variablestruct->SubmenuSwitchKana));
			// Draw submenu text for Clear all text
			variablestruct->XGui->draw(*(variablestruct->SubmenuClear));
			// Draw submenu text for Save to text file
			variablestruct->XGui->draw(*(variablestruct->SubmenuSave));
			// Draw submenu text for Blank
			variablestruct->XGui->draw(*(variablestruct->SubmenuBlank));
			// Draw submenu text for Exit
			variablestruct->XGui->draw(*(variablestruct->SubmenuExit));
		}
		
		// Draw menu text "File"
		variablestruct->XGui->draw(*(variablestruct->MenuFile));
		variablestruct->XGui->display();
		
		renderMutex.unlock();

		// Allows the CPU to "breathe" (looping in thread is demanding)
		sf::sleep(sf::milliseconds(1));

		renderMutex.lock();
	}
	renderMutex.unlock();
}

/*

// **************************** HIRAGANA ************************************

// Accepts input (stringin) and returns sf::String with corresponding kana
sf::String toHiragana (sf::String InputString)
{
	std::size_t InputLength = InputString.getSize();
	sf::Uint32 lastChar1 = 0;
	sf::Uint32 lastChar2 = 0;
	sf::Uint32 lastChar3 = 0;
	if (InputLength > 0)
		lastChar1 = InputString[(InputLength - 1)];
	if (InputLength > 1)
		lastChar2 = InputString[(InputLength - 2)];
	if (InputLength > 2)
		lastChar3 = InputString[(InputLength - 3)];
	
	// Return string
	sf::String kanaOut;
	// A/a	a
	if (lastChar1 == 65 || lastChar1 == 97)
	{
		// Y/y	ya
		if (lastChar2 == 89 || lastChar2 == 121)
		{
			// K/k	kya
			if (lastChar3 == 75 || lastChar3 == 107)
			{
				lastChar1 = 12365;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// N/n	nya
			else if (lastChar3 == 78 || lastChar3 == 110)
			{
				lastChar1 = 12395;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// H/h	hya
			else if (lastChar3 == 72 || lastChar3 == 104)
			{
				lastChar1 = 12402;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// M/m	mya
			else if (lastChar3 == 77 || lastChar3 == 109)
			{
				lastChar1 = 12415;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// R/r	rya
			else if (lastChar3 == 82 || lastChar3 == 114)
			{
				lastChar1 = 12426;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// G/g	gya
			else if (lastChar3 == 71 || lastChar3 == 103)
			{
				lastChar1 = 12366;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// B/b	bya
			else if (lastChar3 == 66 || lastChar3 == 98)
			{
				lastChar1 = 12403;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// P/p	pya
			else if (lastChar3 == 80 || lastChar3 == 112)
			{
				lastChar1 = 12404;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12420;
				kanaOut += lastChar1;
			}
		}
		// H/h	ha
		else if (lastChar2 == 72 || lastChar2 == 104)
		{
			// S/s	sha
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12375;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			// C/c	cha
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12385;
				kanaOut += lastChar1;
				lastChar2 = 12419;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12399;
				kanaOut += lastChar1;
			}
		}
		// S/s	sa
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			lastChar1 = 12373;
			kanaOut += lastChar1;
		}
		// K/k	ka
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12363;
			kanaOut += lastChar1;
		}
		// T/t	ta
		else if (lastChar2 == 84 || lastChar2 == 116)
		{
			lastChar1 = 12383;
			kanaOut += lastChar1;
		}
		// N/n	na
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12394;
			kanaOut += lastChar1;
		}
		// M/m	ma
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12414;
			kanaOut += lastChar1;
		}
		// R/r	ra
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12425;
			kanaOut += lastChar1;
		}
		// W/w	wa
		else if (lastChar2 == 87 || lastChar2 == 119)
		{
			lastChar1 = 12431;
			kanaOut += lastChar1;
		}
		// G/g	ga
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12364;
			kanaOut += lastChar1;
		}
		// Z/z	za
		else if (lastChar2 == 90 || lastChar2 == 122)
		{
			lastChar1 = 12374;
			kanaOut += lastChar1;
		}
		// D/d	da
		else if (lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12384;
			kanaOut += lastChar1;
		}
		// B/b	ba
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12400;
			kanaOut += lastChar1;
		}
		// P/p	pa
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12401;
			kanaOut += lastChar1;
		}
		// J/j	ja
		else if (lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12376;
			kanaOut += lastChar1;
			lastChar2 = 12419;
			kanaOut += lastChar2;
		}
		else
		{
			lastChar1 = 12354;
			kanaOut += lastChar1;
		}
	}
	// I/i	i
	else if (lastChar1 == 73 || lastChar1 == 105)
	{
		// H/h	hi
		if (lastChar2 == 72 || lastChar2 == 104)
		{
			// S/s	shi
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12375;
				kanaOut += lastChar1;
			}
			// C/c	chi
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12385;
				kanaOut += lastChar1;
			}
			else
			{
				lastChar1 = 12402;
				kanaOut += lastChar1;
			}
		}
		// K/k	ki
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12365;
			kanaOut += lastChar1;
		}
		// N/n	ni
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12395;
			kanaOut += lastChar1;
		}
		// M/m	mi
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12415;
			kanaOut += lastChar1;
		}
		// R/r	ri
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12426;
			kanaOut += lastChar1;
		}
		// G/g	gi
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12366;
			kanaOut += lastChar1;
		}
		// Z/z D/d J/j	ji
		else if (lastChar2 == 90 || lastChar2 == 122 || lastChar2 == 68 || lastChar2 == 100 || lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12376;
			kanaOut += lastChar1;
		}
		// B/b	bi
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12403;
			kanaOut += lastChar1;
		}
		// P/p	pi
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12404;
			kanaOut += lastChar1;
		}
		else
		{
			lastChar1 = 12356;
			kanaOut += lastChar1;
		}
	}
	// U/u	u
	else if (lastChar1 == 85 || lastChar1 == 117)
	{
		// Y/y	yu
		if (lastChar2 == 89 || lastChar2 == 121)
		{
			// K/k	kyu
			if (lastChar3 == 75 || lastChar3 == 107)
			{
				lastChar1 = 12365;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// N/n	nyu
			else if (lastChar3 == 78 || lastChar3 == 110)
			{
				lastChar1 = 12395;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// H/h	hyu
			else if (lastChar3 == 72 || lastChar3 == 104)
			{
				lastChar1 = 12402;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// M/m	myu
			else if (lastChar3 == 77 || lastChar3 == 109)
			{
				lastChar1 = 12415;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// R/r	ryu
			else if (lastChar3 == 82 || lastChar3 == 114)
			{
				lastChar1 = 12426;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// G/g	gyu
			else if (lastChar3 == 71 || lastChar3 == 103)
			{
				lastChar1 = 12366;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// B/b	byu
			else if (lastChar3 == 66 || lastChar3 == 98)
			{
				lastChar1 = 12403;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// P/p	pyu
			else if (lastChar3 == 80 || lastChar3 == 112)
			{
				lastChar1 = 12404;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12422;
				kanaOut += lastChar1;
			}
		}
		// H/h F/f	fu
		else if (lastChar2 == 72 || lastChar2 == 104 || lastChar2 == 70 || lastChar2 == 102)
		{
			// S/s	shu
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12375;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			// C/c	chu
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12385;
				kanaOut += lastChar1;
				lastChar2 = 12421;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12405;
				kanaOut += lastChar1;
			}
		}
		// S/s	su
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			// T/t	tsu
			if (lastChar3 == 84 || lastChar3 == 116)
			{
				lastChar1 = 12388;
				kanaOut += lastChar1;
			}
			else
			{
				lastChar1 = 12377;
				kanaOut += lastChar1;
			}
		}
		// K/k	ku
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12367;
			kanaOut += lastChar1;
		}
		// N/n	nu
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12396;
			kanaOut += lastChar1;
		}
		// M/m	mu
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12416;
			kanaOut += lastChar1;
		}
		// R/r	ru
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12427;
			kanaOut += lastChar1;
		}
		// G/g	gu
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12368;
			kanaOut += lastChar1;
		}
		// Z/z D/d	zu
		else if (lastChar2 == 90 || lastChar2 == 122 || lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12378;
			kanaOut += lastChar1;
		}
		// B/b	bu
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12406;
			kanaOut += lastChar1;
		}
		// P/p	pu
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12407;
			kanaOut += lastChar1;
		}
		// V/v	vu
		else if (lastChar2 == 86 || lastChar2 == 118)
		{
			lastChar1 = 12436;
			kanaOut += lastChar1;
		}
		// J/j	ju
		else if (lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12376;
			kanaOut += lastChar1;
			lastChar2 = 12421;
			kanaOut += lastChar2;
		}
		else
		{
			lastChar1 = 12358;
			kanaOut += lastChar1;
		}
	}
	// E/e	e
	else if (lastChar1 == 69 || lastChar1 == 101)
	{
		// H/h	he
		if (lastChar2 == 72 || lastChar2 == 104)
		{
			lastChar1 = 12408;
			kanaOut += lastChar1;
		}
		// S/s	se
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			lastChar1 = 12379;
			kanaOut += lastChar1;
		}
		// K/k	ke
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12369;
			kanaOut += lastChar1;
		}
		// T/t	te
		else if (lastChar2 == 84 || lastChar2 == 116)
		{
			lastChar1 = 12390;
			kanaOut += lastChar1;
		}
		// N/n	ne
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12397;
			kanaOut += lastChar1;
		}
		// M/m	me
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12417;
			kanaOut += lastChar1;
		}
		// R/r	re
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12428;
			kanaOut += lastChar1;
		}
		// G/g	ge
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12370;
			kanaOut += lastChar1;
		}
		// Z/z	ze
		else if (lastChar2 == 90 || lastChar2 == 122)
		{
			lastChar1 = 12380;
			kanaOut += lastChar1;
		}
		// D/d	de
		else if (lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12391;
			kanaOut += lastChar1;
		}
		// B/b	be
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12409;
			kanaOut += lastChar1;
		}
		// P/p	pe
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12410;
			kanaOut += lastChar1;
		}
		else
		{
			lastChar1 = 12360;
			kanaOut += lastChar1;
		}
	}
	// O/o	o
	else if (lastChar1 == 79 || lastChar1 == 111)
	{
		// Y/y	yo
		if (lastChar2 == 89 || lastChar2 == 121)
		{
			// K/k	kyo
			if (lastChar3 == 75 || lastChar3 == 107)
			{
				lastChar1 = 12365;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// N/n	nyo
			else if (lastChar3 == 78 || lastChar3 == 110)
			{
				lastChar1 = 12395;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// H/h	hyo
			else if (lastChar3 == 72 || lastChar3 == 104)
			{
				lastChar1 = 12402;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// M/m	myo
			else if (lastChar3 == 77 || lastChar3 == 109)
			{
				lastChar1 = 12415;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// R/r	ryo
			else if (lastChar3 == 82 || lastChar3 == 114)
			{
				lastChar1 = 12426;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// G/g	gyo
			else if (lastChar3 == 71 || lastChar3 == 103)
			{
				lastChar1 = 12366;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// B/b	byo
			else if (lastChar3 == 66 || lastChar3 == 98)
			{
				lastChar1 = 12403;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// P/p	pyo
			else if (lastChar3 == 80 || lastChar3 == 112)
			{
				lastChar1 = 12404;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12424;
				kanaOut += lastChar1;
			}
		}
		// H/h	ho
		else if (lastChar2 == 72 || lastChar2 == 104)
		{
			// S/s	sho
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12375;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			// C/c	cho
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12385;
				kanaOut += lastChar1;
				lastChar2 = 12423;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12411;
				kanaOut += lastChar1;
			}
		}
		// S/s	so
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			lastChar1 = 12381;
			kanaOut += lastChar1;
		}
		// K/k	ko
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12371;
			kanaOut += lastChar1;
		}
		// T/t	to
		else if (lastChar2 == 84 || lastChar2 == 116)
		{
			lastChar1 = 12392;
			kanaOut += lastChar1;
		}
		// N/n	no
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12398;
			kanaOut += lastChar1;
		}
		// M/m	mo
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12418;
			kanaOut += lastChar1;
		}
		// R/r	ro
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12429;
			kanaOut += lastChar1;
		}
		// W/w	wo
		else if (lastChar2 == 87 || lastChar2 == 119)
		{
			lastChar1 = 12434;
			kanaOut += lastChar1;
		}
		// G/g	go
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12372;
			kanaOut += lastChar1;
		}
		// Z/z	zo
		else if (lastChar2 == 90 || lastChar2 == 122)
		{
			lastChar1 = 12382;
			kanaOut += lastChar1;
		}
		// D/d	do
		else if (lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12393;
			kanaOut += lastChar1;
		}
		// B/b	bo
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12412;
			kanaOut += lastChar1;
		}
		// P/p	po
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12413;
			kanaOut += lastChar1;
		}
		// J/j	jo
		else if (lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12376;
			kanaOut += lastChar1;
			lastChar2 = 12423;
			kanaOut += lastChar2;
		}
		else
		{
			lastChar1 = 12362;
			kanaOut += lastChar1;
		}
	}
	else if	(
				lastChar1 != 65 && lastChar1 != 97 &&	// !(A/a)
				lastChar1 != 73 && lastChar1 != 105 &&	// !(I/i)
				lastChar1 != 85 && lastChar1 != 117 &&	// !(U/u)
				lastChar1 != 69 && lastChar1 != 101 &&	// !(E/e)
				lastChar1 != 79 && lastChar1 != 111 &&	// !(O/o)
				lastChar1 != 89 && lastChar1 != 121 &&	// !(Y/y)
				(lastChar2 == 78 || lastChar2 == 110)	// N/n
			)
	{
		lastChar1 = 12435;
		kanaOut += lastChar1;
	}

	// N/n
	// else if (lastChar1 == 78 || lastChar1 == 110)
	// {
	//	lastChar1 = 12435;
	//	kanaOut += lastChar1;
	// }

	// ,
	else if (lastChar1 == 44)
	{
		lastChar1 = 12289;
		kanaOut += lastChar1;
	}
	// .
	else if (lastChar1 == 46)
	{
		lastChar1 = 12290;
		kanaOut += lastChar1;
	}
	// "Space"
	else if (lastChar1 == 32)
	{
		lastChar1 = 12288;
		kanaOut += lastChar1;
	}
	// $
	else if (lastChar1 == 36)
	{
		lastChar1 = 165;
		kanaOut += lastChar1;
	}
	// -
	else if (lastChar1 == 45)
	{
		lastChar1 = 12540;
		kanaOut += lastChar1;
	}
	// ~
	else if (lastChar1 == 126)
	{
		lastChar1 = 12316;
		kanaOut += lastChar1;
	}
	// (
	else if (lastChar1 == 40)
	{
		lastChar1 = 12304;
		kanaOut += lastChar1;
	}
	// )
	else if (lastChar1 == 41)
	{
		lastChar1 = 12305;
		kanaOut += lastChar1;
	}
	else if (
				lastChar1 == lastChar2 &&				// double character
				( (lastChar1 > 65 && lastChar1 < 91) || (lastChar1 > 97 && lastChar1 < 123) ) &&	// B-Z , b-z
				lastChar1 != 69 && lastChar1 != 101 &&	// !(E/e)
				lastChar1 != 73 && lastChar1 != 105 &&	// !(I/i)
				lastChar1 != 79 && lastChar1 != 111 &&	// !(O/o)
				lastChar1 != 85 && lastChar1 != 117		// !(U/u)
			)
	{
		lastChar1 = 12387;
		kanaOut += lastChar1;
	}
	// other
	else if ( (lastChar1 > 32 && lastChar1 < 65) || (lastChar1 > 90 && lastChar1 < 96) || (lastChar1 > 122 && lastChar1 < 126) )
	{
		kanaOut += lastChar1;
	}
	return kanaOut;
}

// **************************************************************************

// *********************************** KATAKANA *****************************

sf::String toKatakana (sf::String InputString)
{
	std::size_t InputLength = InputString.getSize();
	sf::Uint32 lastChar1 = 0;
	sf::Uint32 lastChar2 = 0;
	sf::Uint32 lastChar3 = 0;
	if (InputLength > 0)
		lastChar1 = InputString[(InputLength - 1)];
	if (InputLength > 1)
		lastChar2 = InputString[(InputLength - 2)];
	if (InputLength > 2)
		lastChar3 = InputString[(InputLength - 3)];
	
	// Return string
	sf::String kanaOut;
	// A/a	a
	if (lastChar1 == 65 || lastChar1 == 97)
	{
		// Y/y	ya
		if (lastChar2 == 89 || lastChar2 == 121)
		{
			// K/k	kya
			if (lastChar3 == 75 || lastChar3 == 107)
			{
				lastChar1 = 12461;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// N/n	nya
			else if (lastChar3 == 78 || lastChar3 == 110)
			{
				lastChar1 = 12491;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// H/h	hya
			else if (lastChar3 == 72 || lastChar3 == 104)
			{
				lastChar1 = 12498;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// M/m	mya
			else if (lastChar3 == 77 || lastChar3 == 109)
			{
				lastChar1 = 12511;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// R/r	rya
			else if (lastChar3 == 82 || lastChar3 == 114)
			{
				lastChar1 = 12522;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// G/g	gya
			else if (lastChar3 == 71 || lastChar3 == 103)
			{
				lastChar1 = 12462;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// B/b	bya
			else if (lastChar3 == 66 || lastChar3 == 98)
			{
				lastChar1 = 12499;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// P/p	pya
			else if (lastChar3 == 80 || lastChar3 == 112)
			{
				lastChar1 = 12500;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12516;
				kanaOut += lastChar1;
			}
		}
		// H/h	ha
		else if (lastChar2 == 72 || lastChar2 == 104)
		{
			// S/s	sha
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12471;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			// C/c	cha
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12481;
				kanaOut += lastChar1;
				lastChar2 = 12515;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12495;
				kanaOut += lastChar1;
			}
		}
		// S/s	sa
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			lastChar1 = 12469;
			kanaOut += lastChar1;
		}
		// K/k	ka
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12459;
			kanaOut += lastChar1;
		}
		// T/t	ta
		else if (lastChar2 == 84 || lastChar2 == 116)
		{
			lastChar1 = 12479;
			kanaOut += lastChar1;
		}
		// N/n	na
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12490;
			kanaOut += lastChar1;
		}
		// M/m	ma
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12510;
			kanaOut += lastChar1;
		}
		// R/r	ra
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12521;
			kanaOut += lastChar1;
		}
		// W/w	wa
		else if (lastChar2 == 87 || lastChar2 == 119)
		{
			lastChar1 = 12527;
			kanaOut += lastChar1;
		}
		// G/g	ga
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12460;
			kanaOut += lastChar1;
		}
		// Z/z	za
		else if (lastChar2 == 90 || lastChar2 == 122)
		{
			lastChar1 = 12470;
			kanaOut += lastChar1;
		}
		// D/d	da
		else if (lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12480;
			kanaOut += lastChar1;
		}
		// B/b	ba
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12496;
			kanaOut += lastChar1;
		}
		// P/p	pa
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12497;
			kanaOut += lastChar1;
		}
		// J/j	ja
		else if (lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12472;
			kanaOut += lastChar1;
			lastChar2 = 12515;
			kanaOut += lastChar2;
		}
		else
		{
			lastChar1 = 12450;
			kanaOut += lastChar1;
		}
	}
	// I/i	i
	else if (lastChar1 == 73 || lastChar1 == 105)
	{
		// H/h	hi
		if (lastChar2 == 72 || lastChar2 == 104)
		{
			// S/s	shi
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12471;
				kanaOut += lastChar1;
			}
			// C/c	chi
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12481;
				kanaOut += lastChar1;
			}
			else
			{
				lastChar1 = 12498;
				kanaOut += lastChar1;
			}
		}
		// K/k	ki
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12461;
			kanaOut += lastChar1;
		}
		// N/n	ni
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12491;
			kanaOut += lastChar1;
		}
		// M/m	mi
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12511;
			kanaOut += lastChar1;
		}
		// R/r	ri
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12522;
			kanaOut += lastChar1;
		}
		// G/g	gi
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12462;
			kanaOut += lastChar1;
		}
		// Z/z D/d J/j	ji
		else if (lastChar2 == 90 || lastChar2 == 122 || lastChar2 == 68 || lastChar2 == 100 || lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12472;
			kanaOut += lastChar1;
		}
		// B/b	bi
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12499;
			kanaOut += lastChar1;
		}
		// P/p	pi
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12500;
			kanaOut += lastChar1;
		}
		else
		{
			lastChar1 = 12452;
			kanaOut += lastChar1;
		}
	}
	// U/u	u
	else if (lastChar1 == 85 || lastChar1 == 117)
	{
		// Y/y	yu
		if (lastChar2 == 89 || lastChar2 == 121)
		{
			// K/k	kyu
			if (lastChar3 == 75 || lastChar3 == 107)
			{
				lastChar1 = 12461;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// N/n	nyu
			else if (lastChar3 == 78 || lastChar3 == 110)
			{
				lastChar1 = 12491;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// H/h	hyu
			else if (lastChar3 == 72 || lastChar3 == 104)
			{
				lastChar1 = 12498;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// M/m	myu
			else if (lastChar3 == 77 || lastChar3 == 109)
			{
				lastChar1 = 12511;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// R/r	ryu
			else if (lastChar3 == 82 || lastChar3 == 114)
			{
				lastChar1 = 12522;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// G/g	gyu
			else if (lastChar3 == 71 || lastChar3 == 103)
			{
				lastChar1 = 12462;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// B/b	byu
			else if (lastChar3 == 66 || lastChar3 == 98)
			{
				lastChar1 = 12499;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// P/p	pyu
			else if (lastChar3 == 80 || lastChar3 == 112)
			{
				lastChar1 = 12500;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12518;
				kanaOut += lastChar1;
			}
		}
		// H/h F/f	fu
		else if (lastChar2 == 72 || lastChar2 == 104 || lastChar2 == 70 || lastChar2 == 102)
		{
			// S/s	shu
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12471;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			// C/c	chu
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12481;
				kanaOut += lastChar1;
				lastChar2 = 12517;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12501;
				kanaOut += lastChar1;
			}
		}
		// S/s	su
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			// T/t	tsu
			if (lastChar3 == 84 || lastChar3 == 116)
			{
				lastChar1 = 12484;
				kanaOut += lastChar1;
			}
			else
			{
				lastChar1 = 12473;
				kanaOut += lastChar1;
			}
		}
		// K/k	ku
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12463;
			kanaOut += lastChar1;
		}
		// N/n	nu
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12492;
			kanaOut += lastChar1;
		}
		// M/m	mu
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12512;
			kanaOut += lastChar1;
		}
		// R/r	ru
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12523;
			kanaOut += lastChar1;
		}
		// G/g	gu
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12464;
			kanaOut += lastChar1;
		}
		// Z/z D/d	zu
		else if (lastChar2 == 90 || lastChar2 == 122 || lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12474;
			kanaOut += lastChar1;
		}
		// B/b	bu
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12502;
			kanaOut += lastChar1;
		}
		// P/p	pu
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12503;
			kanaOut += lastChar1;
		}
		// V/v	vu
		else if (lastChar2 == 86 || lastChar2 == 118)
		{
			lastChar1 = 12532;
			kanaOut += lastChar1;
		}
		// J/j	ju
		else if (lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12472;
			kanaOut += lastChar1;
			lastChar2 = 12517;
			kanaOut += lastChar2;
		}
		else
		{
			lastChar1 = 12454;
			kanaOut += lastChar1;
		}
	}
	// E/e	e
	else if (lastChar1 == 69 || lastChar1 == 101)
	{
		// H/h	he
		if (lastChar2 == 72 || lastChar2 == 104)
		{
			lastChar1 = 12504;
			kanaOut += lastChar1;
		}
		// S/s	se
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			lastChar1 = 12475;
			kanaOut += lastChar1;
		}
		// K/k	ke
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12465;
			kanaOut += lastChar1;
		}
		// T/t	te
		else if (lastChar2 == 84 || lastChar2 == 116)
		{
			lastChar1 = 12486;
			kanaOut += lastChar1;
		}
		// N/n	ne
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12493;
			kanaOut += lastChar1;
		}
		// M/m	me
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12513;
			kanaOut += lastChar1;
		}
		// R/r	re
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12524;
			kanaOut += lastChar1;
		}
		// G/g	ge
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12466;
			kanaOut += lastChar1;
		}
		// Z/z	ze
		else if (lastChar2 == 90 || lastChar2 == 122)
		{
			lastChar1 = 12476;
			kanaOut += lastChar1;
		}
		// D/d	de
		else if (lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12487;
			kanaOut += lastChar1;
		}
		// B/b	be
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12505;
			kanaOut += lastChar1;
		}
		// P/p	pe
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12506;
			kanaOut += lastChar1;
		}
		else
		{
			lastChar1 = 12456;
			kanaOut += lastChar1;
		}
	}
	// O/o	o
	else if (lastChar1 == 79 || lastChar1 == 111)
	{
		// Y/y	yo
		if (lastChar2 == 89 || lastChar2 == 121)
		{
			// K/k	kyo
			if (lastChar3 == 75 || lastChar3 == 107)
			{
				lastChar1 = 12461;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// N/n	nyo
			else if (lastChar3 == 78 || lastChar3 == 110)
			{
				lastChar1 = 12491;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// H/h	hyo
			else if (lastChar3 == 72 || lastChar3 == 104)
			{
				lastChar1 = 12498;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// M/m	myo
			else if (lastChar3 == 77 || lastChar3 == 109)
			{
				lastChar1 = 12511;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// R/r	ryo
			else if (lastChar3 == 82 || lastChar3 == 114)
			{
				lastChar1 = 12522;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// G/g	gyo
			else if (lastChar3 == 71 || lastChar3 == 103)
			{
				lastChar1 = 12462;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// B/b	byo
			else if (lastChar3 == 66 || lastChar3 == 98)
			{
				lastChar1 = 12499;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// P/p	pyo
			else if (lastChar3 == 80 || lastChar3 == 112)
			{
				lastChar1 = 12500;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12520;
				kanaOut += lastChar1;
			}
		}
		// H/h	ho
		else if (lastChar2 == 72 || lastChar2 == 104)
		{
			// S/s	sho
			if (lastChar3 == 83 || lastChar3 == 115)
			{
				lastChar1 = 12471;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			// C/c	cho
			else if (lastChar3 == 67 || lastChar3 == 99)
			{
				lastChar1 = 12481;
				kanaOut += lastChar1;
				lastChar2 = 12519;
				kanaOut += lastChar2;
			}
			else
			{
				lastChar1 = 12507;
				kanaOut += lastChar1;
			}
		}
		// S/s	so
		else if (lastChar2 == 83 || lastChar2 == 115)
		{
			lastChar1 = 12477;
			kanaOut += lastChar1;
		}
		// K/k	ko
		else if (lastChar2 == 75 || lastChar2 == 107)
		{
			lastChar1 = 12467;
			kanaOut += lastChar1;
		}
		// T/t	to
		else if (lastChar2 == 84 || lastChar2 == 116)
		{
			lastChar1 = 12488;
			kanaOut += lastChar1;
		}
		// N/n	no
		else if (lastChar2 == 78 || lastChar2 == 110)
		{
			lastChar1 = 12494;
			kanaOut += lastChar1;
		}
		// M/m	mo
		else if (lastChar2 == 77 || lastChar2 == 109)
		{
			lastChar1 = 12514;
			kanaOut += lastChar1;
		}
		// R/r	ro
		else if (lastChar2 == 82 || lastChar2 == 114)
		{
			lastChar1 = 12525;
			kanaOut += lastChar1;
		}
		// W/w	wo
		else if (lastChar2 == 87 || lastChar2 == 119)
		{
			lastChar1 = 12530;
			kanaOut += lastChar1;
		}
		// G/g	go
		else if (lastChar2 == 71 || lastChar2 == 103)
		{
			lastChar1 = 12468;
			kanaOut += lastChar1;
		}
		// Z/z	zo
		else if (lastChar2 == 90 || lastChar2 == 122)
		{
			lastChar1 = 12478;
			kanaOut += lastChar1;
		}
		// D/d	do
		else if (lastChar2 == 68 || lastChar2 == 100)
		{
			lastChar1 = 12489;
			kanaOut += lastChar1;
		}
		// B/b	bo
		else if (lastChar2 == 66 || lastChar2 == 98)
		{
			lastChar1 = 12508;
			kanaOut += lastChar1;
		}
		// P/p	po
		else if (lastChar2 == 80 || lastChar2 == 112)
		{
			lastChar1 = 12509;
			kanaOut += lastChar1;
		}
		// J/j	jo
		else if (lastChar2 == 74 || lastChar2 == 106)
		{
			lastChar1 = 12472;
			kanaOut += lastChar1;
			lastChar2 = 12519;
			kanaOut += lastChar2;
		}
		else
		{
			lastChar1 = 12458;
			kanaOut += lastChar1;
		}
	}
	else if	(
				lastChar1 != 65 && lastChar1 != 97 &&	// !(A/a)
				lastChar1 != 73 && lastChar1 != 105 &&	// !(I/i)
				lastChar1 != 85 && lastChar1 != 117 &&	// !(U/u)
				lastChar1 != 69 && lastChar1 != 101 &&	// !(E/e)
				lastChar1 != 79 && lastChar1 != 111 &&	// !(O/o)
				lastChar1 != 89 && lastChar1 != 121 &&	// !(Y/y)
				(lastChar2 == 78 || lastChar2 == 110)	// N/n
			)
	{
		lastChar1 = 12531;
		kanaOut += lastChar1;
	}

	// N/n
	// else if (lastChar1 == 78 || lastChar1 == 110)
	// {
	//	lastChar1 = 12531;
	//	kanaOut += lastChar1;
	// }

	// ,
	else if (lastChar1 == 44)
	{
		lastChar1 = 12289;
		kanaOut += lastChar1;
	}
	// .
	else if (lastChar1 == 46)
	{
		lastChar1 = 12290;
		kanaOut += lastChar1;
	}
	// "Space"
	else if (lastChar1 == 32)
	{
		lastChar1 = 12288;
		kanaOut += lastChar1;
	}
	// $
	else if (lastChar1 == 36)
	{
		lastChar1 = 165;
		kanaOut += lastChar1;
	}
	// -
	else if (lastChar1 == 45)
	{
		lastChar1 = 12540;
		kanaOut += lastChar1;
	}
	// ~
	else if (lastChar1 == 126)
	{
		lastChar1 = 12316;
		kanaOut += lastChar1;
	}
	// (
	else if (lastChar1 == 40)
	{
		lastChar1 = 12304;
		kanaOut += lastChar1;
	}
	// )
	else if (lastChar1 == 41)
	{
		lastChar1 = 12305;
		kanaOut += lastChar1;
	}
	else if (
				lastChar1 == lastChar2 &&				// double character
				( (lastChar1 > 65 && lastChar1 < 91) || (lastChar1 > 97 && lastChar1 < 123) ) && // B-Z , b-z
				lastChar1 != 69 && lastChar1 != 101 &&	// !(E/e)
				lastChar1 != 73 && lastChar1 != 105 &&	// !(I/i)
				lastChar1 != 79 && lastChar1 != 111 &&	// !(O/o)
				lastChar1 != 85 && lastChar1 != 117		// !(U/u)
			)
	{
		lastChar1 = 12483;
		kanaOut += lastChar1;
	}
	// other
	else if ( (lastChar1 > 32 && lastChar1 < 65) || (lastChar1 > 90 && lastChar1 < 96) || (lastChar1 > 122 && lastChar1 < 126) )
	{
		kanaOut += lastChar1;
	}
	return kanaOut;
}

// **************************************************************************

// ************************* CONCATENATE ************************************

// Takes struct containing references and concatenates to stringout
void concatenateKana (threadVariables variablestruct)
{
	// variablestruct.InputString = &stringin;
	// variablestruct.OutputString = &stringout;
	// variablestruct.inHiragana = &usingHiragana;
	
	sf::String intermediate;
	if ( *(variablestruct.inHiragana) )
	{
		// Convert last few characters to hiragana character
		intermediate += toHiragana( *(variablestruct.InputString) );
		if (!(intermediate[0] == NULL))
		{
			// Concatenate hiragana to stringout
			*(variablestruct.OutputString) += intermediate;
		}
	}
	else
	{
		// Convert last few characters to hiragana character
		intermediate += toKatakana( *(variablestruct.InputString) );
		if (!(intermediate[0] == NULL))
		{
			// Concatenate hiragana to stringout
			*(variablestruct.OutputString) += intermediate;
		}
	}
}

// **************************************************************************

// *********************** KANA BACKSPACE ***********************************

void kanaBackspace (threadVariables variablestruct)
{
	// variablestruct.InputString = &stringin;
	// variablestruct.OutputString = &stringout;
	// variablestruct.inHiragana = &usingHiragana;

	// Get last 3 characters from stringin
	std::size_t InputLength = variablestruct.InputString->getSize();
	sf::Uint32 inlastChar1 = 0;
	sf::Uint32 inlastChar2 = 0;
	sf::Uint32 inlastChar3 = 0;
	if (InputLength > 0)
		inlastChar1 = (*(variablestruct.InputString))[(InputLength - 1)];
	if (InputLength > 1)
		inlastChar2 = (*(variablestruct.InputString))[(InputLength - 2)];
	if (InputLength > 2)
		inlastChar3 = (*(variablestruct.InputString))[(InputLength - 3)];
	
	// Get last 2 characters from stringout
	std::size_t OutputLength = variablestruct.OutputString->getSize();
	sf::Uint32 outlastChar1 = 0;
	sf::Uint32 outlastChar2 = 0;
	if (OutputLength > 0)
		outlastChar1 = (*(variablestruct.OutputString))[(OutputLength - 1)];
	if (OutputLength > 1)
		outlastChar2 = (*(variablestruct.OutputString))[(OutputLength - 2)];
	
	
	// A/a	a
	if (inlastChar1 == 65 || inlastChar1 == 97)
	{
		// Y/y	ya
		if (inlastChar2 == 89 || inlastChar2 == 121)
		{
			// K/k	kya
			if (inlastChar3 == 75 || inlastChar3 == 107)
			{
				if ( (outlastChar2 == 12365 && outlastChar1 == 12419) || (outlastChar2 == 12461 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// N/n	nya
			else if (inlastChar3 == 78 || inlastChar3 == 110)
			{
				if ( (outlastChar2 == 12395 && outlastChar1 == 12419) || (outlastChar2 == 12491 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// H/h	hya
			else if (inlastChar3 == 72 || inlastChar3 == 104)
			{
				if ( (outlastChar2 == 12402 && outlastChar1 == 12419) || (outlastChar2 == 12498 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// M/m	mya
			else if (inlastChar3 == 77 || inlastChar3 == 109)
			{
				if ( (outlastChar2 == 12415 && outlastChar1 == 12419) || (outlastChar2 == 12511 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// R/r	rya
			else if (inlastChar3 == 82 || inlastChar3 == 114)
			{
				if ( (outlastChar2 == 12426 && outlastChar1 == 12419) || (outlastChar2 == 12522 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// G/g	gya
			else if (inlastChar3 == 71 || inlastChar3 == 103)
			{
				if ( (outlastChar2 == 12366 && outlastChar1 == 12419) || (outlastChar2 == 12462 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// B/b	bya
			else if (inlastChar3 == 66 || inlastChar3 == 98)
			{
				if ( (outlastChar2 == 12403 && outlastChar1 == 12419) || (outlastChar2 == 12499 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// P/p	pya
			else if (inlastChar3 == 80 || inlastChar3 == 112)
			{
				if ( (outlastChar2 == 12404 && outlastChar1 == 12419) || (outlastChar2 == 12500 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			else
			{
				if ( outlastChar1 == 12420 || outlastChar1 == 12516 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// H/h	ha
		else if (inlastChar2 == 72 || inlastChar2 == 104)
		{
			// S/s	sha
			if (inlastChar3 == 83 || inlastChar3 == 115)
			{
				if ( (outlastChar2 == 12375 && outlastChar1 == 12419) || (outlastChar2 == 12471 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// C/c	cha
			else if (inlastChar3 == 67 || inlastChar3 == 99)
			{
				if ( (outlastChar2 == 12385 && outlastChar1 == 12419) || (outlastChar2 == 12481 && outlastChar1 == 12515) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			else
			{
				if ( outlastChar1 == 12399 || outlastChar1 == 12495 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// S/s	sa
		else if (inlastChar2 == 83 || inlastChar2 == 115)
		{
			if ( outlastChar1 == 12373 || outlastChar1 == 12469 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// K/k	ka
		else if (inlastChar2 == 75 || inlastChar2 == 107)
		{
			if ( outlastChar1 == 12363 || outlastChar1 == 12459 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// T/t	ta
		else if (inlastChar2 == 84 || inlastChar2 == 116)
		{
			if ( outlastChar1 == 12383 || outlastChar1 == 12479 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// N/n	na
		else if (inlastChar2 == 78 || inlastChar2 == 110)
		{
			if ( outlastChar1 == 12394 || outlastChar1 == 12490 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// M/m	ma
		else if (inlastChar2 == 77 || inlastChar2 == 109)
		{
			if ( outlastChar1 == 12414 || outlastChar1 == 12510 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// R/r	ra
		else if (inlastChar2 == 82 || inlastChar2 == 114)
		{
			if ( outlastChar1 == 12425 || outlastChar1 == 12521 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// W/w	wa
		else if (inlastChar2 == 87 || inlastChar2 == 119)
		{
			if ( outlastChar1 == 12431 || outlastChar1 == 12527 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// G/g	ga
		else if (inlastChar2 == 71 || inlastChar2 == 103)
		{
			if ( outlastChar1 == 12364 || outlastChar1 == 12460 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// Z/z	za
		else if (inlastChar2 == 90 || inlastChar2 == 122)
		{
			if ( outlastChar1 == 12374 || outlastChar1 == 12470 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// D/d	da
		else if (inlastChar2 == 68 || inlastChar2 == 100)
		{
			if ( outlastChar1 == 12384 || outlastChar1 == 12480 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// B/b	ba
		else if (inlastChar2 == 66 || inlastChar2 == 98)
		{
			if ( outlastChar1 == 12400 || outlastChar1 == 12496 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// P/p	pa
		else if (inlastChar2 == 80 || inlastChar2 == 112)
		{
			if ( outlastChar1 == 12401 || outlastChar1 == 12497 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// J/j	ja
		else if (inlastChar2 == 74 || inlastChar2 == 106)
		{
			if ( (outlastChar2 == 12376 && outlastChar1 == 12419) || (outlastChar2 == 12472 && outlastChar1 == 12515) )
			{
				variablestruct.OutputString->erase((OutputLength - 2), 2);
			}
		}
		else
		{
			if ( outlastChar1 == 12354 || outlastChar1 == 12450 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
	}
	// I/i	i
	else if (inlastChar1 == 73 || inlastChar1 == 105)
	{
		// H/h	hi
		if (inlastChar2 == 72 || inlastChar2 == 104)
		{
			// S/s	shi
			if (inlastChar3 == 83 || inlastChar3 == 115)
			{
				if ( outlastChar1 == 12375 || outlastChar1 == 12471 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
			// C/c	chi
			else if (inlastChar3 == 67 || inlastChar3 == 99)
			{
				if ( outlastChar1 == 12385 || outlastChar1 == 12481 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
			else
			{
				if ( outlastChar1 == 12402 || outlastChar1 == 12498 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// K/k	ki
		else if (inlastChar2 == 75 || inlastChar2 == 107)
		{
			if ( outlastChar1 == 12365 || outlastChar1 == 12461 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// N/n	ni
		else if (inlastChar2 == 78 || inlastChar2 == 110)
		{
			if ( outlastChar1 == 12395 || outlastChar1 == 12491 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// M/m	mi
		else if (inlastChar2 == 77 || inlastChar2 == 109)
		{
			if ( outlastChar1 == 12415 || outlastChar1 == 12511 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// R/r	ri
		else if (inlastChar2 == 82 || inlastChar2 == 114)
		{
			if ( outlastChar1 == 12426 || outlastChar1 == 12522 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// G/g	gi
		else if (inlastChar2 == 71 || inlastChar2 == 103)
		{
			if ( outlastChar1 == 12366 || outlastChar1 == 12462 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// Z/z D/d J/j	ji
		else if (inlastChar2 == 90 || inlastChar2 == 122 || inlastChar2 == 68 || inlastChar2 == 100 || inlastChar2 == 74 || inlastChar2 == 106)
		{
			if ( outlastChar1 == 12376 || outlastChar1 == 12472 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// B/b	bi
		else if (inlastChar2 == 66 || inlastChar2 == 98)
		{
			if ( outlastChar1 == 12403 || outlastChar1 == 12499 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// P/p	pi
		else if (inlastChar2 == 80 || inlastChar2 == 112)
		{
			if ( outlastChar1 == 12404 || outlastChar1 == 12500 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		else
		{
			if ( outlastChar1 == 12356 || outlastChar1 == 12452 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
	}
	// U/u	u
	else if (inlastChar1 == 85 || inlastChar1 == 117)
	{
		// Y/y	yu
		if (inlastChar2 == 89 || inlastChar2 == 121)
		{
			// K/k	kyu
			if (inlastChar3 == 75 || inlastChar3 == 107)
			{
				if ( (outlastChar2 == 12365 && outlastChar1 == 12421) || (outlastChar2 == 12461 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// N/n	nyu
			else if (inlastChar3 == 78 || inlastChar3 == 110)
			{
				if ( (outlastChar2 == 12395 && outlastChar1 == 12421) || (outlastChar2 == 12491 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// H/h	hyu
			else if (inlastChar3 == 72 || inlastChar3 == 104)
			{
				if ( (outlastChar2 == 12402 && outlastChar1 == 12421) || (outlastChar2 == 12498 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// M/m	myu
			else if (inlastChar3 == 77 || inlastChar3 == 109)
			{
				if ( (outlastChar2 == 12415 && outlastChar1 == 12421) || (outlastChar2 == 12511 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// R/r	ryu
			else if (inlastChar3 == 82 || inlastChar3 == 114)
			{
				if ( (outlastChar2 == 12426 && outlastChar1 == 12421) || (outlastChar2 == 12522 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// G/g	gyu
			else if (inlastChar3 == 71 || inlastChar3 == 103)
			{
				if ( (outlastChar2 == 12366 && outlastChar1 == 12421) || (outlastChar2 == 12462 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// B/b	byu
			else if (inlastChar3 == 66 || inlastChar3 == 98)
			{
				if ( (outlastChar2 == 12403 && outlastChar1 == 12421) || (outlastChar2 == 12499 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// P/p	pyu
			else if (inlastChar3 == 80 || inlastChar3 == 112)
			{
				if ( (outlastChar2 == 12404 && outlastChar1 == 12421) || (outlastChar2 == 12500 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			else
			{
				if ( outlastChar1 == 12422 || outlastChar1 == 12518 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// H/h F/f	fu
		else if (inlastChar2 == 72 || inlastChar2 == 104 || inlastChar2 == 70 || inlastChar2 == 102)
		{
			// S/s	shu
			if (inlastChar3 == 83 || inlastChar3 == 115)
			{
				if ( (outlastChar2 == 12375 && outlastChar1 == 12421) || (outlastChar2 == 12471 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// C/c	chu
			else if (inlastChar3 == 67 || inlastChar3 == 99)
			{
				if ( (outlastChar2 == 12385 && outlastChar1 == 12421) || (outlastChar2 == 12481 && outlastChar1 == 12517) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			else
			{
				if ( outlastChar1 == 12405 || outlastChar1 == 12501 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// S/s	su
		else if (inlastChar2 == 83 || inlastChar2 == 115)
		{
			// T/t	tsu
			if (inlastChar3 == 84 || inlastChar3 == 116)
			{
				if ( outlastChar1 == 12388 || outlastChar1 == 12484 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
			else
			{
				if ( outlastChar1 == 12377 || outlastChar1 == 12473 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// K/k	ku
		else if (inlastChar2 == 75 || inlastChar2 == 107)
		{
			if ( outlastChar1 == 12367 || outlastChar1 == 12463 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// N/n	nu
		else if (inlastChar2 == 78 || inlastChar2 == 110)
		{
			if ( outlastChar1 == 12396 || outlastChar1 == 12492 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// M/m	mu
		else if (inlastChar2 == 77 || inlastChar2 == 109)
		{
			if ( outlastChar1 == 12416 || outlastChar1 == 12512 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// R/r	ru
		else if (inlastChar2 == 82 || inlastChar2 == 114)
		{
			if ( outlastChar1 == 12427 || outlastChar1 == 12523 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// G/g	gu
		else if (inlastChar2 == 71 || inlastChar2 == 103)
		{
			if ( outlastChar1 == 12368 || outlastChar1 == 12464 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// Z/z D/d	zu
		else if (inlastChar2 == 90 || inlastChar2 == 122 || inlastChar2 == 68 || inlastChar2 == 100)
		{
			if ( outlastChar1 == 12378 || outlastChar1 == 12474 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// B/b	bu
		else if (inlastChar2 == 66 || inlastChar2 == 98)
		{
			if ( outlastChar1 == 12406 || outlastChar1 == 12502 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// P/p	pu
		else if (inlastChar2 == 80 || inlastChar2 == 112)
		{
			if ( outlastChar1 == 12407 || outlastChar1 == 12503 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// V/v	vu
		else if (inlastChar2 == 86 || inlastChar2 == 118)
		{
			if ( outlastChar1 == 12436 || outlastChar1 == 12532 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// J/j	ju
		else if (inlastChar2 == 74 || inlastChar2 == 106)
		{
			if ( (outlastChar2 == 12376 && outlastChar1 == 12421) || (outlastChar2 == 12472 && outlastChar1 == 12517) )
			{
				variablestruct.OutputString->erase((OutputLength - 2), 2);
			}
		}
		else
		{
			if ( outlastChar1 == 12358 || outlastChar1 == 12454 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
	}
	// E/e	e
	else if (inlastChar1 == 69 || inlastChar1 == 101)
	{
		// H/h	he
		if (inlastChar2 == 72 || inlastChar2 == 104)
		{
			if ( outlastChar1 == 12408 || outlastChar1 == 12504 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// S/s	se
		else if (inlastChar2 == 83 || inlastChar2 == 115)
		{
			if ( outlastChar1 == 12379 || outlastChar1 == 12475 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// K/k	ke
		else if (inlastChar2 == 75 || inlastChar2 == 107)
		{
			if ( outlastChar1 == 12369 || outlastChar1 == 12465 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// T/t	te
		else if (inlastChar2 == 84 || inlastChar2 == 116)
		{
			if ( outlastChar1 == 12390 || outlastChar1 == 12486 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// N/n	ne
		else if (inlastChar2 == 78 || inlastChar2 == 110)
		{
			if ( outlastChar1 == 12397 || outlastChar1 == 12493 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// M/m	me
		else if (inlastChar2 == 77 || inlastChar2 == 109)
		{
			if ( outlastChar1 == 12417 || outlastChar1 == 12513 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// R/r	re
		else if (inlastChar2 == 82 || inlastChar2 == 114)
		{
			if ( outlastChar1 == 12428 || outlastChar1 == 12524 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// G/g	ge
		else if (inlastChar2 == 71 || inlastChar2 == 103)
		{
			if ( outlastChar1 == 12370 || outlastChar1 == 12466 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// Z/z	ze
		else if (inlastChar2 == 90 || inlastChar2 == 122)
		{
			if ( outlastChar1 == 12380 || outlastChar1 == 12476 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// D/d	de
		else if (inlastChar2 == 68 || inlastChar2 == 100)
		{
			if ( outlastChar1 == 12391 || outlastChar1 == 12487 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// B/b	be
		else if (inlastChar2 == 66 || inlastChar2 == 98)
		{
			if ( outlastChar1 == 12409 || outlastChar1 == 12505 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// P/p	pe
		else if (inlastChar2 == 80 || inlastChar2 == 112)
		{
			if ( outlastChar1 == 12410 || outlastChar1 == 12506 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		else
		{
			if ( outlastChar1 == 12360 || outlastChar1 == 12456 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
	}
	// O/o	o
	else if (inlastChar1 == 79 || inlastChar1 == 111)
	{
		// Y/y	yo
		if (inlastChar2 == 89 || inlastChar2 == 121)
		{
			// K/k	kyo
			if (inlastChar3 == 75 || inlastChar3 == 107)
			{
				if ( (outlastChar2 == 12365 && outlastChar1 == 12423) || (outlastChar2 == 12461 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// N/n	nyo
			else if (inlastChar3 == 78 || inlastChar3 == 110)
			{
				if ( (outlastChar2 == 12395 && outlastChar1 == 12423) || (outlastChar2 == 12491 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// H/h	hyo
			else if (inlastChar3 == 72 || inlastChar3 == 104)
			{
				if ( (outlastChar2 == 12402 && outlastChar1 == 12423) || (outlastChar2 == 12498 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// M/m	myo
			else if (inlastChar3 == 77 || inlastChar3 == 109)
			{
				if ( (outlastChar2 == 12415 && outlastChar1 == 12423) || (outlastChar2 == 12511 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// R/r	ryo
			else if (inlastChar3 == 82 || inlastChar3 == 114)
			{
				if ( (outlastChar2 == 12426 && outlastChar1 == 12423) || (outlastChar2 == 12522 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// G/g	gyo
			else if (inlastChar3 == 71 || inlastChar3 == 103)
			{
				if ( (outlastChar2 == 12366 && outlastChar1 == 12423) || (outlastChar2 == 12462 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// B/b	byo
			else if (inlastChar3 == 66 || inlastChar3 == 98)
			{
				if ( (outlastChar2 == 12403 && outlastChar1 == 12423) || (outlastChar2 == 12499 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// P/p	pyo
			else if (inlastChar3 == 80 || inlastChar3 == 112)
			{
				if ( (outlastChar2 == 12404 && outlastChar1 == 12423) || (outlastChar2 == 12500 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			else
			{
				if ( outlastChar1 == 12424 || outlastChar1 == 12520 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// H/h	ho
		else if (inlastChar2 == 72 || inlastChar2 == 104)
		{
			// S/s	sho
			if (inlastChar3 == 83 || inlastChar3 == 115)
			{
				if ( (outlastChar2 == 12375 && outlastChar1 == 12423) || (outlastChar2 == 12471 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			// C/c	cho
			else if (inlastChar3 == 67 || inlastChar3 == 99)
			{
				if ( (outlastChar2 == 12385 && outlastChar1 == 12423) || (outlastChar2 == 12481 && outlastChar1 == 12519) )
				{
					variablestruct.OutputString->erase((OutputLength - 2), 2);
				}
			}
			else
			{
				if ( outlastChar1 == 12411 || outlastChar1 == 12507 )
				{
					variablestruct.OutputString->erase((OutputLength - 1), 1);
				}
			}
		}
		// S/s	so
		else if (inlastChar2 == 83 || inlastChar2 == 115)
		{
			if ( outlastChar1 == 12381 || outlastChar1 == 12477 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// K/k	ko
		else if (inlastChar2 == 75 || inlastChar2 == 107)
		{
			if ( outlastChar1 == 12371 || outlastChar1 == 12467 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// T/t	to
		else if (inlastChar2 == 84 || inlastChar2 == 116)
		{
			if ( outlastChar1 == 12392 || outlastChar1 == 12488 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// N/n	no
		else if (inlastChar2 == 78 || inlastChar2 == 110)
		{
			if ( outlastChar1 == 12398 || outlastChar1 == 12494 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// M/m	mo
		else if (inlastChar2 == 77 || inlastChar2 == 109)
		{
			if ( outlastChar1 == 12418 || outlastChar1 == 12514 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// R/r	ro
		else if (inlastChar2 == 82 || inlastChar2 == 114)
		{
			if ( outlastChar1 == 12429 || outlastChar1 == 12525 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// W/w	wo
		else if (inlastChar2 == 87 || inlastChar2 == 119)
		{
			if ( outlastChar1 == 12434 || outlastChar1 == 12530 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// G/g	go
		else if (inlastChar2 == 71 || inlastChar2 == 103)
		{
			if ( outlastChar1 == 12372 || outlastChar1 == 12468 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// Z/z	zo
		else if (inlastChar2 == 90 || inlastChar2 == 122)
		{
			if ( outlastChar1 == 12382 || outlastChar1 == 12478 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// D/d	do
		else if (inlastChar2 == 68 || inlastChar2 == 100)
		{
			if ( outlastChar1 == 12393 || outlastChar1 == 12489 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// B/b	bo
		else if (inlastChar2 == 66 || inlastChar2 == 98)
		{
			if ( outlastChar1 == 12412 || outlastChar1 == 12508 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// P/p	po
		else if (inlastChar2 == 80 || inlastChar2 == 112)
		{
			if ( outlastChar1 == 12413 || outlastChar1 == 12509 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
		// J/j	jo
		else if (inlastChar2 == 74 || inlastChar2 == 106)
		{
			if ( (outlastChar2 == 12376 && outlastChar1 == 12423) || (outlastChar2 == 12472 && outlastChar1 == 12519) )
			{
				variablestruct.OutputString->erase((OutputLength - 2), 2);
			}
		}
		else
		{
			if ( outlastChar1 == 12362 || outlastChar1 == 12458 )
			{
				variablestruct.OutputString->erase((OutputLength - 1), 1);
			}
		}
	}
	else if	(
				inlastChar1 != 65 && inlastChar1 != 97 &&	// !(A/a)
				inlastChar1 != 73 && inlastChar1 != 105 &&	// !(I/i)
				inlastChar1 != 85 && inlastChar1 != 117 &&	// !(U/u)
				inlastChar1 != 69 && inlastChar1 != 101 &&	// !(E/e)
				inlastChar1 != 79 && inlastChar1 != 111 &&	// !(O/o)
				inlastChar1 != 89 && inlastChar1 != 121 &&	// !(Y/y)
				(inlastChar2 == 78 || inlastChar2 == 110)	// N/n
			)
	{
		if ( outlastChar1 == 12435 || outlastChar1 == 12531 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// ,
	else if (inlastChar1 == 44)
	{
		if ( outlastChar1 == 12289 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// .
	else if (inlastChar1 == 46)
	{
		if ( outlastChar1 == 12290 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// "Space"
	else if (inlastChar1 == 32)
	{
		if ( outlastChar1 == 12288 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// $
	else if (inlastChar1 == 36)
	{
		if ( outlastChar1 == 165 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// -
	else if (inlastChar1 == 45)
	{
		if ( outlastChar1 == 12540 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// ~
	else if (inlastChar1 == 126)
	{
		if ( outlastChar1 == 12316 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// (
	else if (inlastChar1 == 40)
	{
		if ( outlastChar1 == 12304 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// )
	else if (inlastChar1 == 41)
	{
		if ( outlastChar1 == 12305 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	else if (
				inlastChar1 == inlastChar2 &&				// double character
				( (inlastChar1 > 65 && inlastChar1 < 91) || (inlastChar1 > 97 && inlastChar1 < 123) ) && // B-Z , b-z
				inlastChar1 != 69 && inlastChar1 != 101 &&	// !(E/e)
				inlastChar1 != 73 && inlastChar1 != 105 &&	// !(I/i)
				inlastChar1 != 79 && inlastChar1 != 111 &&	// !(O/o)
				inlastChar1 != 85 && inlastChar1 != 117		// !(U/u)
			)
	{
		if ( outlastChar1 == 12387 || outlastChar1 == 12483 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
	// other
	else if ( (inlastChar1 > 32 && inlastChar1 < 65) || (inlastChar1 > 90 && inlastChar1 < 96) || (inlastChar1 > 122 && inlastChar1 < 126) )
	{
		if ( outlastChar1 == inlastChar1 )
		{
			variablestruct.OutputString->erase((OutputLength - 1), 1);
		}
	}
}

// **************************************************************************

// ************************* RENDER DRAWABLES *******************************

// Contains all drawing functions
void renderObjects (renderVariables *variablestruct)
{
//	renderVarInstance.InField = &textinfield;
//	renderVarInstance.OutField = &textoutfield;
//	renderVarInstance.InText = &textin;
//	renderVarInstance.OutText = &textout;
//	renderVarInstance.InCursor = &intextcursor;
//	renderVarInstance.OutCursor = &outtextcursor;
//	renderVarInstance.XGui = &gui;
//	Menu items:
//	renderVarInstance.MouseInArea = &mouseInMenu;
//	renderVarInstance.MouseInSubarea = &mouseInSubmenu;
//	renderVarInstance.ThisSubmenu = &whichSubmenu;
//		File:
//		renderVarInstance.MenuFile = &menu_file;
//		renderVarInstance.MenuFileButtonBox = &menu_file_button_l;
//		renderVarInstance.MenuFileButton = &menu_file_button_b;
//		renderVarInstance.MenuFileSubmenu = &menu_file_submenu_b;
//		Submenu:
//		renderVarInstance.SubmenuButton01 = &menu_file_submenu_button01_b;
//		renderVarInstance.SubmenuButton02 = &menu_file_submenu_button02_b;
//		renderVarInstance.SubmenuButton03 = &menu_file_submenu_button03_b;
//		renderVarInstance.SubmenuButton04 = &menu_file_submenu_button04_b;
//		renderVarInstance.SubmenuButton05 = &menu_file_submenu_button05_b;
//		renderVarInstance.SubmenuSwitchKana = &menu_file_switchkana;
//		renderVarInstance.SubmenuClear = &menu_file_clear;
//		renderVarInstance.SubmenuSave = &menu_file_save;
//		renderVarInstance.SubmenuBlank = &menu_file_blank;
//		renderVarInstance.SubmenuExit = &menu_file_exit;
//	Disclaimer:
//	renderVarInstance.BottomText = &bottomtext;
	
	renderMutex.lock();

	while ( variablestruct->XGui->isOpen() )
	{
		variablestruct->XGui->clear(sf::Color(220,220,220));
		// Draw input text field
		variablestruct->XGui->draw(*(variablestruct->InField));
		// Draw output text field
		variablestruct->XGui->draw(*(variablestruct->OutField));
		// Draw disclamer text
		variablestruct->XGui->draw(*(variablestruct->BottomText));
		

		// If mouse is within "File" menu box area
		if( *(variablestruct->MouseInArea) == 'f' )
		{
			// Draw menu button "File" backshadow
			variablestruct->XGui->draw(*(variablestruct->MenuFileButton));
			// Draw menu button "File" borders
			variablestruct->XGui->draw(*(variablestruct->MenuFileButtonBox));
		}
		
		// Draw input text
		variablestruct->XGui->draw(*(variablestruct->InText));
		// Draw output text
		variablestruct->XGui->draw(*(variablestruct->OutText));
		
		// Fetch MOD10 of current time
		int timemodulus = time(NULL) % 2;
		if (timemodulus == 0 )
		{
			// Draw input text cursor
			variablestruct->XGui->draw(*(variablestruct->InCursor));
			// Draw output text cursor
			variablestruct->XGui->draw(*(variablestruct->OutCursor));
		}
		// If "File" submenu is open
		if( *(variablestruct->ThisSubmenu) == 'f' )
		{
			// Draw "File" submenu box
			variablestruct->XGui->draw(*(variablestruct->MenuFileSubmenu));
			// If mouse is within bounds of button 1 of submenu
			if( *(variablestruct->MouseInSubarea) == '1' )
			{
				// Draw submenu button 1 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton01));
			}
			// If mouse is within bounds of button 2 of submenu
			else if( *(variablestruct->MouseInSubarea) == '2' )
			{
				// Draw submenu button 2 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton02));
			}
			// If mouse is within bounds of button 3 of submenu
			else if( *(variablestruct->MouseInSubarea) == '3' )
			{
				// Draw submenu button 3 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton03));
			}
			// If mouse is within bounds of button 4 of submenu
			else if( *(variablestruct->MouseInSubarea) == '4' )
			{
				// Draw submenu button 4 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton04));
			}
			// If mouse is within bounds of button 5 of submenu
			else if( *(variablestruct->MouseInSubarea) == '5' )
			{
				// Draw submenu button 5 backshadow
				variablestruct->XGui->draw(*(variablestruct->SubmenuButton05));
			}
			// Draw submenu text for Hiragana/Katakana
			variablestruct->XGui->draw(*(variablestruct->SubmenuSwitchKana));
			// Draw submenu text for Clear all text
			variablestruct->XGui->draw(*(variablestruct->SubmenuClear));
			// Draw submenu text for Save to text file
			variablestruct->XGui->draw(*(variablestruct->SubmenuSave));
			// Draw submenu text for Blank
			variablestruct->XGui->draw(*(variablestruct->SubmenuBlank));
			// Draw submenu text for Exit
			variablestruct->XGui->draw(*(variablestruct->SubmenuExit));
		}
		
		// Draw menu text "File"
		variablestruct->XGui->draw(*(variablestruct->MenuFile));
		variablestruct->XGui->display();
		
		renderMutex.unlock();

		// Allows the CPU to "breathe" (looping in thread is demanding)
		sf::sleep(sf::milliseconds(1));

		renderMutex.lock();
	}
	renderMutex.unlock();
}

// **************************************************************************

// ************************* SAVE WINDOW ************************************

// Creates and draws save window
void saveOutput ( sf::String OutputString, sf::Font font )
{
	sf::RenderWindow saveWindow ( sf::VideoMode( 500 , 200 ) , "Save to text file" , sf::Style::Titlebar );
	
	sf::Text description("Input the path for the file you would like to save to.\n\nExample:\n$HOME/Documents/example.txt", font, 12);
	description.setColor(sf::Color::Black);
	description.setPosition( 5, 5 );
	
	sf::RectangleShape filepathfield(sf::Vector2f( 480 , 20 ));
	filepathfield.setPosition( 10, 90 );
	filepathfield.setFillColor(sf::Color::White);
	filepathfield.setOutlineThickness(1);
	filepathfield.setOutlineColor(sf::Color(200, 200, 200));
	
	sf::String filepath = "$HOME/Documents/Untitled.txt";
	
	sf::Text filepathtext(filepath, font, 12);
	filepathtext.setColor(sf::Color::Black);
	filepathtext.setPosition( 12, 92 );
	
	sf::Text defaultbuttontext("Default", font, 12);
	defaultbuttontext.setColor(sf::Color::Blue);
	defaultbuttontext.setPosition( 445, 67 );
	sf::FloatRect defaulttextbounds = defaultbuttontext.getGlobalBounds();
	
	sf::VertexArray defaulttextunderline(sf::Lines, 2);
	defaulttextunderline[0].position = sf::Vector2f(445, 83);
	defaulttextunderline[1].position = sf::Vector2f(485, 83);
	defaulttextunderline[0].color = sf::Color::Blue;
	defaulttextunderline[1].color = sf::Color::Blue;
	
	sf::Text savebuttontext("Save", font, 12);
	savebuttontext.setColor(sf::Color::Black);
	savebuttontext.setPosition( 170, 147 );
	sf::FloatRect savetextbounds = savebuttontext.getGlobalBounds();
	
	sf::RectangleShape savebutton(sf::Vector2f( (savetextbounds.width + 20) , 30 ));
	savebutton.setPosition( 160, 140 );
	savebutton.setFillColor(sf::Color(200,200,200));
	savebutton.setOutlineThickness(1);
	savebutton.setOutlineColor(sf::Color(100, 100, 100));
	
	sf::Text cancelbuttontext("Cancel", font, 12);
	cancelbuttontext.setColor(sf::Color::Black);
	cancelbuttontext.setPosition( 270, 147 );
	sf::FloatRect canceltextbounds = cancelbuttontext.getGlobalBounds();
	
	sf::RectangleShape cancelbutton(sf::Vector2f( (canceltextbounds.width + 20) , 30 ));
	cancelbutton.setPosition( 260, 140 );
	cancelbutton.setFillColor(sf::Color(200,200,200));
	cancelbutton.setOutlineThickness(1);
	cancelbutton.setOutlineColor(sf::Color(100, 100, 100));
	
	sf::String errorstring = "Error: could not open file path.";
	
	sf::Text errortext("Error: Generic error.", font, 12);
	errortext.setColor(sf::Color::Red);
	errortext.setPosition( 5, 112 );
	
	sf::RectangleShape textmask(sf::Vector2f( 10 , 20 ));
	textmask.setPosition( 491, 90 );
	textmask.setFillColor(sf::Color(220,220,220));
	
	sf::Event saveaction;
	sf::Mouse usermouse;
	char mouselocation = '0';
	sf::Vector2i currentMousePosition(0,0);
	bool openfilesuccess = true;
	
	sf::String defaultpath;

	// MS Windows (backslash shenanigans)
	// String containing file path
	//TCHAR filepath_ptr[MAX_PATH];
	//if ( SUCCEEDED( SHGetFolderPath (NULL, CSIDL_PERSONAL|CSIDL_FLAG_CREATE, NULL, 0, filepath_ptr) ) )
	//{
	//	filepath = filepath_ptr;
	//	bool endofstring = false;
	//	std::size_t slashpos = 0;
	//	while (!endofstring)
	//	{
	//		slashpos = filepath.find("\\");
	//		if (slashpos == sf::String::InvalidPos)
	//		{
	//			endofstring = true;
	//		}
	//		else
	//		{
	//			filepath.erase(slashpos, 1);
	//			filepath.insert(slashpos, "/");
	//		}
	//	}
	//	filepath += "/Untitled.txt";
	//	defaultpath = filepath;
	//}
	//else
	//{
	//	errorstring = "Error: Folder path is invalid or folder could not be created.";
	//	openfilesuccess = false;
	//}

	
	while (saveWindow.isOpen())
	{
		while (saveWindow.pollEvent(saveaction))
		{
			if (saveaction.type == sf::Event::LostFocus)
			{
				saveWindow.close();
			}
			if (saveaction.type == sf::Event::TextEntered)
			{
				if (saveaction.text.unicode > 31 && saveaction.text.unicode < 127)
				{
					filepath += saveaction.text.unicode;
				}
				if (saveaction.text.unicode == 8 && filepath.getSize() > 0)
				{
					filepath.erase((filepath.getSize() - 1), 1);
				}
				if (saveaction.text.unicode == 27)
				{
					saveWindow.close();
				}
			}
			if (saveaction.type == sf::Event::KeyPressed)
			{
				if (saveaction.key.code == sf::Keyboard::Return)
				{
					saveWindow.close();
				}
			}
		}
		
		currentMousePosition = usermouse.getPosition(saveWindow);
		
		if ( (currentMousePosition.x >= 160 && currentMousePosition.x <= (savetextbounds.width + 180) ) && (currentMousePosition.y >= 140 && currentMousePosition.y <= 170 ) )
		{
			mouselocation = 's';
		}
		else if ( (currentMousePosition.x >= 260 && currentMousePosition.x <= (canceltextbounds.width + 280) ) && (currentMousePosition.y >= 140 && currentMousePosition.y <= 170 ) )
		{
			mouselocation = 'c';
		}
		else if ( (currentMousePosition.x >= 440 && currentMousePosition.x <= 490 ) && (currentMousePosition.y >= 65 && currentMousePosition.y <= 90 ) )
		{
			mouselocation = 'd';
		}
		else
		{
			mouselocation = '0';
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (mouselocation == 's')
			{
				// Using string conversion function instead of toAnsiString()
				std::string tempout = to_std_string(filepath);
				std::ofstream fileoutput ( tempout.c_str(), std::ios::app );
				if (!fileoutput.is_open())
				{
					errorstring = "Error: Could not open file path. The folder does not exist or is not accessible.";
					openfilesuccess = false;
				}
				else
				{
					// Uses string conversion function
					fileoutput << to_std_string(OutputString);
					try
					{
						fileoutput.close();
						saveWindow.close();
					}
					catch (std::exception e)
					{
						errorstring = "Error: Problem closing filestream.";
						openfilesuccess = false;
					}
				}
			}
			else if (mouselocation == 'c')
			{
				saveWindow.close();
			}
			else if (mouselocation == 'd')
			{
				filepath = defaultpath;
			}
		}
		
		filepathtext.setString(filepath);
		errortext.setString(errorstring);
		
		saveWindow.clear(sf::Color(220,220,220));
		saveWindow.draw(description);
		saveWindow.draw(filepathfield);
		saveWindow.draw(filepathtext);
		if (mouselocation == 's')
		{
			saveWindow.draw(savebutton);
		}
		else if (mouselocation == 'c')
		{
			saveWindow.draw(cancelbutton);
		}
		else if (mouselocation == 'd')
		{
			saveWindow.draw(defaulttextunderline);
		}
		saveWindow.draw(defaultbuttontext);
		saveWindow.draw(savebuttontext);
		saveWindow.draw(cancelbuttontext);
		saveWindow.draw(textmask);
		if (openfilesuccess == false)
		{
			saveWindow.draw(errortext);
		}
		saveWindow.display();
		
		sf::sleep(sf::milliseconds(1));
	}
}

// **************************************************************************

// *********************** CONVERT STRING ***********************************

// Takes sf::String (UTF-32) and returns std::string (UTF-8)
std::string to_std_string(const sf::String& original)
{
	// The final UTF-8 string
    std::string str;
	// Worst case scenario:  4 bytes per codepoint
    str.resize(original.getSize() * 4);

    std::string::iterator last = sf::Utf<32>::toUtf8( original.getData(), original.getData() + original.getSize(), str.begin() );
    str.resize(last - str.begin());

    return str;
}

// **************************************************************************

*/
