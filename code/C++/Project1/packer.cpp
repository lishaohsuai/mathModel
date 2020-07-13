#include "packer.h"
#include <iostream>

const double EPS = 0.0001;
/**************************************************
@brief   : 构造函数
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Packer::Packer(double x_, double y_, double width_, double height_) {
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	root = new Node(x, y, width, height);
}


/**************************************************
@brief   : 由于没有初始化造成的措施
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
void Packer::setPacker(double x_, double y_, double width_, double height_) {
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	root = new Node(x, y, width, height);
}

/**************************************************
@brief   : 填充算法
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
void Packer::fit(std::vector<block> &blocks) {
	int len = blocks.size();
	//double width = len > 0 ? blocks[0].w : 0;
	//double height = len > 0 ? blocks[0].h : 0;
	//root = new Node(0, 0, width, height);
	for (int i = 0; i < blocks.size(); i++) {
		block &b = blocks[i];
		double wid = blocks[i].w;
		double hig = blocks[i].h;
		Node * tmp = findNode(root, b.w, b.h);
		if (tmp != NULL) {
			
			bool canAdd = true;
			for (int i = 0; i < sss.size(); i++) {
				if (isOverlap({ tmp->x, tmp->y, b.w, b.h }, sss[i])) {
					canAdd = false;
					break;
				}
			}
			if (canAdd) {
				b.fit = splitNode(tmp, b.w, b.h);
				sss.push_back({ b.fit->x , b.fit->y, b.w, b.h });
				b.f = { b.fit->x , b.fit->y, b.w, b.h };
				//std::cout << b.fit->x << " " << b.fit->y << " " << b.w << " " << b.h << std::endl;
			}
			else {
				if (wid != b.w) {
					b.w = wid;
					b.h = hig;
				}
				b.fit = splitNode(tmp, b.w, b.h);// 恢复成原来的
			}
		}
		/*else {
			b.fit = growNode(b.w, b.h);
		}*/
	}
	std::cout << "一层拟合结束" << std::endl;
}


/**************************************************
@brief   : 寻找节点
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::findNode(Node *  root, double &width, double &height) {
	if (root->isUsed) {
		Node * tmpR = findNode(root->right, width, height);
		if (tmpR)
			return tmpR;
		else {
			tmpR = findNode(root->down, width, height);
			return tmpR;
		}
	}
	else if ((width <= root->width) && (height <= root->height)) {
		return root;
	}
	else if ((width <= root->height) && (height <= root->width)) {
		// 将鞋盒旋转90°
		double tmp = height;
		height = width;// 交换鞋盒的长和宽
		width = tmp;
		return root;
	}
	else
		return NULL;
}

/**************************************************
@brief   : 节点分离
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::splitNode(Node * node, double w, double h) {
	node->isUsed = true;
	node->down = new Node(node->x, node->y + h, node->width, node->height - h);
	node->right = new Node(node->x + w, node->y, node->width - w, node->height);
	return node;
}



/**************************************************
@brief   : 矩形重合判断
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool Packer::isOverlap(kkey rect1, kkey rect2) {
	double startX1 = rect1.a;
	double startY1 = rect1.b;
	double endX1 = startX1 + rect1.width;
	double endY1 = startY1 + rect1.height;

	double startX2 = rect2.a;
	double startY2 = rect2.b;
	double endX2 = startX2 + rect2.width;
	double endY2 = startY2 + rect2.height;

	return !(endY2 < (startY1  + EPS)|| endY1 <( startY2 + EPS) || (startX1 + EPS) > endX2 || (startX2 + EPS) > endX1);
}

/**************************************************
@brief   : 成长方向
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::growNode(double w, double h) {
	bool canGrowDown = (w <= root->width);
	bool canGrowRight = (h <= root->height);

	bool shouldGrowRight = canGrowRight && (root->height >= (root->width + w));
	bool shouldGrowDown = canGrowDown && (root->width >= (root->height + h));

	if (shouldGrowRight) {
		return growRight(w, h);
	}
	else if (shouldGrowDown) {
		return growDown(w, h);
	}
	else if (canGrowRight) {
		return growRight(w, h);
	}
	else if (canGrowDown) {
		return growDown(w, h);
	}
	else {
		return NULL;
	}
}


/**************************************************
@brief   : 向右成长
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::growRight(double w, double h) {
	Node * tmp = new Node(root->width, 0, w, root->height);
	root = new Node(true, 0, 0, root->width + w, root->height, root, tmp);
	Node * node = findNode(root, w, h);
	if (node != NULL) {
		return splitNode(node, w, h);
	}
	else {
		return NULL;
	}
}


/**************************************************
@brief   : 向下成长
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::growDown(double w, double h) {
	Node * tmp = new Node(0, root->height, root->width, h);
	root = new Node(true, 0, 0, root->width, root->height + h, tmp, root);
	Node * node = findNode(root, w, h);
	if (node != NULL) {
		return splitNode(node, w, h);
	}
	else {
		return NULL;
	}
}