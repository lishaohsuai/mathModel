#include "bigBox.h"

/**************************************************
@brief   : 描述大箱子
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
BigBox::BigBox(double _length, double _width, double _height) {
	length = _length;
	width = _width;
	height = _height;
	havePushHight = 0;
	validPercentage = 0;
}

/**************************************************
@brief   : 加入的层信息
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool BigBox::addFloor(floors x) {
	if (x.height + havePushHight > height) {
		return false;
	}
	else {
		havePushHight += x.height;
		f.push_back(x);
		return true;
	}
}

/**************************************************
@brief   : 计算大箱子的有效利用体积
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
double BigBox::validPercentageVolume() {
	double validBigVolume = 0;
	for (int i = 0; i < f.size(); i++) {
		validBigVolume += f[i].validVolume;
	}
	validPercentage = validBigVolume / (length * width * height);
	return validPercentage;
}



/**************************************************
@brief   : 构造函数2
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
BigBox::BigBox(double _length, double _width, double _height, double _validPercentage) {
	length = _length;
	width = _width;
	height = _height;
	validPercentage = _validPercentage;
}