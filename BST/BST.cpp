#include "BST.h"

int max(int a, int b)
{
	int max = (a > b) ?  a :  b;
	return max;
}
int LeftOf(const int value, const NODE* root)
{
	
	return value < root->key;
}

int RightOf(const int value, const NODE* root)
{
	return value > root->key;
}
NODE* minValueNode(struct NODE* node)
{
	struct NODE* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->p_left != NULL)
		current = current->p_left;

	return current;
}
NODE* CreateNode(int data)
{
	struct NODE* node = (struct NODE*)malloc(sizeof(struct NODE));
	// Assign data to this node 
	node->key = data;
	// Initialize left and right children as NULL 
	node->p_left = NULL;
	node->p_right = NULL;
	return(node);
}
void LRN(NODE* p_root)
{
	if (p_root == NULL)
		return; 
	LRN(p_root->p_left);
	LRN(p_root->p_right);
	cout << p_root->key << " ";
}
void LNR(NODE* p_root)
{
	if (p_root == NULL)
		return;
	LNR(p_root->p_left);
	cout << p_root->key << " ";
	LNR(p_root->p_right);
	
}
void NLR(NODE* p_root)
{
	if (p_root == NULL)
		return;
	cout << p_root->key << " ";
	NLR(p_root->p_left);
	NLR(p_root->p_right);
}
NODE* Search(NODE* p_root, int x)
{
	if (p_root == NULL)
		return nullptr;
	if (p_root->key == x) {
		return p_root;
	}
	else if (LeftOf(x, p_root)) {
		return Search(p_root->p_left, x);
	}
	else if (RightOf(x, p_root)) {
		return Search(p_root->p_right, x);
	}
}
int Height(NODE* p_root)
{
	if (p_root == nullptr)
		return 0;

	// recur for left and right subtree and consider maximum depth
	return 1 + max(Height(p_root->p_left), Height(p_root->p_right));
}
void Insert(NODE*& p_root, int x)
{
	if (p_root == NULL)
		p_root = CreateNode(x);
	if (x < p_root->key)
		Insert(p_root->p_left, x);
	else if (x > p_root->key)
		Insert(p_root->p_right, x);

}
void Remove(NODE*& p_root, int x)
{
	if (p_root == NULL) return;

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (x < p_root->key)
		Remove(p_root->p_left, x);

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (x > p_root->key)
		Remove(p_root->p_right, x);

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{
		// node with only one child or no child 
		if (p_root->p_left == NULL)
		{
			struct NODE* temp = p_root->p_right;
			p_root = temp;
			free(temp);
		}
		else if (p_root->p_right == NULL)
		{
			struct NODE* temp = p_root->p_left;
			p_root = temp;
			free(temp);
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct NODE* temp = minValueNode(p_root->p_right);

		// Copy the inorder successor's content to this node 
		p_root->key = temp->key;

		// Delete the inorder successor 
		Remove(p_root->p_right, temp->key);
	}
}
bool IsBST(NODE* p_root)
{
	if (p_root == NULL)
		return true;

	/* false if left is > than node */
	if (p_root->p_left != NULL && p_root->p_left->key > p_root->key)
		return false;

	/* false if right is < than node */
	if (p_root->p_right != NULL && p_root->p_right->key < p_root->key)
		return false;

	/* false if, recursively, the left or right is not a BST */
	if (!IsBST(p_root->p_left) || !IsBST(p_root->p_right))
		return false;

	return true;
}
int CountNode(NODE* p_root)
{
	
	if (p_root == NULL)
		return 0;
	int count = 1;
	if (p_root->p_left != NULL) {
		count += CountNode(p_root->p_left);
	}
	if (p_root->p_right != NULL) {
		count += CountNode(p_root->p_right);
	}
	return count;
}

int main()
{
	NODE* root = NULL;
	root = CreateNode(6);
	root->p_left = CreateNode(1);
	root->p_right = CreateNode(8);
	root->p_left->p_left = CreateNode(0);
	root->p_left->p_right = CreateNode(7);
	cout << IsBST(root);
	return 0;
}