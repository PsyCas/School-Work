#include <iostream>
#include "sequence_map.h"

int main(){

    std::string first = "AanI";
    std::string second = "TTA'TAA";
    std::string comparison = "Bbni";

    std::cout << first.length();

    SequenceMap map1(first, second);
    SequenceMap map2(comparison, second);

    std::cout << map1;
    std::cout << (map1 < map2);
}