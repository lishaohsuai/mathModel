#include "shoes.h"

/**************************************************
@brief   : 构造函数 长高宽
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
Shoes::Shoes(int _id, double _length,  double _height, double _width, double _share) {
	length = _length;
	width = _width;
	height = _height;
	id = _id;
	share = _share;
}


/**************************************************
@brief   : 析构函数
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
Shoes::~Shoes() {}



/**************************************************
@brief   : 计算鞋底面积
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
double Shoes::area() {
	double area_ = 0;
	area_ = (1 + height * 2 - share) * (length + 1); // 有1cm的长度
	return area_;
}

