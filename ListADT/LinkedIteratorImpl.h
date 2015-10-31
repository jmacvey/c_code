#ifndef _LINKED_ITERATOR_IMPL_H
#define _LINKED_ITERATOR_IMPL_H

template <class ItemType>
LinkedIterator<ItemType>::LinkedIterator(const LinkedList<ItemType>* someList,
	Node<ItemType>* nodePtr) : containerPtr(someList), currentItemPtr(nodePtr)
{
}

template <class ItemType>
const ItemType LinkedIterator<ItemType>::operator*()
{
	return currentItemPtr->getItem();
}

template <class ItemType>
LinkedIterator<ItemType> LinkedIterator<ItemType>::operator++() {
	currentItemPtr = currentItemPtr->getNext();
	return *this;
}

template <class ItemType>
bool LinkedIterator<ItemType>::operator==(const LinkedIterator<ItemType>& rhs) const {
	return ((containerPtr == rhs.containerPtr) &&
		(currentItemPtr == rhs.currentItemPtr));
}

template <class ItemType>
bool LinkedIterator<ItemType>::operator!=(const LinkedIterator<ItemType>& rhs) const {
	return ((containerPtr != rhs.containerPtr) ||
		(currentItemPtr != rhs.currentItemPtr));
}

#endif
