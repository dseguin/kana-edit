#include "../include/backspace.hpp"

// Process backspace
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
