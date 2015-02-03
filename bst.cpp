//=================================================================
// Author       : Daniel Geers
// Mail         : geers[at]cs[dot]uni-frankfurt[dot]de
// Created      : 13.12.2014
// Description  : Binary Search Tree
//=================================================================

#include <iostream>
using namespace std;

// Node structure to represent a node in a binary tree
struct Node
{
	int value;		// value associated with node
	Node* left;		// left subtree ( == 0, if no subtree present)
	Node* right;	// right subtree ( == 0, if no subtree present)
};


/*******************************************
*           HELPER FUNCTIONS               *
*******************************************/

// helper: returns the bigger value of 2 ints
int max(int a, int b){
	if (b < a){
		return a;
	}
	else return b;
}

// helper function: returns true if a node is a leaf, false otherwise
bool is_leaf(Node* node){
	if ((node->left == 0) && (node->right == 0)){
		// cout << node->value << " ist ein Blatt" << endl;
		return true;
	}
	// cout << node->value << " ist kein Blatt" << endl;
	return false;
}

/*******************************************
*         END: HELPER FUNCTIONS            *
*******************************************/

// creates a Node and returns its pointer
Node* CreateNode(int value){
	Node *knoten = new Node;
	knoten->value = value;
	knoten->left = 0;
	knoten->right = 0;
	return knoten;
}


// inserts a node into the binary search tree
void InsertNode(Node* root, Node* node){
	if (root == 0){
		root = node;
	}
	else{
		if (node->value < root->value){
			if (root->left != 0){
				InsertNode(root->left, node);
			}
			else if (root->left == 0){
				root->left = node;
			}
		}
		if (node->value > root->value){
			if (root->right != 0){
				InsertNode(root->right, node);
			}
			else if (root->right == 0){
				root->right = node;
			}
		}
	}

}


// inserts a value into a node
void InsertValue(Node* node, int value){
	Node *nodeptr = CreateNode(value);
	InsertNode(node, nodeptr);
}


// creates a bst and returns its pointer
Node* CreateTree(int* values, unsigned int size){
	Node* ptr = CreateNode(*values);
	for (unsigned int i = 0; i < size; i++){
		InsertValue(ptr, *values);
		values++;
	}
	return ptr;
}


// prints the sorted bst
void PrintTreeSorted(Node* node){
	if (node == 0) return;
	PrintTreeSorted(node->left);
	cout << node->value << "  ";
	PrintTreeSorted(node->right);
}


// deletes a bst to free memory
void DeleteTree(Node* node){
	if (node != 0) {
		DeleteTree(node->left);
		DeleteTree(node->right);
		cout << "\t...deleting node " << node->value << endl;
		delete node;
	}
}

int counter = 1;
// computes the amount of nodes in a tree, use of counter as a global
int NumTreeNodes(Node* node){
	if (node->left != 0){
		// cout << "\tfound node " << node->left->value << " in left child of " << node->value << endl;
		NumTreeNodes(node->left);
		counter++;
	}
	if (node->right != 0){
		// cout << "\tfound node " << node->right->value << " in right child of " << node->value << endl;
		NumTreeNodes(node->right);
		counter++;
	}
	// cout << "counter: " << counter << endl;
	return counter;
}



// computes the depth of a tree, returns it as an int
int TreeDepth(Node* root){
	if (!root){ return 0; }
	else return 1 + max(TreeDepth(root->left), TreeDepth(root->right));
}



// prints the subtrees of a tree represented by '(' / ')' - e.g. tree(sub1(x,y))
void PrintTree(Node* root) {
	if (root == 0) return;
	cout << root->value;
	if (root->left || root->right) {
		cout << "(";
		PrintTree(root->left);
		cout << ",";
		PrintTree(root->right);
		cout << ")";
	}
}


// returns the adress of the node with the value of int param value if found, 0 Pointer otherwise
Node* FindNode(Node* root, int value){
	cout << "\tsearching for " << value << " within node with adress " << root << endl;
	if (root != 0 && root->value == value){
		cout << "yay, " << value << " successfully found in node " << root << " :) " << endl << endl;
		return root;
	}
	if (root->left != 0)
		FindNode(root->left, value);
	if (root->right != 0)
		FindNode(root->right, value);
	return 0;
}



// removes a node from a tree
Node* RemoveNode(Node* root, Node* node){
	if (root == 0){ return root; }
	// case 1: node has no children:
	if (is_leaf(node)){
		node->value = 0;
		delete node;
	}
	// case 2: todo :)
	cout << "RemoveNode not (completely) implemented yet" << endl;
	return root;
}

int main(){
	cout << "Filling Binary Search Tree with values..." << endl << endl;
	int values[] = { 7, 1, 3, 8, 2, 9, 5, 4, 6, 0 };
	Node* tree = CreateTree(values, 10);
	cout << "Tree created...printing sorted tree: " << endl << endl;
	cout << "\t";
	PrintTreeSorted(tree);
	cout << endl << endl;
	cout << "Deleting Binary Search Tree..." << endl << endl;
	DeleteTree(tree);
	cout << "...done!" << endl << endl;
	//reset counter
	counter = 1;

	int values2[15] = { 8, 12, 5, 24, 2, 6, 98, 67, 1, 4, 312, 380, 410, 612, 780 };
	Node* tree2 = CreateTree(values2, 15);
	cout << "PrintTree():";
	PrintTree(tree2);
	cout << endl << "NumTreeNodes: " << NumTreeNodes(tree2) << endl;
	cout << "TreeDepth: " << TreeDepth(tree2) << endl << endl << "Deleting Binary Search Tree..." << endl << endl;
	DeleteTree(tree2);
	cout << "...done!" << endl << endl;
	//reset counter
	counter = 1;

	int values3[] = { 8, 12, 5, 2, 6, 67, 24, 98, 1, 4 };
	Node* tree3 = CreateTree(values3, 10);
	cout << "PrintTree(): ";
	PrintTree(tree3);
	cout << endl;
	// remove an entry from the tree
	int delVal = 67;
	cout << endl << "Removing " << delVal << " from tree:" << endl;
	Node* delNode = FindNode(tree3, delVal);
	if (delNode)
		tree3 = RemoveNode(tree3, delNode);
	PrintTree(tree3);
	cout << endl << endl;
	cout << "Freeing Memory: Deleting Binary Search Tree..." << endl << endl;
	DeleteTree(tree3);
	cout << "...done!" << endl << endl;
	return 0;
}
