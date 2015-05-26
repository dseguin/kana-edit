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
