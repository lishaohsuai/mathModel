#ifndef __PACKER_H__
#define __PACKER_H__
#include <vector>
#include <set>
#include <string>

struct kkey {
	int a;
	int b;
	int width;
	int height;
	kkey(int _a, int _b, int _c, int _d) {
		a = _a;
		b = _b;
		width = _c;
		height = _d;
	}
};

struct Node {
	int x;
	int y;
	int width;
	int height;
	bool isUsed;
	Node * right;
	Node * down;
	Node(int _x, int _y, int _width, int _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		right = NULL;
		down = NULL;
		isUsed = false;
	}
	Node(bool _isUsed, int _x, int _y, int _width, int _height, Node * _down, Node * _right) {
		isUsed = _isUsed;
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		down = _down;
		right = _right;
	}
};

struct info {
	int x;
	int y;
	int w;
	int h;
	info(int _x, int _y, int _w, int _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};
struct block {
	int w;
	int h;
	Node * fit;
	info f;
	block(int _w, int _h):f(0, 0, 0, 0) {
		w = _w;
		h = _h;
		fit = NULL;
	}
};
class Packer { // 大矩形箱子
public:
	int width;
	int height;
	int x;
	int y;
	std::vector<kkey> sss;
	Packer(int x_, int y_, int width_, int height_);
	Packer() {};
	~Packer() {};
	void fit(std::vector<block> &blocks);
	Node * findNode(Node * node, int width, int height);
	Node * splitNode(Node * node, int w, int h);
	Node * growNode(int w, int h);
	Node * growRight(int w, int h);
	Node * growDown(int w, int h);
	bool isOverlap(kkey a, kkey b);
	Node * root;
};

#endif
