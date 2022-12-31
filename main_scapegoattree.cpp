#include <iostream>

#include "ScapegoatTree.h"

int main() {

    /*ScapegoatTree<std::string> tree;

    tree.printPretty();

    tree.insert("tokyo");
    tree.insert("delhi");
    tree.insert("shangai");
    tree.insert("sao paulo");
    tree.insert("mexico city");
    tree.insert("cairo");
    tree.insert("dhaka");
    tree.insert("mumbai");
    tree.insert("beijing");
    tree.insert("osaka");

    tree.printPretty();*/
    ScapegoatTree<int> tree;
tree.insert(9);
tree.insert(4);
tree.insert(7);
tree.insert(17);
tree.insert(18);


tree.insert(37);
tree.insert(40);

tree.insert(31);
tree.insert(21);
tree.insert(38);

tree.insert(34);
tree.insert(23);
tree.insert(24);
tree.insert(35);
tree.insert(32);
tree.insert(39);
tree.insert(22);
tree.insert(27);
tree.insert(28);
tree.insert(25);
tree.insert(29); // 2tane giricek


tree.insert(26);

tree.printPretty();
/*tree.printPretty();
tree.remove(11);
tree.remove(3);
tree.remove(16);
tree.remove(2);
tree.remove(10);
tree.remove(12);
tree.remove(5);
tree.remove(1);
tree.remove(13);
tree.remove(19);
tree.remove(20);
tree.remove(6);
tree.remove(15);
tree.remove(8);
tree.remove(14);
tree.printPretty();

tree.insert(37);
tree.insert(40);
tree.insert(31);
tree.insert(21);
tree.insert(38);
tree.insert(34);
tree.insert(23);
tree.insert(24);
tree.insert(35);
tree.insert(32);
tree.insert(39);
tree.insert(22);
tree.insert(27);
tree.insert(28);
tree.insert(25);
tree.insert(29);
tree.insert(26);
tree.insert(30);
tree.insert(33);
tree.insert(36);
tree.printPretty();*/

    return 0;
}
