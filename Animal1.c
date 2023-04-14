#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Animal {
public:
    std::vector<std::string> chromosomes;

    Animal(std::vector<std::string> chr) : chromosomes(chr) {}

    int getGeneticSimilarity(Animal other) {
        int commonChromosomes = 0;
        int commonGenes = 0;
        int totalGenes = 0;

        for (const std::string& chromosome : chromosomes) {
            if (std::find(other.chromosomes.begin(), other.chromosomes.end(), chromosome) != other.chromosomes.end()) {
                commonChromosomes++;
                int numGenes = chromosome.size();
                for (int i = 0; i < numGenes; i++) {
                    if (chromosome[i] == other.chromosomes[commonChromosomes - 1][i]) {
                        commonGenes++;
                    }
                    totalGenes++;
                }
            }
        }

        if (totalGenes == 0) {
            return 0;
        }

        return (commonGenes * 100) / totalGenes;
    }

    int getNumChromosomes() {
        return chromosomes.size();
    }
};

int main() {
    std::vector<std::string> chr1 = {"ACGTACGT", "CGTCGTCG", "ATATATAT"};
    std::vector<std::string> chr2 = {"CGTCGTCG", "ACGTACGT", "TATATATA"};
    std::vector<std::string> chr3 = {"CGTCGTCG", "ACGTACGT", "TATATATA"};

    Animal animal1(chr1);
    Animal animal2(chr2);
    Animal animal3(chr3);

    std::cout << animal1.getGeneticSimilarity(animal2) << std::endl;
    std::cout << animal1.getGeneticSimilarity(animal3) << std::endl;

    if (animal1.getNumChromosomes() == animal2.getNumChromosomes() && animal1.getGeneticSimilarity(animal2) > 70) {
        std::cout << "Both animals are of the same species." << std::endl;
        return true;
    } else {
        std::cout << "Both animals are not of the same species." << std::endl;
        return false;
    }
}
