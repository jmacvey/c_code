#ifndef _BINARY_SEARCH_TREE_IMPL_H
#define _BINARY_SEARCH_TREE_IMPL_H


//------------------------------------------------------------
// Protected Utility Methods Section:
// Recursive helper methods for the public methods.
//------------------------------------------------------------

template <class ItemType>
LinkedTreeNode<ItemType>* BinarySearchTree<ItemType>::insertInOrder(LinkedTreeNode<ItemType>* subTreePtr,
	LinkedTreeNode<ItemType>* newNode)
{
	// if the node is a nullptr, return the newNodePtr
	if (subTreePtr == nullptr)
	{
		return newNode;
	}
	// else if the root is great, recurse down left
	else if (subTreePtr->getItem() > newNode->getItem())
	{
		LinkedTreeNode<ItemType>* tempNode = insertInOrder(subTreePtr->getLChild(), newNode);
		// link the tree
		subTreePtr->setLChildPtr(tempNode);
	}
	// else the root is less
	else
	{
		LinkedTreeNode<ItemType>* tempNode = insertInOrder(subTreePtr->getRChild(), newNode);
		subTreePtr->setRChildPtr(tempNode);
	}
	return subTreePtr;
}

template <class ItemType>
LinkedTreeNode<ItemType>* BinarySearchTree<ItemType>::removeValue(LinkedTreeNode<ItemType>* subTreePtr,
	const ItemType target,
	bool& success){
	if (subTreePtr == nullptr)
	{
		success = true;
		return nullptr;
	}
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else if (subTreePtr->getItem() > target)
	{
		LinkedTreeNode<ItemType>* tempPtr = removeValue(subTreePtr->getLChild(), target, success);
		subTreePtr->setLChildPtr(tempPtr);
		return subTreePtr;
	}
	else
	{
		LinkedTreeNode<ItemType>* tempPtr = removeValue(subTreePtr->getRChild(), target, success);
		subTreePtr->setRChildPtr(tempPtr);
		return subTreePtr;
	}
}

template <class ItemType>
LinkedTreeNode<ItemType>* BinarySearchTree<ItemType>::removeNode(LinkedTreeNode<ItemType>* nodePtr)
{
	// case I: node is a leaf
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	// case II: node is parent to a single child
	else if (nodePtr->getLChild() == nullptr || nodePtr->getRChild() == nullptr)
	{
		LinkedTreeNode<ItemType>* nodeToConnect = nullptr;
		// if the child is a left child, get it
		if (nodePtr->getLChild() != nullptr)
		{
			nodeToConnect = nodePtr->getLChild();
		}
		// else get the right child
		else
		{
			nodeToConnect = nodePtr->getRChild();
		}
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnect;
	}
	// case III: node has two children
	else
	{
		// newNodeItem is guaranteed to be initialized after tempPtr is called
		ItemType newNodeItem;
		LinkedTreeNode<ItemType>* tempPtr = removeLeftmostNode(nodePtr->getRChild(), newNodeItem);
		nodePtr->setRChildPtr(tempPtr);
		nodePtr->setItem(newNodeItem);
		return nodePtr;
	}
}

template <class ItemType>
LinkedTreeNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(
	LinkedTreeNode<ItemType>* subTreePtr, ItemType& inorderSuccessor) {
	// if  
	if (subTreePtr->getLChild() == nullptr)
	{
		inorderSuccessor = subTreePtr->getItem();
		return removeNode(subTreePtr);
	}
	else
	{
		return removeLeftmostNode(subTreePtr->getLChild(), inorderSuccessor);
	}
}

template <class ItemType>
LinkedTreeNode<ItemType>* BinarySearchTree<ItemType>::findNode(LinkedTreeNode<ItemType>* treePtr,
	const ItemType& target) const {
	// if the value is equal to target, return that node
	if (treePtr == nullptr)
	{
		return treePtr;
	}
	else if (treePtr->getItem() == target)
	{
		return treePtr;
	}
	else
	{
		if (treePtr->getItem() > target)
		{
			LinkedTreeNode<ItemType>* tempNode = findNode(treePtr->getRChild(), target);
		}
		else
		{
			LinkedTreeNode<ItemType>* tempNode = findNode(treePtr->getLChild(), target);
		}
		return treePtr;
	}
}



//------------------------------------------------------------
// Constructor and Destructor Section.
//------------------------------------------------------------

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr) {
}

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) {
	rootPtr = new LinkedTreeNode<ItemType>(rootItem);
}

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& rhs) {
	rootPtr = this->copyTree(rhs.rootPtr);
}

template <class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(BinarySearchTree<ItemType> rhs) {
	LinkedTree<ItemType>::swap(*this, rhs);
	return *this;
}

template <class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {
	this->destroyTree(rootPtr);
}

// Public methods

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
	return this->getNumberOfNodesHelper(rootPtr);
}

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const {
	return rootPtr->getItem();
}

template <class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) {
	rootPtr->setItem(newData);
}


template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {
	LinkedTreeNode<ItemType>* newNodePtr = new LinkedTreeNode<ItemType>(newData);
	rootPtr = this->insertInOrder(rootPtr, newNodePtr);
	return true;
}

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& data) {
	bool success;
	this->removeValue(rootPtr, data, success);
	return success;
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
	return rootPtr == nullptr;
}

template <class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
	return this->getHeightHelper(rootPtr);
}

//------------------------------------------------------------
// Traversal Methods
//------------------------------------------------------------

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const {
	this->preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
	this->inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const {
	this->postorder(visit, rootPtr);
}

//------------------------------------------------------------
// Additional Methods Section.
//------------------------------------------------------------

template<class ItemType>
void BinarySearchTree<ItemType>::reverse() {
	// reverse the tree
	this->reverseHelper(rootPtr);
}

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getMaxValue() const {
	return this->getMaxValueHelper(rootPtr);
}

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getMinValue() const {
	return this->getMinValueHelper(rootPtr);
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isBST() const {
	return this->isBSTHelper(rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType>::printRootToLeafs() const {
	if (!isEmpty())
	{
		if (rootPtr->isLeaf())
		{
			std::cout << rootPtr->getItem();
		}
		else
		{
			int maxPathLength = getHeight();
			// create array of size sufficient for longest path
			ItemType* pathArray = new ItemType[maxPathLength];
			// initialize the first item in array to be the path start
			pathArray[0] = rootPtr->getItem();
			// call the printing function helper
			printRootToLeafsHelper(rootPtr, pathArray, 0);
			delete[] pathArray;
		}
	}
}

template <class ItemType>
bool BinarySearchTree<ItemType>::doesSomePathHaveSum(int sum) const
{
	return this->doesSomePathHaveSumHelper(rootPtr, 0, sum);
}




#endif
