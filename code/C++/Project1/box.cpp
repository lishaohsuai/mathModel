#include "box.h"


/**************************************************
@brief   : 构造函数
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
Box::Box(int _id, double _length, double _width, double _height) {
	id = _id;
	length = _length;
	width = _width;
	height = _height;
}

/**************************************************
@brief   : 析构函数
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
Box::~Box() {}


/**************************************************
@brief   : 计算鞋底对应的鞋盒面积 
@author  : lee
@input   ：none
@output  ：none
@time    : none
**************************************************/
double Box::area(){
	return length * width;
}