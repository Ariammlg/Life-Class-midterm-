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

    void complementary_palindrome(int bi){
        int n;

        switch(bi){
            case 1:
                for(int i=3; i<= RNA.size(); i++){
                    for(int j=0; j< RNA.size()+1-i; j++ ){
                        n=0;
                        for(int k = j; k < j+i; k++){
                            if(RNA[k] == comp_char(RNA[j+i-1-(k-j)])){
                                n++;
                            }
                        }
                        if(n == i){
                            for(int k=j; k<j+i; k++){
                                cout<< RNA[k];
                            }
                            cout<< ", ";
                        }
                    }
                }
                break;


            case 2:
                for(int i=3; i<= (DNA.size()-1)/2; i++){
                    for(int j=0; j< (DNA.size()-1)/2-i+1; j++ ){
                        n=0;
                        for(int k = j; k < j+i; k++){
                            if(DNA[k] == comp_char(DNA[i+j-1-(k-j)]) ){
                                n++;
                            }
                        }
                        if(n == i){
                            for(int k=j; k<j+i; k++){
                                cout<< DNA[k];
                            }
                            cout<< ", ";
                        }
                    }
                }

                break;
        }


        }








};






class Cell{
public:
    int chromosome_count;
    vector<Genome> chromosomes;


    void receive(int n){
        string chro;
        chromosome_count = n;
        for(int i=0; i<n; i++){
            Genome a;
            std::getline(cin, chro);
            chromosomes.push_back(a);
            chromosomes[i].receive(chro);

        }
    }

    void display(){
        for(int i=0; i< chromosomes.size(); i++){
            cout<< i+1 << ':'<< endl;
            chromosomes[i].display_DNA();
        }
    }


    void cell_death(){
        int counter, counter1, counter2;
        for(auto i : chromosomes){
            counter = 0;
            counter1 = 0;
            counter2 = 0;
            for(int j=0; j < (i.DNA.size()-1)/2; j++){
                if(i.DNA[j] != comp_char(i.DNA[j+(i.DNA.size()+1)/2])){
                    counter++;
                }
                else if((i.DNA[j] == 'A' && i.DNA[j+(i.DNA.size()+1)/2] == 'T') || (i.DNA[j]== 'T' && i.DNA[j+(i.DNA.size()+1)/2]== 'A')){
                    counter1++;
                }
                else{
                    counter2++;
                }

            }
            if(counter > 5 || counter1 > 3*counter2){
                delete this;
            }
        }
    }


    void minor_mutation(char c1, char c2, int n, int m){
        chromosomes[m-1].minor_mutation(c1, c2, n);
    }


    void major_mutation(string s1, int n, string s2, int m){
        chromosomes[n-1].major_mutation(s1, s2);
        chromosomes[m-1].major_mutation(s2, s1);

    }

    void inverse_mutation(string s, int n){

        chromosomes[n-1].inverse_mutation(s);

    }

    /* void complementary_palindrome(Genome a): we write this method into the previous class because,
        it applies to chromosomes(DNA) so this method had better be a Genome's method. */

    void complementary_palindrome(int t){
        chromosomes[t-1].complementary_palindrome(2);
    }







};



int main(){
    Genome spider;
    spider.receive("AATTAAGCTC");
    spider.complementary_palindrome(1);
    return 0;
}

