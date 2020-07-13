#ifndef __SHOES_H__
#define __SHOES_H__
class Shoes {
public:
	Shoes(int _id, double _length, double _width, double _height, double _share);
	~Shoes();
	double length;// 鞋子的长度
	double width;// 鞋子的宽度
	double height;// 鞋子的高度
	double share;
	int id;
	// 计算鞋底面积
	double area();
};

#endif
