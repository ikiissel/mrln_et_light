#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../lib/etana/proof.h"
#include "../include/mklab.h"
//extern "C" {
//#include "../include/HTS_engine.h"
//}

 CDisambiguator Disambiguator;
 CLinguistic Linguistic;


typedef unsigned char uchar;

wchar_t *UTF8_to_WChar(const char *string) {
    long b = 0,
            c = 0;
    for (const char *a = string; *a; a++)
        if (((uchar) * a) < 128 || (*a & 192) == 192)
            c++;
    wchar_t *res = new wchar_t[c + 1];

    res[c] = 0;
    for (uchar *a = (uchar*) string; *a; a++) {
        if (!(*a & 128))
            res[b] = *a;
        else if ((*a & 192) == 128)
            continue;
        else if ((*a & 224) == 192)
            res[b] = ((*a & 31) << 6) | a[1]&63;
        else if ((*a & 240) == 224)
            res[b] = ((*a & 15) << 12) | ((a[1]&63) << 6) | a[2]&63;
        else if ((*a & 248) == 240) {
            res[b] = '?';
        }
        b++;
    }
    return res;
}

void ReadUTF8Text(CFSWString &text, const char *fn) {

    std::ifstream fs;
    fs.open(fn, std::ios::binary);
    if (fs.fail()) {
        fprintf(stderr,"Ei leia sisendteksti!\n");
        exit(1);
    }
    fs.seekg(0, std::ios::end);
    size_t i = fs.tellg();    
    fs.seekg(0, std::ios::beg);
    char* buf = new char[i+1];
    fs.read(buf, i);
    fs.close();
    buf[i] = '\0';
    wchar_t* w_temp = UTF8_to_WChar(buf);
    text = w_temp;
    delete [] buf;
    delete [] w_temp;
}

int PrintUsage() {
    fprintf(stderr,"\t-train 	  [sisendtekst on utf8 festivali formaadis] \n");
    fprintf(stderr,"\t-check_wav  [kataloog. kontrollib vastava wav-i olemasolu kataloogis]");
    fprintf(stderr,"\t-f 	  [sisendtekst utf8-s] \n");
    fprintf(stderr,"\t-o 	  [väljundi kataloog] \n");
    fprintf(stderr,"\t-lex 	  [analüüsi sõnastik]  \n");
    fprintf(stderr,"\t-lexd	  [ühestaja sõnastik]  \n");
    fprintf(stderr,"\n\tnäide: \n");
    fprintf(stderr,"\t\tbin/genlab -lex dct/et.dct -lexd dct/et3.dct \\ \n");
    fprintf(stderr,"\t\t-o lab/ -f in.txt\n");
    exit(0);
}

char *convert_vec(const std::string & s) {
    char *pc = new char[s.size() + 1];
    strcpy(pc, s.c_str());
    return pc;
}

void fill_char_vector(std::vector<std::string>& v, std::vector<char*>& vc) {
    std::transform(v.begin(), v.end(), std::back_inserter(vc), convert_vec);
}

void clean_char_vector(std::vector<char*>& vc) {
    for (size_t x = 0; x < vc.size(); x++)
        delete [] vc[x];
}




void cfileexists(const char * filename) {
    FILE *file;
    if (file = fopen(filename, "r")) {
        fclose(file);
        remove(filename);
    }
}

bool fileexists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

bool WriteToFile(std::string fn, std::string s) {
    std::ofstream file;
    file.open(fn.c_str());
    file << s;
    file.close();
return true;
}

std::string to_stdstring(CFSWString s) {
    std::string res = "";
    for (INTPTR i = 0; i < s.GetLength(); i++)
        res += s.GetAt(i);
    return res;
}

std::string to_stdstring_a(CFSAString s) {
    std::string res = "";
    for (INTPTR i = 0; i < s.GetLength(); i++)
        res += s.GetAt(i);
    return res;
}

void do_label_files(CFSWString text, CFSAString OutDir, std::string check_wav_dir) {
    CFSWString rida;
    CFSArray<CFSWString> arr;
    std::string file_id_list_scp;
        
    for (INTPTR i = 0; i < text.GetLength(); i++) {

        CFSWString c = text.GetAt(i);
        if (c == '\n') {
            arr.AddItem(rida);
            rida = L"";
        } else {
            rida += c;
        }
    }

    for (INTPTR i = 0; i < arr.GetSize(); i++) {

        rida = arr[i];
        rida.Delete(0, 2);

        //wprintf(L"\n");
        CFSWString fname = rida.Mid(0, rida.Find(L" "));
        
        std::string out_dir = to_stdstring_a(OutDir);
        
        std::string fn = to_stdstring(rida.Mid(0, rida.Find(L" ")));
                
        /*
         Kontroll, et kas vastavad wav-d on olemas
         */
        file_id_list_scp += fn + "\n";
        if (check_wav_dir.length() > 0) {
            
           if (fileexists(check_wav_dir + fn + ".wav") == false) {
               
               std::cout << "Puudub " + fn + ".wav\n";
           }
        }
        
        
        fn = out_dir + fn + ".lab";
        rida.Delete(0, rida.Find(L" ")+2);
        
        
        wprintf(fname+L"\n");
        //wprintf(L"\n");
        rida = DealWithText(rida);
        CFSArray<CFSWString> rres = do_utterances(rida);
        CFSArray<CFSWString> lab;
          //wprintf(rres[0]);
          //wprintf(L"\t");

        lab = do_all(rres[0], false, false);        
        std::string tulemus = "";
        for (INTPTR u = 0; u < lab.GetSize(); u++) {
            tulemus += to_stdstring(lab[u]);
            if (u < (lab.GetSize() - 1)) tulemus += "\n";
        }
        
        WriteToFile(fn, tulemus);

    }
    WriteToFile("file_id_list.scp", file_id_list_scp);    
    wprintf(L"\nValmis");
    wprintf(L"\n");
    
    exit(1);
}

int main(int argc, char* argv[]) {
    
    
    char* in_fname;
    
    
    
    
    bool train = false;    
    
    

    CFSAString LexFileName, LexDFileName, OutDir;
    std::string fn_text = "temp";
    std::string file_id_dir = "";
    std::string check_wav_dir = "";
    FSCInit();    
    

    for (int i = 0; i < argc; i++) {
        if (CFSAString("-lex") == argv[i]) {
            if (i + 1 < argc) {
                LexFileName = argv[++i];
            } else {
                return PrintUsage();
            }
        }
        if (CFSAString("-lexd") == argv[i]) {
            if (i + 1 < argc) {
                LexDFileName = argv[++i];
            } else {
                return PrintUsage();
            }
        }
        if (CFSAString("-check_wav") == argv[i]) {
            if (i + 1 < argc) {                
                check_wav_dir = argv[++i];
            } else {
                return PrintUsage();
            }
        }
        
        if (CFSAString("-o") == argv[i]) {
            if (i + 1 < argc) {
                OutDir = argv[i + 1];
                //cfileexists(output_fname);
            } else {
                fprintf(stderr, "Viga: puudb väljundkataloog\n");
                PrintUsage();
                exit(0);
            }
        }
        if (CFSAString("-f") == argv[i]) {
            if (i + 1 < argc) {
                in_fname = argv[i + 1];
            } else {
                fprintf(stderr, "Viga: puudb sisendfaili nimi\n");
                PrintUsage();
                exit(0);
            }
        }
       
        if (CFSAString("-train") == argv[i]) {
            train = true;
        }
    }

    Linguistic.Open(LexFileName);
    Disambiguator.Open(LexDFileName);

    CFSWString text;
    ReadUTF8Text(text, in_fname);

    if (train) {
       do_label_files(text, OutDir, check_wav_dir);
       exit(0);
    }
    
    std::string file_id_list;
    text = DealWithText(text);
    CFSArray<CFSWString> res = do_utterances(text);
    
    for (INTPTR i = 0; i < res.GetSize(); i++) {

        CFSArray<CFSWString> label = do_all(res[i], false, false);
        std::string s;
        for (INTPTR j = 0; j < label.GetSize(); j++) {
            s += to_stdstring(label[j]);
            if (j < (label.GetSize() - 1)) s += "\n";
        }
        std::string nr = std::to_string(i);
        
        if (nr.length() == 1) nr = "0" + nr; // Ilu peräst
        
        file_id_list += fn_text + nr + "\n";
        
        std::string  fn = to_stdstring_a(OutDir)+ "prompt-lab/" + fn_text + nr + ".lab";        
        WriteToFile(fn, s);


    } //synth loop
    
    WriteToFile(to_stdstring_a(OutDir) + "test_id_list.scp", file_id_list);
    Linguistic.Close();
    FSCTerminate();
    return 0;
}
