#ifndef _LINKED_TREE_NODE_H
#define _LINKED_TREE_NODE_H

// link-based version of tree node
template<class ItemType>
class LinkedTreeNode
{
private:
	ItemType dataMember;
	LinkedTreeNode<ItemType>* lChildPtr;
	LinkedTreeNode<ItemType>* rChildPtr;
	
public:
	LinkedTreeNode(); // default constructor - no implementation
	LinkedTreeNode(const ItemType& dMember);
	LinkedTreeNode(const ItemType& dMember, LinkedTreeNode<ItemType>* lChild, LinkedTreeNode<ItemType>* rChild);
	~LinkedTreeNode();
	void setItem(const ItemType& newItem);
	ItemType getItem() const;
	void setLChildPtr(LinkedTreeNode<ItemType>* newLChildPtr);
	void setRChildPtr(LinkedTreeNode<ItemType>* newRChildPtr);
	LinkedTreeNode<ItemType>* getLChild() const;
	LinkedTreeNode<ItemType>* getRChild() const;
	bool isLeaf() const;
}; // end treeNode

template<class ItemType>
inline LinkedTreeNode<ItemType>::LinkedTreeNode() : lChildPtr(nullptr), rChildPtr(nullptr){}

template<class ItemType>
inline LinkedTreeNode<ItemType>::LinkedTreeNode(const ItemType& dMember) :
dataMember(dMember), lChildPtr(nullptr), rChildPtr(nullptr){}

template<class ItemType>
inline LinkedTreeNode<ItemType>::LinkedTreeNode(const ItemType& dMember, LinkedTreeNode<ItemType>* lChild,
	LinkedTreeNode<ItemType>* rChild) : dataMember(dMember), lChildPtr(lChild), rChildPtr(rChild){}

template<class ItemType>
inline void LinkedTreeNode<ItemType>::setItem(const ItemType& newItem) {
	dataMember = newItem;
}

template<class ItemType>
inline LinkedTreeNode<ItemType>::~LinkedTreeNode() {
}

template<class ItemType>
inline ItemType LinkedTreeNode<ItemType>::getItem() const {
	return dataMember;
}

template <class ItemType>
inline void LinkedTreeNode<ItemType>::setLChildPtr(LinkedTreeNode<ItemType>* newLChildPtr) {
	lChildPtr = newLChildPtr;
}

template<class ItemType>
inline void LinkedTreeNode<ItemType>::setRChildPtr(LinkedTreeNode<ItemType>* newRChildPtr) {
	rChildPtr = newRChildPtr;
}

template<class ItemType>
inline LinkedTreeNode<ItemType>* LinkedTreeNode<ItemType>::getLChild() const {
	return lChildPtr;
}

template<class ItemType>
inline LinkedTreeNode<ItemType>* LinkedTreeNode<ItemType>::getRChild() const {
	return rChildPtr;
}

template <class ItemType>
inline bool LinkedTreeNode<ItemType>::isLeaf() const {
	return (lChildPtr == nullptr && rChildPtr == nullptr);
}
// end class declaration and inline definitions

#endif