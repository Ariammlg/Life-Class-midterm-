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
        cout<<endl;
        return Complement;
    }


    void display_RNA(){
        for(int i=0; i < RNA.size(); i++){
            cout<< RNA[i];
        }
        cout<<endl;
    }

    void display_DNA(){
        for(int i=0; i < DNA.size(); i++ ){
            cout<< DNA[i];
        }
        cout<<endl;
    }




};


