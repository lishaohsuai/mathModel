#include "solution.h"
const double EPS = 1e-6;
bool cmp(const block &a, const block & b) {
	return a.w > b.w;
}

/**************************************************
@brief   : 读取鞋子数据
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
int Solution::readShoes(std::string filename){
	FILE* file = fopen(filename.c_str(), "r");
	int id;
	double length;
	double width;
	double height;
	double share;
	while (fscanf(file, "%d %lf %lf %lf %lf", &id, &length, &height, &width, &share) != EOF) {
		shoes.push_back({ id, length, height, width, share });
	}
	printf("%d Shoes Records in Total\n", shoes.size());// 输出总共存储了多少条数据
	return shoes.size();
}

/**************************************************
@brief   : 读取鞋盒数据
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
int Solution::readBox(std::string filename) {
	FILE* file = fopen(filename.c_str(), "r");
	int id;
	double length;
	double width;
	double height;
	while (fscanf(file, "%d %lf %lf %lf", &id, &length, &width, &height) != EOF) {
		boxes.push_back({ id, length, width, height});
	}
	printf("%d Boxes Records in Total\n", boxes.size());// 输出总共存储了多少条数据
	return boxes.size();
}


/**************************************************
@brief   : 解决问题1
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
int Solution::solveQuestion1() {
	// 对每一个鞋子尝试匹配每一个鞋盒
	for (int i = 0; i < shoes.size(); i++) {
		for (int j = 0; j < boxes.size(); j++) {
			if (questionOneJudge1(shoes[i], boxes[j])) {
				if (questionOneJudge2(shoes[i], boxes[j])) {
					answer1[shoes[i].id].push_back(boxes[j].id);
					answer1_b1[boxes[j].id].push_back(shoes[i].id); // 以鞋盒为中心对应鞋子
					std::cout << "[answer] " << shoes[i].id << "鞋子可以选择" << boxes[j].id << std::endl;
				}
			}
		}
	}
	return 1;
}


/**************************************************
@brief   : 判断问题1，约束条件1 鞋与鞋盒之间长宽高间隔空隙分别不少于1cm
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
bool Solution::questionOneJudge1(Shoes &s, Box &b) {
	if (b.length - s.length > 1 + EPS)
		if (b.height - s.width > 1 + EPS)
			if (b.width - (s.height * 2 - s.share)> 1 + EPS)
				return true;
	return false;
}

/**************************************************
@brief   : 判断问题1，约束条件2 运动鞋占鞋盒总空间不少于70%
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
bool Solution::questionOneJudge2(Shoes &s, Box &b) {
	if (s.area() / b.area() > 0.7 - EPS)
		return true;
	return false;
}

/**************************************************
@brief   : 生成排列组合数
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool Solution::questionTwoCombination(std::vector<int>& vec, int n) {
	int k = vec.size() - 1;
	for (; k >= 0; k--) {
		if (vec[k] < n + k - vec.size() + 1) break;
	}
	if (k < 0) return false;
	vec[k]++;
	for (int i = k + 1; i < vec.size(); i++) {
		vec[k + 1] = vec[k] + 1;
	}
	return true;
}

/**************************************************
@brief   : 生成组合数的辅助函数
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool Solution::questionTwoCombinationAuxi(int k, int n) {
	std::vector<int> vec;
	for (int i = 1; i <= k; i++) {
		vec.push_back(i);
	}
	bool check = false;
	std::vector<int> validBox;
	validBox.push_back(0);// 先存入一个空值
	for (auto it = answer1_b1.begin(); it != answer1_b1.end(); it++) {
		validBox.push_back(it->first);
	}
	do {
		// 生成可靠数组
		std::vector<int> v;
		for (int i = 0; i < vec.size(); i++) {
			//printf("%d ", vec[i]);
			v.push_back(vec[i]);
		}
		//printf("\n");
		if (questionTwoJudge1(v, validBox)) {
			check = true;

			std::vector<int> rlt;
			for (int i = 0; i < v.size(); i++) {
				rlt.push_back(validBox[v[i]]);
			}
			answer2.push_back(rlt);
		}
	} while (questionTwoCombination(vec, n));
	if (check) {
		return true;
	}
	return false;
}

/**************************************************
@brief   : 校验函数对于问题2
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool Solution::questionTwoJudge1(std::vector<int> &include, std::vector<int>& validBox) {
	std::vector<bool> shoe;// 鞋子数组
	shoe.resize(shoes.size() + 1);
	for (int i = 0; i < shoe.size(); i++) {
		shoe[i] = false;
	}
	for (int i = 0; i < include.size(); i++) {
		for (auto it = answer1_b1[validBox[include[i]]].begin(); it != answer1_b1[validBox[include[i]]].end(); it++) {
			shoe[*it] = true;
		}
	}
	bool check = true;
	for (int i = 1; i < shoe.size(); i++) {
		if (!shoe[i]) {
			check = false;
			break;
		}
	}
	return check;
}

/**************************************************
@brief   : 解决问题2 使用尽可能少的鞋盒
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
int Solution::solveQuestion2() {
	std::vector<bool> shoe;// 鞋子数组
	shoe.resize(shoes.size() + 1);
	for (int i = 0; i < shoe.size(); i++) {
		shoe[i] = false;
	}
	// 得到 有效鞋盒数组 4  5  7 8 9 16 放入一个零时数组中
	std::vector<int> validBox;
	validBox.push_back(0);// 先存入一个空值
	for (auto it = answer1_b1.begin(); it != answer1_b1.end(); it++) {
		validBox.push_back(it->first);
	}
	int validN = validBox.size() - 1;// 减去 空值
	int k = 1; //k 从 1 开始遍历
	// 生成组合数
	// 将组合数对应的有效鞋盒检验鞋子数组
	for (int k = 1; k < validBox.size() - 1; k++) {
		if (questionTwoCombinationAuxi(k, validN)) {
			for (int i = 0; i < answer2.size(); i++) {
				std::cout << "[answer2]";
				for (int j = 0; j < answer2[i].size(); j++) {
					std::cout << " " << answer2[i][j];
				}
				std::cout << std::endl;
			}
			return true;
		}
	}

	return 1;
}





/**************************************************
@brief   : 读取订单
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
int Solution::readOrder(std::string filename) {
	FILE* file = fopen(filename.c_str(), "r");
	int shoeId;
	int number;
	while (fscanf(file, "%d %d", &shoeId, &number) != EOF) {
		order[shoeId] = number;
	}
	printf("%d Order Records in Total\n", order.size());// 输出总共存储了多少条数据
	return order.size();
}



/**************************************************
@brief   : 问题3 读取所有鞋盒的信息 构建 block数组
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool Solution::questionThreeConstruct() {
	for (auto it = order.begin(); it != order.end(); it++) {
		// 得到这一类鞋子的长和
	}
	return true;
}

/**************************************************
@brief   :
1. 思路1 计算问题三 根据订单1得到所用的包装箱数量最少 采用回溯法 可能要采用遗传算法
2. 思路2 计算问题三 可以采用 先构成一层 选这一层中最大的元素 作为这一层的高度
					只要尽可能的将一层的面积最大化就好了
					然后构成许多层，遍历这么多层选择剩余空间做小的贪心算法 构成这一个箱子
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
int Solution::solveQuestion3() {
	// 1. 选方案  因为 有多个鞋子方案
	for (int i = 0; i < answer2.size(); i++) {
		std::vector<int> scheme;
		std::vector<int> schemeNumber;
		std::vector<block> blocks; // 盒子数组
		for (int j = 0; j < answer2[i].size(); j++) {
			scheme.push_back(answer2[i][j]); // 先暂时不遍历所有的鞋子可以选择的鞋盒方案  从小号鞋盒开始选择
		}
		// 先暂时不遍历所有的鞋子可以选择的鞋盒方案  从小号鞋盒开始选择
		for (auto it = order.begin(); it != order.end(); it++) {
			int number = it->second;
			for (auto iit = answer1[it->first].begin(); iit != answer1[it->first].end(); iit++) {
				auto findRlt = std::find(scheme.begin(), scheme.end(), *iit);
				if (findRlt == scheme.end()) {
					// std::cout << "有部分错误" << it->first << "鞋子所选择的对应的鞋盒" << *iit << std::endl;
				}
				else {
					std::cout << it->first << "鞋子所选择的对应的鞋盒" << *findRlt << "个数"<< number<< std::endl;
					// 将生成的鞋盒种类和个数加入blocks
					for (int i = 0; i < number; i++) {
						blocks.push_back({ boxes[*findRlt - 1].height, boxes[*findRlt - 1].length, boxes[*findRlt - 1].width });
					}
					break;
				}
			}
		}
	// 2. 生成许多“层”
		bigBoxes.clear();
		std::sort(blocks.begin(), blocks.end(), cmp);
		std::vector<floors> v; // 单纯存储一层的长宽高
		std::vector<std::vector<block>> floorInfo;  // 存储一层的矩形排布
		while (blocks.size()) {
			Packer packer;
			packer.setPacker(0, 0, 80, 55); // 针对问题4
			packer.fit(blocks);
			// 将所有的有效信息存储到 floorInfo
			std::vector<block> oneFloorInfo;
			for (int i = 0; i < blocks.size(); i++) {
				if (blocks[i].f.x != 0 || blocks[i].f.y != 0 || blocks[i].f.w != 0 || blocks[i].f.h != 0) {
					oneFloorInfo.push_back(blocks[i]);
				}
			}
			floorInfo.push_back(oneFloorInfo);
			std::vector<block> tmpBlock;
			// 删除所有有有效信息的block
			for (int i = 0; i < blocks.size(); i++) {
				if (blocks[i].f.x != 0 || blocks[i].f.y != 0 || blocks[i].f.w != 0 || blocks[i].f.h != 0) {
					
				}
				else {
					tmpBlock.push_back(blocks[i]);
				}
			}
			blocks.clear();
			for (int i = 0; i < tmpBlock.size(); i++) {
				blocks.push_back(tmpBlock[i]);
			}
		}
		// 提取 每一层的核心信息
		for (int i = 0; i < floorInfo.size(); i++) {
			double maxHight = 0; // 每层的最高距离
			double validVolume = 0;
			for (int j = 0; j < floorInfo[i].size(); j++) {
				// 存储一定的block信息
				validVolume += floorInfo[i][j].volume();
				if (maxHight < floorInfo[i][j].l) {
					maxHight = floorInfo[i][j].l;
				}
			}
			v.push_back({ 80, 55, maxHight, 80 * 55 * maxHight, validVolume, i}); //针对问题4
			std::cout << "this floor" << maxHight << " allVolume " << 80 * 55 * maxHight << " validVolume " << validVolume << " rate " << validVolume / (80 * 55 * maxHight) << std::endl;
		}
		int index = 0;
		// 
		// 先按照顺序填充箱子
		while (v.size()) {
			BigBox bb(80, 55, 21); // 针对问题4
			// 遍历一遍填充箱子
			std::vector<floors> vv; // 备份
			for (int i = 0; i < v.size(); i++) {
				if (bb.addFloor(v[i])) {

				}
				else {
					vv.push_back(v[i]);
				}
			}
			v.clear();
			for (int i = 0; i < vv.size(); i++) {
				v.push_back(vv[i]);
			}
			bb.validPercentageVolume();// 计算有效利用率
			index++;
			std::cout << "[debug] " << index << std::endl;
			std::cout << "箱子的有效利用率[debug]" << bb.validPercentage << std::endl;
			bigBoxes.push_back(bb);
		}
		// 计算输出每个箱子的填充率
		for (int i = 0; i < bigBoxes.size(); i++) {
			std::cout << "箱子 " << i << " 的填充率 " << bigBoxes[i].validPercentage << std::endl;
		}
		for (int i = 0; i < bigBoxes.size(); i++) {
			std::cout << "第 " << i << " 个箱子排布方式" << std::endl;
			for (int j = 0; j < bigBoxes[i].f.size(); j++) {
				std::cout << "第 " << j << " 层箱子排布方式" << std::endl;
				std::cout << "选取原层次数中 " << bigBoxes[i].f[j].index << " 层箱子排布方式" << std::endl;
				for (int k = 0; k < floorInfo[bigBoxes[i].f[j].index].size(); k++) {
					std::cout << "[" << floorInfo[bigBoxes[i].f[j].index][k].f.x << ","
						<< floorInfo[bigBoxes[i].f[j].index][k].f.y << ","
						<< floorInfo[bigBoxes[i].f[j].index][k].f.w << ","
						<< floorInfo[bigBoxes[i].f[j].index][k].f.h << "]," << std::endl;
				}
			}
		}

	}
	
	// 3. 填充箱子
		// a. 计算并输出每个箱子填充率
		// b. 输出每个箱子每一层的填充方案 盒子 - 对应的坐标
	return 1;
}