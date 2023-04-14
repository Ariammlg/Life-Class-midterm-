#include<iostream>
#include<vector>
#include "animal.h"
#include "cell.h"

using std:: cout, std::cin, std::endl, std::vector, std::string;


int main(){
    int n1, n2, m1, m2;
    char c1, c2;
    double d;
    vector<char> v1;
    Genome G;
    Cell C;
    Animal A, R;
    Virus V;
    string s1, s2, t1, t2;
    cout<<"1.Genome\n2.Cell\n3.Animal\n4.Virus"<<endl;
    cin >> n1;
    cin.ignore();
    switch(n1){
        case 1:
            cout<< "Please enter the RNA of your genome: "<<endl;
            std::getline(cin, s1);
            G.receive_RNA(s1);
            cout<< "please enter the DNA of your genome:\n"
                   "(note that you have to enter it with a space bar between the strands like this: AAA TTT)"<<endl;
            std::getline(cin, s2);
            G.receive_DNA(s2);
            cout<<"1.creating the DNA from RNA\n2.Minor Mutation\n3.Major Mutation\n4.Inverse Mutation\n"
                  "5.Complementary palindrome"<<endl;
            cin >>n2;
            switch(n2){
                case 1:
                    G.DNA_Builder();
                    break;
                case 2:
                    cout<<"Enter the nucleotide in your DNA that you want to change: "<<endl;
                    cin>> c1;
                    if(c1!= 'A' && c1!= 'T' && c1!= 'G' && c1!= 'C' ){
                        cout<<"Invalid nucleotide! Please enter the nucleotides A, T, G ,C in capitals "<<endl;
                        break;
                    }
                    cout<<"Enter the nucleotide in your DNA that you want to substitute"<<endl;
                    cin>>c2;
                    if(c2!= 'A' && c2!= 'T' && c2!= 'G' && c2!= 'C' ){
                        cout<<"Invalid nucleotide! Please enter the nucleotides A, T, G ,C in capitals "<<endl;
                        break;
                    }
                    cout<<"How many times do you want to replace " << c1 << " with "<< c2<<"?: "<<endl;
                    cin >> m1;
                    G.minor_mutation(c1, c2, m1);
                    G.display_RNA();
                    G.display_DNA();
                    break;
                case 3:
                    cout<< "Enter the substring in your gene that you want to change: "<<endl;
                    cin>> t1;
                    cout<<"Enter the substring you want to substitute: "<< endl;
                    cin>> t2;
                    G.major_mutation(t1, t2);
                    G.display_RNA();
                    G.display_DNA();
                    break;
                case 4:
                    cout<< "Enter the substring you want to invert: "<<endl;
                    cin>> t1;
                    G.inverse_mutation(t1);
                    G.display_RNA();
                    G.display_DNA();
                    break;
                case 5:
                    cout<<"1.Complementary Palindromes from RNA\n2.Complementary Palindrome from DNA"<<endl;
                    cin>> m1;
                    G.complementary_palindrome(m1);
                    break;
                default:
                    cout<< "Please enter the RNA of your genome: "<<endl;
            }
            break;
        case 2:
            cout<< "How many chromosomes does your cell have: "<<endl;
            cin>> m1;
            cout<< "Enter the "<< m1<< " chromosomes(DNAs) on different lines: "<<endl;
            cin.ignore();
            C.receive(m1);
            cout<<"1.Cell Death\n2.Minor Mutation\n3.Major Mutation\n"
                  "4.Inverse Mutation\n5.Complementary Palindromes"<<endl;
            cin >> n2;
            switch(n2){
                case 1:
                    C.cell_death();
                    break;
                case 2:
                    cout<<"Enter the index of your chromosome that you want to change: "<< endl;
                    cin >> m1;
                    cout<<"Enter the nucleotide in your chromosome that you want to change: "<<endl;
                    cin>> c1;
                    if(c1!= 'A' && c1!= 'T' && c1!= 'G' && c1!= 'C' ){
                        cout<<"Invalid nucleotide! Please enter the nucleotides A, T, G ,C in capitals "<<endl;
                        break;
                    }
                    cout<<"Enter the nucleotide in your chromosome that you want to substitute"<<endl;
                    cin>>c2;
                    if(c2!= 'A' && c2!= 'T' && c2!= 'G' && c2!= 'C' ){
                        cout<<"Invalid nucleotide! Please enter the nucleotides A, T, G ,C in capitals "<<endl;
                        break;
                    }
                    cout<<"How many times do you want to replace " << c1 << " with "<< c2<<"?: "<<endl;
                    cin >> m2;
                    C.minor_mutation(c1, c2,m2,m1);
                    C.display();
                    break;
                case 3:
                    cout << "Enter the index of the chromosome you want to change: "<<endl;
                    cin>> m1;
                    cout<<"Enter the substring that you want to change: "<< endl;
                    cin >> s1;
                    cout<< "Enter the index of the chromosome you want to change: "<<endl;
                    cin >> m2;
                    cout<<"Enter the nucleotide that you want to substitute: "<< endl;
                    cin>> s2;
                    C.major_mutation(s1, m1, s2, m2);
                    C.display();
                    break;
                case 4:
                    cout<< "Enter the index of the chromosome you want to change: "<<endl;
                    cin>> m1;
                    cout<<"Enter the substring that you want to invert: "<< endl;
                    cin>> s1;
                    C.inverse_mutation(s1, m1);
                    C.display();
                    break;
                case 5:
                    cout<< "Enter the index of the chromosome you want to check: ";
                    cin>> m1;
                    C.complementary_palindrome(m1);
                    break;
                default:
                    cout<<"Invalid input! Please enter one of the numbers from above.";
            }
            break;
        case 3:
            cout<<"1.Genetic Similarity\n2.Asexual Reproduction\n3.Sexual reproduction\n4.Chromosome Death"<<endl;
            cin>>n2;
            switch(n2){
                case 1:
                    cout<<"How many chromosomes does the first animal have?: "<<endl;
                    cin>>m1;
                    cin.ignore();
                    cout<<"Enter the chromosomes of the first animal on different lines: "<<endl;
                    A.receive(m1);
                    cout<<"How many chromosomes does the second animal have?: "<<endl;
                    cin>>m2;
                    cin.ignore();
                    cout<<"Enter the chromosomes of the second animal on different lines: "<<endl;
                    R.receive(m2);
                    d = genetic_similarity(A,R);
                    cout<<"The animals have "<<d<<"% genetic similarity."<<endl;
                    break;
                case 2:
                    cout<<"How many chromosomes does the animal have?: "<<endl;
                    cin>>m1;
                    cin.ignore();
                    cout<<"Enter the chromosomes of the animal on different lines: "<<endl;
                    A.receive(m1);
                    A.asexual_reproduction().display();
                    break;
                case 3:
                    cout<<"How many chromosomes does the first animal have?: "<<endl;
                    cin>>m1;
                    cin.ignore();
                    cout<<"Enter the chromosomes of the first animal on different lines: "<<endl;
                    A.receive(m1);
                    cout<<"How many chromosomes does the second animal have?: "<<endl;
                    cin>>m2;
                    cin.ignore();
                    cout<<"Enter the chromosomes of the second animal on different lines: "<<endl;
                    R.receive(m2);
                    (A+R).display();
                    break;
                case 4:
                    cout<<"How many chromosomes does the animal have?: "<<endl;
                    cin>>m1;
                    cin.ignore();
                    cout<<"Enter the chromosomes of the animal on different lines: "<<endl;
                    A.receive(m1);
                    A.chromosome_death();
                    A.display();
                    break;
            }
            break;
        case 4:
            cout<<"Enter the RNA of your virus: "<<endl;
            cin>> s1;
            V.receive_RNA(s1);
            cout<<"Enter the number of the chromosomes the animal has: "<<endl;
            cin>> m1;
            cout<<"Enter the chromosomes(DNAs) of the animal on separate lines: "<<endl;
            A.receive(m1);
            V.infection(A);
            break;
        default:
            cout<<"Invalid input! Please enter one of the numbers given above.";
    }
    return 0;
}

