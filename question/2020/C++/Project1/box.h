#ifndef __BOX_H__
#define __BOX_H__
class Box {
public:
	Box(int _id, double _length, double _width, double _height);
	~Box();
	double length;
	double width;
	double height;
	int id;
	// 计算鞋底对应的面积
	double area();
};

#endif
