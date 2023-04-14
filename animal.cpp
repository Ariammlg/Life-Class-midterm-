#include <iostream>
#include <vector>
#include <random>
#include<chrono>
#include "cell.h"
#include "animal.h"


using std:: cout, std::cin, std::endl, std::vector, std::string;

//This function returns the minimum of 3 integers given as parameters.
//We use this function to write our levenshtein function.
int min(int a1, int a2, int a3){
    int m=a1;
    if(a2<m){
        m=a2;
    }
    if(a3<m){
        m=a3;
    }
    return m;
}
//This function returns the maximum of 2 integers
int max(int a1, int a2){
    int m=a1;
    if(a2>m){
        m=a2;
    }
    return m;
}


//This bool function returns true if the first argument is a subvector of the second.
bool inv(vector<char> v1, vector<char> v2){
    int n;
    for(int i=0; i <= v2.size()-v1.size();i++){
        n=0;
        for(int j=i; j < i+v1.size(); j++){
            if(v2[j]==v1[j-i]){
                n++;
            }
        }
        if(n== v1.size()){
            return true;
        }

    }
    return false;
}



// this function returns the Levenshtein distance of 2 strings. (vector<char> here)
int levenshtein_distance(vector<char> v1, vector<char> v2 ){
    if(v1.size()==0){
        return v2.size();
    }
    else if(v2.size()==0){
        return v1.size();
    }
    else if(v1[0]==v2[0]){
        v1.erase(v1.begin());
        v2.erase(v2.begin());
        return levenshtein_distance(v1,v2);
    }
    else{
        int n1, n2, n3;
        vector<char> w1=v1, w2=v2;
        w1.erase(w1.begin());
        n1= levenshtein_distance(w1,w2);
        w1=v1;
        w2.erase(w2.begin());
        n2= levenshtein_distance(w1,w2);
        w1.erase(w1.begin());
        n3= levenshtein_distance(w1, w2);
        return 1+min(n1,n2,n3);

    }
}


    //This function returns the offspring from an asexual reproduction.
    Animal  Animal::asexual_reproduction(){
        Animal A;
        int m, n=0;
        int random_index ;
        double probability= 0.5;
        char c1, c2;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution dist(probability);
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<> dis(0, 3);
        for(auto i : chromosomes){
            if(dist(rng)){
                Genome t;
                A.chromosomes.push_back(t);
                A.chromosomes[n].DNA = i.DNA;
                n++;
            }
            else{
                random_index =  dis(gen);
                switch (random_index) {
                    case 0:
                        c1 = 'A';
                        break;
                    case 1:
                        c1 = 'T';
                        break;
                    case 2:
                        c1 = 'C';
                        break;
                    case 3:
                        c1 = 'G';
                        break;
                    default:
                        c1=' ';

                }
                random_index =  dis(gen);
                switch (random_index) {
                    case 0:
                        c2 = 'A';
                        break;
                    case 1:
                        c2 = 'T';
                        break;
                    case 2:
                        c2 = 'C';
                        break;
                    case 3:
                        c2 = 'G';
                        break;
                    default:
                        c2= ' ';
                }

                random_index =  dis(gen);
                switch (random_index) {
                    case 0:
                        m = 1;
                        break;
                    case 1:
                        m = 2;
                        break;
                    case 2:
                        m = 3;
                        break;
                    case 3:
                        m = 4;
                        break;
                    default:
                        m=1;
                }
                Genome t;
                A.chromosomes.push_back(t);
                A.chromosomes[n].DNA = i.DNA;
                A.chromosomes[n].minor_mutation(c1, c2,m);
                n++;
            }
        }
        return A;
    }

    //This function checks if the chromosomes are healthy and in case they are not,
    //they will be deleted from the animal's cell.
    void Animal::chromosome_death(){
        int counter, counter1, counter2, n=0;
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
                chromosomes.erase(chromosomes.begin()+n);
                chromosome_count--;
            }
            n++;
        }
    }


//This function prints the genetic similarity percentage, and returns the percentage as a double.
double genetic_similarity(Animal a1, Animal a2){
    int m = max(a1.chromosome_count, a2.chromosome_count);
    double ave, sum=0;
    vector<char> v1, v2;
    vector<int> v;
    vector<double> R;
    for(int i=0; i<m; i++){
        v1 = a1.chromosomes[i].DNA;
        v2 = a2.chromosomes[i].DNA;
        v1.erase(v1.begin()+(v1.size()-1)/2, v1.end());
        v2.erase(v2.begin()+ (v2.size()-1)/2, v2.end());
        v.push_back(levenshtein_distance(v1,v2));
        R.push_back((1-v[i]/(double)max(v1.size(),v2.size()))*100);
    }

    for(auto t : R){
     sum += t;
    }
    ave = sum/(double)R.size();
    return ave;
    
}


// overloading the "==" operator for Animal objects:
bool operator==(const Animal& A1, const Animal& A2){
    return (A1.chromosome_count == A2.chromosome_count && genetic_similarity(A1,A2)>70);
}

//This function performs sexual reproduction of two Animal objects and returns the offspring.
Animal operator+( Animal a1, Animal a2){
    Animal h1, h2, B;
    h1= a1.asexual_reproduction();
    h2= a2.asexual_reproduction();
    if(!(a1==a2)){
        cout<< "These two animals are not the same species, therefore they can't reproduce.";
        return B;
    }
    else{
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        B.chromosome_count = h1.chromosome_count;
        double prob = 0.5;
        std::default_random_engine rng(seed);
        std::bernoulli_distribution dist(prob);

        for(int i=0; i < a1.chromosome_count; i++){
            Genome t;
            B.chromosomes.push_back(t);
            if(dist(rng)){
                B.chromosomes[i].DNA = h1.chromosomes[i].DNA;
            }
            else{
                B.chromosomes[i].DNA = h2.chromosomes[i].DNA;
            }

        }
    }
    return B;
}


void Virus::infection(Animal& a){
    vector<char> cb;
    vector<vector<char>> t;
    int count,n, m= a.chromosomes[0].DNA.size();
    for(int i=0; i< a.chromosome_count;i++){
        if( m>= a.chromosomes[i].DNA.size() ){
            m=a.chromosomes[i].DNA.size();
            n=i;
        }
    }
    for(int i= (m-1)/2; i>0; i--){
        for(int j=0; j<= (m-1)/2 -i; j++ ){
            for(int k=j; k< j+i; k++){
                cb.push_back(a.chromosomes[n].DNA[k]);
            }
            count=0;
            for(int s=0; s<a.chromosome_count; s++){
                vector<char> checker(a.chromosomes[s].DNA.begin(), a.chromosomes[s].DNA.begin()+(a.chromosomes[s].DNA.size()-1)/2);
                if(inv(cb,checker)){
                    count++;
                    checker.clear();
                }
            }
            if(count== a.chromosome_count){
                t.push_back(cb);
            }
            cb.clear();
        }
        if(!t.empty()){
            break;
        }
    }
    vector<char> comp;
    for(auto s: t){
       for(auto q: s){
           comp.push_back(comp_char(q));
       }
       if(RNA==s || RNA==comp){
           cout<< "The virus is infectious to this Animal."<<endl;
           return;
       }
    }
    cout<<"The virus is not infectious to this Animal."<< endl;

}