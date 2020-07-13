#include <iostream>
#include "packer.h"
#include <vector>
#include <algorithm>
bool cmp(const block &a, const block & b)
{
	return a.w > b.w;
}
int main() {
	std::vector<block> blocks;
	for (int i = 0; i < 29; i++) {
		blocks.push_back({210, 140});
	}
	for (int i = 0; i < 150; i++) {
		blocks.push_back({ 235, 165 });
	}
	for (int i = 0; i < 77; i++) {
		blocks.push_back({ 275,175 });
	}
	sort(blocks.begin(), blocks.end(), cmp);
	Packer packer(0, 0, 800, 600);
	packer.fit(blocks);
	//for (int i = 0; i < blocks.size(); i++) {
	//	std::cout << blocks[i].f.x << blocks[i].f.y << blocks[i].f.w << blocks[i].f.h << std::endl;
	//}
	system("pause");
}