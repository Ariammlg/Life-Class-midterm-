#include <iostream>
#include <vector>
//#include <cmath>

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
        cout<<endl<<endl;
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
        for(int i=0; i< (DNA.size()-1)/2 && m > 0 ; i++){
            if(DNA[i] == c1){
                DNA[i] = c2;
                DNA[i+((DNA.size()-1)/2)+1]= comp_char(c2);
                m--;
                if(m <= 0){
                    break;
                }
            }
            if(DNA[i+((DNA.size()-1)/2)+2] == c1){
                DNA[i+((DNA.size()-1)/2)+2] = c2;
                DNA[i+1]= comp_char(c2);
                m--;
            }


        }



    }

    void major_mutation(string s1, string s2){
        int cnt, cnt1;

        for(int i=0; i<= RNA.size()-s1.size(); i++){
            cnt=0;
            for(int j=0; j< s1.size(); j++){
                if(s1[j] == RNA[j+i] ){
                    cnt++;
                }
            }
            if(cnt == s1.size()){
                for(int k=0; k<s1.size(); k++){
                    RNA.erase(RNA.begin()+i);
                }
                for(int k=0; k<s2.size(); k++){
                    RNA.insert(RNA.begin()+k+i,s2[k]);
                }
                break;
            }

        }

        for(int i=0; i <= (DNA.size()-1)/2 - s1.size() ; i++ ){
            cnt = 0;
            cnt1= 0;
            for(int j=0; j< s1.size(); j++){
                if(s1[j] == DNA[j+i]){
                    cnt++;
                }
                if(s1[j] == DNA[i + j + (DNA.size()+1)/2]){
                    cnt1++;
                }

            }
            if(cnt == s1.size()){
                for(int k=0; k<s1.size(); k++){
                    DNA.erase(DNA.begin()+i+(DNA.size()+1)/2);
                    DNA.erase(DNA.begin()+i);

                }
                for(int k=0; k<s2.size(); k++){
                    DNA.insert(DNA.begin() + i + k + (DNA.size()+1)/2 , comp_char(s2[k]));
                    DNA.insert(DNA.begin()+k+i,s2[k]);

                }
                break;
            }
            else if(cnt1 == s1.size()){
                for(int k=0; k<s1.size(); k++){
                    DNA.erase(DNA.begin()+i+ (DNA.size()+1)/2);
                    DNA.erase(DNA.begin()+i);
                }
                for(int k=0; k<s2.size(); k++){
                    DNA.insert(DNA.begin()+i+k+ (DNA.size()+1)/2, s2[k]);
                    DNA.insert(DNA.begin()+k+i, comp_char(s2[k]));
                }
                break;

            }


        }


    }

    void inverse_mutation(string s) {
        int cnt,cnt1;
        for (int i = 0; i <= RNA.size() - s.size(); i++) {
            cnt = 0;
            for (int j = 0; j < s.size(); j++) {
                if (s[j] == RNA[i + j]) {
                    cnt++;
                }
            }
            if (cnt == s.size()) {
                for (int p = 0; p < s.size(); p++) {
                    RNA[i + p] = s[s.size() - 1 - p];
                }
                break;
            }

        }

        for(int i=0; i <= (DNA.size()-1)/2 - s.size() ; i++ ){
            cnt = 0;
            cnt1= 0;
            for(int j=0; j< s.size(); j++){
                if(s[j] == DNA[j+i]){
                    cnt++;
                }
                if(s[j] == DNA[i + j + (DNA.size()+1)/2]){
                    cnt1++;
                }

            }

            if(cnt == s.size()){
                for(int p=0; p < s.size(); p++){
                    DNA[i+p] = s[s.size()-1-p];
                    DNA[i+p+(DNA.size()+1)/2]= comp_char(DNA[i+p]);
                }
                break;
            }

            else if(cnt1==s.size()){
                for(int p=0; p < s.size(); p++){
                    DNA[i+p+(DNA.size()+1)/2] = s[s.size()-1-p];
                    DNA[i+p]= comp_char(DNA[i+p+(DNA.size()+1)/2]);
                }
            }
        }

    }




};



int main(){
    Genome g1;
    g1.receive("ATCGATCG");
    g1.receive("AAGTCTCAGT TTCAGAGTCA");
    g1.inverse_mutation("GATC");
    g1.display_DNA();
    g1.display_RNA();
    return 0;
}


