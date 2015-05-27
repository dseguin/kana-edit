#include "../include/savewindow.hpp"

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

	/* MS Windows (backslash shenanigans)
	// String containing file path
	TCHAR filepath_ptr[MAX_PATH];
	if ( SUCCEEDED( SHGetFolderPath (NULL, CSIDL_PERSONAL|CSIDL_FLAG_CREATE, NULL, 0, filepath_ptr) ) )
	{
		filepath = filepath_ptr;
		bool endofstring = false;
		std::size_t slashpos = 0;
		while (!endofstring)
		{
			slashpos = filepath.find("\\");
			if (slashpos == sf::String::InvalidPos)
			{
				endofstring = true;
			}
			else
			{
				filepath.erase(slashpos, 1);
				filepath.insert(slashpos, "/");
			}
		}
		filepath += "/Untitled.txt";
		defaultpath = filepath;
	}
	else
	{
		errorstring = "Error: Folder path is invalid or folder could not be created.";
		openfilesuccess = false;
	}
	*/
	
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