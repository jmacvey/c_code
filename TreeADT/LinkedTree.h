#ifndef _LINKED_TREE_H
#define _LINKED_TREE_H

#include "BinaryTreeInterface.h"
#include "LinkedTreeNode.h"
#include "exceplib.h"
#include <cassert> // assertions
#include <algorithm> // std::max
#include <iostream>
template <class ItemType>
class LinkedTree : public BinaryTreeInterface<ItemType> {
private:
	LinkedTreeNode<ItemType>* rootPtr;
protected: 
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	int getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const;
	int getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const;
	// recursively delete all nodes from tree
	void destroyTree(LinkedTreeNode<ItemType>* subTreePtr);
	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced
	LinkedTreeNode<ItemType>* balancedAdd(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);
	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& success);
	// Copies values up the tree to overwrite value in current node until
	// a leaf is reached; the leaf is then removed, since its value is
	// stored in the parent.
	LinkedTreeNode<ItemType>* moveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr);
	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* treePtr, 
		const ItemType& target, bool& success) const;
	// Recursively searches for the node pointing to target value in the tree
	LinkedTreeNode<ItemType>* findNodeBefore(LinkedTreeNode<ItemType>* treePtr,
		const ItemType& target, bool& success);
	// Copies the tree rooted at treePtr and returns a pointer to
	// the copy.
	LinkedTreeNode<ItemType>* copyTree(const LinkedTreeNode<ItemType>* treePtr) const;
	// reverse helper
	void reverseHelper(LinkedTreeNode<ItemType>* treePtr);
	// swap function for the tree ptrs to help reverseHelper
	void swapChildren(LinkedTreeNode<ItemType>* treePtr);
	// assists getMaxValue function to get maximum valued item in the tree
	ItemType getMaxValueHelper(const LinkedTreeNode<ItemType>* treePtr) const;
	// max of 3 values to assist the getMaxValueHelper function
	ItemType maxOfThree(const ItemType& rootItem,
		const ItemType& leftChildItem, const ItemType& rightChildItem) const;
	// assists getMinValue function to get minimum valued item in the tree
	ItemType getMinValueHelper(const LinkedTreeNode<ItemType>* treePtr) const;
	// min of 3 values to assist the getMinValueHelper function
	ItemType minOfThree(const ItemType& rootItem,
		const ItemType& leftChildItem, const ItemType& rightChildItem) const;
	// assists isBST to determine if the current tree is a binary search tree
	bool isBSTHelper(const LinkedTreeNode<ItemType>* treePtr) const;
	// assist printRootToLeafs to print out all paths from root to leaf
	void printRootToLeafsHelper(const LinkedTreeNode<ItemType>* treePtr, 
		ItemType* arrayPointer, int pathSoFar) const;
	// assist doesSomePathHaveSum to determine if nodes along a path add to a specific number
	bool doesSomePathHaveSumHelper(const LinkedTreeNode<ItemType>* treePtr, 
		int nodeAddr, int sum) const;
	// Recursive traversal helper methods:
	void preorder(void visit(ItemType&),
		LinkedTreeNode<ItemType>* treePtr) const;
	void inorder(void visit(ItemType&),
		LinkedTreeNode<ItemType>* treePtr) const;
	void postorder(void visit(ItemType&),
		LinkedTreeNode<ItemType>* treePtr) const;
public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	LinkedTree();
	LinkedTree(const ItemType& rootItem);
	LinkedTree(const ItemType& rootItem,
		const LinkedTree<ItemType>* leftChildPtr, 
		const LinkedTree<ItemType>* rightChildPtr);
	LinkedTree(const LinkedTree<ItemType>& rhs);
	LinkedTree<ItemType>& operator=(LinkedTree<ItemType> rhs);
	void swap(LinkedTree<ItemType>& lhs, LinkedTree<ItemType>& rhs);
	~LinkedTree();
	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const;
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData);
	bool remove(const ItemType& data);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const
		throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;
	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;
	//------------------------------------------------------------
	// Additional Methods Section.
	//------------------------------------------------------------
	void reverse();
	ItemType getMaxValue() const;
	ItemType getMinValue() const;
	bool isBST() const;
	void printRootToLeafs() const;
	bool doesSomePathHaveSum(int sum) const;
};

#include "LinkedTreeImpl.h"

#endif
