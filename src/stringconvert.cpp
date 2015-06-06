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

#include "../include/stringconvert.hpp"

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
