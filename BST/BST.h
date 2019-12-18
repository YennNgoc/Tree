#include <iostream>
using namespace std;
#include "stdio.h"
#include "stdlib.h"
struct  NODE
{
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* CreateNode(int data);
void LRN(NODE* p_root);
void LNR(NODE* p_root);
void NLR(NODE* p_root);
NODE* Search(NODE* p_root, int x);
int Height(NODE* p_root);
void Insert(NODE* &p_root, int x);
void Remove(NODE* &p_root, int x);
bool IsBST(NODE* p_root);
int CountNode(NODE* p_root);
