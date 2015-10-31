/* AXIOMS FOR THE LIST ADT */
/** 
1. (new List()).isEmpty() = true
2. (new List()).getLength() = 0
3. aList.getLength() = (aList.insert(i, x)).getLength() - 1
4. aList.getLength() = (aList.remove(i)).getLength() + 1
5. (aList.insert(i, item)).isEmpty() = false
6. (new List()).remove(i) = false
7. (aList.insert(i, x)).remove(i) = aList
8. (new List()).getEntry(i) = error
9. (aList.insert(i, x)).getEntry(i) = x
10. aList.getEntry(i) = (aList.insert(i, x)).getEntry(i + 1)
11. aList.getEntry(i + 1) = (aList.remove(i)).getEntry(i)
12. (new List()).setEntry(i, x) = error
13. (aList.setEntry(i, x)).getEntry(i) = x
*/