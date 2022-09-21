#include "../etana/proof.h"
#include "util.h"


CFSWString SylVowel(CFSClassArray<TPhone> A) {
	
	for (INTPTR i = 0; i < A.GetSize(); i++) {		
		if (A[i].Phone == L"a" || A[i].Phone == L"e" || A[i].Phone == L"i" ||
			A[i].Phone == L"o" || A[i].Phone == L"u" || A[i].Phone == L"ou" ||
			A[i].Phone == L"ae" || A[i].Phone == L"oe" || A[i].Phone == L"ue") 
			return A[i].Phone;
	}
		return L"x";
}

CFSWString gpos(CFSWString c) {
    CFSWString res = L"z";
    if (c.FindOneOf(L"DGIKXY") > -1) return res = L"d";
    else
        if (c.FindOneOf(L"ACHNOPSU") > -1) return res = L"a";
    else
        if (c.FindOneOf(L"V") > -1) return res = L"v";
    else
        if (c.FindOneOf(L"J") > -1) return res = L"j";
    else
        return res;
}

void CalcPhrases(CFSClassArray<TWord> &TWA) {
	
	
	INTPTR MaxP = TWA[TWA.GetSize()-1].h3;
	CFSArray<INTPTR> PSylCount;
        CFSArray<INTPTR> PWordCount;
	for (INTPTR Ph = 1; Ph <= MaxP; Ph++) {
		INTPTR CSF = 0;
		INTPTR CAF = 0;
                INTPTR SylCount = 0;
		CFSArray<INTPTR> A, B;
		for(INTPTR i = 0; i < TWA.GetSize(); i++) {
			
			if (TWA[i].h3 == Ph) {				
				CAF++;
				TWA[i].e3 = CAF;
				B.InsertItem(0, CAF);

				for (INTPTR j = 0; j < TWA[i].TSA.GetSize(); j++) {
					CSF++;
                                        SylCount++;
					TWA[i].TSA[j].b6 = CSF;
					A.InsertItem(0, CSF);
				}

			}
		  }
		
		INTPTR C = 0;
		INTPTR D = 0;
                INTPTR h1 = A[0];                
                INTPTR h2 = B[0];
                PSylCount.AddItem(h1);
                PWordCount.AddItem(h2);
                
		
		for(INTPTR i = 0; i < TWA.GetSize(); i++) {			
			if (TWA[i].h3 == Ph) {
				TWA[i].e4 = B[D];
                                TWA[i].h1 = h1;
                                TWA[i].h2 = h2;
                                TWA[i].h3 = Ph;
                                TWA[i].h4 = MaxP - (Ph-1);
				D++;
				for (INTPTR j = 0; j < TWA[i].TSA.GetSize(); j++) {
					TWA[i].TSA[j].b7 = A[C];
					C++;
				}

			}
		}
		
		
		

	}
        INTPTR USylCount = 0, UWordCount = 0;
        for (int i = 0; i < PSylCount.GetSize(); i++)
            USylCount += PSylCount[i];

        for (int i = 0; i < PWordCount.GetSize(); i++)
            UWordCount += PWordCount[i];



	for (INTPTR Ph = 1; Ph <= MaxP; Ph++) {
		for(INTPTR i = 0; i < TWA.GetSize(); i++) {
                    TWA[i].j1 = USylCount;
                    TWA[i].j2 = UWordCount;
                    TWA[i].j3 = MaxP;
                    if (TWA[i].h3 == Ph) {

                        if (Ph == 1) {

                            TWA[i].g1 = 0;
                            TWA[i].g2 = 0;
                        }
                        else {
                         TWA[i].g1 = PSylCount[Ph-2];
                         TWA[i].g2 = PWordCount[Ph-2];
                        }

                
                        if (Ph == MaxP) {
                            TWA[i].i1 = 0;
                            TWA[i].i2 = 0;
                            
                        }
                        else {
                         TWA[i].i1 = PSylCount[Ph];
                         TWA[i].i2 = PWordCount[Ph];
                            
                        }
                    
                    }



                }
        }




}

void TUtterance::DoCalculations(CFSClassArray<TWord> &TWA) {
	INTPTR iWord = TWA.GetSize();
	for (INTPTR i = 0; i < iWord; i++) {
		
		TWA[i].e1 = gpos(TWA[i].TWMInfo.m_cPOS);
		if (i > 0) {
		TWA[i].d1 = gpos(TWA[i-1].TWMInfo.m_cPOS);
		TWA[i].d2 = TWA[i-1].TSA.GetSize();	
		} else
		{
			TWA[i].d1 = L"x";
			TWA[i].d2 = 0;
		}
		if (i < TWA.GetSize()-1) {
			TWA[i].f1 = gpos(TWA[i+1].TWMInfo.m_cPOS);
			TWA[i].f2 = TWA[i+1].TSA.GetSize();	
		} else
		{
			TWA[i].f1 = L"x";
			TWA[i].f2 = 0;
			
		}
		
		INTPTR jSyl = TWA[i].TSA.GetSize();
		for (INTPTR j = 0; j < jSyl; j++) {
			TSyl S;
			if (j > 0)
				S = TWA[i].TSA[j - 1];
			else
				if (i > 0)
				S = TWA[i - 1].TSA[TWA[i - 1].TSA.GetSize() - 1];

			if (S.Syl.GetLength() > 0) {
				TWA[i].TSA[j].a1 = S.Stress;
				TWA[i].TSA[j].a2 = S.DoQ;
				TWA[i].TSA[j].a3 = S.TPA.GetSize();
			} else {
				TWA[i].TSA[j].a1 = 0;
				TWA[i].TSA[j].a2 = 0;
				TWA[i].TSA[j].a3 = 0;
			}
			TWA[i].TSA[j].b1 = TWA[i].TSA[j].Stress;
			TWA[i].TSA[j].b2 = TWA[i].TSA[j].DoQ;
			TWA[i].TSA[j].b4 = j + 1;
			TWA[i].TSA[j].b5 = jSyl - j;
			TWA[i].TSA[j].b16 = SylVowel(TWA[i].TSA[j].TPA);

			if (j < jSyl - 1)
				S = TWA[i].TSA[j + 1];
			else
				if (i < iWord - 1)
				S = TWA[i + 1].TSA[0];
			else
				S.Syl = L"";
					


			if (S.Syl.GetLength() > 0) {
				TWA[i].TSA[j].c1 = S.Stress;
				TWA[i].TSA[j].c2 = S.DoQ;
				TWA[i].TSA[j].c3 = S.TPA.GetSize();
			} else {
				TWA[i].TSA[j].c1 = 0;
				TWA[i].TSA[j].c2 = 0;
				TWA[i].TSA[j].c3 = 0;
			}
			
			INTPTR kPhone = TWA[i].TSA[j].TPA.GetSize();
			for (INTPTR k = 0; k < kPhone; k++) {




			} //kPhone

		} //jSyl
		
	} //iWord

	CalcPhrases(TWA);

}
//Printer Pr;

CFSClassArray<TPhone> TUtterance::DoPhoneArray(CFSClassArray<TWord> &TWA, INTPTR ut){
    CFSClassArray<TPhone> TPA;
	INTPTR LastBreak;
	CFSWString BreakEnd;
    for(INTPTR i = 0; i < TWA.GetSize(); i++) {
        TWord W = TWA[i];
        for (INTPTR j = 0; j < TWA[i].TSA.GetSize(); j++){
            TSyl S = TWA[i].TSA[j];
            for (INTPTR k = 0; k < TWA[i].TSA[j].TPA.GetSize(); k++) {
                TPhone P = TWA[i].TSA[j].TPA[k];
                P.PhraseBreak = W.h3;
				P.PL = L"";
                P.PL = its(P.p6) + L"_" + its(P.p7);
                P.PL += L"/A:" + its(S.a1) + L"_" + its(S.a2) + L"_" + its(S.a3);
                P.PL += L"/B:" + its(S.b1) + L"-" + its(S.b2) + L"-" + its(S.b3) + L"@" + its(S.b4) + L"-" + its(S.b5) + L"&" + its(S.b6) + L"-" + its(S.b7)+ L"|" + S.b16;
                P.PL += L"/C:" + its(S.c1) + L"+" + its(S.c2) + L"+" + its(S.c3);
				P.PL += L"/D:" + W.d1 + L"_" + its(W.d2);
				P.PL += L"/E:" + W.e1 + L"+" + its(W.e2) + L"@" + its(W.e3) + L"+" + its(W.e4);
				P.PL += L"/F:" + W.f1 + L"_" + its(W.f2);
                P.PL += L"/G:" + its(W.g1) + L"_" + its(W.g2);
                P.PL += L"/H:" + its(W.h1) + L"=" + its(W.h2) + L"^" + its(W.h3) + L"=" + its(W.h4);
				P.PL += L"/I:" + its(W.i1) + L"=" + its(W.i2);
				P.PL +=  L"/J:" + its(ut) + L"^" + its(W.j1) + L"+" + its(W.j2) + L"-" + its(W.j3);				
                                TPA.AddItem(P);
            }
        }
		BreakEnd = L"/J:" + its(ut) + L"^" + its(W.j1) + L"+" + its(W.j2) + L"-" + its(W.j3);
	}
	CFSWString Break = L"x_x/A:0_0_0/B:0-0-0@0-0&0-0|x/C:0+0+0/D:x_0/E:x+0@0+0/F:x_0/G:0_0/H:0=0^0=0/I:0=0" + BreakEnd;
	TPhone P;
	P.PL = Break;
	P.Phone = L"brth";
	CFSClassArray<TPhone> TPA2;
	
	
	for (INTPTR i = 0; i < TPA.GetSize(); i ++) {
		if (i == 0) {
			P.Phone = L"brth";
			TPA2.AddItem(P);
		}
		if (i > 0 && TPA[i].PhraseBreak != TPA[i-1].PhraseBreak) {
			P.Phone = L"pau";
			TPA2.AddItem(P);
		}
			
		TPA2.AddItem(TPA[i]);
	}
	P.Phone = L"brth";
	TPA2.AddItem(P);
	
	
	TPA.Cleanup();
	for (INTPTR i = 0; i < TPA2.GetSize(); i++) {
		TPhone P = TPA2[i];

		if (i == 0) {
	P.Phone = L"x^x-" +
							P.Phone +  L"+" +
							TPA2[i+1].Phone +  L"=" +
							TPA2[i+2].Phone + L"@";			
		} else
			if (i == 1) {
					P.Phone = L"x^" +
							TPA2[i-1].Phone + L"-" +
							P.Phone +  L"+" +
							TPA2[i+1].Phone +  L"=" +
							TPA2[i+2].Phone + L"@";
			} else
				if (i == TPA2.GetSize() - 2) {
						P.Phone = TPA2[i-2].Phone + L"^" +
							TPA2[i-1].Phone + L"-" +
							P.Phone +  L"+" +
							TPA2[i+1].Phone +  L"=" +
							L"x" + L"@";
				} else
					if (i == TPA2.GetSize() - 1) {
						
						P.Phone = TPA2[i-2].Phone + L"^" +
							TPA2[i-1].Phone + L"-" +
							P.Phone +  L"+" +
							L"x" +  L"=" +
							L"x" + L"@";
					} else
					{
						P.Phone = TPA2[i-2].Phone + L"^" +
							TPA2[i-1].Phone + L"-" +
							P.Phone +  L"+" +
							TPA2[i+1].Phone +  L"=" +
							TPA2[i+2].Phone + L"@";
					}
		P.Phone += P.PL;
		TPA.AddItem(P);
	}
	
	
	return TPA;
}







