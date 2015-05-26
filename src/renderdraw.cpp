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
