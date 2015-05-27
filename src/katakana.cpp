#include "../include/katakana.hpp"

// Accepts input (stringin) and returns sf::String with corresponding kana
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
	/* N/n
	else if (lastChar1 == 78 || lastChar1 == 110)
	{
		lastChar1 = 12531;
		kanaOut += lastChar1;
	}*/
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
