#ifndef ANIMAL_H
#define ANIMAL_H
#include<iostream>
#include<vector>


int min(int a1, int a2, int a3);
int max(int a1, int a2);
int levenshtein_distance(std::vector<char> v1, std::vector<char> v2 );
class Animal: public Cell{
public:
    Animal asexual_reproduction();
    void chromosome_death();
};

double genetic_similarity(Animal a1, Animal a2);
bool operator==(const Animal& A1, const Animal& A2);
Animal operator+( Animal a1, Animal a2);

#endif

