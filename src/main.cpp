/****************************************************************************
 *
 * Simple Kana Editor
 *
 * Author: David Seguin (dseguin @ github.com)
 * Date: May 2015
 * Git repo: https://github.com/dseguin/kana-edit.git
 *
 * Description:
 *      kana-edit is a simple editor for katakana and hiragana. You can type
 *  in standard romanji (english representations of kana characters) and it
 *  will "translate" what you type *on the fly*.
 *      The top box is the input field--where input text is displayed, and
 *  the lower box is the output field--where the processed kana is displayed.
 *  In the top left is an options menu, where you can...
 *  
 *          - Switch between Katakana mode and Hiragana mode
 *          - Clear the screen (both text fields)
 *          - Save what is in the output field to a unicode text file
 *          - Exit the program
 *
 *      The program uses SFML as a display interface. Future updates may
 *  make use of SFML's other features, such as sound or networking.
 *
 * Note to developers:
 *      You're free to do whatever you want with this code. The kana source
 *  could make a handy library if you're working with unicode characters.
 *  However, some of the code is very long, and there's a complicated series
 *  of 'if' statements powering the processing of text. Be warned.
 *
 *
 ***************************************************************************/

#include "../include/main.hpp"

// --------------------------------------------------------------------------
// ---   ---   ---   ---   -  MAIN FUNCTION  -   ---   ---   ---   ---   ---
// --------------------------------------------------------------------------

// MS Windows
#ifdef _WIN32
// Replaces main() to run without console
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
//
#else
int main()
#endif
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

		// MS Windows
		#ifdef _WIN32
		sf::RenderWindow gui ( sf::VideoMode( userResolutionX , userResolutionY ) , "Simple Kana Editor" );
		//
		#else
		sf::RenderWindow gui ( sf::VideoMode( userResolutionX , userResolutionY ) , "Simple Kana Editor" , sf::Style::Close );
		#endif

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

				// MS Windows
				#ifdef _WIN32
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
				#endif
				//

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
							if (stringout[(stringout.getSize() - 1)] == '\n' && stringin[(stringin.getSize() - 1)] == '\n')
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

