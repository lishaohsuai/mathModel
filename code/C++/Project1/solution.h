#ifndef __SOLUTION_H__
#define __SOLUTION_H__
#include "shoes.h"
#include "box.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include "packer.h"
#include "bigBox.h"

class Solution {
public:
	Solution() {}
	~Solution() {}
	std::vector<Shoes> shoes;
	std::vector<Box> boxes;
	std::vector<BigBox> bigBoxes;
	std::map<int, std::vector<int>> answer1;// 问题1 的解 以鞋子为中心对应鞋盒
	std::map<int, std::vector<int>> answer1_b1;// 问题1 的解 以鞋盒为中心对应鞋子
	std::vector<std::vector<int>> answer2;// 问题2的解
	std::map<int, int> order;// 订单数据 鞋子 - 双数
public:
	int readShoes(std::string filename);
	int readBox(std::string filename);
	int readOrder(std::string filename);
	int solveQuestion1();
	bool questionOneJudge1(Shoes &s, Box &b);
	bool questionOneJudge2(Shoes &s, Box &b);

	int solveQuestion2();
	bool questionTwoCombination(std::vector<int>& vec, int n); 
	bool questionTwoCombinationAuxi(int k, int n);
	bool questionTwoJudge1(std::vector<int> &include, std::vector<int>& validBox);


	int solveQuestion3();
	bool questionThreeConstruct();
};
#endif
