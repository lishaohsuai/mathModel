#ifndef __PACKER_H__
#define __PACKER_H__
#include <vector>
#include "packer.h"
struct floors {
	double length;
	double height;
	double width;
	double allVolume;//总体积
	double validVolume;//有效的体积
	int index; // 第几层
	floors(double _length, double _width, double _height, double _allVolume, double _validVolume, int _index) {
		length = _length;
		width = _width;
		height = _height;
		allVolume = _allVolume;
		validVolume = _validVolume;
		index = _index;
	}
};

struct Node {
	double x;
	double y;
	double width;
	double height;
	bool isUsed;
	Node * right;
	Node * down;
	Node(double _x, double _y, double _width, double _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		right = NULL;
		down = NULL;
		isUsed = false;
	}
	Node(bool _isUsed, double _x, double _y, double _width, double _height, Node * _down, Node * _right) {
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
	double x;
	double y;
	double w;
	double h;
	info(double _x, double _y, double _w, double _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};
struct block {
	double l;// 高度   注意  注意有所不同
	double w;// 长度
	double h;// 宽度
	Node * fit;
	info f;
	block(double _l, double _w, double _h) :f(0, 0, 0, 0) {
		l = _l;
		w = _w;
		h = _h;
		fit = NULL;
	}
public:
	double volume() {
		return l * w * h;
	}
};

struct kkey {
	double a;
	double b;
	double width;
	double height;
	kkey(double _a, double _b, double _c, double _d) {
		a = _a;
		b = _b;
		width = _c;
		height = _d;
	}
};


class Packer { // 二维矩形
public:
	double width;
	double height;
	double x;
	double y;
	std::vector<kkey> sss;
	Packer(double x_, double y_, double width_, double height_);
	Packer() {};
	void setPacker(double x_, double y_, double width_, double height_);
	~Packer() {};
	void fit(std::vector<block> &blocks);
	Node * findNode(Node * node, double &width, double &height);
	Node * splitNode(Node * node, double w, double h);
	Node * growNode(double w, double h);
	Node * growRight(double w, double h);
	Node * growDown(double w, double h);
	bool isOverlap(kkey a, kkey b);
	Node * root;
};

#endif
