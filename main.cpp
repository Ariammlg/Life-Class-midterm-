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

    void DNA_Builder(){
        
    }




};


