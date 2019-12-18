#include "AVL.h"
NODE* minValueNode(struct NODE* node)
{
	struct NODE* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->p_left != NULL)
		current = current->p_left;

	return current;
}
int max(int a, int b)
{
	int max = (a > b) ? a : b;
	return max;
}
int height(NODE* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
int getBalance(NODE* N)
{
	if (N == NULL)
		return 0;
	return height(N->p_left) - height(N->p_right);
}
NODE* rightRotate(NODE* y)
{
	NODE* x = y->p_left;
	NODE* T2 = x->p_right;

	// Perform rotation  
	x->p_right = y;
	y->p_left = T2;

	// Update heights  
	y->height = max(height(y->p_left),
		height(y->p_right)) + 1;
	x->height = max(height(x->p_left),
		height(x->p_right)) + 1;

	// Return new root  
	return x;
}
NODE* leftRotate(NODE* x)
{
	NODE* y = x->p_right;
	NODE* T2 = y->p_left;

	// Perform rotation  
	y->p_left = x;
	x->p_right = T2;

	// Update heights  
	x->height = max(height(x->p_left),
		height(x->p_right)) + 1;
	y->height = max(height(y->p_left),
		height(y->p_right)) + 1;

	// Return new root  
	return y;
}
NODE* CreateNode(int data)
{
	struct NODE* node = (struct NODE*)malloc(sizeof(struct NODE));
	// Assign data to this node 
	node->key = data;
	// Initialize left and right children as NULL 
	node->p_left = NULL;
	node->p_right = NULL;
	node->height = 1;
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
void Insert(NODE*& p_root, int x)
{
	if (p_root == NULL)
	{
		p_root = CreateNode(x);
		return;
	}
	else if (x < p_root->key)
	{
		Insert(p_root->p_left, x);
	}
	else if (x > p_root->key)
	{
		Insert(p_root->p_right, x);
	}
	else // Equal keys are not allowed in BST  
		return;

	/* 2. Update height of this ancestor node */
	p_root->height = 1 + max(height(p_root->p_left),height(p_root->p_right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(p_root);

	// If this node becomes unbalanced, then  
	// there are 4 cases  

	// Left Left Case  
	if (balance > 1 && x < p_root->p_left->key)
	{
		p_root = rightRotate(p_root);
		return;
	}
		
	// Right Right Case  
	if (balance < -1 && x > p_root->p_right->key)
	{
		p_root = leftRotate(p_root);
		return;
	}
		

	// Left Right Case  
	if (balance > 1 && x > p_root->p_left->key)
	{
		p_root->p_left = leftRotate(p_root->p_left);
		p_root = rightRotate(p_root);
		return;
	}

	// Right Left Case  
	if (balance < -1 && x < p_root->p_right->key)
	{
		p_root->p_right = rightRotate(p_root->p_right);
		p_root = leftRotate(p_root);
		return;
	}
}
void Remove(NODE*& p_root, int x)
{
	if (p_root == NULL)
		return;

	// If the key to be deleted is smaller  
	// than the root's key, then it lies 
	// in left subtree  
	if (x < p_root->key)
		Remove(p_root->p_left, x);

	// If the key to be deleted is greater  
	// than the root's key, then it lies  
	// in right subtree  
	else if (x > p_root->key)
		Remove(p_root->p_right, x);

	// if key is same as root's key, then  
	// This is the node to be deleted 
	else
	{
		// node with only one child or no child  
		if ((p_root->p_left == NULL) ||
			(p_root->p_right == NULL))
		{
			NODE* temp = p_root->p_left ?
				p_root->p_left :
				p_root->p_right;

			// No child case  
			if (temp == NULL)
			{
				temp = p_root;
				p_root = NULL;
			}
			else // One child case  
				*p_root = *temp; // Copy the contents of  
							   // the non-empty child  
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			NODE* temp = minValueNode(p_root->p_right);

			// Copy the inorder successor's  
			// data to this node  
			p_root->key = temp->key;
			// Delete the inorder successor  
			Remove(p_root->p_right, temp->key);
		}
	}

	// If the tree had only one node 
	// then return  
	if (p_root == NULL)
		return;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
	p_root->height = 1 + max(height(p_root->p_left),
		height(p_root->p_right));

	// STEP 3: GET THE BALANCE FACTOR OF  
	// THIS NODE (to check whether this  
	// node became unbalanced)  
	int balance = getBalance(p_root);

	// If this node becomes unbalanced,  
	// then there are 4 cases  

	// Left Left Case  
	if (balance > 1 &&getBalance(p_root->p_left) >= 0)
	{
		p_root = rightRotate(p_root);
		return;
	}
	// Left Right Case  
	if (balance > 1 && getBalance(p_root->p_left) < 0)
	{
		p_root->p_left = leftRotate(p_root->p_left);
		p_root = rightRotate(p_root);
		return;
	}

	// Right Right Case  
	if (balance < -1 && getBalance(p_root->p_right) <= 0)
	{
		p_root = leftRotate(p_root);
		return;
	}

	// Right Left Case  
	if (balance < -1 &&	getBalance(p_root->p_right) > 0)
	{
		p_root->p_right = rightRotate(p_root->p_right);
		p_root = leftRotate(p_root);
		return;
	}
}
bool IsAVL(NODE* p_root)
{
	int lh;
	int rh;
	if (p_root == NULL)
		return 1;
	lh = height(p_root->p_left); // left height
	rh = height(p_root->p_right); // right height
	if (abs(lh - rh) <= 1 && IsAVL(p_root->p_left) && IsAVL(p_root->p_right)) return 1;
	return 0;
}
void printGivenLevel(NODE* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		cout << root->key << " ";
	else if (level > 1)
	{
		printGivenLevel(root->p_left, level - 1);
		printGivenLevel(root->p_right, level - 1);
	}
}
void LevelOrder(NODE* p_root)
{
	for (int i = 1; i <= p_root->height; i++)
		printGivenLevel(p_root, i);
}
