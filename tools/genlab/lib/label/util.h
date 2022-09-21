#include "../etana/proof.h"


struct phone_struct {
    CFSWString phone;
    CFSWString lpos, pos, rpos;
    INTPTR syl_p, word_p, phr_p, utt_p;
    INTPTR p6, p7, a1, a3, b1, b3, c1, c3, b4, b5, b6, b7, d2, e2, f2, e3, e4, g1, g2, h1, h2, i1, i2, h3, h4, j1, j2, j3;
};

struct syl_struct {
    CFSWString syl;
    INTPTR stress;
    CFSArray<phone_struct> phone_vector;
    INTPTR phone_c, word_p, phr_p, utt_p;
};

struct word_struct {
    CMorphInfo mi;
    CFSArray<syl_struct> syl_vector;
    INTPTR phone_c, syl_c, phr_p, utt_p;
};

struct phrase_struct {
    CFSWString s;
    CFSArray<word_struct> word_vector;
    INTPTR phone_c, syl_c, word_c, utt_p;
};

struct utterance_struct {
    CFSWString s;
    CFSArray<phrase_struct> phr_vector;
    INTPTR phone_c, syl_c, word_c, phra_c;
};

struct text_struct {
    CFSArray<utterance_struct> utt_vector;
};

const CFSWString sp = L" ";
const CFSWString d = L"-";
const CFSWString colon = L":";
const CFSWString no_synth = L"-";
const CFSWString empty_str = L""; //peaks vaatama, et kuidas ilusti nullida
const CFSWString doq = L"w";

bool is_lvowel(CFSWString c);
bool is_uvowel(CFSWString c);
bool is_lconsonant(CFSWString c);
bool is_uconsonant(CFSWString c);
bool is_vowel(CFSWString c);
bool is_consonant(CFSWString c);
bool is_upper(CFSWString c);
bool is_char(CFSWString c);
bool is_fchar(CFSWString c);
bool is_tab(CFSWString c);
bool is_break(CFSWString c);
bool is_space(CFSWString c);
bool is_whitespace(CFSWString c);
bool is_ending(CFSWString c);
bool is_digit(CFSWString c);
bool is_dash (CFSWString c);
bool is_colon(CFSWString c);
bool is_semicolon(CFSWString c);
bool is_comma(CFSWString c);
bool is_symbol(CFSWString c);
bool is_bbracket(CFSWString c);
bool is_ebracket(CFSWString c);
bool is_conju(CFSWString c);
bool is_hyphen(CFSWString c);
bool is_bhyphen(CFSWString c);
bool is_underscore(CFSWString c);
bool is_compound_word(CFSWString c);
bool is_upper_word(CFSWString c);

bool has_vowel(CFSWString s);
void make_ctype_array(CFSWString s, CFSArray<CFSWString> &a);

CFSWString make_char_string(CFSWString c);
CFSWString make_digit_string(CFSWString c);
INTPTR ctype(CFSWString c);

INTPTR is_abbreviation(CFSWString s, CFSArray<CFSWString> &a);
CFSWString replace_fchar(CFSWString c);
CFSWString replace_schar(CFSWString c);
INTPTR explode(CFSWString s, CFSWString cSplitter, CFSArray<CFSWString> &Array);
CMorphInfo clean_anaroot_output(CMorphInfo MI);
CFSWString its(INTPTR i);

//Muud jubinad

// fprintf sobilik convert
const char* ccstr(CFSWString s);

CFSWString its(INTPTR i);
bool NumberIsOK(CFSWString s);

//INTPTR UttType = 1;


class PPrinter {

    CFSWString length(CFSWString s, INTPTR l) {
        while (s.GetLength() < l)
            s += L" ";
        return s;
    }

    const char* cstr(CFSWString s) {
        return FSStrWtoA(s, FSCP_UTF8);
    }

public:
    /* tulba laius */
    INTPTR l = 25;

    /* prindib %s+space */
    void pr(CFSWString s) {

        fprintf(stderr, "%s ", cstr(s));
    }
    /* prindib lihtsalt  %s + l */
    void prn(CFSWString s) {
        s = length(s, l);
        fprintf(stderr, "%s", cstr(s));
    }

    /* prindib \\n */
    void prnn() {
        fprintf(stderr, "\n");
    }

    /* prindib %s\\n */
    void prnn(CFSWString s) {
        s = length(s, l);
        fprintf(stderr, "%s\n", cstr(s));
    }
    /* prindib %s1\\t%s2\\n */
    void prn2n(CFSWString s1, CFSWString s2) {
        s1 += L" " + s2;
        s1 = length(s1, l);
        fprintf(stderr, "%s1\n", cstr(s1));
    }
    
    
    /* prindib \\t%s\\n */
    void prntn(CFSWString s) {
        s = length(s, l);
        fprintf(stderr, "\t%s\n", cstr(s));
    }
/* prindib täisatvu*/
    void prni (INTPTR i) {
        //CFSWString s = length (s, l);
        CFSWString nr = its(i);
        //nr = length (nr, l);
        fprintf(stderr, "%s ", cstr(nr));
                
    }

};

        
        
        
/*Tipmine class kuhu ühestamise tulemus kokku võtta*/
class TPhone {
public:
    CFSWString Phone;
    CFSWString PL;
    INTPTR PhraseBreak;
    CFSWString pp, p, n, nn;
    /* position of the current phoneme identity in the current syllable (forward)
    position of the current phoneme identity in the current syllable (backward) */
    INTPTR p6, p7;
    // the number of phrases in this utterance
    //INTPTR j3;
};

class TSyl {
public:
    /*
     whether the previous syllable stressed or not (0: not stressed, 1: stressed)
     whether the previous syllable accented or not (0: not accented, 1: accented)
     the number of phonemes in the previous syllable
     * "x" väärtused kõik välja
     */
    INTPTR a1, a2, a3;
    /* 
     *whether the current syllable stressed or not (0: not stressed, 1: stressed)
      whether the current syllable accented or not (0: not accented, 1: accented)
     * the number of phonemes in the current syllable 
     */
    INTPTR b1, b2, b3;
    /*
     position of the current syllable in the current word (forward)
     position of the current syllable in the current word (backward)     
     */
    INTPTR b4, b5;
    
    /*
     position of the current syllable in the current phrase (forward)
     position of the current syllable in the current phrase (backward)
     */
    INTPTR b6, b7;
    
    /*
    name of the vowel of the current syllable
     */
    CFSWString b16;
    /*
     whether the next syllable stressed or not (0: not stressed, 1: stressed)
     whether the next syllable accented or not (0: not accented, 1: accented)
    the number of phonemes in the next syllable     
     */
    INTPTR c1, c2, c3;


    
    CFSWString Syl;
    INTPTR Stress;
    INTPTR DoQ = 0;
    CFSClassArray<TPhone> TPA;
    void DoPhones (TSyl &T);
};

class TWord {
private:
public:
    /* 
     * gpos (guess part-of-speech) of the current word
     * the number of syllables in the current word 
     * position of the current word in the current phrase (forward)
     * position of the current word in the current phrase (backward)
     */
    CFSWString e1;
    INTPTR e2;
    INTPTR e3, e4;

    /*
     gpos (guess part-of-speech) of the next word
     the number of syllables in the next word
     */
    CFSWString f1;
    INTPTR f2;
    /*the number of syllables in the previous phrase
    the number of words in the previous phrase*/
    INTPTR g1, g2;
    
    /*
    the number of syllables in the current phrase
    the number of words in the current phrase
     */
     INTPTR h1, h2;
    
    /*  h3 position of the current phrase in this utterance (forward) 
        h4 position of the current phrase in this utterance (backward) 
        */
    INTPTR h3, h4;

    /*
     
     the number of syllables in the next phrase
the number of words in the next phrase
     */
    
    INTPTR i1, i2;

    /*
       j1 the number of syllables in this utterance
     * j2 the number of words in this utterance
     * j3 the number of phrases in this utterance 
     */
    
    INTPTR j1, j2, j3;

    /*
     gpos (guess part-of-speech) of the previous word
     the number of syllables in the previous word
     */
    CFSWString d1;
    INTPTR d2;

    
    CFSWString Token;
    CMorphInfo TWMInfo;
    /*Sõna lõpetab fraasi
     1 = lihtne fraasipiir
     2 = jõuga fraasipiir nt "sulgudes"*/
    INTPTR PhrBreakAfter = 0;
    
    /*
     Lause tüüp 1=jutustav, 2=hüüd, 3=küsi
     */
    INTPTR UttType = 1;
    
    
    /*Liidab tüvele lõpud*/
    CFSClassArray<TSyl> TSA;
    
    void AddEndings() {
        TWMInfo.m_szRoot += make_char_string(TWMInfo.m_szEnding) + TWMInfo.m_szClitic;
    }
    void CleanUp() {
        Token = L"";
        TWMInfo.m_cPOS = 0;
        TWMInfo.m_szRoot = L"";
        TWMInfo.m_szClitic = L"";
        TWMInfo.m_szForm = L"";
    }

};

class TTypeRecord {
public:
    CFSWString s;
    INTPTR Type;
};


class TUtterance {
private:
    CFSClassArray<TWord> DoTokens(CFSClassArray<TWord> TWA);
    CFSClassArray<TWord> DoNumbers(CFSClassArray<TWord> TWA);
    void DoSyls(TWord &TW);
    void DoCalculations(CFSClassArray<TWord> &TWA);
    void DoPhrases(CFSClassArray<TWord> &TWA);
    CFSClassArray<TPhone> DoPhoneArray(CFSClassArray<TWord> &TWA, INTPTR ut);
    
public:
    CFSClassArray<TWord> TWA;
    CFSClassArray<TPhone> TPA;
    
    INTPTR UttT = 1;
    
    void AnalyzeText() {
        TWA = DoTokens(TWA);
        TWA = DoNumbers(TWA);
    }
    /*Sõnad silpideks ja silbid foneemideks*/
    void Syllabify() {
        for (INTPTR i = 0; i < TWA.GetSize(); i++) {
            DoSyls(TWA[i]);
	}
    }
    /*Fraseerimine*/
    void Phrasing() {
        DoPhrases(TWA);
    }
     void Calculate() {
        DoCalculations(TWA);
    }
     void PhoneArray() {
        TPA = DoPhoneArray(TWA, UttT);
      }
    
};

void MakeTypeArray (CFSWString s, CFSClassArray<TTypeRecord> &a);