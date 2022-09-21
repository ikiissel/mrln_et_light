/*
 * IntToStr by fun2code. http://www.cplusplus.com/forum/lounge/74394/
 * RomanToDecimal by https://www.geeksforgeeks.org/
 */
#include "../etana/proof.h"
#include "util.h"



int value(char r) 
{ 
    if (r == 'I') 
        return 1; 
    if (r == 'V') 
        return 5; 
    if (r == 'X') 
        return 10; 
    if (r == 'L') 
        return 50; 
    if (r == 'C') 
        return 100; 
    if (r == 'D') 
        return 500; 
    if (r == 'M') 
        return 1000; 
  
    return -1; 
}

INTPTR RomanToDecimal(CFSWString &str) {
	int res = 0;
	for (int i = 0; i < str.GetLength(); i++) {
		int s1 = value(str[i]);
		if (i + 1 < str.GetLength()) {
			int s2 = value(str[i + 1]);
			if (s1 >= s2) {
				res = res + s1;
			}
			else {
				res = res + s2 - s1;
				i++;
			}
		}
		else {
			res = res + s1;
		}
	}
	return res;
}



void Fill(CFSWString *a, CFSWStringArray &b, INTPTR c) {

	for (INTPTR i = 0; i < c; i++) {
		b.AddItem(a[i]);
	}

}

CFSWString IntToStr(CFSWString numStr, bool Ordinal, INTPTR decl, bool Sg) {
	CFSWString rs;
	numStr = make_digit_string(numStr);

	CFSWString onesNimetav[] = {
		L"üks", L"kaks", L"kolm", L"neli", L"viis", L"kuus", L"seitse", L"kaheksa", L"üheksa"
	};

	CFSWString teensNimetav[] = {
		L"kümme", L"üksteist", L"kaksteist", L"kolmteist", L"neliteist", L"viisteist", L"kuusteist", L"seitseteist", L"kaheksateist", L"üheksateist"
	};

	CFSWString tensNimetav[] = {
		L"kakskümmend", L"kolmkümmend", L"nelikümmend", L"viiskümmend", L"kuuskümmend", L"seitsekümmend", L"kaheksakümmend", L"üheksakümmend"
	};


	CFSWString onesOmastav[] = {
		L"ühe", L"kahe", L"kolme", L"nelja", L"viie", L"kuue", L"seitsme", L"kaheksa", L"üheksa",
	};

	CFSWString teensOmastav[] = {
		L"kümne", L"üheteistkümne", L"kaheteistkümne", L"kolmeteistkümne", L"neljateistkümne",
		L"viieteistkümne", L"kuueteistkümne", L"seitsmeteistkümne", L"kaheksateistkümne", L"üheksateistkümne"
	};

	CFSWString tensOmastav[] = {
		L"kahekümne", L"kolmekümne", L"neljakümne", L"viiekümne", L"kuuekümne", L"seitsmekümne", L"kaheksakümne", L"üheksakümne"
	};

	CFSWString onesNimetavJarg[] = {
		L"esimene", L"teine", L"kolmas", L"neljas", L"viies", L"kuues", L"seitsmes", L"kaheksas", L"üheksas"
	};

	CFSWString teensNimetavJarg[] = {
		L"kümnes", L"üheteistkümnes", L"kaheteistkümnes", L"kolmeteistkümnes", L"neljateistkümnes",
		L"viieteistkümnes", L"kuueteistkümnes", L"seitsmeteistkümnes", L"kaheksateistkümnes", L"üheksateistkümnes"
	};
	CFSWString tensNimetavJarg[] = {
		L"kahekümnes", L"kolmekümnes", L"neljakümnes", L"viiekümnes", L"kuuekümnes", L"seitsmekümnes", L"kaheksakümnes", L"üheksakümnes"
	};

	CFSWString onesOmastavJarg[] = {
		L"esimese", L"teise", L"kolmanda", L"neljanda", L"viienda", L"kuuenda", L"seitsmenda", L"kaheksanda", L"üheksanda",
	};
	CFSWString teensOmastavJarg[] = {
		L"kümnenda", L"üheteistkümnenda", L"kaheteistkümnenda", L"kolmeteistkümnenda", L"neljateistkümnenda",
		L"viieteistkümnenda", L"kuueteistkümnenda", L"seitsmeteistkümnenda", L"kaheksateistkümnenda", L"üheksateistkümnenda"
	};
	CFSWString tensOmastavJarg[] = {
		L"kahekümnenda", L"kolmekümnenda", L"neljakümnenda", L"viiekümnenda", L"kuuekümnenda", L"seitsmekümnenda", L"kaheksakümnenda", L"üheksakümnenda"
	};

	CFSWString onesOsastavJarg[] = {
		L"esimest", L"teist", L"kolmandat", L"neljandat", L"viiendat", L"kuuendat", L"seitsmendat", L"kaheksandat", L"üheksandat"
	};
	CFSWString teensOsastavJarg[] = {
		L"kümnendat", L"üheteistkümnendat", L"kaheteistkümnendat", L"kolmeteistkümnendat", L"neljateistkümnendat",
		L"viieteistkümnendat", L"kuueteistkümnendat", L"seitsmeteistkümnendat", L"kaheksateistkümnendat", L"üheksateistkümnendat"
	};
	CFSWString tensOsastavJarg[] = {
		L"kahekümnendat", L"kolmekümnendat", L"neljakümnendat", L"viiekümnendat", L"kuuekümnendat", L"seitsmekümnendat", L"kaheksakümnendat", L"üheksakümnendat"
	};




	CFSWString onesNimetavPL[] = {
		L"ühed", L"kahed", L"kolmed", L"neljad", L"viied", L"kuued",
		L"seitsmed",
		L"kaheksad", L"üheksad"
	};

	CFSWString teensNimetavPL[] = {
		L"kümned", L"üheteistkümned", L"kaheteistkümned", L"kolmeteistkümned",
		L"neljateistkümned",
		L"viieteistkümned", L"kuueteistkümned", L"seitsmeteistkümned",
		L"kaheksateistkümned",
		L"üheksateistkümned"
	};

	CFSWString tensNimetavPL[] = {
		L"kahekümned", L"kolmekümned", L"neljakümned", L"viiekümned",
		L"kuuekümned", L"seitsmekümned", L"kaheksakümned",
		L"üheksakümned"
	};

	CFSWString onesOmastavPL[] = {
		L"ühtede", L"kahtede", L"kolmede", L"neljade", L"viite", L"kuute",
		L"seitsmete",
		L"kaheksate", L"üheksate",
	};

	CFSWString teensOmastavPL[] = {
		L"kümnete", L"üheteistkümnete", L"kaheteistkümnete",
		L"kolmeteistkümnete", L"neljateistkümnete",
		L"viieteistkümnete", L"kuueteistkümnete", L"seitsmeteistkümnete",
		L"kaheksateistkümnete", L"üheksateistkümnete"
	};

	CFSWString tensOmastavPL[] = {
		L"kahekümnete", L"kolmekümnete", L"neljakümnete", L"viiekümnete",
		L"kuuekümnete", L"seitsmekümnete", L"kaheksakümnete", L"üheksakümnete"
	};

	CFSWString onesNimetavJargPL[] = {
		L"esimesed", L"teised", L"kolmandad", L"neljandad", L"viiendad",
		L"kuuendad",
		L"seitsmendad", L"kaheksandad", L"üheksandad"
	};

	CFSWString teensNimetavJargPL[] = {
		L"kümnendad", L"üheteistkümnendad", L"kaheteistkümnendad",
		L"kolmeteistkümnendad", L"neljateistkümnendad",
		L"viieteistkümnendad", L"kuueteistkümnendad", L"seitsmeteistkümnendad",
		L"kaheksateistkümnendad", L"üheksateistkümnendad"
	};
	CFSWString tensNimetavJargPL[] = {
		L"kahekümnendad", L"kolmekümnendad", L"neljakümnendad",
		L"viiekümnendad",
		L"kuuekümnendad", L"seitsmekümnendad", L"kaheksakümnendad",
		L"üheksakümnendad"
	};

	CFSWString onesOmastavJargPL[] = {
		L"esimeste", L"teiste", L"kolmandate", L"neljandate", L"viiendate",
		L"kuuendate", L"seitsmendate", L"kaheksandate", L"üheksandate",
	};
	CFSWString teensOmastavJargPL[] = {
		L"kümnendate", L"üheteistkümnendate", L"kaheteistkümnendate",
		L"kolmeteistkümnendate", L"neljateistkümnendate",
		L"viieteistkümnendate", L"kuueteistkümnendate",
		L"seitsmeteistkümnendate", L"kaheksateistkümnendate",
		L"üheksateistkümnendate"
	};
	CFSWString tensOmastavJargPL[] = {
		L"kahekümnendate", L"kolmekümnendate", L"neljakümnendate",
		L"viiekümnendate", L"kuuekümnendate", L"seitsmekümnendate",
		L"kaheksakümnendate", L"üheksakümnendate"
	};




	CFSWString illion_preName[] = {L"m", L"b", L"tr", L"kvadr", L"kvint", L"sekst", L"sept", L"okt", L"non", L"dets"};
	CFSWString decillion_preName[] = {L"un", L"duo", L"tre", L"kvattuor", L"kvin", L"seks", L"septen", L"okto", L"novem"};



	CFSWString hndr;


	CFSWStringArray ones, teens, tens;


	if (!Ordinal) {
		if (decl == 1) {
			Fill(onesNimetav, ones, 9);
			Fill(teensNimetav, teens, 10);
			Fill(tensNimetav, tens, 8);
			hndr = L"sada ";
			

		}
		if (decl == 2) {
			Fill(onesOmastav, ones, 9);
			Fill(teensOmastav, teens, 10);
			Fill(tensOmastav, tens, 8);
			hndr = L"saja ";
			

		}
		if (decl == 3) {
			Fill(onesNimetav, ones, 9);
			Fill(teensNimetav, teens, 10);
			Fill(tensNimetav, tens, 8);
			hndr = L"sada ";
			

		}


	} else { // kui on järgarv
		if (decl == 1) {

			Fill(onesNimetavJarg, ones, 9);
			Fill(teensNimetavJarg, teens, 10);
			Fill(tensNimetavJarg, tens, 8);
			hndr = L"saja ";
			


		}

		if (decl == 2) {
			Fill(onesOmastavJarg, ones, 9);
			Fill(teensOmastavJarg, teens, 10);
			Fill(tensOmastavJarg, tens, 8);
			hndr = L"saja ";
			

		}
		if (decl == 3) {
			Fill(onesNimetavJarg, ones, 9);
			Fill(teensNimetavJarg, teens, 10);
			Fill(tensNimetavJarg, tens, 8);
			hndr = L"sada ";
			

		}

	}


	while (numStr.GetAt(0) == L'0') {
		rs += L"null ";
		numStr.Delete(0,1);
	}
	
if (numStr.GetLength() == 0) {	
	rs.Trim();
	return rs;
	}




	while (numStr.GetLength() % 3 != 0) numStr = L'0' + numStr;


	INTPTR x = numStr.GetLength() / 3;
	bool Last = false;


	for (unsigned int i = 0; i < numStr.GetLength(); i += 3) {
		x--;
		if (x == 0) Last = true;

		if (numStr.GetAt(i) == L'0' && numStr.GetAt(i + 1) == L'0' && numStr.GetAt(i + 2) == L'0')
			continue;

		if (numStr.GetAt(i + 0) > L'0') {
			//sajad sadade sajandad sajandate
			CFSWString End;
			if (!Last) {

				if (!Ordinal && (decl == 1 || decl == 3)) {
					rs += onesNimetav[ numStr.GetAt(i + 0) - 48 - 1 ] + L"sada ";
				} else {
					rs += onesOmastav[ numStr.GetAt(i + 0) - 48 - 1 ] + L"saja ";
				}


			} else { // kui on viimased 3
				// Kui viimased 3 on x00												
				if (numStr.GetAt(i + 1) == L'0' && numStr.GetAt(i + 2) == L'0') {

					if (!Ordinal) { //ei ole järgarv                            
						//Osastav läheb nimetavas siin. Lihtsalt tundub parem
						if (decl == 1 || decl == 3) 
						
						if (Sg) End = L"sada ";
							else End = L"sajad ";
						
						if (decl == 2) 
							if (Sg) End = L"saja ";
							else End = L"sadade ";

					} else //on järgarv
					{
						if (decl == 1) 
							if (Sg) End = L"sajas "; else End = L"sajandad ";
						if (decl == 2) 
							if (Sg) End = L"sajanda "; else End = L"sajandate ";
						if (decl == 3)
							if (Sg) End = L"sajandat "; else End = L"sajandad ";
					}
					if (decl == 1 && !Ordinal)
						rs += onesNimetav[ numStr.GetAt(i + 0) - 48 - 1 ] + End;
					else
						rs += onesOmastav[ numStr.GetAt(i + 0) - 48 - 1 ] + End;
				} else {
					if ((decl == 1 || decl == 3) && !Ordinal && Sg) {
						rs += onesNimetav[ numStr.GetAt(i + 0) - 48 - 1 ] + L"sada ";
					} else {
						rs += onesOmastav[ numStr.GetAt(i + 0) - 48 - 1 ] + L"saja ";

					}

				}
			}
		}


		
	if (numStr.GetAt(i + 1) == L'0' || numStr.GetAt(i + 1) > L'1') {
		
		
		if (numStr.GetAt(i + 1) > L'1') {				
			
			if (numStr.GetAt(i + 2) > L'0') {
				if((decl == 1 || decl == 3) && !Ordinal && Sg)
					rs += tensNimetav[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
				else
					rs += tensOmastav[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
			} else
			{
					
				if (Last) {
					if (Sg) {
					if (Ordinal && decl == 3)	
						rs += tensOsastavJarg[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
					else
						rs += tens[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
					}
					else // mitmuses
					{

						if (decl == 1 || decl == 3) {
							if (Ordinal) {
								rs += tensNimetavJargPL[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
							} else {
								rs += tensNimetavPL[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
								
							}
						} else //Kui on 2
						{
							if (Ordinal) {
								rs += tensOmastavJargPL[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
							} else {
								rs += tensOmastavPL[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";
							}
						}
						
					}
				}
				else {
				if (decl == 1 && !Ordinal) {
				rs += tensNimetav[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";	
					}
					else {
				rs += tensOmastav[ numStr.GetAt(i + 1) - 48 - 2 ] + L" ";		
					}
				}
			}
		
		}



			if (numStr.GetAt(i + 2) > L'0') {
				if (Last) {
					if (Sg) {
						if (Ordinal && decl == 3)
						rs += onesOsastavJarg[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
						else
						rs += ones[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
					} else
						{ // Kui on mitmuses
					if (decl == 1 || decl == 3) {
						if (Ordinal)
							rs += onesNimetavJargPL[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
						else
							rs += onesNimetavPL[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
					} else
						if (decl == 2) {
						if (Ordinal)
							rs += onesOmastavJargPL[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
						else
							rs += onesOmastavPL[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";

					}
				}

				} else {
					if (!Ordinal && (decl == 1 || decl == 3)) {
						rs += onesNimetav[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
					} else {
						rs += onesOmastav[ numStr.GetAt(i + 2) - 48 - 1 ] + L" ";
					}
				}

			}
		} else {

		if (!Ordinal && !Last) {
			if (decl == 1 || decl == 3)
			rs += teensNimetav[ numStr.GetAt(i + 2) - 48 ] + L" ";
			else
			rs += teensOmastav[ numStr.GetAt(i + 2) - 48 ] + L" ";
		}
		else
		if (Ordinal && !Last) {
				rs += teensOmastav[ numStr.GetAt(i + 2) - 48 ] + L" ";
			} else
				if (!Ordinal && !Last && decl == 3) // Mingi viga loendites ei leia praegu
				rs += teensNimetav[ numStr.GetAt(i + 2) - 48 ] + L" ";
			else {
				if (Sg)
					if (Ordinal && decl == 3)
					rs += teensOsastavJarg[ numStr.GetAt(i + 2) - 48 ] + L" ";
					else
					rs += teens[ numStr.GetAt(i + 2) - 48 ] + L" ";
				else { // Kui on mitmuses
					if (decl == 1 || decl == 3) {
						if (Ordinal)
							rs += teensNimetavJargPL[ numStr.GetAt(i + 2) - 48 ] + L" ";
						else
							rs += teensNimetavPL[ numStr.GetAt(i + 2) - 48 ] + L" ";
					} else
						if (decl == 2) {
						if (Ordinal)
							rs += teensOmastavJargPL[ numStr.GetAt(i + 2) - 48 ] + L" ";
						else
							rs += teensOmastavPL[ numStr.GetAt(i + 2) - 48 ] + L" ";

					}
				}

			}
		}


		unsigned int j = (numStr.GetLength() - i) / 3;
		if (j == 2) {
		//kui on X000	
		if (numStr.GetAt(i+3) == L'0' && numStr.GetAt(i+4) == L'0' && numStr.GetAt(i+5) == L'0') {
			
			if (Sg)	{ //Kui on ainsuses
				if (!Ordinal) {
					if (decl == 1 || decl == 3) 
					rs += L"tuhat ";
					else
					rs += L"tuhande ";	
				}
				else
				{ // ON järgarv
					if (decl == 1 || decl == 3) 
					rs += L"tuhandes ";
					else
					rs += L"tuhandenda ";						
				}
			}
			else
			{ //Kui on mitmuses
				if (!Ordinal) {
					if (decl == 1 || decl == 3) 
					rs += L"tuhanded ";
					else
					rs += L"tuhandete ";	
				}
				else
				{ // ON järgarv
					if (decl == 1 || decl == 3) 
					rs += L"tuhandendad ";
					else
					rs += L"tuhandendate ";						
				}
				
			}
		}
		else
		if ((decl == 1 || decl == 3) && !Ordinal && Sg)
				rs += L"tuhat ";
			else
				rs += L"tuhande ";
		} else if (j > 2) {

			if (j <= 12) {
				rs += illion_preName[ j - 3 ];
			} else if (j <= 21) {
				rs += decillion_preName[ j - 13 ] + L"dets";
			} else if (j == 22) {
				rs += L"vigint";
			}
			rs += L"iljonit ";
		}
	}

	rs.Trim();

	return rs;
}

