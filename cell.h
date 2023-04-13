#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>


char comp_char(char c);

class Genome{
public:
    // We use vectors of characters instead of strings due to their flexibility.
    std::vector<char> RNA;
    std::vector<char> DNA;

    void receive(std::string s);
    std::vector<char> DNA_Builder();
    void display_RNA();
    void display_DNA();
    void minor_mutation(char c1, char c2, int n);
    void major_mutation(std::string s1, std::string s2);
    void inverse_mutation(std::string s);
    void complementary_palindrome(int bi);

};

class Cell{
public:
    //the number of chromosomes in a cell
    int chromosome_count;

    //The vector of chromosomes, the chromosomes are considered as DNA strings.
    std::vector<Genome> chromosomes;
    void receive(int n);
    void display();
    void cell_death();
    void minor_mutation(char c1, char c2, int n, int m);
    void major_mutation(std::string s1, int n, std::string s2, int m);
    void inverse_mutation(std::string s, int n);
    void complementary_palindrome(int t);

};


#endif
