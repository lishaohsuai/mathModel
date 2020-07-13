#include "packer.h"
#include <iostream>
#include <sstream>
/**************************************************
@brief   : 构造函数
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
//const double EPS = 0.0001;

Packer::Packer(int x_, int y_, int width_, int height_) {
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
	//int width = len > 0 ? blocks[0].w : 0;
	//int height = len > 0 ? blocks[0].h : 0;
	//root = new Node(0, 0, width, height);
	for (int i = 0; i < blocks.size(); i++) {
		block b = blocks[i];
		Node * tmp = findNode(root, b.w, b.h);

		if (tmp != NULL) {
			//std::cout << " 剩余空间 " << tmp->x << " " << tmp->y << " " << tmp->width << " " << tmp->height << std::endl;
			b.fit = splitNode(tmp, b.w, b.h);
			bool canAdd = true;
			for (int i = 0; i < sss.size(); i++) {
				if (isOverlap({ b.fit->x, b.fit->y, b.w, b.h }, sss[i])) {
					canAdd = false;
					break;
				}
			}
			if (canAdd) {
				sss.push_back({ b.fit->x , b.fit->y, b.w, b.h });
				b.f = { b.fit->x , b.fit->y, b.w, b.h };
				std::cout << b.fit->x << " " << b.fit->y << " " << b.w << " " << b.h << std::endl;
			}

		}
		//else {
		//	b.fit = growNode(b.w, b.h);
		//}
	}
}


/**************************************************
@brief   : 寻找节点
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::findNode(Node * node, int width, int height) {
	if (node == NULL)
		return NULL;
	if (node->isUsed) {
		Node * tmpR = findNode(node->right, width, height);
		if (tmpR!=NULL)
			return tmpR;
		else {
			Node * tmpL = findNode(node->down, width, height);
			if(tmpL !=NULL)
				return tmpL;
			return NULL;
		}
	}
	else if ((width <= (node->width)) && (height <= (node->height))) {
		return node;
	}
	else
		return NULL;
}

std::string int2str(int a) {
	std::stringstream ss;
	ss << a;
	std::string rlt;
	ss >> rlt;
	return rlt;
}

/**************************************************
@brief   : 节点分离
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::splitNode(Node * node, int w, int h) {
	node->isUsed = true;
	// std::cout << " dd " << node->height - h << "  " << node->width - w << std::endl;
	

	node->right = new Node(node->x + w, node->y, node->width - w, node->height);
	node->down = new Node(node->x, node->y + h, node->width, node->height - h);

	return node;
}




/**************************************************
@brief   : 成长方向
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::growNode(int w, int h) {
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
@brief   : 矩形重合判断
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
bool Packer::isOverlap(kkey rect1, kkey rect2) {
	int startX1 = rect1.a;
	int startY1 = rect1.b;
	int endX1 = startX1 + rect1.width;
	int endY1 = startY1 + rect1.height;

	int startX2 = rect2.a;
	int startY2 = rect2.b;
	int endX2 = startX2 + rect2.width;
	int endY2 = startY2 + rect2.height;

	return !(endY2 <= startY1 || endY1 <= startY2 || startX1 >= endX2 || startX2 >= endX1);
}

/**************************************************
@brief   : 向右成长
@author  : lee
@input   : none
@output  : none
@time    : none
**************************************************/
Node * Packer::growRight(int w, int h) {
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
Node * Packer::growDown(int w, int h) {
	Node * tmp = new Node(0, root->height, root->width, h);
	root = new Node(true, 0, 0, root->width, root->height + h, tmp , root);
	Node * node = findNode(root, w, h);
	if (node != NULL) {
		return splitNode(node, w, h);
	}
	else {
		return NULL;
	}
}