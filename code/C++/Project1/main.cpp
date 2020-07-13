#include <iostream>
#include "solution.h"
int main() {
	Solution solve;
	solve.readShoes("shoes.txt");
	solve.readBox("boxes.txt");
	solve.solveQuestion1();
	solve.solveQuestion2();
	solve.readOrder("order2.txt");
	solve.solveQuestion3();
	system("pause");
}