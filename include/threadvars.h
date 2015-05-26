#ifndef THREADVARS_H
#define THREADVARS_H

// Structure containing references to I/O variables
struct threadVariables
{
	sf::String *InputString;
	sf::String *OutputString;
	bool *inHiragana;
	bool *wrapToNewline;
};

#endif // THREADVARS_H
