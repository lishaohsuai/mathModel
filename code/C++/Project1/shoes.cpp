#include "shoes.h"

/**************************************************
@brief   : ���캯�� ���߿�
@author  : lee
@input   ��none
@output  ��none
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
@brief   : ��������
@author  : lee
@input   ��none
@output  ��none
@time    : none
**************************************************/
Shoes::~Shoes() {}



/**************************************************
@brief   : ����Ь�����
@author  : lee
@input   ��none
@output  ��none
@time    : none
**************************************************/
double Shoes::area() {
	double area_ = 0;
	area_ = (1 + height * 2 - share) * (length + 1); // ��1cm�ĳ���
	return area_;
}

