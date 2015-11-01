#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include "BinaryTreeInterface.h"
#include "LinkedTree.h"
#include "LinkedTreeNode.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include "exceplib.h"

// BST is a binary tree, so inherit publicly

template <class ItemType>
class BinarySearchTree : public LinkedTree<ItemType> {
private:
	LinkedTreeNode<ItemType>* rootPtr;
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// recursively finds where the given node should be placed and
	// inserts it in a leaf at that point
	LinkedTreeNode<ItemType>* insertInOrder(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNode);
	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr,
		const ItemType target,
		bool& success);
	// Removes a given node from a tree while maintaining a
	// binary search tree.
	LinkedTreeNode<ItemType>* removeNode(LinkedTreeNode<ItemType>* nodePtr);
	// Removes the leftmost node in the left subtree of the node
	// pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	LinkedTreeNode<ItemType>* removeLeftmostNode(
		LinkedTreeNode<ItemType>* subTreePtr, ItemType& inorderSuccessor);
	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* treePtr,
		const ItemType& target) const;
public:
	BinarySearchTree(); // default constructor
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& rhs); // copy constructor
	BinarySearchTree<ItemType>& operator=(BinarySearchTree<ItemType> rhs); // assignment operator
	~BinarySearchTree(); // default destructor
	//------------------------------------------------------------
	// Public Methods
	//------------------------------------------------------------
	int getNumberOfNodes() const;
	ItemType getRootData() const;
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData);
	bool remove(const ItemType& data);
	bool isEmpty() const;
	int getHeight() const; 
	//------------------------------------------------------------
	// Traversal Methods
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

#include "BinarySearchTreeImpl.h"

#endif
