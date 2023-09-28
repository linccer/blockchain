#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm> 
#include <chrono> 


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::to_string;


void readf();
string hash();
void add(vector<int>& vec, unsigned long long x);
void square(vector<int>& vec);
void collisionTest ();


string input="";
const int X = 73;



int main () {

    readf(); 


auto start = std::chrono::high_resolution_clock::now();    //start timer


    cout<<"Sugeneruotas hash:\n"<<hash();
    collisionTest();


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
    vector<string> hashes;
    input="";
    string output="";


    while (getline (file2, line)){

        if (first==true) {input=line; first=false;}

        else {
            first=true;
            input=input + " " + line;

            hashes.push_back( hash() );
            input="";
            }
    }//while

    sort(hashes.begin(),hashes.end());

    bool collisions = std::adjacent_find(hashes.begin(), hashes.end()) != hashes.end();
    if (collisions) cout<<"\n\nCollisions found\n"; else cout<<"\n\nNo collisions found\n";

    for (auto i:hashes) output+=(i+"\n");

    ofstream outp ("collision_test_hash_list.txt");
    outp<<output;
    outp.close();


}
//________________________________________________________________________________________________________________________________________________________
