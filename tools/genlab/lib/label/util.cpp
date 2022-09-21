#include <iostream>
#include "../etana/proof.h"
#include "util.h"

//Printer PR;

bool is_lvowel (CFSWString c) {
	if (c.FindOneOf(L"aeiouõäöüy") > -1)	return true;
		return false;
}

bool is_uvowel (CFSWString c) {
	if (c.FindOneOf(L"AEIOUÕÄÖÜY") > -1)	return true;
		return false;
}

bool is_lconsonant (CFSWString c) {
	if (c.FindOneOf(L"bcdfghjklmnpqrsšžtvwxz") > -1)	return true;
		return false;
}

bool is_uconsonant (CFSWString c) {
	if (c.FindOneOf(L"BCDFGHJKLMNPQRSŠŽTVWXZ") > -1) return true;
		return false;
}

bool is_ending (CFSWString c) {
	if (c.FindOneOf(L".?!;") > -1)	return true;
		return false;
}

bool is_tab (CFSWString c) {
	if (c.FindOneOf(L"\t\n") > -1)	return true;
		return false;
}

bool is_break (CFSWString c) {
	if (c.FindOneOf(L"\n") > -1)	return true;
		return false;
}

bool is_space (CFSWString c) {
	if (c.FindOneOf(sp) > -1)	return true;
		return false;
}

bool is_fchar (CFSWString c) {
	if (c.FindOneOf(L"ÀÁÂÃàáâãÈÉÊËèéêëÌÍÎÏŸÝìíîïÿýÒÓÔÅòóôåÙÚÛùúûæÆØŒøœñÑçÇßÐÞðþ") > -1)	return true;
		return false;
}

bool is_underscore (CFSWString c) { //liitsõna värk, selleks lahku
	if (c.FindOneOf(L"_") > -1)	return true;
		return false;
}

bool is_symbol (CFSWString c) {
	if ( (c.FindOneOf(L"-*@#€$£%&/\\=+~<>§αβγδ") > -1) || is_underscore(c)) 	return true;
		return false;
}

bool is_digit (CFSWString c) {
	if (c.FindOneOf(L"0123456789") > -1)	return true;
		return false;
}

bool is_colon (CFSWString c) {
	if (c.FindOneOf(L":") > -1)	return true;
		return false;
}

bool is_semicolon (CFSWString c) {
	if (c.FindOneOf(L";") > -1)	return true;
		return false;
}

bool is_comma (CFSWString c) {
	if (c.FindOneOf(L",") > -1)	return true;
		return false;
}

bool is_dash (CFSWString c) {
	if (c.FindOneOf(L"–") > -1)	return true;
		return false;
}

bool is_hyphen (CFSWString c) {
	if (c.FindOneOf(L"-") > -1)	return true;
		return false;
}

bool is_bbracket (CFSWString c) {
	if (c.FindOneOf(L"([{") > -1)	return true;
		return false;
}

bool is_ebracket (CFSWString c) {
	if (c.FindOneOf(L")]}") > -1)	return true;
		return false;
}

bool is_bhyphen (CFSWString c) {
	if (is_hyphen(c) || is_dash(c)) return true;
		return false;
}


bool is_whitespace (CFSWString c) {
	if (is_tab(c) || is_space(c)) return true;
		return false;
}

bool is_vowel (CFSWString c) {
	if (is_lvowel(c) || is_uvowel(c)) return true;
		return false;
}

bool is_consonant (CFSWString c) {
	if (is_lconsonant(c) || is_uconsonant(c))	return true;
		return false;
}

bool is_upper (CFSWString c) {
	if (is_uconsonant(c) || is_uvowel(c))	return true;
		return false;
}

bool is_char (CFSWString c) {
	if (is_vowel(c) || is_consonant(c))	return true;
		return false;
}

bool is_conju (CFSWString c) {
	if (c == L"ja" || c == L"ning" || c == L"ega" || c == L"ehk" || c == L"või")	return true;
		return false;
}

bool is_compound_word (CFSWString c) {
		for (INTPTR i = 0; i < c.GetLength(); i++)
			if (is_underscore(c.GetAt(i))) return true;
		return false;
}

bool is_upper_word (CFSWString c) {
		for (INTPTR i = 0; i < c.GetLength(); i++)
			if (!is_upper(c.GetAt(i))) return false;
		return true;
}


bool is_fsymbol (CFSWString c) { //ainult tüübiarray jaoks
	if (is_symbol(c) || is_ending(c) || is_colon(c) || is_dash(c) || is_hyphen(c) || is_comma(c))	return true;
		return false;
}


bool has_vowel(CFSWString s) {
		for (INTPTR i = 0; i < s.GetLength(); i++)	{
			if (is_vowel(s.GetAt(i))) return true;
		}
		return false;
}

INTPTR ctype (CFSWString c) {
	if (is_char(c)) return 1;
		else
	if (is_fsymbol(c)) return 2;
	 else
	if (is_digit(c)) return 3;
	return 0;
}

void make_ctype_array (CFSWString s, CFSArray<CFSWString> &a) {
	for (INTPTR i = 0; i < s.GetLength(); i++)	{
		CFSWString c = s.GetAt(i);
		if (i == 0) {
			a.AddItem(c);
		}
		else {
			INTPTR arr_size = a.GetSize()-1;
			CFSWString lc = a[arr_size];
			lc = lc.GetAt(lc.GetLength()-1);
			if ( ctype(c) == ctype(lc) ) 
					a[arr_size] += c;			
				else 
					a.AddItem(c);
		}
	}
}


void MakeTypeArray (CFSWString s, CFSClassArray<TTypeRecord> &a) {
	TTypeRecord T;
	for (INTPTR i = 0; i < s.GetLength(); i++)	{
		CFSWString c = s.GetAt(i);
		if (i == 0) {
			T.s = c;
			a.AddItem(T);
		}
		else {
			INTPTR arr_size = a.GetSize()-1;
			CFSWString lc = a[arr_size].s;
			lc = lc.GetAt(lc.GetLength()-1);
			if ( ctype(c) == ctype(lc) ) 
					a[arr_size].s += c;			
				else {
				T.s = c;
				a.AddItem(T);
				}
		}
	}
	
	for (INTPTR i = 0; i < a.GetSize(); i++) {		
		a[i].Type = ctype(a[i].s.GetAt(0));
	}
/*	P.prnn(L"MAKE TYPE ARRAYST");
	for (INTPTR i = 0; i < a.GetSize(); i++) {
		P.prn(a[i].s);
		P.prni(a[i].Type);
		P.prnn();
	
	}
*/
}



CFSWString make_char_string (CFSWString c) {
	CFSWString res;
	for (INTPTR i = 0; i < c.GetLength(); i++)	{
		if (is_char(c.GetAt(i))) res += c.GetAt(i);
	}		
	return res;
}
CFSWString make_digit_string (CFSWString c) {
	CFSWString res;
	for (INTPTR i = 0; i < c.GetLength(); i++)	{
		if (is_digit(c.GetAt(i))) res += c.GetAt(i);
	}		
	return res;
}

CFSWString its(INTPTR i) {
    /* kui foneeme on lausungis rohkem, kui 1M - kukub */
    if (i < 0) return L"x";
    CFSWString s = empty_str;
    wchar_t buffer [8];
    swprintf(buffer, 8, L"%i", i);
    s += buffer;
    return s;
}
INTPTR explode(CFSWString s, CFSWString cSplitter, CFSArray<CFSWString> &Array) {
	Array.Cleanup();
	INTPTR ipStart=0;
	for (INTPTR ip=0; ip<s.GetLength(); ip++){
		if (s.GetAt(ip)==cSplitter){
			Array.AddItem(s.Mid(ipStart, ip-ipStart));
			ipStart=ip+1;
		}
		else
		if (cSplitter.GetLength() == 0)
			Array.AddItem(s.GetAt(ip));
	}
	if (cSplitter.GetLength() > 0) 
		Array.AddItem(s.Mid(ipStart));
	return Array.GetSize();
}


CMorphInfo clean_anaroot_output (CMorphInfo MI) {
	CFSWString s;
	for (INTPTR i=0; i < MI.m_szRoot.GetLength(); i++) {
		if (MI.m_szRoot.GetAt(i) != L'=') s += MI.m_szRoot.GetAt(i);
	}	
	MI.m_szRoot = s;
	return MI;
}

bool NumberIsOK(CFSWString s) {
	//return false;
	if (make_digit_string(s).GetLength() == s.GetLength()) return true;
	CFSArray<CFSWString> A;
	s.Replace(L".", L",", 1);
	int x = explode(s, L",", A);
	
	if ( A.GetSize() == 2){ 
		if (A[0].GetLength() == make_digit_string(A[0]).GetLength()
			&&
			A[1].GetLength() == make_digit_string(A[1]).GetLength()
			)       
		{
			
			return true;
		}
	}

	return false;
}


const char* ccstr (CFSWString s) {
    return FSStrWtoA(s, FSCP_UTF8);
}


INTPTR is_abbreviation(CFSWString s, CFSArray<CFSWString> &a) {
    // Lühendid EKRst
    if (s.GetAt(s.GetLength() - 1) == L'.') s.Delete(s.GetLength() - 1, 1);


//    if (s == L"aj") return explode(L"ajutine", sp, a);
    if (s == L"ak") return explode(L"arveldus_konto", sp, a);
    if (s == L"apr") return explode(L"aprill", sp, a);
    if (s == L"AS") return explode(L"aktsia_selts", sp, a);
    if (s == L"aug") return explode(L"august", sp, a);
    if (s == L"aü") return explode(L"ameti_ühing", sp, a);
    if (s == L"ca") return explode(L"tsirka", sp, a);
    if (s == L"dets") return explode(L"detsember", sp, a);
  //  if (s == L"dl") return explode(L"dessert_lusika_täis", sp, a);
    if (s == L"dots") return explode(L"dotsent", sp, a);
    if (s == L"dr") return explode(L"doktor", sp, a);
    if (s == L"eKr") return explode(L"enne Kristuse sündi", sp, a);
    if (s == L"EL") return explode(L"Euroopa Liit", sp, a);
    if (s == L"e.m.a") return explode(L"enne meie aja_arvamist", sp, a);
//    if (s == L"end") return explode(L"endine", sp, a);
    if (s == L"FIE") return explode(L"füüsilisest isikust ette_võtja", sp, a);
    //if (s == L"hr") return explode(L"härra", sp, a);
    if (s == L"hrl") return explode(L"harilikult", sp, a);
    if (s == L"ik") return explode(L"isiku_kood", sp, a);
  //  if (s == L"ins") return explode(L"insener", sp, a);
  //  if (s == L"it") return explode(L"info_tehnoloogia", sp, a);
    if (s == L"IT") return explode(L"info_tehnoloogia", sp, a);
    if (s == L"j.a") return explode(L"juures asuv", sp, a);
  //  if (s == L"jaan") return explode(L"jaanuar", sp, a);
  // ?  if (s == L"jj") return explode(L"ja järgmine", sp, a);
  // ?  if (s == L"jm") return explode(L"ja muud", sp, a);
    if (s == L"jms") return explode(L"ja muud sellised", sp, a);
    if (s == L"jmt") return explode(L"ja mitmed teised", sp, a);
  // ?  if (s == L"jn") return explode(L"joonis", sp, a);
    if (s == L"jne") return explode(L"ja nii edasi", sp, a);
    if (s == L"jpt") return explode(L"ja paljud teised", sp, a);
  //  if (s == L"jr") return explode(L"juunior", sp, a);
    if (s == L"jrk") return explode(L"järje_kord", sp, a);
    if (s == L"jsk") return explode(L"jaos_kond", sp, a);
    if (s == L"jt") return explode(L"ja teised", sp, a);
    if (s == L"juh") return explode(L"juhataja", sp, a);
    if (s == L"jun") return explode(L"juunior", sp, a);
  //  if (s == L"jv") return explode(L"järv", sp, a);
    if (s == L"k.a") return explode(L"kaasa arvatud", sp, a);
  // ?  if (s == L"kd") return explode(L"köide", sp, a);
    if (s == L"kg") return explode(L"kilogramm", sp, a);
    if (s == L"khk") return explode(L"kihel_kond", sp, a);
 //   if (s == L"kk") return explode(L"kesk_kool", sp, a);
 //   if (s == L"kl") return explode(L"kell", sp, a);
    if (s == L"knd") return explode(L"kandidaat", sp, a);
    if (s == L"kod") return explode(L"kodanik", sp, a);
  //  if (s == L"kpl") return explode(L"kauplus", sp, a);
  //  if (s == L"kr") return explode(L"kroon", sp, a);
  // ?  if (s == L"kt") return explode(L"kohuse_täitja", sp, a);
  //  if (s == L"kub") return explode(L"kubermang", sp, a);
  //  if (s == L"kv") return explode(L"kvartal", sp, a);
    if (s == L"KÜ") return explode(L"korteri_ühistu", sp, a);
    if (s == L"lg") return explode(L"lõige", sp, a);
  //  if (s == L"lj") return explode(L"linna_jagu", sp, a);
    if (s == L"lk") return explode(L"lehe_külg", sp, a);
  //  if (s == L"LK") return explode(L"loodus_kaitse all", sp, a);
  //  if (s == L"lm") return explode(L"liidu_maa", sp, a);
  //  if (s == L"lo") return explode(L"linna_osa", sp, a);
    if (s == L"lp") return explode(L"lugu_peetud", sp, a);
    if (s == L"lüh") return explode(L"lühemalt", sp, a); 
  //  if (s == L"M") return explode(L"meestele", sp, a);
    if (s == L"mag") return explode(L"magister", sp, a);
    if (s == L"m.a.j") return explode(L"meie aja_arvamise järgi", sp, a);
    if (s == L"mh") return explode(L"muu_hulgas", sp, a);
  //  if (s == L"min") return explode(L"minut", sp, a);
  // ? if (s == L"mk") return explode(L"maa_kond", sp, a);
    if (s == L"mld") return explode(L"miljard", sp, a);
    if (s == L"mln") return explode(L"miljon", sp, a);
    if (s == L"mnt") return explode(L"maantee", sp, a);
    if (s == L"mob") return explode(L"mobiil_telefon", sp, a);
 //   if (s == L"ms") return explode(L"muu_seas", sp, a);
    if (s == L"MTÜ") return explode(L"mitte_tulundus_ühing", sp, a);
    if (s == L"nim") return explode(L"nimeline", sp, a);
    if (s == L"nn") return explode(L"nii_nimetatud", sp, a);
    if (s == L"nov") return explode(L"november", sp, a);
    if (s == L"nr") return explode(L"number", sp, a);
    if (s == L"nt") return explode(L"näiteks", sp, a);
    if (s == L"nö") return explode(L"nii öelda", sp, a);
    if (s == L"okt") return explode(L"oktoober", sp, a);
    if (s == L"osk") return explode(L"osa_kond", sp, a);
    if (s == L"OÜ") return explode(L"osa_ühing", sp, a);
//    if (s == L"pa") return explode(L"pool_aasta", sp, a);
//    if (s == L"pk") return explode(L"post_kast", sp, a);
    if (s == L"pKr") return explode(L"pärast Kristuse sündi", sp, a);
    if (s == L"pms") return explode(L"peamiselt", sp, a);
    if (s == L"p.o") return explode(L"peab olema", sp, a);
 //   if (s == L"pr") return explode(L"proua", sp, a);
    if (s == L"prl") return explode(L"preili", sp, a);
    if (s == L"prof") return explode(L"professor", sp, a);
  //  if (s == L"ps") return explode(L"pool_saar", sp, a);
    if (s == L"pst") return explode(L"puies_tee", sp, a);
    if (s == L"ptk") return explode(L"pea_tükk", sp, a);
  //  if (s == L"raj") return explode(L"rajoon", sp, a);
    if (s == L"rbl") return explode(L"rubla", sp, a);
  //  if (s == L"RE") return explode(L"riigi_ettevõte", sp, a);
  //  if (s == L"reg") return explode(L"registreerimis", sp, a);
   // if (s == L"rg") return explode(L"registri", sp, a);
    if (s == L"rmtk") return explode(L"raamatu_kogu", sp, a);
  //  if (s == L"rkl") return explode(L"riigi_kogu_liige", sp, a);
    if (s == L"rtj") return explode(L"raud_tee_jaam", sp, a);
    if (s == L"SA") return explode(L"siht_asutus", sp, a);
    if (s == L"s.a") return explode(L"sel aastal", sp, a);
    if (s == L"saj") return explode(L"sajand", sp, a);
 //   if (s == L"sh") return explode(L"seal_hulgas", sp, a);
    if (s == L"sen") return explode(L"seenior", sp, a);
    if (s == L"sept") return explode(L"september", sp, a);
    if (s == L"skp") return explode(L"selle kuu päeval", sp, a);
    if (s == L"spl") return explode(L"supi_lusika_täis", sp, a);
    if (s == L"sl") return explode(L"supi_lusika_täis", sp, a);
 //   if (s == L"sm") return explode(L"seltsi_mees", sp, a);
    if (s == L"s.o") return explode(L"see on", sp, a);
    if (s == L"s.t") return explode(L"see tähendab", sp, a);
 //   if (s == L"st") return explode(L"see tähendab", sp, a);
    if (s == L"stj") return explode(L"saatja", sp, a);
    if (s == L"srn") return explode(L"surnud", sp, a);
   // if (s == L"sü") return explode(L"säilitus_üksus", sp, a);
 //   if (s == L"snd") return explode(L"sündinud", sp, a);
 //   if (s == L"tehn") return explode(L"tehniline", sp, a);
    if (s == L"tel") return explode(L"telefon", sp, a);
// ?    if (s == L"tk") return explode(L"tükk", sp, a);
    if (s == L"tl") return explode(L"teelusika_täis", sp, a);
    if (s == L"tlk") return explode(L"tõlkija", sp, a);
    if (s == L"Tln") return explode(L"Tallinn", sp, a);
 //   if (s == L"tn") return explode(L"tänav", sp, a);
 //   if (s == L"tr") return explode(L"trükk", sp, a);
    if (s == L"Trt") return explode(L"Tartu", sp, a);
 //   if (s == L"u") return explode(L"umbes", sp, a); 
    if (s == L"ukj") return explode(L"uue kalendri järgi", sp, a);
    if (s == L"UÜ") return explode(L"usaldus_ühing", sp, a);
 //   if (s == L"v.a") return explode(L"välja arvatud", sp, a);
    if (s == L"van") return explode(L"vananenud", sp, a);
//    if (s == L"VE") return explode(L"väike_ettevõte", sp, a);
    if (s == L"veebr") return explode(L"veebruar", sp, a);
    if (s == L"vkj") return explode(L"vana kalendri järgi", sp, a);
// ?   if (s == L"vm") return explode(L"või muud", sp, a);
    if (s == L"vms") return explode(L"või muu seesugune", sp, a);
    if (s == L"vrd") return explode(L"võrdle", sp, a);
    if (s == L"vt") return explode(L"vaata", sp, a);
    if (s == L"õa") return explode(L"õppe_aasta", sp, a);
 //   if (s == L"õp") return explode(L"õpetaja", sp, a);
    if (s == L"õpil") return explode(L"õpilane", sp, a);
    if (s == L"ÄÜ") return explode(L"äri_ühing", sp, a);
    if (s == L"ÜE") return explode(L"ühis_ette_võte", sp, a);
    if (s == L"SEK") return explode(L"Rootsi krooni", sp, a);
    if (s == L"NOK") return explode(L"Norra krooni", sp, a);
    if (s == L"RUR") return explode(L"Vene rubla", sp, a);
    if (s == L"USD") return explode(L"dollar", sp, a);
    if (s == L"GBP") return explode(L"nael", sp, a);
    if (s == L"LVL") return explode(L"latt", sp, a);
    if (s == L"LTL") return explode(L"litt", sp, a);
    if (s == L"EEK") return explode(L"kroon", sp, a);
    
 //   if (s == L"m") return explode(L"meeter", sp, a);
    if (s == L"mm") return explode(L"milli_meeter", sp, a);
    if (s == L"cm") return explode(L"senti_meeter", sp, a);
    if (s == L"dm") return explode(L"detsi_meeter", sp, a);
 //   if (s == L"km") return explode(L"kilo_meeter", sp, a);
  
    if (s == L"cl") return explode(L"sentiliiter", sp, a);
    if (s == L"ml") return explode(L"milli_liiter", sp, a);
    if (s == L"dl") return explode(L"detsi_liiter", sp, a);
  
    if (s == L"gr") return explode(L"gramm", sp, a);
    if (s == L"kg") return explode(L"kilo_gramm", sp, a);
 // if (s == L"t") return explode(L"tonn", sp, a);
 
 //   if (s == L"h") return explode(L"tund", sp, a);
 //   if (s == L"s") return explode(L"sekund", sp, a);
    if (s == L"m/s") return explode(L"meetrit sekundis", sp, a);
    if (s == L"km/h") return explode(L"kilo_meetrit tunnis", sp, a);
    if (s == L"km/t") return explode(L"kilo_meetrit tunnis", sp, a);
  
    if (s == L"m2") return explode(L"ruut_meeter", sp, a);
    if (s == L"m3") return explode(L"kuup_meeter", sp, a);
    if (s == L"Hz") return explode(L"herts", sp, a);
    if (s == L"kW") return explode(L"kilo_vatt", sp, a);
    if (s == L"kWh") return explode(L"kilo_vatt_tund", sp, a);
    if (s == L"dB") return explode(L"detsi_bell", sp, a);
    if (s == L"km2") return explode(L"ruut_kilo_meeter", sp, a);
    if (s == L"mg") return explode(L"milli_gramm", sp, a);
    if (s == L"mbar") return explode(L"milli_baar", sp, a);
    
	
	return 0;
}


CFSWString replace_fchar (CFSWString c) {
	if (c == L"À") return L"a";
	if (c == L"Á") return L"a";
	if (c == L"Â") return L"a";
	if (c == L"Ã") return L"a";
	if (c == L"à") return L"a";
	if (c == L"á") return L"a";
	if (c == L"â") return L"a";
	if (c == L"ã") return L"a";
	if (c == L"È") return L"e";
	if (c == L"É") return L"e";
	if (c == L"Ê") return L"e";
	if (c == L"Ë") return L"e";
	if (c == L"è") return L"e";
	if (c == L"é") return L"e";
	if (c == L"ê") return L"e";
	if (c == L"ë") return L"e";
	if (c == L"Ì") return L"i";
	if (c == L"Í") return L"i";
	if (c == L"Î") return L"i";
	if (c == L"Ï") return L"i";
	if (c == L"Ÿ") return L"i";
	if (c == L"Ý") return L"i";
	if (c == L"ì") return L"i";
	if (c == L"í") return L"i";
	if (c == L"î") return L"i";
	if (c == L"ï") return L"i";
	if (c == L"ÿ") return L"ü";
	if (c == L"ý") return L"ü";
	if (c == L"Ò") return L"o";
	if (c == L"Ó") return L"o";
	if (c == L"Ô") return L"o";
	if (c == L"Å") return L"o";
	if (c == L"ò") return L"o";
	if (c == L"ó") return L"o";
	if (c == L"ô") return L"o";
	if (c == L"å") return L"o";
	if (c == L"Ù") return L"u";
	if (c == L"Ú") return L"u";
	if (c == L"Û") return L"u";
	if (c == L"ù") return L"u";
	if (c == L"ú") return L"u";
	if (c == L"û") return L"u";
	if (c == L"æ") return L"ä";
	if (c == L"Æ") return L"ä";
	if (c == L"Ø") return L"ö";
	if (c == L"Œ") return L"ö";
	if (c == L"ø") return L"ö";
	if (c == L"œ") return L"ö";
	if (c == L"ñ") return L"n";
	if (c == L"Ñ") return L"n";
	if (c == L"ç") return L"s";
	if (c == L"Ç") return L"s";
	if (c == L"ß") return L"s";
	if (c == L"Ð") return L"k";
	if (c == L"Þ") return L"k";
	if (c == L"ð") return L"k";
	if (c == L"þ") return L"k";	
        
	return L"a";
}

CFSWString replace_schar (CFSWString c) {
    c = c.ToLower();
    if (c == L"a") return L"aa";
    if (c == L"b") return L"pee";
    if (c == L"c") return L"tse";
    if (c == L"d") return L"tee";
    if (c == L"e") return L"ee";
    if (c == L"f") return L"ef";
    if (c == L"g") return L"kee";
    if (c == L"h") return L"haa";
    if (c == L"i") return L"ii";
    if (c == L"j") return L"jott";
    if (c == L"k") return L"kaa";
    if (c == L"l") return L"ell";
    if (c == L"m") return L"emm";
    if (c == L"n") return L"enn";
    if (c == L"o") return L"oo";
    if (c == L"p") return L"pee";
    if (c == L"q") return L"kuu";
    if (c == L"r") return L"er";
    if (c == L"s") return L"ess";
    if (c == L"š") return L"shaa";
    if (c == L"ž") return L"shee";
    if (c == L"t") return L"tee";
    if (c == L"u") return L"uu";
    if (c == L"v") return L"vee";
    if (c == L"w") return L"kaksisvee";
    if (c == L"õ") return L"õõ";
    if (c == L"ä") return L"ää";
    if (c == L"ö") return L"öö";
    if (c == L"ü") return L"üü";
    if (c == L"x") return L"iks";
    if (c == L"y") return L"igrek";
    if (c == L"z") return L"tsett";
    if (c == L".") return L"punkt";
    if (c == L",") return L"koma";
    if (c == L":") return L"koolon";
    if (c == L";") return L"semikoolon";
    if (c == L"-") return L"kriips";
	if (c == L"–") return L"mõttekrips";
    if (c == L"_") return L"alakriips";
    if (c == L"*") return L"tärn";
    if (c == L"!") return L"hüüumärk";
    if (c == L"?") return L"küsimärk";
    if (c == L"@") return L"ätt";
    if (c == L"#") return L"trellid";
    if (c == L"€") return L"euro";
    if (c == L"$") return L"dollar";
    if (c == L"£") return L"nael";
	if (c == L"§") return L"paragraaf";
    if (c == L"%") return L"protsent";
    if (c == L"°") return L"kraad";
	if (c == L"&") return L"änd";
    if (c == L"/") return L"kaldkriips";
    if (c == L"\\") return L"tagurpidi kaldkriips";    
    if (c == L"=") return L"võrdub";
    if (c == L"+") return L"pluss";
    if (c == L"~") return L"tilde";
    if (c == L">") return L"suurem kui";
    if (c == L"<") return L"väiksem kui";    
    if (c == L"(") return L"sulgudes";
    if (c == L"[") return L"nurksulgudes";
    if (c == L"{") return L"loogsulgudes";
    if (c == L"α") return L"alfa";
    if (c == L"β") return L"beta";
    if (c == L"γ") return L"gamma";
    if (c == L"δ") return L"delta";
	
    
    return L"tundmatumärk";
}












