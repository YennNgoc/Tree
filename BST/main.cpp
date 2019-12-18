#include "AVL.h" 
int main()
{
	NODE* p_root = nullptr;
	p_root = CreateNode(50);
	Insert(p_root, 30);
	Insert(p_root, 20);
	Insert(p_root, 40);
	Insert(p_root, 70);
	Insert(p_root, 60);
	Insert(p_root, 80);
	//NODE* temp = Search(p_root, 40);
	int c = CountNode(p_root);
	LNR(p_root);
	cout << endl << c;
}