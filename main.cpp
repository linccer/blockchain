#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm> 
#include <chrono> 
#include <bitset>
#include <limits>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::to_string;
using std::bitset;
using std::numeric_limits;
using std::streamsize;


void readf();
string hash();
void add(vector<int>& vec, unsigned long long x);
void square(vector<int>& vec);
void collisionTest ();
void avalancheTest ();
double comparehex(string hash1, string hash2);
double comparebit(string hash1, string hash2);
int charToHexVal(char a);


string input="";
const int X = 73;



int main () {

    char choice='a';
    bool readfile=false;
    bool testcollisions=false;
    bool testavalanche=false;

    cout<<"Atlikti koliziju testa failui generated.txt? Taip - 'T', Ne - 'N'\n";
        cin>>choice;
        if (choice=='t' || choice=='T') testcollisions=true;
        else {  while (choice!='n' && choice!='N' && choice!='t' && choice!='T') {cout<<"\nKlaida. Iveskite T arba N. "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin>>choice;}  }

    choice='a';
    cout<<"Atlikti procentinio skirtingumo testa failui generated2.txt? Taip - 'T', Ne - 'N'\n";
        cin>>choice;
        if (choice=='t' || choice=='T') testavalanche=true;
        else {  while (choice!='n' && choice!='N' && choice!='t' && choice!='T') {cout<<"\nKlaida. Iveskite T arba N. "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin>>choice;}  }

    choice='a';
    cout<<"Skaityti input faila? Taip - 'T', Ne - 'N'\n";
        cin>>choice;
        if (choice=='t' || choice=='T') readfile=true;
        else {  while (choice!='n' && choice!='N' && choice!='t' && choice!='T') {cout<<"\nKlaida. Iveskite T arba N. "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin>>choice;}  }






    if (readfile) readf(); 


auto start = std::chrono::high_resolution_clock::now();    //start timer


    if (readfile) cout<<"Sugeneruotas hash:\n"<<hash();
    if (testcollisions) collisionTest();
    if (testavalanche) avalancheTest();


auto stop = std::chrono::high_resolution_clock::now();     //end timer
std::chrono::duration<double> dur = stop-start;
cout<<"\nProgramos darbo laikas: "<< dur.count()<<endl;

}
//________________________________________________________________________________________________________________________________________________________



void readf(){

    cout<<"\nIveskite input failo pavadinima  (pvz:  input.txt)\n";
    string txt="";
    cin>>txt;
    //txt="input.txt";

    ifstream file(txt);
    try { if (file.fail()) { throw 1; }

        stringstream sstream;
        sstream << file.rdbuf();
        input = sstream.str();

    } catch (int) { cout<<"Failas nerastas. "; txt="";}
    
}
//________________________________________________________________________________________________________________________________________________________



string hash(){

    unsigned long long unicode;
    vector<int> value;

     //  for each character of the input string:
    while (input.length()!=0){

        unicode = static_cast<int>(static_cast<char>(input[0]));    //get unicode
        //cout<<unicode<<" ";
        unicode = unicode * pow(X,(input.length() % 10));   //X raised to length % 9
        //cout<<unicode<<endl;

        add(value, unicode);


        input.erase(0, 1);
        unicode=0;
    }



    //adjust length to be over 64
    while(value.size()<64) {
        square(value); 
    }



    //output
    string output="";
    for (auto &i:value) {
        if(i<10) output+=to_string(i);
        else switch (i) {
            case 10: output+="a"; break;
            case 11: output+="b"; break;
            case 12: output+="c"; break;
            case 13: output+="d"; break;
            case 14: output+="e"; break;
            case 15: output+="f"; break;
        }
    }
    reverse(output.begin(), output.end()); 
    value.clear();
    


    //shorten
    while(output.length()>64) {

        switch (output.length() % 10) {
            case 0: output.erase((output.length()/2), 1); break;
            case 1: output.erase((output.length()/6), 1); break;
            case 2: output.erase(1, 1); break;
            case 3: output.erase((output.length()*2/3), 1); break;
            case 4: output.erase((output.length()*5/9), 1); break;
            case 5: output.erase((output.length()/8), 1); break;
            case 6: output.erase((output.length()*3/7), 1); break;
            case 7: output.erase((output.length()/10), 1); break;
            case 8: output.erase((output.length()*15/23), 1); break;
            case 9: output.erase((output.length()*3/4), 1); break;
        }
    }
    //if (output.length()>64) output.erase(1, (output.length()-64));


    return output;
}
//________________________________________________________________________________________________________________________________________________________



void add(vector<int>& vec, unsigned long long x) {
    unsigned long long carry = x;                      // Initialize the carry with the value of X

    for (size_t i = 0; i < vec.size(); ++i) {
        unsigned long long sum = vec[i] + carry;
        vec[i] = sum % 16;              // Update the current digit
        carry = sum / 16;               // Update the carry
    }

    // If there's a remaining carry, add it as a new digit
    while (carry > 0) {
        vec.push_back(carry % 16);
        carry /= 16;
    }
}
//________________________________________________________________________________________________________________________________________________________



void square(vector<int>& vec) {
    vector<int> result(vec.size() * 2, 0);

    for (size_t i = 0; i < vec.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < vec.size(); ++j) {
            int product = vec[i] * vec[j] + result[i + j] + carry;
            result[i + j] = product % 16;
            carry = product / 16;
        }
        result[i + vec.size()] = carry;
    }

    // Remove zeros from front
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }


    vec = result;
}
//________________________________________________________________________________________________________________________________________________________



void collisionTest () {

    ifstream file2("generated.txt");
    string line;
    bool first=true;
    input="";
    string temp="";
    string hash1="";
    string hash2="";
    bool collisions=false;

    cout<<"\nRunning colision test...\n";

    while (getline (file2, line)){

        if (first==true) {
            input=line;
            temp=line;
            first=false;
            hash1=hash();
            }

        else {
            first=true;
            input=line;
            hash2=hash();

            if (hash1==hash2){
                collisions=true;
                break;
            }//if
            }//else
    }//while

    if (collisions) {cout<<"\n\nCollisions found\nString 1: "<<temp<<"\nHash 1: "<<hash1<<"\nString 2: "<<line<<"\nHash 2: "<<hash2<<endl; }
    else cout<<"\n\nNo collisions found\n";
}
//________________________________________________________________________________________________________________________________________________________



void avalancheTest () {

    ifstream file3("generated.txt");
    string line;
    bool first=true;
    vector<double> hexdiff;
    vector<double> bitdiff;
    input="";
    string hash1="";
    string hash2="";

    cout<<"\nRunning avalanche test...\n";

    //bool print=true;

    while (getline (file3, line)){

        if (first==true) {
            input=line;
            first=false;
            hash1=hash();
            }

        else {
            first=true;
            input=line;
            hash2=hash();

            //hex diff
            hexdiff.push_back( comparehex(hash1,hash2));

            //bit diff
            bitdiff.push_back( comparebit(hash1,hash2));

            //if (print){print=false; cout<<"\n"<<hash1<<"\n"<<hash2<<"\n"<<comparehex(hash1,hash2)<<endl<<comparebit(hash1,hash2)<<endl;}

            }//else
    }//while

    sort(hexdiff.begin(),hexdiff.end());
    sort(bitdiff.begin(),bitdiff.end());

    long double avghex=0;
    long double avgbit=0;
    for (auto i:hexdiff) avghex+=i;
    for (auto i:bitdiff) avgbit+=i;
    avghex=avghex/hexdiff.size();
    avgbit=avgbit/bitdiff.size();

    cout<<"\nProcentinis skirtingumas:\n\nHex lygmenyje:\n     min: "<<hexdiff[0]<<"\n     max: "<<hexdiff.at(hexdiff.size()-1)<<"\n     vidurkis: "<<avghex<<"\n\nBit lygmenyje:\n     min: "<<bitdiff[0]<<"\n     max: "<<bitdiff.at(bitdiff.size()-1)<<"\n     vidurkis: "<<avgbit<<endl;


    hexdiff.clear();
    bitdiff.clear();
}
//________________________________________________________________________________________________________________________________________________________



double comparehex(string hash1, string hash2){

    double counter=0.0;

    for (int a=0; a<64; a++){
        if (hash1[a]==hash2[a]) counter++;
    }

    counter=(counter*100.0)/64.0;
    return counter;
}
//________________________________________________________________________________________________________________________________________________________



double comparebit(string hash1, string hash2){

    int temp=0;
    string binary1="";
    string binary2="";

    //get binary
    for (int a=0; a<64; a++) {

        temp=charToHexVal(hash1[a]);
        bitset<4> binary(temp);
        binary1+=binary.to_string();

        temp=charToHexVal(hash2[a]);
        bitset<4> binaryy(temp);
        binary2+=binaryy.to_string();
    }
    //

    double counter=0.0;

    //count matches
    for (int a=0; a<256; a++){
        if (binary1[a]==binary2[a]) counter++;
    }

    //cout<<"\nbinary 1 - "<<binary1<<"\nlength - "<<binary1.length()<<endl;
    //cout<<"\nbinary 2 - "<<binary2<<"\nlength - "<<binary2.length()<<endl<<counter<<endl;
    counter=(counter*100.0)/256.0;
    return counter;
}
//________________________________________________________________________________________________________________________________________________________


int charToHexVal(char a){
    switch(a){
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;}
return -1;
}
