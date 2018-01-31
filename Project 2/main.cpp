#include<iostream>
#include<string>
#include<vector>
#include"CompleteBinTree.h";
#include"CompleteBinTreeParentList.h";
#include"CompleteChainBinTree.h"
#include"CompleteLinkBinTree.h"
#include"Participant.h"
using namespace std;
/**
*
* author realization Silvia Ivanova
* author tasks 5, 6, 7, 8 Silvia Yonkova
* author tests Emil Simeonov
*
*/
void testFunctionsForCompleteBinTree()
{
	cout << "\nTESTING FUNCTIONS: \n";
	cout << "1. Get participants from file\n";
	cout << "Print vector with participants: ";
	vector<Participant> leaves;
	leaves = getParticipantsFromFile();
	for (int i = 0; i < leaves.size(); i++)
		cout << leaves[i] << " ";

	cout << "\n\n2. Passing vector to the function fillTree\n";
	CompleteBinTree<Participant> tree;
	filltree(leaves, tree);

	cout << "\n\n3. Call method tournament() for tree";
	tree.tournament();

	cout << "\n\n4.    Winner: " << tree.getRoot() << endl;
	cout << "Fights: " << tree<<endl;

	int countParticipants = leaves.size();
	cout << "Print all battles:" << endl;
	tree.printBattles(countParticipants);
	
	cout << "\n\n5. Enter name: ";
	string name;
	getline(cin, name);
	tree.findPath(name);
}

void testCompleteBinTree()
{
	cout << "Testing CompleteBinTree" << endl;
	cout << "Create tree of ints" << endl;
	CompleteBinTree<int> tree;
	cout << "Is the tree empty?: ";
	(tree.empty() ? cout << "Yes\n" : cout << "No\n");
	cout << "Print root of the tree: ";
	cout << tree.getRoot() << endl;
	cout << "Print tree: ";
	cout << tree << endl;
	cout << "Print Left subtree: " << tree.leftTree() << endl;
	cout << "Print right subtree: " << tree.leftTree() << endl;

	cout << "\nCreate tree2 of ints with custom constructor with root (0) " << endl;
	CompleteBinTree<int> tree1(0);
	cout << "Is the tree empty?: ";
	(tree1.empty() ? cout << "Yes\n" : cout << "No\n");
	cout << "Print root of the tree: " << tree1.getRoot() << endl;
	cout << "Print tree: " << tree1 << endl;

	cout << "\nAdd leaves (0), (1) and (2) to the tree " << endl;
	CompleteBinTree<int> tree2;
	vector<CompleteBinTree<int>> vec;
	tree2.addChild(0, vec);
	tree2.addChild(1, vec);
	tree2.addChild(2, vec);
	cout << "Is the tree empty?: ";
	(tree2.empty() ? cout << "Yes\n" : cout << "No\n");
	cout << "Print root of the tree: " << tree2.getRoot() << endl;
	cout << "Print tree: " << tree2 << endl;
	cout << "Print Left subtree: " << tree2.leftTree() << endl;
	cout << "Print right subtree: " << tree2.rightTree() << endl;

	cout << "\nTest copy constructor\n";
	cout << "CompleteBinTree<int> tree3 = tree2. Print tree3: ";
	CompleteBinTree<int> tree3 = tree2;
	cout << tree3 << endl;

	cout << "\nTest operator= \n";
	cout << "tree4 = tree2. Print tree4: ";
	CompleteBinTree<int> tree4;
	tree4 = tree2;
	cout << tree4 << endl;

	cout << "\nAdd 10 more leaves to tree4\n";
	for (int i = 3; i < 14; i++)
		tree4.addChild(i, vec);
	cout << "Print tree4: ";
	cout << tree4 << endl;
	cout << "Print Left subtree: " << tree4.leftTree() << endl;
	cout << "Print right subtree: " << tree4.rightTree() << endl;

	cout << "\n tree5 = right subtree of tree4 \n";
	cout << "Print tree5: ";
	CompleteBinTree<int> tree5 = tree4.rightTree();
	cout << tree5 << endl;
	cout << "Is the tree5 empty?: ";
	(tree2.empty() ? cout << "Yes\n" : cout << "No\n");
	cout << "Print root of the tree5: " << tree5.getRoot() << endl;
	cout << "Print Left subtree: " << tree5.leftTree() << endl;
	cout << "Print right subtree: " << tree5.rightTree() << endl;

	/*************** Test functions *******************/
	testFunctionsForCompleteBinTree();

	cout << endl << "The end of Testing CompleteBinTree.h" << endl << endl;
}

/**
*
*author realization Tsvetomir Lyubenov
*author tasks 5, 6, 7, 8  Silvia Ivanova
*author tests Silvia Yonkova
*
*/
void testFunctionsForCompleteBinTreeParentList()
{
	cout << "1. Calling getParticipants (the function from task 6) "
		<< "and storing the result in the vector participants." << endl;
	ifstream in("Participants.txt");
	vector<Participant> participants = getParticipants(in);
	in.close();

	cout << "2. Creating a tree and passing the vector to the filltree function." << endl;
	CompleteBinTreeParentList<Participant> battleTr;
	filltree(participants, battleTr);

	cout << "3. Calling the method tournament() for the tree which has "
		<< "the participants from the vector as leaves." << endl;
	battleTr.tournament();

	cout << "4. Printing all battles by rounds and the name of the winner:" << endl;
	battleTr.displayBattles();

	cout << "5. Calling the findpath function for name of a participant given by the user:" << endl;
	string name;
	cout << "Name: ";
	getline(cin, name);
	battleTr.findpath(name);
}

void testCompleteBinTreeParentList()
{
	cout << "Testing CompleteBinTreeParentList.h with trees of ints:" << endl << endl;

	cout << "(1) Testing default ctor on tree_1:" << endl;
	CompleteBinTreeParentList<int> tree_1;
	cout << "empty?: " << (tree_1.empty() ? "Empty!" : "Not empty!") << endl;
	cout << "getRootValue: " << tree_1.getRootValue() << endl;
	cout << endl;

	///////////////////

	cout << "(2) Testing custom ctor on tree_2:" << endl;
	cout << "Creating values array with contents {5, 20, 16, 7, 10}." << endl;
	int vals[5] = { 5, 20, 16, 7, 10 };
	cout << "Creating parents array with contents {-1, 0, 0, 1, 1}." << endl;
	int prs[5] = { -1, 0, 0, 1, 1 };
	cout << "Then passing those arrays as parameters." << endl;
	CompleteBinTreeParentList<int> tree_2(5, vals, prs);
	cout << "empty?: " << (tree_2.empty() ? "Empty!" : "Not empty!") << endl;
	cout << "getRootValue: " << tree_2.getRootValue() << endl;
	cout << "print: "; tree_2.print();
	cout << endl;

	///////////////////

	cout << "(3) Testing copy ctor by declaring tree_3 and initializing it from tree_2:" << endl;
	CompleteBinTreeParentList<int> tree_3 = tree_2;
	cout << "print tree_2: "; tree_2.print();
	cout << "print tree_3: "; tree_3.print();
	cout << endl;

	///////////////////

	cout << "(4) Testing operator= by creating tree_4 and then assigning tree_4 = tree_3:" << endl;
	CompleteBinTreeParentList<int> tree_4;
	tree_4 = tree_3;
	cout << "print tree_3: "; tree_3.print();
	cout << "print tree_4: "; tree_4.print();
	cout << endl;

	///////////////////

	cout << "(5) Testing createEmptyTree with the size of 7 on tree_4:" << endl;
	tree_4.createEmptyTree(7);
	cout << "getSize: " << tree_4.getSize() << endl;
	cout << "print tree_4: "; tree_4.print();
	cout << endl;

	///////////////////

	cout << "(6) Testing addLeaf by adding three leaves 91, 54, 2 to tree_4:" << endl;
	cout << "(addLeaf requires previously allocated memory and adds the elements in the lowest level)" << endl;
	tree_4.addLeaf(91);
	tree_4.addLeaf(54);
	tree_4.addLeaf(2);
	cout << "getSize: " << tree_4.getSize() << endl;
	cout << "print tree_4: "; tree_4.print();
	cout << endl;

	///////////////////

	cout << "(7) Testing create by creating tree_5:" << endl;
	CompleteBinTreeParentList<int> tree_5;
	tree_5.create();
	cin.ignore();
	cout << "empty?: " << (tree_5.empty() ? "Empty!" : "Not empty!") << endl;
	cout << "getRootValue: " << tree_5.getRootValue() << endl;
	cout << "print tree_5: "; tree_5.print();
	cout << endl;


	/////////////////// Testing functions ///////////////////
	cout << "Testing functions for tasks 5, 6, 7, 8:" << endl;
	testFunctionsForCompleteBinTreeParentList();

	cout << endl << "The end of Testing CompleteBinTreeParentList.h" << endl;
}
/**
*
* author realization Silvia Yonkova
* author tasks 5, 6, 7, 8  Emil Simeonov
* author tests Tsvetomir Lyubenov
*
*/
void testFunctionsForCompleteChainBinTree()
{
	cout << "Calling the function from task 6 and storing the result in a vector." << endl;
	vector<Participant> players = choosePatricipantsFromFile();

	cout << "Creating a tree which leaves hold the participants from the vector." << endl;
	CompleteChainBinTree<Participant> tr;
	filltree(players, tr);

	cout << "Calling the method tournament() for the tree." << endl;
	tr.tournament();

	cout << "Displaying all battles:" << endl;
	tr.printAllBattles();

	cout << "Displaying all the battles that a player with a given name has taken part in." << endl;
	if (!tr.empty())
	{
		string name;
		cout << "Name: " << endl;
		getline(cin, name);

		Participant p;
		p.setName(name);
		cout << "battles in which " << name << " participated:" << endl;
		tr.findPath(name);
	}
	cout << "winner: " << tr.getRootValue() << endl;
}

void testCompleteChainBinTree()
{
	cout << "Testing CompleteChainBinTree.h" << endl << endl;

	cout << "1) Testing methods of an empty tree:" << endl;
	CompleteChainBinTree<int> tree;

	cout << "empty: " << (tree.empty() ? "Yes" : "No") << endl;
	cout << "root: " << tree.getRootValue() << endl;

	cout << "print: ";
	tree.print();
	cout << endl;

	//------------------------------------------------------------------------------

	cout << endl << "2) Testing methods of a non-empty tree:" << endl << endl;

	cout << "A) Testing methods when the tree consists only of a root:" << endl;
	cout << " Add 1 leaf:" << endl;
	CompleteChainBinTree<int> tree_root;
	tree_root.addLeaf(1);

	cout << " empty: " << (tree_root.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree_root.getRootValue() << endl;
	cout << " print: ";
	tree_root.print();
	cout << endl;

	//------------------------------------------------------------------------------

	cout << endl << "B) Testing methods when the tree has more than 1 element:" << endl;
	cout << " Add 3 leaves:" << endl;
	for (int i = 0; i < 3; i++)
		tree.addLeaf(i);

	cout << " empty: " << (tree.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree.getRootValue() << endl;
	cout << " print: ";
	tree.print();
	cout << endl;

	//------------------------------------------------------------------------------

	cout << "3) Testing copy constructor, operator == and create:" << endl << endl;

	cout << "A) testing copy constructor:" << endl;
	CompleteChainBinTree<int> tree1 = tree;
	cout << " empty: " << (tree1.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree1.getRootValue() << endl;
	cout << " print: ";
	tree1.print();
	cout << endl;

	cout << "B) testing create:" << endl;
	CompleteChainBinTree<int> tree2;
	tree2.create();
	cin.ignore();
	cout << " empty: " << (tree2.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree2.getRootValue() << endl;
	cout << " print: ";
	tree2.print();
	cout << endl;

	cout << "C) testing operator =:" << endl;
	CompleteChainBinTree<int> tree3;
	tree3 = tree2;

	cout << " empty: " << (tree3.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree3.getRootValue() << endl;
	cout << " print: ";
	tree3.print();
	cout << endl;

	//--------------------------------------------------------------------------

	cout << endl << "4) Testing functions:" << endl;

	cout << "FIRST TIME:" << endl;
	testFunctionsForCompleteChainBinTree();

	cout << endl << "SECOND TIME:" << endl;
	testFunctionsForCompleteChainBinTree();

	cout << endl << "THIRD TIME:" << endl;
	testFunctionsForCompleteChainBinTree();

	cout << endl << "The end of Testing CompleteChainBinTree.h" << endl << endl;
}
/**
*
* author realization Emil Siomeonov
* author tasks 5, 6, 7, 8  Tsvetomir Lyubenov
* author tests Silvia Ivanova
*
*/
void testFunctionsForCompleteLinkBinTree()
{
	CompleteLinkBinTree<Participant> tree4;
	vector<Participant> arr = getParticipants();
	filltree(arr, tree4);
	tree4.tournament();

	if (!tree4.empty())
	{
		Participant p = arr[0];
		string n = p.getName();
		cout << "Fights in which " << n << " participated:" << endl;
		tree4.findpath(n);
	}
	cout << "Print TREE:" << endl;
	tree4.print();

	cout <<endl<< "winner: " << tree4.getRootValue() << endl;

	cout<<endl << "Print all fights in the tournament:" << endl;
	tree4.printBattles();
}
void testCompleteLinkBinTree()
{
	cout << "Testing CompleteLinkBinTree.h" << endl;

	cout << endl << "1) Testing methods when tree is empty:" << endl;
	CompleteLinkBinTree<int> tree;
	cout << "empty: " << (tree.empty() ? "Yes" : "No") << endl;
	cout << "root: " << tree.getRootValue() << endl;
	cout << "count elements: " << tree.getCountElements() << endl << endl;
	cout << "print: ";		tree.print();  cout << endl;

	cout << "Left Tree:";
	CompleteLinkBinTree<int> leftTree = tree.leftTree();
	leftTree.print();
	cout << "Right Tree:";
	CompleteLinkBinTree<int> rightTree = tree.rightTree();
	rightTree.print();

	//------------------------------------------------------------------------------

	cout << endl << "2) Testing methods when tree isn`t empty:" << endl;

	cout << endl << "A) Testing methods when tree has an only root:" << endl;
	cout << " Add leaf (1):" << endl;
	CompleteLinkBinTree<int> tree_root;
	tree_root.addLeaf(1);

	cout << " empty: " << (tree_root.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree_root.getRootValue() << endl;
	cout << " count elements: " << tree_root.getCountElements() << endl;
	cout << " print: ";		tree_root.print();

	cout << endl << " Left Tree: ";
	leftTree = tree_root.leftTree();		leftTree.print();
	cout << " empty: " << (leftTree.empty() ? "Yes" : "No") << endl;
	cout << " root: " << leftTree.getRootValue() << endl;
	cout << " count elements: " << leftTree.getCountElements() << endl;
	cout << " print: ";		leftTree.print();

	cout << endl << " Right Tree: ";
	rightTree = tree.rightTree();		rightTree.print();
	cout << " empty: " << (rightTree.empty() ? "Yes" : "No") << endl;
	cout << " root: " << rightTree.getRootValue() << endl;
	cout << " count elements: " << rightTree.getCountElements() << endl;
	cout << " print: ";		rightTree.print();

	//------------------------------------------------------------------------------

	cout << endl << "B) Testing methods when tree has more elements:" << endl;
	cout << " Add leaves (1), (2), (3):" << endl;
	for (int i = 1; i < 4; i++)
		tree.addLeaf(i);

	cout << " empty: " << (tree.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree.getRootValue() << endl;
	cout << " count elements: " << tree.getCountElements() << endl;
	cout << " print: ";		tree.print();

	cout << endl << " Left Tree: ";
	leftTree = tree.leftTree();		leftTree.print();
	cout << " empty: " << (leftTree.empty() ? "Yes" : "No") << endl;
	cout << " root: " << leftTree.getRootValue() << endl;
	cout << " count elements: " << leftTree.getCountElements() << endl;
	cout << " print: ";		leftTree.print();

	cout << endl << " Right Tree: ";
	rightTree = tree.rightTree();		rightTree.print();
	cout << " empty: " << (rightTree.empty() ? "Yes" : "No") << endl;
	cout << " root: " << rightTree.getRootValue() << endl;
	cout << " count elements: " << rightTree.getCountElements() << endl;
	cout << " print: ";		rightTree.print();

	//------------------------------------------------------------------------------

	cout << endl << "3) Testing copy constructor, operator == and create:" << endl;

	cout << endl << "A) testing copy constructor:" << endl;
	CompleteLinkBinTree<int> tree1 = tree;
	cout << " empty: " << (tree1.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree1.getRootValue() << endl;
	cout << " count elements: " << tree1.getCountElements() << endl;
	cout << " print: ";		tree1.print();

	cout << endl << "B) testing create:" << endl;
	CompleteLinkBinTree<int> tree2;
	tree2.create();
	cout << " empty: " << (tree2.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree2.getRootValue() << endl;
	cout << " count elements: " << tree2.getCountElements() << endl;
	cout << " print: ";		tree2.print();

	cout << endl << "C) testing operator =:" << endl;
	CompleteLinkBinTree<int> tree3;
	tree3 = tree2;

	cout << " empty: " << (tree3.empty() ? "Yes" : "No") << endl;
	cout << " root: " << tree3.getRootValue() << endl;
	cout << " count elements: " << tree3.getCountElements() << endl;
	cout << " print: ";		tree3.print();

	cout << endl << " Left Tree:";
	leftTree = tree3.leftTree();		leftTree.print();
	cout << endl << " Right Tree:";
	leftTree = tree3.rightTree();		rightTree.print();

	//--------------------------------------------------------------------------

	cout << endl << "4) Testing functions:" << endl;

	cout << "FIRST TIME:" << endl;
	testFunctionsForCompleteLinkBinTree();

	cout << endl << "SECOND TIME:" << endl;
	testFunctionsForCompleteLinkBinTree();

	cout << endl << "THIRD TIME:" << endl;
	testFunctionsForCompleteLinkBinTree();

	cout << endl << "The end of Testing CompleteLinkBinTree.h" << endl << endl;
}
int main()
{
	
	testCompleteBinTree();
	testCompleteLinkBinTree();
	testCompleteBinTreeParentList();
	testCompleteChainBinTree();

	system("pause");
	return 0;
}