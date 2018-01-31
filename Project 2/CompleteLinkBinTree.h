#ifndef COMPLETE_LINK_BIN_TREE_H
#define COMPLETE_LINK_BIN_TREE_H
#include "Participant.h"
#include <string>
#include "LList.h"
template<typename T>
struct TreeNode
{
	T value;
	TreeNode<T> *right;
	TreeNode<T> *left;
};
template<typename T>
class CompleteLinkBinTree
{
private:
	TreeNode<T> *root;
	unsigned size;
	void deleteTree(TreeNode<T> *&);
	void copyComplBinTree(const CompleteLinkBinTree<T> &); //Copy whole tree
	void coppy(TreeNode<T> *&, TreeNode<T> *) const;
	void prPrint(TreeNode<T> *&);
	bool leftFull(TreeNode<T>*&);
	void prAddLeaf(TreeNode<T> *&, T const &);
	void getSize(TreeNode<T> *&, unsigned&);
	void height(TreeNode<T>*, int&);
public:
	//BIG 4
	CompleteLinkBinTree();
	~CompleteLinkBinTree();
	CompleteLinkBinTree(CompleteLinkBinTree<T> const &);
	CompleteLinkBinTree& operator=(CompleteLinkBinTree<T> const &);
	T getRootValue() const;
	bool empty() const;
	void create();
	void print();
	unsigned int getCountElements() const;
	void addLeaf(T val);
	CompleteLinkBinTree<T> leftTree();
	CompleteLinkBinTree<T> rightTree();

	//tasks
	void createEmptyTree(int);
	//task 7
	void tournament();
	//task 8
	void findpath(string name);
private:
	void StartFights(TreeNode<T>*);
	Participant BlackOrWhite(Participant, Participant);
	void printFights(TreeNode<T>*, const string&, bool&);
	LList<T> level(int) const;
	void prPrintBattles(TreeNode<T>*);
public:
	void printBattles();
	LList<T> level(int, TreeNode<T>*) const;
	TreeNode<T>* getRoot()
	{
		return root;
	}
};
/*****BIG 4*****************************/
template<typename T>
CompleteLinkBinTree<T>::CompleteLinkBinTree()
{
	root = NULL;
	size = 0;
}

template<typename T>
CompleteLinkBinTree<T>::~CompleteLinkBinTree()
{
	deleteTree(root);
}

template<typename T>
CompleteLinkBinTree<T>::CompleteLinkBinTree(CompleteLinkBinTree<T> const &other)
{
	copyComplBinTree(other);
}

template<typename T>
CompleteLinkBinTree<T>& CompleteLinkBinTree<T>::operator=(CompleteLinkBinTree<T> const &other)
{
	if (this != &other)
	{
		deleteTree(root);
		copyComplBinTree(other);
	}
	return *this;
}

/****** Return the value of the root ******/
template<typename T>
T CompleteLinkBinTree<T>::getRootValue() const
{
	if (this->empty())
	{
		cerr << "ERROR! No Root! ";
		return T();
	}
	else
		return root->value;
}

/****** Is the tree empty? ******/
template<typename T>
bool CompleteLinkBinTree<T>::empty() const
{
	return root == NULL;
}

/****** Height ******/
template<typename T>
void CompleteLinkBinTree<T>::height(TreeNode<T>* newRoot, int& i)
{
	if (newRoot->left != NULL)
	{
		height(newRoot->left, i);
		i++;
	}
}

/****** Delete tree ******/
template<typename T>
void CompleteLinkBinTree<T>::deleteTree(TreeNode<T> *& newRoot)
{
	if (newRoot != NULL)
	{
		deleteTree(newRoot->left);
		deleteTree(newRoot->right);
		delete newRoot;
		newRoot = NULL;
	}
}

/****** Copy whole tree ******/
template<typename T>
void CompleteLinkBinTree<T>::copyComplBinTree(const CompleteLinkBinTree<T> &other)
{
	coppy(root, other.root);
	size = other.size;
}

/****** Copy tree to the root of the other tree ******/
template<typename T>
void CompleteLinkBinTree<T>::coppy(TreeNode<T> *&newRoot, TreeNode<T> *otherNewRoot) const
{
	if (otherNewRoot != NULL)
	{
		newRoot = new TreeNode<T>;
		newRoot->value = otherNewRoot->value;
		coppy(newRoot->left, otherNewRoot->left);
		coppy(newRoot->right, otherNewRoot->right);
	}
	else
		newRoot = NULL;
}

/****** Print tree ******/
template<typename T>
void CompleteLinkBinTree<T>::print()
{
	if (!root)
	{
		cerr << "Tree is empty!" << endl;
		return;
	}
	prPrint(root);
	cout << endl;
}

/****** Private print tree ******/
template<typename T>
void CompleteLinkBinTree<T>::prPrint(TreeNode<T> *&newRoot)
{
	if (newRoot != NULL)
	{
		cout << newRoot->value;
		if (newRoot->left != NULL)
		{
			cout << " ( ";
			prPrint(newRoot->left);
			if (newRoot->right != NULL)
				prPrint(newRoot->right);
			cout << ") ";
		}
		else
			cout << " ";
	}
}

/****** Return the number of leaves ******/
template<typename T>
unsigned int CompleteLinkBinTree<T>::getCountElements() const
{
	return size;
}

// When doing an insertion, 
// we go left if this condition is true:
// -the left subtree is not full 
// else, we go right
template<typename T>
void CompleteLinkBinTree<T>::prAddLeaf(TreeNode<T> *& newRoot, T const & val)
{
	//If there are no leafes, we create the first one
	if (newRoot == NULL)
	{
		newRoot = new TreeNode<T>;
		newRoot->value = val;
		newRoot->left = NULL;
		newRoot->right = NULL;
		size++;
		return;
	}
	if (newRoot->left == NULL)
	{
		newRoot->left = new TreeNode<T>;
		newRoot->left->value = val;
		newRoot->left->left = NULL;
		newRoot->left->right = NULL;
		size++;
	}
	else if (newRoot->right == NULL)
	{
		newRoot->right = new TreeNode<T>;
		newRoot->right->value = val;
		newRoot->right->left = NULL;
		newRoot->right->right = NULL;
		size++;
	}
	else if (leftFull(newRoot))
		prAddLeaf(newRoot->right, val);
	else
		prAddLeaf(newRoot->left, val);
}

/*This method uses the number of nodes in the
left subtree in order to check if it is full.*/
template<typename T>
bool CompleteLinkBinTree<T>::leftFull(TreeNode<T>*& newRoot)
{
	unsigned Size = 0;
	getSize(newRoot, Size);
	int used, leafs = 1;
	while (leafs <= Size + 1)
	{
		leafs *= 2;
	}
	leafs /= 2;
	used = (Size + 1) % leafs;
	if (used >= (leafs / 2))
		return true;
	else
		return false;
}

/****** Return the size of tree to the root ******/
template<typename T>
void CompleteLinkBinTree<T>::getSize(TreeNode<T> *& newRoot, unsigned& Size)
{
	if (newRoot == NULL)
		return;
	if (newRoot->left != NULL)
		getSize(newRoot->left, Size);
	if (newRoot->right != NULL)
		getSize(newRoot->right, Size);
	Size++;
}

/****** public add leaf ******/
template<typename T>
void CompleteLinkBinTree<T>::addLeaf(T val)
{
	prAddLeaf(root, val);
}

/****** Create new tree ******/
template<typename T>
void CompleteLinkBinTree<T>::create()
{
	T value;
	char s;
	do
	{
		cout << "Value: ";
		cin >> value;
		addLeaf(value);
		cout << "Next element - y/n? ";
		cin >> s;
	} while (s == 'Y' || s == 'y');
}

/****** Return the left subtree ******/
template<typename T>
CompleteLinkBinTree<T> CompleteLinkBinTree<T>::leftTree()
{
	CompleteLinkBinTree<T> tr;
	tr.root = NULL;	tr.size = 0;
	if (this->empty())		// If the tree is empty, return empty tree
		return tr;
	coppy(tr.root, root->left);
	getSize(root->left, tr.size);
	return tr;
}

/****** Return the right subtree ******/
template<typename T>
CompleteLinkBinTree<T> CompleteLinkBinTree<T>::rightTree()
{
	CompleteLinkBinTree<T> tr;
	tr.root = NULL;	tr.size = 0;
	if (this->empty())		// If the tree is empty, return empty tree
		return tr;
	coppy(tr.root, root->right);
	getSize(root->right, tr.size);
	return tr;
}

/***************************** TASKS 5, 6, 7, 8 *****************************/

// Tournament method
template<typename T>
void CompleteLinkBinTree<T>::tournament()
{
	if (this->empty())		// If the tree is empty print error
	{
		cerr << "ERROR! The tree is empty!" << endl;
		return;
	}
	if (size > 1)
		StartFights(root);

}

//Recursive method which conducts fights
template<typename T>
void CompleteLinkBinTree<T>::StartFights(TreeNode<T>* node)
{
	if (node->left->value.getPower() == -1)
		StartFights(node->left);
	if (node->right->value.getPower() == -1)
		StartFights(node->right);
	node->value = BlackOrWhite(node->left->value, node->right->value);
}

// Determine participant who wins
template<typename T>
Participant CompleteLinkBinTree<T>::BlackOrWhite(Participant p1, Participant p2)
{
	int power1 = p1.getPower();
	int power2 = p2.getPower();

	int sum = power1 + power2;   // The number of balls to choose from.

	unsigned int seed = time(0);
	srand(seed);

	int ball = rand() % sum + 1;  // A random chosen ball.

	if (ball <= power1)  // Decide who the winner is.
		return p1;
	else
		return p2;
}

//Create tree with empty nodes for the fifth task
template<typename T>
void CompleteLinkBinTree<T>::createEmptyTree(int n)
{
	if (n < 0)
	{
		cerr << "ERROR!" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		this->addLeaf(T());
	}
}

//Find path method
template<typename T>
void CompleteLinkBinTree<T>::findpath(string name)  // Displays all the battles a participant has taken part in.
{
	if (size < 1)
	{
		cerr << "There are no fights!" << endl;
		return;
	}
	bool hasFights = 0;   // Has participant taken part in fights?
	printFights(root, name, hasFights);
	if (!hasFights)
		cerr << "Participant with name: " << name << " hasn't taken part in any fight! " << endl;

}

//Recursive method which print fights for "findpath" method
template<typename T>
void CompleteLinkBinTree<T>::printFights(TreeNode<T>* node, const string& name, bool& hasFights)
{
	if (node->left == NULL || node->right == NULL)
		return;
	printFights(node->left, name, hasFights);
	printFights(node->right, name, hasFights);
	if (node->left->value.getName() == name)
	{
		cout << "( " << node->left->value.getName() << " vs " << node->right->value.getName() << " ) " << endl;
		hasFights = 1;
	}
	if (node->right->value.getName() == name)
	{
		cout << "( " << node->left->value.getName() << " vs " << node->right->value.getName() << " ) " << endl;
		hasFights = 1;
	}
}


// Fill tree function
template<typename T>
void filltree(vector<T> leaves, CompleteLinkBinTree<T>& tree)
{

	srand(time(NULL));
	size_t size = leaves.size();

	for (int i = 1, number = 1; size > 1; i++)  // This loop counts how many empty elements
	{											 // must be created 
		if (size <= pow(2, i))
		{
			tree.createEmptyTree(number);
			break;
		}
		number += (pow(2, i));
	}

	unsigned index;
	while (!leaves.empty())					//This loop adds randomly participants in leaves
	{
		index = rand() % size;
		tree.addLeaf(leaves[index]);
		leaves.erase(leaves.begin() + index);
		size--;
	}
}


/*
DISCLAIMER: We took a decision to extract from the file not just a random number of participants (leaves for the tree)
but instead a number – still random – which is any power of two less than the total number of participants present in the file.
The reason behind this is the fact that only when the leaves are 2^x in number we have a properly functioning complete binary
tree for the purposes of single-elimination kind of tournament. Otherwise there always will appear a player who does not have
an opponent, which leads to his trouble-free classification for the next round, until the final match-up -  a case that is not
fair to all the other players (this case is explained in detail in the last messages in our random channel)
*/

//This function 
//gets paricipants from  file participant.txt and return vector with random number of random participants
vector<Participant> getParticipants()
{
	srand(time(NULL));
	ifstream file("participants.txt");			//Open file participants.txt
	vector<Participant> selectedParticipants;	//Vector with random number of random participants
	if (file.is_open())
	{
		Participant player;
		vector<Participant> players;
		while (file >> player) // Read all participants in a vector Players
		{
			players.push_back(player);
		}

		vector<int> powerOf2;
		for (int j = 0; pow(2, j) <= players.size(); j++) //This loop fills the powerOf2 vector
			powerOf2.push_back(pow(2, j));				  //with numbers powers of 2

		int numberOfParticipants = powerOf2[rand() % powerOf2.size()]; // Random number of participants
																	   // power of 2

		int index;
		while (selectedParticipants.size() < numberOfParticipants)	//This loop fills vector selectedParticipants
		{
			index = rand() % players.size(); // Index of random participant
			selectedParticipants.push_back(players[index]);
			players.erase(players.begin() + index);
		}
	}
	else
		cerr << "ERROR! File is not open!" << endl;

	return selectedParticipants;
}

template<typename T>
void CompleteLinkBinTree<T>::printBattles()
{
	if (this->empty())
	{

		cerr << "There is no fights! " << endl;
		return;
	}
	int round = 1;
	LList<T> par;
	int i = 1;
	for (this->height(root, i); i > 0; i--)
	{
		par = this->level(i);
		par.IterStart();

		int size = par.length();
		for (int j = 1; j < size; j += 2)
		{
			T player1, player2;
			cout << "Round: " << round << " ";
			par.DeleteElem(par.Iter(), player1);
			cout << player1;
			cout << " vs ";
			par.DeleteElem(par.Iter(), player2);
			cout << player2;
			cout << endl;
		}
		round++;
	}

	//int i = 1; // Number of rounds
	//stack<Participant> st;
	//prPrintBattles(root);
	cout << "Winner: " << this->getRootValue() << endl;
}

template<typename T>
LList<T> CompleteLinkBinTree<T>::level(int x) const
{
	return level(x, root);
	//cout << endl;
}
template<typename T>
LList<T> CompleteLinkBinTree<T>::level(int k, TreeNode<T>* r) const
{
	LList<T> l;
	if (r == NULL)	return l;

	if (k == 1)		l.ToEnd(r->value);

	else if (k > 1)
	{
		l.concat(level(k - 1, r->left));
		l.concat(level(k - 1, r->right));
	}
	return l;
}

#endif
