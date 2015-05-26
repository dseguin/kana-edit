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
