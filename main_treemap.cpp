#include <iostream>

#include "TreeMap.h"

int main() {

    TreeMap<std::string, int> treeMap;

    treeMap.print();

    treeMap.update("tokyo", 37468000);
    treeMap.update("delhi", 28514000);
    treeMap.update("shangai", 25582000);

    printf("valueeee: %d",treeMap.get("tokyo"));
    printf("%d",treeMap.ceilingEntry("tokyo").getValue());
    treeMap.pollFirstEntry();
    treeMap.print();

    return 0;
}
