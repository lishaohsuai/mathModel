#ifndef __BIGBOX_H__
#define __BIGBOX_H__
#include <vector>
#include "packer.h"
//struct floors {
//	double length;
//	double height;
//	double width;
//	double allVolume;//总体积
//	double validVolume;//有效的体积
//	floors(double _length, double _width, double _height, double _allVolume, double _validVolume) {
//		length = _length;
//		width = _width;
//		height = _height;
//		allVolume = _allVolume;
//		validVolume = _validVolume;
//	}
//};
class BigBox {
public:
	double length;
	double width;
	double height;
	double havePushHight;
	double validPercentage;
	BigBox(double _length, double _width, double _height);
	BigBox(double _length, double _width, double _height, double _validPercentage);
	double validPercentageVolume();
	~BigBox() {};
	bool addFloor(floors x);
	std::vector<floors> f;// 加入的层信息

};

#endif __BIGBOX_H__