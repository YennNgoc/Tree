#include <iostream>
using namespace std;
#include "stdio.h"
#include "stdlib.h"
struct NODE 
{ 
	int key; 
	NODE* p_left; 
	NODE* p_right; 
	int height; 
};
int height(NODE* N);
NODE* CreateNode(int data);
void LRN(NODE* p_root);
void LNR(NODE* p_root);
void NLR(NODE* p_root);
void Insert(NODE*& p_root, int x);
void Remove(NODE*& p_root, int x);
bool IsAVL(NODE* p_root);
void LevelOrder(NODE* p_root);


