// DRIVER FILE FOR BINARY TREE


#include "LinkedTree.h"
#include <string>
#include "eslib.h"
#include <iostream> // std::cout
#include "BinarySearchTree.h"
#include <fstream> // std::ifstream
#include <streambuf>

struct cout_guard {
	explicit cout_guard(std::streambuf* original_buf) : buf_(original_buf) { }; // constructor

	~cout_guard() {
		std::cout.rdbuf(buf_);
	} // destructor
private:
	std::streambuf* buf_;
};


typedef void (*visitFunc)(std::string&);

void visit(std::string& myString)
{
	std::cout << myString << ",";
};

visitFunc display = &visit;

void writeToFile(std::string& myString)
{
	std::cout << "writing " << "\"" << myString << "\"" << " to file." << std::endl;
	std::ofstream standard_output;
	standard_output.open("./myFile.txt", std::ios::app);
	if (!standard_output)
		exit(-1);
	else
	{
		// puts the std::out into the guard
		cout_guard guard(std::cout.rdbuf());
		std::cout.rdbuf(standard_output.rdbuf()); // redirect cout to buffer in standard_out
		visit(myString);
		standard_output.close();
	}
}

visitFunc writeToTheFile = &writeToFile;

void LinkedTreeTester() {
	using std::cout; using std::cin; using std::endl;
	cout << "Beginning Binary Tree Tests..." << endl;
	LinkedTree<std::string> myLinkedTreeNode;
	// test addition
	cout << "isEmpty() returns: " << myLinkedTreeNode.isEmpty() << "; should be 1 (true)." << endl;
	cout << "Adding item to tree..." << endl;
	std::string myString = "A"; myLinkedTreeNode.add(myString);
	cout << "isEmpty() returns: " << myLinkedTreeNode.isEmpty() << "; should be 0 (false)." << endl;
	cout << "getHeight() returns: " << myLinkedTreeNode.getHeight() << "; should be 1." << endl;
	cout << "Adding three more items to the tree..." << endl;
	std::string myNextString[] = { "B", "C", "D", "E" };
	for (int i = 0; i < 4; i++)
	{
		myLinkedTreeNode.add(myNextString[i]);
	}
	cout << "inOrder Traversal of tree yields: "; myLinkedTreeNode.inorderTraverse(display);
	cout << "; should be D, B, A, E, C" << endl;
	cout << "preOrder Traversal of tree yields: "; myLinkedTreeNode.preorderTraverse(display);
	cout << "; should be A, B, D, C, E" << endl;
	cout << "postOrder Traversal of tree yields: "; myLinkedTreeNode.postorderTraverse(display);
	cout << "; should be D, B, E, C, A" << endl;
	// testing reversal method
	cout << "Reversing the tree..." << endl; myLinkedTreeNode.reverse();
	cout << "preOrder Traversal of tree yields: "; myLinkedTreeNode.preorderTraverse(display);
	cout << "; should be A, C, E, B, D" << endl;
	// testing max and min items method
	cout << "getMaxValue() returns: " << myLinkedTreeNode.getMaxValue() << "; should be \"E\"" << endl;
	cout << "getMinValue() returns: " << myLinkedTreeNode.getMinValue() << "; should be \"A\"" << endl;
	// checking if the tree is a bst
	cout << "isBST() returns: " << myLinkedTreeNode.isBST() << "; should be 0 (false)." << endl;
	// testing removals incorporating height and root data tests
	cout << "getHeight() returns: " << myLinkedTreeNode.getHeight() << "; should be 3." << endl;
	cout << "Removing item \"C\" from the tree." << endl; myLinkedTreeNode.remove("C");
	cout << "inOrder Traversal of tree yields: "; myLinkedTreeNode.inorderTraverse(display);
	cout << "; should be E, A, D, B" << endl;
	cout << "getHeight() returns: " << myLinkedTreeNode.getHeight() << "; should be 3." << endl;
	cout << "Removing item \"A\" from the tree." << endl; myLinkedTreeNode.remove("A");
	cout << "getMinValue() returns: " << myLinkedTreeNode.getMinValue() << "; should be \"B\"" << endl;
	cout << "inOrder Traversal of tree yields: "; myLinkedTreeNode.inorderTraverse(display);
	cout << "; should be E, B, D" << endl;
	cout << "root data points to a node containing item " << myLinkedTreeNode.getRootData() 
		<< "; should be \"E\"" << endl;
	cout << "getHeight() returns: " << myLinkedTreeNode.getHeight() << "; should be 3." << endl;
	cout << "Removing item \"B\" from the tree." << endl; myLinkedTreeNode.remove("B");
	cout << "getHeight() returns: " << myLinkedTreeNode.getHeight() << "; should be 2." << endl;
	cout << "root data points to a node containing item " << myLinkedTreeNode.getRootData()
		<< "; should be \"D\"" << endl;
	cout << "Removing item \"D\" from the tree." << endl; myLinkedTreeNode.remove("D");
	cout << "Removing item \"E\" from the tree." << endl; myLinkedTreeNode.remove("E");
	cout << "getHeight() returns: " << myLinkedTreeNode.getHeight() << "; should be 0." << endl;
	// secondary isBST test
	cout << "Creating new tree that is a binary search tree..." << endl;
	LinkedTree<std::string> secondTree;
	std::string myThirdString[] = { "H", "B", "K", "A", "C" };
	for (int i = 0; i < 5; i++)
	{
		secondTree.add(myThirdString[i]);
	}
	secondTree.add("D");
	secondTree.add("L");
	cout << "number of nodes in tree: " << secondTree.getNumberOfNodes() << endl;
	cout << "preOrder Traversal of tree yields: "; secondTree.preorderTraverse(display);
	cout << "; should be H, B, A, D, K, C, L" << endl;
	cout << "Writing tree contents to file..." << endl;
	secondTree.preorderTraverse(writeToTheFile);
	// isBST test
	cout << "isBST() returns: " << secondTree.isBST() << "; should be 1 (true)" << endl;
	// root to leaves tests
	cout << "Prnting paths from roots to leaves: " << endl; secondTree.printRootToLeafs();
	cout << endl << "should be: " << endl <<  " H B A \n H B D \n H K C \n H K L" << endl;
	// create integer tree for final tests
	cout << "Creating a new integer tree..." << endl;
	LinkedTree<int> thirdTree;
	int i[] = { 50, 80, 40, 30, 10, 70, 20, 60 };
	for (int j = 0; j < 8; j++)
	{
		thirdTree.add(i[j]);
	}
	//testing doesSomePathHaveSum
	cout << "doesSomePathHaveSum(100) yields: " << thirdTree.doesSomePathHaveSum(100) 
		<< "; should be 1 (true)" << endl;
	cout << "doesSomePathHaveSum(120) yeilds: "
		<< thirdTree.doesSomePathHaveSum(120) << "; should be 0 (false)" << endl << endl;
}

void BSTtester() {
	using std::string; using std::cout; using std::endl;
	BinarySearchTree<string> myBST;
	cout << "Beginning BinarySearchTree Tests..." << endl;
	cout << "isEmpty() returns: " << myBST.isEmpty() << "; should be 1 (true)." << endl;
	cout << "Adding item to tree..." << endl;
	std::string myString = "A"; myBST.add(myString);
	cout << "isEmpty() returns: " << myBST.isEmpty() << "; should be 0 (false)." << endl;
	cout << "getHeight() returns: " << myBST.getHeight() << "; should be 1." << endl;
	cout << "Adding three more items to the tree..." << endl;
	std::string myNextString[] = { "B", "C", "D", "E" };
	for (int i = 0; i < 4; i++)
	{
		myBST.add(myNextString[i]);
	}
	cout << "inOrder Traversal of tree yields: "; myBST.inorderTraverse(display);
	cout << "; should be A, B, C, D, E" << endl;
	cout << "preOrder Traversal of tree yields: "; myBST.preorderTraverse(display);
	cout << "; should be A, B, C, D, E" << endl;
	cout << "postOrder Traversal of tree yields: "; myBST.postorderTraverse(display);
	cout << "; should be E, D, C, B, A" << endl;
	cout << "getMaxValue() returns: " << myBST.getMaxValue() << "; should be \"E\"" << endl;
	cout << "getMinValue() returns: " << myBST.getMinValue() << "; should be \"A\"" << endl;
	// checking if the tree is a bst
	cout << "isBST() returns: " << myBST.isBST() << "; should be 1 (true)." << endl;
	cout << "Removing item \"C\" from the tree." << endl; myBST.remove("C");
	cout << "inOrder Traversal of tree yields: "; myBST.inorderTraverse(display);
	cout << "; should be A, B, D, E" << endl;
	cout << "isBST() returns: " << myBST.isBST() << "; should be 1 (true)." << endl;
	BinarySearchTree<string> myBST2;

}

int main() {
	LinkedTreeTester();
	BSTtester();
	exitScript();
	return 0;
}

