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

#include "../include/savewindow.hpp"

// Creates and draws save window
void saveOutput ( sf::String OutputString, sf::Font font )
{
	sf::RenderWindow saveWindow ( sf::VideoMode( 500 , 200 ) , "Save to text file" , sf::Style::Titlebar );
	
	#ifdef _WIN32
	sf::String s_description("Input the path for the file you would like to save to.\nPlease use forward slashes for path names (\"/\").\n\nExample:\n");
	#else
	sf::String s_description("Input the path for the file you would like to save to.\n\nExample:\n");
	#endif
	s_description += DEFAULT_SAVE_PATH;
	s_description += "/example.txt";
	sf::Text description(s_description, font, 12);
	description.setColor(sf::Color::Black);
	description.setPosition( 5, 5 );
	
	sf::RectangleShape filepathfield(sf::Vector2f( 480 , 20 ));
	filepathfield.setPosition( 10, 90 );
	filepathfield.setFillColor(sf::Color::White);
	filepathfield.setOutlineThickness(1);
	filepathfield.setOutlineColor(sf::Color(200, 200, 200));
	
	sf::String filepath = DEFAULT_SAVE_PATH;
	filepath += "/Untitled.txt";
	
	sf::Text filepathtext(filepath, font, 12);
	filepathtext.setColor(sf::Color::Black);
	filepathtext.setPosition( 12, 92 );
	
	sf::Text defaultbuttontext("Default", font, 12);
	defaultbuttontext.setColor(sf::Color::Blue);
	defaultbuttontext.setPosition( 445, 67 );
	//sf::FloatRect defaulttextbounds = defaultbuttontext.getGlobalBounds();
	
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
	bool saverequest = false;
	
	sf::String defaultpath = DEFAULT_SAVE_PATH;
	defaultpath += "/Untitled.txt";

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
			// Return key causes strange bug
			// (creates directory, but prints error message)
			/*
			if (saveaction.type == sf::Event::KeyPressed)
			{
				if (saveaction.key.code == sf::Keyboard::Return)
				{
					saverequest = true;
				}
			}
			*/
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
				saverequest = true;
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

		// Save to file
		if (saverequest)
		{
			// Using string conversion function instead of toAnsiString()
			std::string tempout = to_std_string(filepath);
			std::ofstream fileoutput ( tempout.c_str(), std::ios::app );
			if (!fileoutput.is_open())
			{
				// Convoluted way of stripping off junk after the last '/'
				sf::String s_temp = filepath;
				sf::String s_out;
				bool foundslash = false;
				//bool endofstring = false;
				std::size_t tempsize = s_temp.getSize();
				std::size_t index = tempsize + 1;
				while ( index > 0 && !foundslash )
				{
					index -= 1;
					if ( s_temp[index] == '/' )
					{
						foundslash = true;
					}
				}
				if(foundslash)
				{
					for ( unsigned int i = 0 ; i < index ; i++ )
					{
						s_out += s_temp[i];
					}
					std::string s_mkdir = to_std_string(s_out);

					char * ch = new char[s_mkdir.size() + 1];
					std::copy(s_mkdir.begin(), s_mkdir.end(), ch);
					ch[s_mkdir.size()] = '\0';

					#ifdef _WIN32
					int execvreturn = _mkdir(ch);

					#else // Assume linux
					//char *const mkdirargs[] = { "mkdir" , "-p" , ch , NULL };
					char mkdir_a[8], mkdir_b[8];
					char *const mkdirargs[] = { strcpy(mkdir_a, "mkdir") , strcpy(mkdir_b, "-p") , ch , NULL };
				
					// - Pipe - Fork - Execv -
					int execvreturn = 0;
					int execpipe[2];
					pipe(execpipe);
					fcntl(execpipe[1], F_SETFD, fcntl(execpipe[1], F_GETFD) | FD_CLOEXEC);
					if(fork() == 0)
					{
						close(execpipe[0]);
						execvp( "mkdir" , mkdirargs );
						write(execpipe[1], &errno, sizeof(errno));
						_exit(0);
					}
					else
					{
						close(execpipe[1]);
						int childErrno;
						if(read(execpipe[0], &childErrno, sizeof(childErrno)) == sizeof(childErrno))
						{
							// exec failed
							execvreturn = -1;
						}
					}
					// -----------------------
					#endif
					delete[] ch;

					if ( execvreturn == -1 )
					{
						errorstring = "Error: Could not create directory ";
						errorstring += s_out;
						#ifdef _WIN32
						errorstring += ". _mkdir cannot create directories recursively.";
						#else
						errorstring += ". Execv failed.";
						#endif
						openfilesuccess = false;
					}
					else
					{
						std::ofstream fileoutput2 ( tempout.c_str(), std::ios::app );
						if (!fileoutput2.is_open())
						{
							errorstring = "Error: Problems creating directory ";
							errorstring += s_out;
							errorstring += ". Permission denied.";
							openfilesuccess = false;
						}
						else
						{
							// Uses string conversion function
							fileoutput2 << to_std_string(OutputString);
							try
							{
								fileoutput2.close();
								saveWindow.close();
							}
							catch (std::exception e)
							{
								errorstring = "Error: Problem closing filestream.";
								openfilesuccess = false;
							}
						}
					}
				}
				else
				{
					errorstring = "Error: Could not open file path. The path is not parsable or leads to a directory.";
					openfilesuccess = false;
				}
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
			saverequest = false;
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
