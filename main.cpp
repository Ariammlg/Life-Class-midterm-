#include <iostream>
#include <vector>
#include <cmath>

using std:: cout, std::cin, std::endl, std::vector, std::string;


class Genome{
public:
    vector<char> RNA;
    vector<char> DNA;

    void receive(string s){
        if(s.find('\n') == string::npos){
            for(int i=0; i<s.size();i++){
                RNA.push_back(s[i]);
            }
        }
        else{
            for(int i=0; i < s.size();i++){
                DNA.push_back(s[i]);
            }
        }
    }

    vector<char> DNA_Builder(){
        vector<char> Complement;
        DNA.push_back('\n');
        for(int i=0; i< RNA.size();i++){
            switch(RNA[i]){
                case 'A':
                    Complement.push_back('T');
                    cout<<'T';
                    break;
                case 'C':
                    Complement.push_back('G');
                    cout<<'G';
                    break;
                case 'G':
                    Complement.push_back('C');
                    cout<<'C';
                    break;
                case 'T':
                    Complement.push_back('A');
                    cout<<'A';
                    break;

            }
        }
        return Complement;
    }




};


int main(){
    Genome g1;
    g1.receive("ATTCGGGGA");
    g1.DNA_Builder();


}