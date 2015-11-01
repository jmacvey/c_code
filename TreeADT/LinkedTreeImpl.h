#ifndef _LINKED_TREE_IMPL_H
#define _LINKED_TREE_IMPL_H

/** IMPLEMENTATION FILE FOR LINKED_TREE_H */

//------------------------------------------------------------
// Protected Utility Methods Section:
// Recursive helper methods for the public methods.
//------------------------------------------------------------

template <class ItemType>
int LinkedTree<ItemType>::getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
	if (subTreePtr == nullptr)
	{
		return 0;
	}
	else return 1 + std::max(getHeightHelper(subTreePtr->getLChild()), getHeightHelper(subTreePtr->getRChild()));
}

template <class ItemType>
int LinkedTree<ItemType>::getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
	if (subTreePtr == nullptr)
	{
		return 0;
	}
	else return 1 + getNumberOfNodesHelper(subTreePtr->getLChild()) + getNumberOfNodesHelper(subTreePtr->getRChild());
}

template<class ItemType>
void LinkedTree<ItemType>::destroyTree(LinkedTreeNode<ItemType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		// destroy the left tree
		destroyTree(subTreePtr->getLChild());
		// destroy the right tree
		destroyTree(subTreePtr->getRChild());
		// destroy the node itself
		delete subTreePtr;
	}
}



template <class ItemType>
LinkedTreeNode<ItemType>* LinkedTree<ItemType>::balancedAdd(LinkedTreeNode<ItemType>* subTreePtr,
	LinkedTreeNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
	{
		// if the subTreePtr is null, then the new node ptr is a root
		return newNodePtr;
	}
	else {
		LinkedTreeNode<ItemType>* leftChildPtr = subTreePtr->getLChild();
		LinkedTreeNode<ItemType>* rightChildPtr = subTreePtr->getRChild();
		// equality test
		if (getHeightHelper(rightChildPtr) == getHeightHelper(leftChildPtr))
		{
			if (getNumberOfNodesHelper(rightChildPtr) >= getNumberOfNodesHelper(leftChildPtr))
			{
				leftChildPtr = balancedAdd(leftChildPtr, newNodePtr);
				// link the node to the left subtree
				subTreePtr->setLChildPtr(leftChildPtr);
			}
			else {
				rightChildPtr = balancedAdd(rightChildPtr, newNodePtr);
				// link the node to the right subtree
				subTreePtr->setRChildPtr(rightChildPtr);
			}
		}
		else
		{
			if (getHeightHelper(rightChildPtr) < getHeightHelper(leftChildPtr))
			{
				// if left height is greater than right height, balance add the 
				// node to the right side
				rightChildPtr = balancedAdd(rightChildPtr, newNodePtr);
				// link the node to the right subtree
				subTreePtr->setRChildPtr(rightChildPtr);

			}
			else
			{
				// else balancadd the node to the left side
				leftChildPtr = balancedAdd(leftChildPtr, newNodePtr);
				// link the node to the left subtree
				subTreePtr->setLChildPtr(leftChildPtr);
			}
			return subTreePtr;
		}
	}
}

template <class ItemType>
LinkedTreeNode<ItemType>* LinkedTree<ItemType>::removeValue(LinkedTreeNode<ItemType>* subTreePtr,
	const ItemType& target, bool& success) {
	// check if root is alone
	if (rootPtr->isLeaf())
	{
		delete rootPtr;
		rootPtr = nullptr;
	}
	else {
		LinkedTreeNode<ItemType>* nodeToRemove = findNode(subTreePtr, target, success);
		// check if the node is a leaf
		if (nodeToRemove->isLeaf())
		{
			LinkedTreeNode<ItemType>* nodeBefore = findNodeBefore(subTreePtr, target, success);
			if (nodeBefore->getLChild() != nullptr && nodeBefore->getLChild()->getItem() == target)
			{ // check if its the left child of the node before
				delete nodeBefore->getLChild();
				nodeBefore->setLChildPtr(nullptr);
			}
			// else must be right child
			else
			{
				delete nodeBefore->getRChild();
				nodeBefore->setRChildPtr(nullptr);
			}
		}
		else
		{	// else can move the values up the tree
			moveValuesUpTree(nodeToRemove);

		}
		// copy the values up the tree, effectively erasing the node
		//std::cout << "\t Exiting removeValue..." << std::endl;
		return nullptr;
	}
}

template <class ItemType>
LinkedTreeNode<ItemType>* LinkedTree<ItemType>::moveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr)
{
	// should only get called
	assert(subTreePtr != nullptr && !subTreePtr->isLeaf());
	LinkedTreeNode<ItemType>* lChildPointer = subTreePtr->getLChild();
	LinkedTreeNode<ItemType>* rChildPointer = subTreePtr->getRChild();
	if (lChildPointer != nullptr)
	{
		ItemType copyItem = lChildPointer->getItem();
		//std::cout << "Copying " << copyItem << "over " << subTreePtr->getItem();
		subTreePtr->setItem(copyItem);
		if (lChildPointer->isLeaf())
		{
			delete lChildPointer;
			subTreePtr->setLChildPtr(nullptr);
		}
		else
		{
			moveValuesUpTree(lChildPointer);
		}
	}
	else if (rChildPointer != nullptr)
	{
		ItemType copyItem = rChildPointer->getItem();
		//std::cout << "Copying " << copyItem << "over " << subTreePtr->getItem();
		subTreePtr->setItem(copyItem);
		if (rChildPointer->isLeaf())
		{
			delete rChildPointer;
			subTreePtr->setRChildPtr(nullptr);
		}
		else
		{
			moveValuesUpTree(rChildPointer);
		}
	}
	return nullptr;
}

template <class ItemType>
LinkedTreeNode<ItemType>* LinkedTree<ItemType>::findNodeBefore(LinkedTreeNode<ItemType>* treePtr,
	const ItemType& target, bool& success)
{
	//std::cout << "calling findNodeBefore..." << std::endl;
	if (treePtr == nullptr)
	{
		//std::cout << "returning nullptr." << std::endl;
		return treePtr;
	}
	else if ((treePtr->getLChild() != nullptr && treePtr->getLChild()->getItem() == target)
		|| (treePtr->getRChild() != nullptr && treePtr->getRChild()->getItem() == target))
	{
		//std::cout << "NodeBefore is found..." << std::endl;
		//std::cout << "Exiting findNodeBefore..." << std::endl;
		return treePtr;
	}
	// else check if it's the left node
	else
	{
		if (treePtr->getLChild() != nullptr)
		{
			//std::cout << "Checking left node..." << std::endl;
			LinkedTreeNode<ItemType>* Node = findNodeBefore(treePtr->getLChild(), target, success);
			if (Node == nullptr)
			{ // if it's not the left node, check if it's the right node
				if (treePtr->getRChild() != nullptr)
				{
					//	std::cout << "Checking right node..." << std::endl;
					Node = findNodeBefore(treePtr->getRChild(), target, success);
				}
				// return either nullPtr or the appropriate node
				//std::cout << "Exiting findNode with value: " << Node << std::endl;
				return Node;
			}
		}
		return nullptr;
	}
}


template <class ItemType>
LinkedTreeNode<ItemType>* LinkedTree<ItemType>::findNode(LinkedTreeNode<ItemType>* treePtr,
	const ItemType& target, bool& success) const
{
	//std::cout << "Calling findNode..." << std::endl;
	// if nullptr, return it
	if (treePtr == nullptr)
	{
		//std::cout << "Exiting findNode with value: " << treePtr << std::endl;
		return treePtr;
	}
	// if it's the target, return that
	if (treePtr->getItem() == target)
	{
		//std::cout << "Returning Value " << treePtr->getItem() << "@ address " << treePtr << std::endl;
		//std::cout << "Exiting findNode for that item..." << std::endl;
		return treePtr;
	}
	else
	{
		// else check if it's the left node
		if (treePtr->getLChild() == nullptr && treePtr != rootPtr)
		{
			return nullptr;
		}
		LinkedTreeNode<ItemType>* Node = findNode(treePtr->getLChild(), target, success);
		if (Node == nullptr)
		{ // if it's not the left node, check if it's the right node
			if (treePtr->getRChild() == nullptr)
			{
				return nullptr;
			}
			//std::cout << "Checking right node..." << std::endl;
			Node = findNode(treePtr->getRChild(), target, success);
		}
		return Node;
	}
	//std::cout << "Checking left node..." << std::endl;

	// return either nullPtr or the appropriate node
	//std::cout << "Exiting findNode with value: " << Node << std::endl;
}

template <class ItemType>
LinkedTreeNode<ItemType>* LinkedTree<ItemType>::copyTree(const LinkedTreeNode<ItemType>* treePtr) const
{
	LinkedTreeNode<ItemType>* newTreePtr = nullptr;
	while (treePtr != nullptr)
	{
		// copy the root 
		newTreePtr = new LinkedTreeNode<ItemType>(treePtr->getItem());
		// copy the left subtree
		newTreePtr->setLChildPtr(copyTree(treePtr->getLChild()));
		// copy the right subtree
		newTreePtr->setRChildPtr(copyTree(treePtr->getRChild()));
	}
	return newTreePtr;

}

template<class ItemType>
void LinkedTree<ItemType>::reverseHelper(LinkedTreeNode<ItemType>* treePtr){
	using std::swap;
	// recursive base case: treePtr is a leaf
	if (!treePtr->isLeaf())
	{
		// swap data pointed to left and right pointers
		swapChildren(treePtr);
		if (treePtr->getLChild() != nullptr)
		{
			// recursive call to reverse the left subtree 
			reverseHelper(treePtr->getLChild());
		}
		if (treePtr->getRChild() != nullptr)
		{
			// recursive call to reverse the right subtree
			reverseHelper(treePtr->getRChild());
		}
	}
}

template <class ItemType>
void LinkedTree<ItemType>::swapChildren(LinkedTreeNode<ItemType>* treePtr) {
	LinkedTreeNode<ItemType>* temp = treePtr->getLChild();
	treePtr->setLChildPtr(treePtr->getRChild());
	treePtr->setRChildPtr(temp);
}

template <class ItemType>
ItemType LinkedTree<ItemType>::getMaxValueHelper(const LinkedTreeNode<ItemType>* treePtr) const {
	// treePtr should never be nullptr
	assert(treePtr != nullptr);
	// if the tree is a leaf, then max value is the root (base case)
	if (treePtr->isLeaf())
	{
		return treePtr->getItem();
	}
	// if tree has only right pointer, then compare the root to the max value in right subtree
	else if (treePtr->getLChild() == nullptr)
	{
		return std::max(treePtr->getItem(), getMaxValueHelper(treePtr->getRChild()));
	}
	// else if tree has only a left child, compare the root to the max value in left subtree
	else if (treePtr->getRChild() == nullptr)
	{
		return std::max(treePtr->getItem(), getMaxValueHelper(treePtr->getRChild()));
	}
	// else if both right and left children exist, compare the root to the max value in the left and right subtrees
	else
	{
		return maxOfThree(treePtr->getItem(),
			getMaxValueHelper(treePtr->getLChild()), getMaxValueHelper(treePtr->getRChild()));
	}
}


template <class ItemType>
ItemType LinkedTree<ItemType>::maxOfThree(const ItemType& rootItem,
	const ItemType& leftChildItem, const ItemType& rightChildItem) const {
	if (rootItem >= leftChildItem && rootItem >= rightChildItem)
	{
		return rootItem;
	}
	else if (leftChildItem >= rootItem && leftChildItem >= rightChildItem)
	{
		return leftChildItem;
	}
	else
	{
		return rightChildItem;
	}
}

template <class ItemType>
ItemType LinkedTree<ItemType>::getMinValueHelper(const LinkedTreeNode<ItemType>* treePtr) const {
	// treePtr should never be nullptr
	assert(treePtr != nullptr);
	// if the tree is a leaf, then min value is the root (base case)
	if (treePtr->isLeaf())
	{
		return treePtr->getItem();
	}
	// if tree has only right pointer, then compare the root to the min value in right subtree
	else if (treePtr->getLChild() == nullptr)
	{
		return std::min(treePtr->getItem(), getMinValueHelper(treePtr->getRChild()));
	}
	// else if tree has only a left child, compare the root to the max value in left subtree
	else if (treePtr->getRChild() == nullptr)
	{
		return std::min(treePtr->getItem(), getMinValueHelper(treePtr->getRChild()));
	}
	// else if both right and left children exist, compare the root to the max value in the left and right subtrees
	else
	{
		return minOfThree(treePtr->getItem(),
			getMinValueHelper(treePtr->getLChild()), getMinValueHelper(treePtr->getRChild()));
	}
}

template <class ItemType>
ItemType LinkedTree<ItemType>::minOfThree(const ItemType& rootItem,
	const ItemType& leftChildItem, const ItemType& rightChildItem) const {
	if (rootItem <= leftChildItem && rootItem <= rightChildItem)
	{
		return rootItem;
	}
	else if (leftChildItem <= rootItem && leftChildItem <= rightChildItem)
	{
		return leftChildItem;
	}
	else
	{
		return rightChildItem;
	}
}

template <class ItemType>
bool LinkedTree<ItemType>::isBSTHelper(const LinkedTreeNode<ItemType>* treePtr) const {
	bool success = false;
	// recursive base case: any leaf if automatically a BST
	if (treePtr->isLeaf())
	{
		success = true;
	}
	// if left child is null, then determine if the right side is greater than or equal
	// to the root and recurse down the right side
	else if (treePtr->getLChild() == nullptr)
	{
		if (treePtr->getRChild()->getItem() >= treePtr->getItem())
		{
			success = isBSTHelper(treePtr->getRChild());
		}
		else
		{
			success = false;
		}
	}
	// else if right child is null, then determine if the left side is less than 
	// the root and recurse down the left side
	else if (treePtr->getRChild() == nullptr)
	{
		if (treePtr->getLChild()->getItem() < treePtr->getItem())
		{
			success = isBSTHelper(treePtr->getLChild());
		}
		else
		{
			success = false;
		}
	}
	// else both children exists, so ensure left is less than root  right and
	// ensure right is greater than root
	else
	{
		if ((treePtr->getLChild()->getItem() < treePtr->getItem()
			&& treePtr->getLChild()->getItem() < treePtr->getRChild()->getItem())
			&& treePtr->getRChild()->getItem() >= treePtr->getItem())
		{
			// recurse down the left side first
			success = isBSTHelper(treePtr->getLChild());
			// if the left side of the tree is a BST, recurse down the right side
			if (success)
			{
				success = isBSTHelper(treePtr->getRChild());
			}
		}
		else
		{
			success = false;
		}
	}
	return success;
}

template <class ItemType>
void LinkedTree<ItemType>::printRootToLeafsHelper(const LinkedTreeNode<ItemType>* treePtr,
	ItemType* arrayPointer, int pathSoFar) const {
	// recursive base case: if the treePtr is a leaf,
	// print out the path 
	if (treePtr->isLeaf())
	{
		for (int i = 0; i <= pathSoFar; i++)
		{
			std::cout << arrayPointer[i];
			if (i != pathSoFar)
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	else
	{
		// else if there is a left child but no right child
		// add the item to the current index in the array and 
		if (treePtr->getRChild() == nullptr)
		{
			pathSoFar++;
			arrayPointer[pathSoFar] = treePtr->getLChild()->getItem();
			// recurse through the rightSubTree
			printRootToLeafsHelper(treePtr->getLChild(), arrayPointer, pathSoFar);
		}
		// else if there is a right child but no left child
		// add the item to the current index in the array and 
		else if (treePtr->getLChild() == nullptr)
		{
			pathSoFar++;
			arrayPointer[pathSoFar] = treePtr->getRChild()->getItem();
			// recurse through the right
			printRootToLeafsHelper(treePtr->getRChild(), arrayPointer, pathSoFar);
		}
		// default case when both children exist
		else
		{
			pathSoFar++;
			// add to the array for the left child
			arrayPointer[pathSoFar] = treePtr->getLChild()->getItem();
			// recurse down left
			printRootToLeafsHelper(treePtr->getLChild(), arrayPointer, pathSoFar);
			// then do the same for the right child
			arrayPointer[pathSoFar] = treePtr->getRChild()->getItem();
			printRootToLeafsHelper(treePtr->getRChild(), arrayPointer, pathSoFar);
		}
	}
}

template <class ItemType>
bool LinkedTree<ItemType>::doesSomePathHaveSumHelper(const LinkedTreeNode<ItemType>* treePtr,
	int nodeAddr, int sum) const {
	if (!isEmpty())
	{
		bool success = false;
		// if the node is a leaf, add that node and see if it is a sum
		nodeAddr += treePtr->getItem();
		if (treePtr->isLeaf())
		{
			// if the addition all the nodes is equal to a sum, then we have a success
			success = (nodeAddr == sum);
		}
		// else if the subtree is lacking a left child, we recurse down right
		else if (treePtr->getLChild() == nullptr)
		{
			success = doesSomePathHaveSumHelper(treePtr->getRChild(), nodeAddr, sum);
		}
		// else if the subtree is lacking a right child, we recurse down left
		else if (treePtr->getRChild() == nullptr)
		{
			success = doesSomePathHaveSumHelper(treePtr->getLChild(), nodeAddr, sum);
		}
		// else default case: both children exist, so recurse down left first, and then right
		// if still not successful
		else
		{
			success = doesSomePathHaveSumHelper(treePtr->getLChild(), nodeAddr, sum);
			if (!success)
			{
				success = doesSomePathHaveSumHelper(treePtr->getRChild(), nodeAddr, sum);
			}
		}
		return success;
	}
	return false;
}

template <class ItemType>
void LinkedTree<ItemType>::inorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const {
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLChild());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRChild());
	}
}

template <class ItemType>
void LinkedTree<ItemType>::preorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const {
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		preorder(visit, treePtr->getLChild());
		preorder(visit, treePtr->getRChild());
	}
}

template <class ItemType>
void LinkedTree<ItemType>::postorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const {
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLChild());
		postorder(visit, treePtr->getRChild());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
	}
}

//------------------------------------------------------------
// Constructor and Destructor Section.
//------------------------------------------------------------

template<class ItemType>
LinkedTree<ItemType>::LinkedTree() : rootPtr(nullptr) {}

template<class ItemType>
LinkedTree<ItemType>::LinkedTree(const ItemType& rootItem) {
	rootPtr = new LinkedTreeNode<ItemType>(rootItem);
}

template<class ItemType>
LinkedTree<ItemType>::LinkedTree(const ItemType& rootItem,
	const LinkedTree<ItemType>* leftChildPtr,
	const LinkedTree<ItemType>* rightChildPtr) {
	rootPtr = new LinkedTreeNode<ItemType>(rootItem, copyTree(leftChildPtr->rootPtr), copyTree(rightChildPtr->rootPtr));
}

template <class ItemType>
LinkedTree<ItemType>::LinkedTree(const LinkedTree<ItemType>& rhs) {
	rootPtr = copyTree(rhs.rootPtr);
}

template <class ItemType>
LinkedTree<ItemType>& LinkedTree<ItemType>::operator=(LinkedTree<ItemType> rhs) {
	LinkedTree<ItemType>::swap(*this, rhs);
	return *this;
}

template <class ItemType>
void LinkedTree<ItemType>::swap(LinkedTree<ItemType>& lhs, LinkedTree<ItemType>& rhs) {
	using std::swap;
	swap(lhs.rootPtr, rhs.rootPtr);
}

template<class ItemType>
LinkedTree<ItemType>::~LinkedTree() {
	//std::cout << "LinkedTree Destructor invoked" << std::endl;
	destroyTree(rootPtr);
}

//------------------------------------------------------------
// Public BinaryTreeInterface Methods Section.
//------------------------------------------------------------

template<class ItemType>
bool LinkedTree<ItemType>::isEmpty() const {
	return rootPtr == nullptr;
}

template<class ItemType>
int LinkedTree<ItemType>::getHeight() const {
	return getHeightHelper(rootPtr);
}

template<class ItemType>
int LinkedTree<ItemType>::getNumberOfNodes() const {
	return getNumberOfNodesHelper(rootPtr);
}

template <class ItemType>
ItemType LinkedTree<ItemType>::getRootData() const {
	return rootPtr->getItem();
}

template <class ItemType>
void LinkedTree<ItemType>::setRootData(const ItemType& newData) {
	rootPtr->setItem(newData);
}

template<class ItemType>
bool LinkedTree<ItemType>::add(const ItemType& newData) {
	LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>(newData);
	rootPtr = balancedAdd(rootPtr, newNode);
	return true;
}

template <class ItemType>
bool LinkedTree<ItemType>::remove(const ItemType& data) {
	bool success = true;
	removeValue(rootPtr, data, success);
	//std::cout << "Value removed." << std::endl;
	return success;
}

template <class ItemType>
void LinkedTree<ItemType>::clear() {
	// destroy the tree
	destroyTree(rootPtr);
}

template <class ItemType>
bool LinkedTree<ItemType>::contains(const ItemType& anEntry) const{
	bool success = false;
	LinkedTreeNode<ItemType>* nodeWithItem = findNode(rootPtr, anEntry, success);
	if (nodeWithItem != nullptr && nodeWithItem->getItem() == anEntry)
	{
		success = true;
	}
	return success;
}

template <class ItemType>
ItemType LinkedTree<ItemType>::getEntry(const ItemType& anEntry) const
throw(NotFoundException) {
	bool success = true;
	if (!contains(anEntry))
	{
		throw NotFoundException("Binary Tree does not contain item.");
	}
	else {
		LinkedTreeNode<ItemType>* nodeWithItem = findNode(rootPtr, anEntry, success);
		return nodeWithItem->getItem();
	}
}

//------------------------------------------------------------
// Public Traversals Section.
//------------------------------------------------------------

template<class ItemType>
void LinkedTree<ItemType>::preorderTraverse(void visit(ItemType&)) const {
	preorder(visit, rootPtr);
}

template<class ItemType>
void LinkedTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
	inorder(visit, rootPtr);
}

template<class ItemType>
void LinkedTree<ItemType>::postorderTraverse(void visit(ItemType&)) const {
	postorder(visit, rootPtr);
}

//------------------------------------------------------------
// Additional Methods Section.
//------------------------------------------------------------

template<class ItemType>
void LinkedTree<ItemType>::reverse() {
	// reverse the tree
	reverseHelper(rootPtr);
}

template <class ItemType>
ItemType LinkedTree<ItemType>::getMaxValue() const {
	return getMaxValueHelper(rootPtr);
}

template <class ItemType>
ItemType LinkedTree<ItemType>::getMinValue() const {
	return getMinValueHelper(rootPtr);
}

template <class ItemType>
bool LinkedTree<ItemType>::isBST() const {
	return isBSTHelper(rootPtr);
}

template <class ItemType>
void LinkedTree<ItemType>::printRootToLeafs() const {
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
bool LinkedTree<ItemType>::doesSomePathHaveSum(int sum) const
{
	return doesSomePathHaveSumHelper(rootPtr, 0, sum);
}



#endif
