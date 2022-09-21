#include "../etana/proof.h"
#include "../../include/mklab.h"

#include "util.h"
#include "word.h"
#include "number.h"
#include "syls.h"
#include "label.h"

CFSWString DealWithText(CFSWString text) {
	/* Proovin kogu sõnniku minema loopida */
    
    
	CFSWString res;
	text.Trim();
        CFSWString x = text;
        text.Replace(L"\n\n", L"\n", 1);
	for (INTPTR i = 0; i < text.GetLength(); i++) {
		CFSWString c = text.GetAt(i);
		CFSWString pc = res.GetAt(res.GetLength() - 1);
		CFSWString nc = text.GetAt(i + 1);
		
                if (is_char(c)) res += c;
		else
			if (is_digit(c)) res += c;
		else
			//if (is_hyphen(c) && is_char(pc) && is_char(nc)) res += sp;
			//else
			if (is_symbol(c)) res += c;
		else
			if (is_dash(c)) res += c;
		else
			if (is_colon(c) && !is_colon(pc)) res += c;
		else
			if (is_bbracket(c) && !is_bbracket(pc)) res += c;
		else
			if (is_ebracket(c) && is_ending(nc)) res += L"";
		else
			if (is_ebracket(c) && !is_ebracket(pc)) res += c;
		else
			if (is_comma(c) && !is_comma(pc)) res += c;
		else
			if (is_fchar(c)) res += replace_fchar(c);
		else
			if (is_space(c) && !is_whitespace(pc)) res += c;
		else
			if (is_break(c) && !is_break(pc)) {

			res += c;
		}//kahtlane
		else
			if (is_tab(c) && !is_whitespace(pc)) res += c;
		else
			if (is_ending(c) && !is_ending(pc) && !is_whitespace(pc)) res += c;

	
        }
	
        res.Trim();
        
	return res;

}


CFSArray<CFSWString> do_utterances(CFSWString s) {

	CFSWString res = empty_str;
	CFSArray<CFSWString> res_array;

	if (s.GetLength() == 1)
		res_array.AddItem(s);
	else
		for (INTPTR i = 0; i < s.GetLength(); i++) {
			CFSWString c = s.GetAt(i);
			CFSWString pc = res.GetAt(res.GetLength() - 1);
			CFSWString nc = s.GetAt(i + 1);
			CFSWString nnc = s.GetAt(i + 2);

			if (is_ending(c) && is_whitespace(nc) && is_upper(nnc)) {
				res.Trim();
                                res += c;
				res_array.AddItem(res);
				res = empty_str;
			} else
				if (is_tab(c)) {
				if (res.GetLength() > 0) {
					res.Trim();
					res_array.AddItem(res);
					res = empty_str;
				}
			} else
				res += c;
		}
	res.Trim();

	if (res.GetLength() > 0) {
		//while (is_ending(res.GetAt(res.GetLength() - 1))) {
		//	res.Delete(res.GetLength() - 1, 1);
		//}

		res_array.AddItem(res);
	}

/*	for (INTPTR i = 0; i < res_array.GetSize(); i++) {
		if (is_ending(res_array[i].GetAt(res_array[i].GetLength() - 1)))
			res_array[i].Delete(res_array[i].GetLength() - 1, 1);

	} */
        //for (INTPTR i = 0; i < res_array.GetSize(); i++) {
          //P.prnn(res_array[i]);
        //}
	return res_array;
}

CFSWString PrepareTokens(CFSWString s) {
    CFSWString res;
    INTPTR first = 0;
    INTPTR last = s.GetLength() - 1;

    for (INTPTR i = 0; i < s.GetLength(); i++) {
        CFSWString c = s.GetAt(i);
        if (c == L"(" || c == L"[" || c == L"{") {
            if (i == first) {
                res += L"sulgudes, ";
            } else
                if (i == last) {
                res += L" alustav sulg";
            } else
                res += L", sulgudes, ";
        } else
            if (c == L")" || c == L"]" || c == L"}") {
            if (i == first) res += L"lõpetav sulg, ";
            else
                if (i == last) {
            } else
                res += L", ";

        } else
            res += c;

    }
    s = res;
    s.Replace(L"°C", L" kraadi ", 1);
    s.Replace(L" – ", L", ", 1);
    s.Replace(L" –, L", L", ", 1);
    s.Replace(L"–", L" ", 1);
    s.Replace(L"\"", L" ", 1);
    s.Replace(L"„", L" ", 1);
    s.Replace(L"”", L" ", 1);
    s.Replace(L"„", L" ", 1);
    s.Replace(L"-", L" ", 1);
    s.Replace(L":", L", ", 1);
    s.Replace(L"…", L" ", 1);

    s.Replace(L"...", L". ", 1);
    s.Replace(L" ,", L", ", 1);
    s.Replace(L" .", L". ", 1);
    s.Replace(L" ?", L"? ", 1);
    s.Replace(L" !", L"! ", 1);
    s.Replace(L",,", L",", 1);

    s.Replace(L"  ", L" ", 1);
    s.Replace(L"  ", L" ", 1);
    s.Replace(L"  ", L" ", 1);
    
    return s;
    
}


bool is_word(CFSWString s) {
	if ((has_vowel(s) == true) &&
		(s.GetLength() == make_char_string(s).GetLength()) &&
		(s.GetLength() > 1))
		return true;
	return false;
}

bool IsOrdinal(CFSWString s) {

	bool res = true;
	//            pr.prnn(s.GetAt(s.GetLength()-1));
	CFSWString punkt = s.GetAt(s.GetLength() - 1);
	if (punkt == L'.') {
		//                pr.prnn(L"on punkt");
		for (INTPTR u = 0; u < s.GetLength() - 1; u++) {
			if (!is_digit(s.GetAt(u))) res = false;
			//                    pr.prnn(s.GetAt(u));
		}

	} else res = false;
	return res;
}


void AddNumber(CFSWString s, CFSClassArray<TWord> &TWA, TWord Result) {
	if (s.Left(7) == L"ühe tuh" || s.Left(7) == L"üks tuh") {
		s.Delete(0, 4);
	}


	CFSArray<CFSWString> Temp;
	explode(s, L" ", Temp);
	for (INTPTR j = 0; j < Temp.GetSize(); j++) {
		if (j == 0) {
			Temp[j].Replace(L"ükssa", L"sa", 1);
			Temp[j].Replace(L"ühesa", L"sa", 1);
		}
		TWord Word;
		Word.TWMInfo.m_cPOS = Result.TWMInfo.m_cPOS;
		Word.TWMInfo.m_szRoot = Temp[j];
		Word.Token = Result.Token;
		TWA.AddItem(Word);
	}

}

bool IsOKNumber(TWord T) {
	if (T.TWMInfo.m_cPOS != L'N') return false;
	CFSWString s = make_digit_string(T.Token);
	if (s.GetLength() != T.Token.GetLength()) return false;
	return true;
}

bool OK1(CFSWString token, CFSWString root) {
	token.Replace(L"-", L"", 1);
	if (token.GetLength() == root.GetLength()) return true;
	return false;
}

/*
 Kui arvud on jaotatud 3 kaupa siis läheb koos lugemiseks
 Muudel juhtudel 1 kaupa välja hõigata
 */
bool IsByThree(CFSArray<CFSWString> A) {
	for (INTPTR i = 1; i < A.GetSize(); i++)
		if (A[i].GetLength() != 3) return false;

	if (A[0].GetLength() > 3) return false;

	return true;
}

bool ExplodeNumber(CFSWString s, CFSClassArray<TWord> &TWA) {
	CFSArray<CFSWString> A;
	TWord T;
	T.TWMInfo.m_cPOS = L'N';
	T.TWMInfo.m_szForm = L"sg n";
	explode(s, L"", A);
	for (INTPTR i = 0; i < A.GetSize(); i++) {
		T.Token = A[i];
		T.TWMInfo.m_szRoot = A[i];
		TWA.AddItem(T);
	}

	return true;
}

bool IsNumberWithSeparator(CFSWString number, CFSWString sep) {
	if (number.Find(sep, 0) == -1) return false;
	for (INTPTR i = 0; i < number.GetLength(); i++) {
		if (!is_digit(number.GetAt(i)) && number.GetAt(i) != sep)
			return false;
	}
	return true;
}

CFSClassArray<TWord> TUtterance::DoNumbers(CFSClassArray<TWord> TWA) {
	CFSClassArray<TWord> Result;
	Result.Cleanup();


	for (INTPTR i = 0; i < TWA.GetSize(); i++) {
		// POS peab olema N või O
		if (TWA[i].TWMInfo.m_cPOS == 'N' || TWA[i].TWMInfo.m_cPOS == 'O') {



			bool Ordinal;
			if (TWA[i].TWMInfo.m_cPOS == 'N')
				Ordinal = false;
			else
				Ordinal = true;

			if (i < TWA.GetSize() - 1) { // Eksisteerib numbrile järgnev sõna

				CFSArray<CFSWString> MorfA;
				explode(TWA[i + 1].TWMInfo.m_szForm, L" ", MorfA);


				INTPTR MorfASize = MorfA.GetSize();
				// Kui on lühike sisseütlev
				//PRAEGU VALE Ilmselt automaatselt O
				if (MorfASize == 1 && MorfA[0] == L"adt") {
					MorfA.Cleanup();
					MorfA.AddItem(L"sg");
					MorfA.AddItem(L"p");
					MorfASize = 2;
				}
				/////////////////////////////

				/* Kui järgneb pärisnimi*/
				if (TWA[i + 1].TWMInfo.m_cPOS == L'H') {

					CFSWString s = IntToStr(TWA[i].Token, Ordinal, 1, true);
					AddNumber(s, Result, TWA[i]);
				} else
					if (MorfA[0] == L"sg" || MorfA[0] == L"pl" && MorfASize == 2) { //Ainsuses
					bool Sg = true;
					if (MorfA[0] == L"pl") Sg = false;


					if (MorfA[1] == L"n") { //nimetav

						CFSWString s = IntToStr(TWA[i].Token, Ordinal, 1, Sg);

						AddNumber(s, Result, TWA[i]);
					} else
						if (MorfA[1] == L"p") { // osastav
						CFSWString s = IntToStr(TWA[i].Token, Ordinal, 3, Sg);
						AddNumber(s, Result, TWA[i]);

					} else // omastava juhtumid
					{

						CFSWString s = IntToStr(TWA[i].Token, Ordinal, 2, Sg);

						// Läbi eituse sest neid on vähem
						// Ei liitu g ter es kom ab
						if (MorfA[1] != L"g" && MorfA[1] != L"ter" &&
							MorfA[1] != L"es" && MorfA[1] != L"kom" &&
							MorfA[1] != L"ab") {
							// kuna m_szEnding saab olla väärtusega "0"
							s += make_char_string(TWA[i + 1].TWMInfo.m_szEnding);
							AddNumber(s, Result, TWA[i]);
						} else {
							AddNumber(s, Result, TWA[i]);
						}
					}

				} else { // Järgmine sõna pole käändsõna
					CFSWString s = IntToStr(TWA[i].Token, Ordinal, 1, true);
					AddNumber(s, Result, TWA[i]);
				}


			} else // Kui on lausungi lõpus, läheb lihtnumbrina
			{
				CFSWString s = IntToStr(TWA[i].Token, Ordinal, 1, true);
				AddNumber(s, Result, TWA[i]);
			}
		} else // ei ole number
		{
			Result.AddItem(TWA[i]);
		}

	}
	return Result;

}



CFSClassArray<TWord> TUtterance::DoTokens(CFSClassArray<TWord> TWA) {
	CFSClassArray<TWord> Result;
	CFSArray<CFSWString> Temp;
	TWord TW;
	CFSClassArray<TTypeRecord> TRecA;
	CFSArray<CFSWString> PrevNumber;



	for (INTPTR i = 0; i < TWA.GetSize(); i++) {

		CFSWString Token = TWA[i].Token;
		// Komad ära ja fraasibreigid paika.
		if ((is_comma(Token.GetAt(Token.GetLength() - 1)) ||
			is_colon(Token.GetAt(Token.GetLength() - 1)) ||
			is_semicolon(Token.GetAt(Token.GetLength() - 1)))
			&& Token.GetLength() > 1) {

			if (i < TWA.GetSize() - 1) {
				if (is_semicolon(Token.GetAt(Token.GetLength() - 1)))
					TWA[i + 1].PhrBreakAfter = 2;
				else
					TWA[i + 1].PhrBreakAfter = 1;
			}

			Token.Delete(Token.GetLength() - 1, 1);
			TWA[i].Token = Token;
		}
		// Sidesõnad fraasipiiriks
		if (is_conju(TWA[i].TWMInfo.m_szRoot))
			TWA[i].PhrBreakAfter = 1;



		// 1 TINGIMUS
		if (i < (TWA.GetSize() - 1) && IsOKNumber(TWA[i]) &&
			IsOKNumber(TWA[i + 1])) {
			PrevNumber.AddItem(TWA[i].Token);
		} else
			// 2 TINGIMUS
			if (TWA[i].TWMInfo.m_cPOS == 'O') {
			CFSWString s = TWA[i].Token;
			// Kui peaks olema punktiga
			if (s.GetAt(s.GetLength() - 1) == L'.') {
				s.Delete(s.GetLength() - 1, 1);
			}
			// Rooma number või tekstiline järgarv n "teine"
			if (make_char_string(s).GetLength() == s.GetLength()) {
				CFSWString Romans = L"IVXLCDM";
				CFSWString Safe = s.GetAt(0);
				if (Romans.FindOneOf(Safe) > -1) {
					s = its(RomanToDecimal(s));
					TWA[i].TWMInfo.m_szForm = s;
					TWA[i].Token = s;
					Result.AddItem(TWA[i]);
				} else {
					TWA[i].TWMInfo.m_cPOS = L'S';
					Result.AddItem(TWA[i]);
				}

			} else //Lihtne järgarv nt "12."
				if (make_digit_string(s).GetLength() == s.GetLength()) {
				Result.AddItem(TWA[i]);
			} else // Nii 10nda kui ka 12-nda juhtumid
			{

				TW.CleanUp();
				TW.TWMInfo.m_cPOS = L'S';
				TW.TWMInfo.m_szForm = L"sg g";
				TW.Token = s;
				TRecA.Cleanup();
				MakeTypeArray(s, TRecA);
				if (TRecA.GetSize() == 2 && TRecA[0].Type == 3 && TRecA[1].Type == 1) {
					CFSWString nr = IntToStr(TRecA[0].s, false, 2, true);
					explode(nr, L" ", Temp);

					for (INTPTR k = 0; k < Temp.GetSize(); k++) {
						if (k == Temp.GetSize() - 1)
							TW.TWMInfo.m_szRoot = Temp[k] + TRecA[1].s;
						else
							TW.TWMInfo.m_szRoot = Temp[k];
						Result.AddItem(TW);
					}
				}
				if (TRecA.GetSize() == 3 && TRecA[0].Type == 3 && TRecA[1].s == L"-" && TRecA[2].Type == 1) {
					CFSWString nr = IntToStr(TRecA[0].s, false, 2, true);
					explode(nr, L" ", Temp);

					for (INTPTR k = 0; k < Temp.GetSize(); k++) {
						if (k == Temp.GetSize() - 1)
							TW.TWMInfo.m_szRoot = Temp[k] + TRecA[2].s;
						else
							TW.TWMInfo.m_szRoot = Temp[k];
						Result.AddItem(TW);
					}
				}
			}
		} else
			// 3 TINGIMUS
			if (TWA[i].TWMInfo.m_cPOS == 'N' && IsNumberWithSeparator(TWA[i].Token, L".")) {
			TW.CleanUp();
			Temp.Cleanup();
			TW.TWMInfo.m_cPOS = L'N';
			explode(TWA[i].Token, L".", Temp);
			for (INTPTR k = 0; k < Temp.GetSize(); k++) {
				TW.Token = Temp[k];
				TW.TWMInfo.m_szRoot = Temp[k];
				Result.AddItem(TW);
			}

		} else
			// 4 TINGIMUS
			if (TWA[i].TWMInfo.m_cPOS == 'N' && IsNumberWithSeparator(TWA[i].Token, L":")) {
			TW.CleanUp();
			Temp.Cleanup();
			TW.TWMInfo.m_cPOS = L'N';
			explode(TWA[i].Token, L":", Temp);
			for (INTPTR k = 0; k < Temp.GetSize(); k++) {
				TW.Token = Temp[k];
				TW.TWMInfo.m_szRoot = Temp[k];
				Result.AddItem(TW);
			}

		} else
			// 5 TINGIMUS				
			if (TWA[i].TWMInfo.m_cPOS == 'N' && IsNumberWithSeparator(TWA[i].Token, L",")) {

			Temp.Cleanup();
			TW.CleanUp();

			explode(TWA[i].Token, L",", Temp);

			for (INTPTR k = 0; k < Temp.GetSize(); k++) {
				TW.TWMInfo.m_cPOS = L'N';
				TW.TWMInfo.m_szForm = L"";
				TW.Token = Temp[k];
				TW.TWMInfo.m_szRoot = Temp[k];
				Result.AddItem(TW);
				if (k < Temp.GetSize() - 1) {
					TW.Token = L",";
					TW.TWMInfo.m_szRoot = L"koma";
					TW.TWMInfo.m_cPOS = L'S';
					TW.TWMInfo.m_szForm = L"sg n";
					Result.AddItem(TW);
				}
			}
		} else
			// 6 TINGIMUS
			if (TWA[i].TWMInfo.m_cPOS == 'N' && NumberIsOK(TWA[i].Token)) {


			// Numbrite lahus kirjutamise koht. xx +xxx +xxx
			if (PrevNumber.GetSize() > 0) {
				PrevNumber.AddItem(TWA[i].Token);
				CFSWString s;


				if (IsByThree(PrevNumber)) { //kui on 3sed rühmad
					for (INTPTR k = 0; k < PrevNumber.GetSize(); k++)
						s += PrevNumber[k];
					TWA[i].Token = s;
					TWA[i].TWMInfo.m_szRoot = s;
					Result.AddItem(TWA[i]);
				} else { // kui on n telefoni number
					for (INTPTR k = 0; k < PrevNumber.GetSize(); k++)
						ExplodeNumber(PrevNumber[k], Result);


				}
				PrevNumber.Cleanup();
			} else // Siia ei tohiks vist kunagi jõuda
				Result.AddItem(TWA[i]);


		} else
			// Kui on midagi perses, kahtlusta tingimuse 2. poolt
			// 7 TINGIMUS
			if (TWA[i].TWMInfo.m_cPOS < 'Y' && is_word(TWA[i].Token)) {
			//et "kaks" ei läheks numbritesse          
			if (TWA[i].TWMInfo.m_cPOS == L'N') TWA[i].TWMInfo.m_cPOS = L'S';
			Result.AddItem(TWA[i]);

		} else
			// Kui lühendid või on toimunud keyboard smash
		{
			/*
			 * ERIJUHUD
			 *
			 */

			TRecA.Cleanup();
			MakeTypeArray(TWA[i].Token, TRecA);


			Temp.Cleanup();
			is_abbreviation(TWA[i].Token, Temp);

			// 1 ERIJUHT
			// Lühendid loendist
			if (Temp.GetSize() > 0) {

				//Kujutan ette, et kui on mitmesõaline siis ei käändu
				if (Temp.GetSize() == 1) {

					if (i == 0) {
						TWA[i].TWMInfo.m_szRoot = Temp[0];
						Result.AddItem(TWA[i]);
					} else {

						CFSArray<CMorphInfo> MInfos;
						CMorphInfo MInfo;
						MInfo.m_szRoot = Temp[0];
						MInfo.m_cPOS = L'*';
						MInfo.m_szForm = TWA[i - 1].TWMInfo.m_szForm;

						MInfos = Linguistic.Synthesize(MInfo, L"");
						if (MInfos.GetSize() > 0) {


							MInfos[0].m_szRoot += make_char_string(MInfos[0].m_szEnding);
							TWA[i].TWMInfo = MInfos[0];
							Result.AddItem(TWA[i]);

						} else {
							//  "1 kroon" ja "2 krooni"
							MInfos.Cleanup();
							MInfo.m_cPOS = L'*';
							MInfo.m_szForm = L"sg p";
							MInfo.m_szRoot = Temp[0];
							MInfos = Linguistic.Synthesize(MInfo, L"");

							if (TWA[i - 1].TWMInfo.m_cPOS == L'N' &&
								TWA[i - 1].Token != L"1" &&
								TWA[i - 1].Token != L"üks" &&
								TWA[i - 1].PhrBreakAfter == 0) { // kui eelneb fraasipiir siis ei käändu

								if (MInfos.GetSize() > 0) {

									MInfos[0].m_szRoot += make_char_string(MInfos[0].m_szEnding);
									TWA[i].TWMInfo = MInfos[0];
									Result.AddItem(TWA[i]);
								} else {

									TWA[i].TWMInfo.m_szRoot = Temp[0];
									Result.AddItem(TWA[i]);
								}
							} else {
								TWA[i].TWMInfo.m_szRoot = Temp[0];
								Result.AddItem(TWA[i]);
							}
						}
					}



				} else {
					for (INTPTR k = 0; k < Temp.GetSize(); k++) {
						TW.Token = TWA[i].Token;
						TW.TWMInfo.m_szRoot = Temp[k];
						Result.AddItem(TW);
					}
				}
			} else
				// 2 ERIJUHT
				// USA-sse (vajavad kõik eraldi kontrolli, sest lkdjf@ladkj.alksjd on samuti lühend)
				if (TWA[i].TWMInfo.m_cPOS == L'Y' && OK1(TWA[i].Token, TWA[i].TWMInfo.m_szRoot)) {
				Result.AddItem(TWA[i]);
			} else
				// 3 ja 4 ERIJUHT
				// 2le
				if ((TRecA.GetSize() == 2 && TRecA[0].Type == 3 && TRecA[1].Type == 1) ||
				(TRecA.GetSize() == 3 && TRecA[0].Type == 3 && TRecA[2].Type == 1 && is_bhyphen(TRecA[1].s))) {
				if (TRecA.GetSize() == 3) TRecA.RemoveItem(1, 1);
				TW.CleanUp();
				Temp.Cleanup();
				CFSWString s = IntToStr(TRecA[0].s, false, 2, true);
				explode(s, L" ", Temp);
				TW.Token = TWA[i].Token;
				TW.TWMInfo.m_cPOS = L'S';

				TW.TWMInfo.m_szForm = L"sg g";
				for (INTPTR k = 0; k < Temp.GetSize(); k++) {
					if (k == Temp.GetSize() - 1)
						TW.TWMInfo.m_szRoot = Temp[k] + TRecA[1].s;
					else
						TW.TWMInfo.m_szRoot = Temp[k];
					Result.AddItem(TW);
				}

			}
			else
				// 5 ERIJUHT 25-30 25 kuni 30
				if (TRecA.GetSize() == 3 && TRecA[0].Type == 3 &&
				TRecA[2].Type == 3 && is_bhyphen(TRecA[1].s)) {
				TW.CleanUp();
				TW.Token = TRecA[0].s;
				TW.TWMInfo.m_cPOS = L'N';
				TW.TWMInfo.m_szRoot = TRecA[0].s;
				Result.AddItem(TW);
				TW.TWMInfo.m_cPOS = L'J';
				TW.Token = TRecA[1].s;
				TW.TWMInfo.m_szRoot = L"kuni";
				Result.AddItem(TW);
				TW.TWMInfo.m_cPOS = L'N';
				TW.TWMInfo.m_szRoot = TRecA[2].s;
				TW.Token = TRecA[2].s;
				Result.AddItem(TW);

			}				
				/*ERIJUHTUDE LÕPP*/
			else
				for (INTPTR j = 0; j < TRecA.GetSize(); j++) {
					//P.l = 30;


					Temp.Cleanup();
					TW.CleanUp();


					if (TRecA[j].Type == 1) { //tähed
						if (is_word(TRecA[j].s)) { //näeb välja nagu sõna
							TW.Token = TRecA[j].s;
							TW.TWMInfo.m_szRoot = TRecA[j].s.ToLower();
							Result.AddItem(TW);
						} else { // ei ole sõna moodi
							explode(TRecA[j].s, L"", Temp);
							for (INTPTR k = 0; k < Temp.GetSize(); k++) {
								CFSWString s;
								s = replace_schar(Temp[k]);
								TW.Token = s;
								TW.TWMInfo.m_szRoot = s;
								Result.AddItem(TW);
							}
						}
					} else
						if (TRecA[j].Type == 2) { //sümbolid


						while (TRecA[j].s.GetAt(0) == L'-' && TRecA[j].s.GetLength() > 1)
							TRecA[j].s.Delete(0, 1);
						explode(TRecA[j].s, L"", Temp);

						for (INTPTR k = 0; k < Temp.GetSize(); k++) {
							CFSWString s;
							s = replace_schar(Temp[k]);
							if (j > 0 && Temp[k].FindOneOf(L"%°§£$€") > -1 && TRecA[j - 1].s != L"1") {
								CFSArray<CMorphInfo> MInfos;
								CMorphInfo MInfo;
								MInfo.m_cPOS = L'*';
								MInfo.m_szForm = L"sg p";
								MInfo.m_szRoot = s;
								MInfos = Linguistic.Synthesize(MInfo, L"");

								if (MInfos.GetSize() > 0)
									s = MInfos[0].m_szRoot + make_char_string(MInfos[0].m_szEnding);
							}

							TW.Token = s;
							TW.TWMInfo.m_szRoot = s;
							Result.AddItem(TW);
						}
					} else
						if (TRecA[j].Type == 3) { //numbrid
						TW.Token = TRecA[j].s;
						TW.TWMInfo.m_cPOS = 'N';
						Result.AddItem(TW);

					} else { //eestikeelse teksti puhul jõuavad siia ainult sulud
						if (is_bbracket(TRecA[j].s)) { //alustav
							CFSWString s = L"sulgudes";
							TW.Token = s;
							TW.TWMInfo.m_szRoot = s;
							// jõuga fraasipiir enne ja järel;
							TW.PhrBreakAfter = 2;
							Result.AddItem(TW);
							if (Result.GetSize() > 0)
								Result[Result.GetSize() - 1].PhrBreakAfter = 2;
						}

						if (is_ebracket(TRecA[j].s) && Result.GetSize() > 0) { //lõpetav
							//Result[Result.GetSize() - 1].PhrBreakAfter = 2;
                                                     
                                                    //TWA[i+2].PhrBreakAfter = 2;
						}
					}
				}
		}
	}
	return Result;
}


void TUtterance::DoPhrases(CFSClassArray<TWord>& TWA) {
	INTPTR pCount, PNr = 1, FromPrev = 0;
	CFSArray<INTPTR> Reverse;
	//INTPTR PNr = 1
	for (INTPTR i = 0; i < TWA.GetSize(); i++) {
		if (TWA[i].PhrBreakAfter == 2) {
			PNr++;
			FromPrev = 0;
		} else
			if (TWA[i].PhrBreakAfter == 1 && FromPrev > 0) {
			PNr++;
			FromPrev = 0;
		} else
			FromPrev++;

		TWA[i].h3 = PNr;
		Reverse.InsertItem(0, PNr);
	}
	for (INTPTR i = 0; i < TWA.GetSize(); i++) {
		TWA[i].h4 = Reverse[i];

	}
}

void TSyl::DoPhones(TSyl &T) {
	TPhone P;

	INTPTR l = T.Syl.GetLength();
	T.b3 = l;
	for (INTPTR i = 0; i < l; i++) {
		CFSWString c = T.Syl.GetAt(i);
		if (c == ':') {
			T.TPA[T.TPA.GetSize()-1].Phone = T.TPA[T.TPA.GetSize()-1].Phone + L"w";
		} else
		{
			if ((c == L'š') || (c == L'ž')) c = L"sh";
			if (c == L'õ') c = L"ou";
			if (c == L'ä') c = L"ae";
			if (c == L'ö') c = L"oe";
			if (c == L'ü') c = L"ue";
                //if (c == L'g') c = L"k";
                //if (c == L'b') c = L"p";
                //if (c == L'd') c = L"t";
                

			P.Phone = c;
			P.p6 = i + 1;
			P.p7 = l - i;
			T.TPA.AddItem(P);
		}
	}

	//for (INTPTR i = 0; i < T.TPA.GetSize(); i++) {
	//	PPP.pr(T.TPA[i].Phone);
	//}
	//PPP.prnn();

}


CFSArray<CFSWString> do_all(CFSWString utt, bool print_label, bool print_utt) {
	CFSArray<CFSWString> res, TempA;
	CFSArray<CPTWord> PTW;
	TUtterance TU;
        
        
        if (utt.GetLength() > 1) 
               utt = PrepareTokens(utt);
        

	explode(utt, L" ", TempA);

	for (INTPTR i = 0; i < TempA.GetSize(); i++) {
		PTW.AddItem(TempA[i]);
	}

	CFSArray<CMorphInfos> MRs = Disambiguator.Disambiguate(Linguistic.AnalyzeSentense(PTW));

//        P.prnn();
        
        
        INTPTR UttType = 1;
	for (INTPTR i = 0; i < MRs.GetSize(); i++) {
		TWord TW;
		TW.Token = MRs[i].m_szWord;
		
                CFSWString pc = TW.Token.GetAt(TW.Token.GetLength() - 1);
                if (is_ending(pc) && i == MRs.GetSize()-1) {
                    if (pc == L"?") UttType = 3;
                        else
                    if (pc == L"!") UttType = 2;
                        else
                    UttType = 1;
                    //P.prnn(pc);
                    TW.Token.Delete(TW.Token.GetLength() - 1, 1);
                }
                
                
                TW.TWMInfo = MRs[i].m_MorphInfo[0];
		TW.AddEndings();
		TU.TWA.AddItem(TW);
                for (int j = 0; j < MRs[i].m_MorphInfo.GetSize(); j ++) {
                   // P.prnn(MRs[i].m_MorphInfo[j].m_szRoot +MRs[i].m_MorphInfo[j].m_szEnding);
                    
                //    P.prnn(MRs[i].m_szWord);
                }
                
                
	}
        
        
        TU.UttT = UttType;
	TU.AnalyzeText();
        TU.Syllabify();
        TU.Phrasing();
	TU.Calculate();
        TU.PhoneArray();

        
        for (INTPTR i = 0; i < TU.TPA.GetSize(); i++) {
		res.AddItem(TU.TPA[i].Phone);
		//P.prnn(TU.TPA[i].Phone);
                
                

	}        
	return res;
}

