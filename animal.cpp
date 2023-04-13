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



class Animal: public Cell{
public:
    //This function returns the offspring from an asexual reproduction.
    Animal asexual_reproduction(){
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

};


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
    //cout<< "The genetic similarity percentage between these two animals is " << ave << '%'<< endl;
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



int main(){
    Animal T1, T2;
    T1.receive(2);
    T2.receive(2);
    (T1+T2).display();
    return 0;
}