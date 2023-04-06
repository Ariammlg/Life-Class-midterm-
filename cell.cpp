#include <iostream>
#include <vector>
#include <cmath>

using std:: cout, std::cin, std::endl, std::vector, std::string;

char comp_char(char c){
    switch(c){
        case 'A':
            return 'T';
        case 'T':
            return 'A';
        case 'C':
            return 'G';
        case 'G':
            return 'C';
    }
}


class Genome{
public:
    vector<char> RNA;
    vector<char> DNA;

    void receive(string s){
        if(s.find(' ') == string::npos){
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
        for(int i=0; i< RNA.size();i++){
            Complement.push_back(comp_char(RNA[i]));
            cout << comp_char(RNA[i]);
        }
        cout<< endl;
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
            if(DNA[i] != ' '){
                cout << DNA[i];
            }
            else{
                cout<< endl;
            }
        }
        cout<<endl;
    }

    void minor_mutation(char c1, char c2, int n){
        int m = n;
        for(int i=0; i < RNA.size() && m > 0 ; i++){
            if(RNA[i] == c1){
                RNA[i] = c2;
                m --;
            }
        }
        m = n;
        for(int i=0; i< RNA.size() && m > 0 ; i++){
            if(DNA[i] == c1){
                DNA[i] = c2;
                DNA[i+RNA.size()+1]= comp_char(c2);
                m--;
                if(m <= 0){
                    break;
                }
            }
            if(DNA[i+RNA.size()+2] == c1){
                DNA[i+RNA.size()+2] = c2;
                DNA[i+1]= comp_char(c2);
                m--;
            }


        }



    }




};



int main(){
    Genome g1;
    g1.receive("ACCTTG TGGAAC");
    g1.receive("ACCTTG");
    g1.minor_mutation('A', 'C', 2);
    g1.display_DNA();
    g1.display_RNA();
    return 0;
}


