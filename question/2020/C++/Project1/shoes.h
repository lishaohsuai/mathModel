#ifndef __SHOES_H__
#define __SHOES_H__
class Shoes {
public:
	Shoes(int _id, double _length, double _width, double _height, double _share);
	~Shoes();
	double length;// Ь�ӵĳ���
	double width;// Ь�ӵĿ��
	double height;// Ь�ӵĸ߶�
	double share;
	int id;
	// ����Ь�����
	double area();
};

#endif
