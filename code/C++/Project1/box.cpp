#include "box.h"


/**************************************************
@brief   : ���캯��
@author  : lee
@input   ��none
@output  ��none
@time    : none
**************************************************/
Box::Box(int _id, double _length, double _width, double _height) {
	id = _id;
	length = _length;
	width = _width;
	height = _height;
}

/**************************************************
@brief   : ��������
@author  : lee
@input   ��none
@output  ��none
@time    : none
**************************************************/
Box::~Box() {}


/**************************************************
@brief   : ����Ь�׶�Ӧ��Ь����� 
@author  : lee
@input   ��none
@output  ��none
@time    : none
**************************************************/
double Box::area(){
	return length * width;
}