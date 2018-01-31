#ifndef COMPLETE_BIN_TREE_PARENT_LIST_H
#define COMPLETE_BIN_TREE_PARENT_LIST_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<string>
#include"Participant.h"


using namespace std;

template <typename T>
class CompleteBinTreeParentList
{
private:

	T* values;       // An array containing the values of each node.
	int* parents;    // An array containing the indices of each node's parent.
	int n;           // Number of nodes in the tree.

	void copy(const CompleteBinTreeParentList<T>&);       // Creates a copy of "tree" in the calling object.
	void del();                                           // Deletes the contents of the calling object.

public:

	CompleteBinTreeParentList();                                                             // Default Constructor
	CompleteBinTreeParentList(const CompleteBinTreeParentList<T>&);                          // Copy Constructor
	CompleteBinTreeParentList(int, T*, int*);                                                // A custom constructor
	CompleteBinTreeParentList<T>& operator=(const CompleteBinTreeParentList<T>&);            // Assignment operator
	~CompleteBinTreeParentList();                                                            // Destructor
	bool empty() const;                                                                      // Checks whether a tree is empty.
	T getRootValue() const;	                                                                 // Returns a copy of the root value.
	T& getRootReference();                                                                   // Returns a reference to the root value.
	void create();                                                                           // Creates a tree.
	void createEmptyTree(int);                                                               // Creates an empty tree of size "size".
	void addLeaf(T);                                                                         // Adds a leaf to the tree.
	void print();                                                                            // Prints all the elements in the tree.
	int getSize() const;                                                                     // Returns the size of the tree.
	void findAll(T, vector<int>&) const;                                                     // Finds and stores all elements with value "value" into a vector.
	void findpath(const string);										         			 // Displays all the battles a participant has taken part in.
	T CompleteBinTreeParentList<T>::getOtherChild(int) const;                                // Returns the other child to the father of the element with index "index"    
	CompleteBinTreeParentList<T> leftTree();	                                             // Returns the left subtree of the tree.
	CompleteBinTreeParentList<T> rightTree();	                                             // Returns the right subtree of the tree.
	void tournament();
	void displayBattles() const;
};

template<typename T>
void CompleteBinTreeParentList<T>::copy(const CompleteBinTreeParentList<T>& tree)
{
	n = tree.n;
	values = new T[n];
	parents = new int[n];

	for (int i = 0; i < n; i++)
	{
		values[i] = tree.values[i];
		parents[i] = tree.parents[i];
	}
}

template<typename T>
void CompleteBinTreeParentList<T>::del()
{
	delete[] values;
	delete[] parents;
}

template<typename T>
CompleteBinTreeParentList<T>::CompleteBinTreeParentList()
{
	values = nullptr;
	parents = nullptr;
	n = 0;
}

template<typename T>
CompleteBinTreeParentList<T>::CompleteBinTreeParentList(const CompleteBinTreeParentList<T>& tree)
{
	copy(tree);
}

template<typename T>
CompleteBinTreeParentList<T>::CompleteBinTreeParentList(int number, T* vals, int* prs)
{
	n = number;

	values = new T[n];
	parents = new int[n];

	for (int i = 0; i < n; i++)
	{
		values[i] = vals[i];
		parents[i] = prs[i];
	}
}

template<typename T>
CompleteBinTreeParentList<T>& CompleteBinTreeParentList<T>::operator=(const CompleteBinTreeParentList<T>& tree)
{
	if (this != &tree)
	{
		del();
		copy(tree);
	}

	return *this;
}

template<typename T>
CompleteBinTreeParentList<T>::~CompleteBinTreeParentList()
{
	del();
}

template<typename T>
bool CompleteBinTreeParentList<T>::empty() const
{
	return n == 0;
}

template<typename T>
T CompleteBinTreeParentList<T>::getRootValue() const
{
	if (n != 0)
		return values[0];
	else
	{
		cerr << "The tree is empty!" << endl;
		return T();
	}
}

template<typename T>
T& CompleteBinTreeParentList<T>::getRootReference()
{
	if (n != 0)
		return values[0];
}

template<typename T>
void CompleteBinTreeParentList<T>::create()
{
	T x;

	cout << "Enter the number of nodes: " << endl;
	cin >> n;
	cin.ignore();

	values = new T[n];
	parents = new int[n];

	int currentNode;                 // The first node in the tree with less than 2 children.
	int children = 0;                // The number of children of currentNode.

	for (int i = 0; i < n; i++)
	{
		cout << "node: ";            // Enter the value of the new node.
		cin >> x;

		values[i] = x;               // Store the value of the new node.

		if (i == 0)                  // Check if the new node is the root.
		{
			parents[i] = -1;
			currentNode = 0;
		}
		else
		{
			if (children < 2)       // If the number of children of currentNode is less than 2, than it is the parent of the new node
			{
				parents[i] = currentNode;
				children++;
			}
			else                    // Else, the parent of the new node is the node after currentNode.
			{
				currentNode++;
				children = 0;

				parents[i] = currentNode;
				children++;
			}
		}
	}
}

template<typename T>
void CompleteBinTreeParentList<T>::createEmptyTree(int size)
{
	n = size;
	values = new T[n]();
	parents = new int[n];

	parents[0] = -1;

	for (int i = 1; i < n; i++)
	{
		parents[i] = (i - 1) / 2;
	}
}

template<typename T>
void CompleteBinTreeParentList<T>::print()
{
	if (n == 0)
	{
		cerr << "The tree is empty!" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (i != n - 1)
			cout << values[i] << " ";
		else
			cout << values[i] << endl;
	}
}

template<typename T>
int CompleteBinTreeParentList<T>::getSize() const
{
	return n;
}

template<typename T>
CompleteBinTreeParentList<T> CompleteBinTreeParentList<T>::leftTree()
{
	if (n > 1)                                                  // If the tree has more than 1 nodes, then it has a left subtree.
	{
		T* newValues = new T[1];                                // The nodes of the left subtree.
		int* newParents = new int[1];                           // The parents of the nodes of the left subtree.
		int newNumber = 1;                                      // The number of nodes in the left subtree.

		int* storedIndeces = new int[1];

		newValues[0] = values[1];                               // Add the root of the left subtree.
		newParents[0] = -1;
		storedIndeces[0] = 1;


		for (int i = 2; i < n; i++)                             // Check for each node in the original tree if its parent is part of the left subtree, and if it is,
		{                                                       // increase the number of nodes in the left subtree, and add the node.
			for (int j = 0; j < newNumber; j++)
			{
				if (parents[i] == storedIndeces[j])
				{
					T* tempValues = newValues;
					int* tempParents = newParents;
					int* tempStoredIndeces = storedIndeces;

					newValues = new T[newNumber + 1];
					newParents = new int[newNumber + 1];
					storedIndeces = new int[newNumber + 1];

					for (int k = 0; k < newNumber; k++)
					{
						newValues[k] = tempValues[k];
						newParents[k] = tempParents[k];
						storedIndeces[k] = tempStoredIndeces[k];
					}

					newValues[newNumber] = values[i];
					newParents[newNumber] = j;
					storedIndeces[newNumber] = i;

					newNumber++;


					delete[] tempValues;
					delete[] tempParents;
					delete[] tempStoredIndeces;

					break;
				}
			}
		}

		CompleteBinTreeParentList<T> tree(newNumber, newValues, newParents);

		return tree;
	}
}

template<typename T>
CompleteBinTreeParentList<T> CompleteBinTreeParentList<T>::rightTree()
{
	if (n > 2)                                            // If the tree has more than 2 nodes, then it has a right subtree.
	{
		T* newValues = new T[1];                          // The nodes of the right subtree.
		int* newParents = new int[1];                     // The parents of the nodes of the right subtree.
		int newNumber = 1;                                // The number of nodes in the right subtree.

		int* storedIndeces = new int[1];

		newValues[0] = values[2];                         // Add the root of the right subtree.
		newParents[0] = -1;
		storedIndeces[0] = 2;

		for (int i = 3; i < n; i++)                       // Check for each node in the original tree if its parent is part of the right subtree, and if it is,
		{                                                 // increase the number of nodes in the right subtree, and add the node.
			for (int j = 0; j < newNumber; j++)
			{
				if (parents[i] == storedIndeces[j])
				{
					T* tempValues = newValues;
					int* tempParents = newParents;
					int* tempStoredIndeces = storedIndeces;

					newValues = new T[newNumber + 1];
					newParents = new int[newNumber + 1];
					storedIndeces = new int[newNumber + 1];

					for (int k = 0; k < newNumber; k++)
					{
						newValues[k] = tempValues[k];
						newParents[k] = tempParents[k];
						storedIndeces[k] = tempStoredIndeces[k];
					}

					newValues[newNumber] = values[i];
					newParents[newNumber] = j;
					storedIndeces[newNumber] = i;

					newNumber++;

					delete[] tempValues;
					delete[] tempParents;
					delete[] tempStoredIndeces;

					break;
				}
			}
		}

		CompleteBinTreeParentList<T> tree(newNumber, newValues, newParents);

		return tree;
	}
}




template<typename T>
void CompleteBinTreeParentList<T>::addLeaf(T value)
{
	int firstLeaf = n / 2;     // The index of the first leaf.
	int lastLeaf = n - 1;      // The index of the last leaf.

	for (int i = firstLeaf; i <= lastLeaf; i++) // Iterate through each leaf until an empty one is met.
	{
		if (values[i] == T())    // If an empty leaf is met, store "value" into it.
		{
			values[i] = value;
			return;
		}
	}

}

template<typename T>
T CompleteBinTreeParentList<T>::getOtherChild(int index) const
{
	int parentIndex = (index - 1) / 2;     // The index of the parent of the element with index "index".

	for (int i = 0; i < n; i++)            // Go through all the nodes in the tree, until you find the other child of the node with index "parentIndex".
	{
		if (parents[i] == parentIndex && i != index)
			return values[i];
	}
}

/***************************** TASKS 5, 6, 7, 8 *****************************/

template<typename T>
void CompleteBinTreeParentList<T>::findAll(T value, vector<int>& buffer) const
{
	// Go through all the nodes in the tree and whenever the needed value is met store its index in the buffer vector.
	for (int i = 0; i < n; i++)
	{
		if (values[i] == value)
			buffer.push_back(i);
	}
}

//We fill the leaves of a tree with values by randomly choosing elements from a vector
template <typename T>
void filltree(const vector<T> &leaves, CompleteBinTreeParentList<T> &tree)
{
	//The tree which leaves are going to be filled with values from the vector
	//The number of leaves in the tree.
	int sizeOfLeaves = leaves.size();

	//A vector which helps us check if a leaf had already been stored in the tree
	vector<int> visited(sizeOfLeaves, 0);

	unsigned int seed = time(0);
	srand(seed);

	//An integer which holds a random index of the vector
	int randomIndex = rand() % sizeOfLeaves;
	//An integer that counts the number of leaves already created
	int leavesCreated = 0;

	//we create an empty tree with the required number of nodes
	tree.createEmptyTree(sizeOfLeaves + sizeOfLeaves - 1);

	//We add leaves until all the elements from the vector have been stored in the tree
	while (leavesCreated < sizeOfLeaves)
	{
		if (visited[randomIndex] == 0)
		{
			tree.addLeaf(leaves[randomIndex]);
			leavesCreated++;
			visited[randomIndex] = 1;
		}
		randomIndex = rand() % sizeOfLeaves;
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
//We read a list of participants from a file and stores them in a vector
vector<Participant> getParticipants(istream& file)
{
	int allParticipants = 0;
	vector<int> possibleNumbers;

	vector<Participant> allParticipantsInfo;
	vector<Participant> chosenParticipants;
	Participant currentParticipant;

	//Count the number of participnats from the file
	while (file >> currentParticipant)
		allParticipants++;

	file.clear();
	file.seekg(0, ios::beg);

	vector<int> visitedParticipants(allParticipants, 0);

	while (file >> currentParticipant)
		allParticipantsInfo.push_back(currentParticipant);

	for (int i = 1; i <= allParticipants; i *= 2)
		possibleNumbers.push_back(i);

	int seed = time(0);
	srand(seed);

	int randomNumberOfParticipants;

	randomNumberOfParticipants = possibleNumbers[rand() % possibleNumbers.size()];

	int currentIndex;
	int i = 0;

	while (i < randomNumberOfParticipants)
	{
		currentIndex = rand() % allParticipants;

		if (visitedParticipants[currentIndex] == 0)
		{
			chosenParticipants.push_back(allParticipantsInfo[currentIndex]);
			visitedParticipants[currentIndex] = 1;
			i++;
		}
	}


	return chosenParticipants;
}

template<typename T>
void CompleteBinTreeParentList<T>::findpath(const string name)
{
	vector<string> battles;
	vector<int> buffer;

	if (getRootValue() == Participant())
	{
		cerr << "The tree is empty!" << endl;
		return;
	}

	if (n == 1 && getRootValue().getName() == name)
	{
		cerr << "The participant doesn't take part in any fight.";
		return;
	}

	Participant objective;
	objective.setName(name);

	for (int i = 0; i < n; i++)
	{
		if (values[i].getName() == name)
		{
			objective.setPower(values[i].getPower());
			break;
		}
	}

	//Store all the indexes where the objective participant is present, in the buffer vector
	findAll(objective, buffer);

	if (buffer.empty())
	{
		cerr << "Incorrect name!" << endl;
		return;
	}

	int currentBattle = 0;

	//Go through all the indexes in the buffer vector and store the battles in the battles vector
	for (int i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] != 0)
		{
			battles.push_back(name + " vs ");
			Participant opponent = getOtherChild(buffer[i]);
			battles[currentBattle] += opponent.getName();
			currentBattle++;
		}
	}

	for (int i = 0; i < battles.size(); i++) // Display all the battles in the correct order.
	{
		cout << battles[battles.size() - i - 1] << endl;
	}
}

template<typename T>
void CompleteBinTreeParentList<T>::displayBattles() const
{
	if (n < 3)
	{
		cerr << "There are no battles to display!" << endl;
		return;
	}

	int round = 1;
	string battle = "";
	int allNodes = n;
	int leaves = allNodes - allNodes / 2;
	int leavesLeft = leaves / 2;

	for (int i = n - 1; i >= 2; i -= 2)
	{
		if (leavesLeft == 0)
		{
			allNodes -= leaves;
			leaves = allNodes - allNodes / 2;
			leavesLeft = leaves / 2;
		}

		if (leavesLeft == leaves / 2)
		{
			cout << "Round " << round << ":" << endl;
			round++;
		}

		battle = values[i].getName() + " vs " + values[i - 1].getName();
		cout << battle << endl;
		cout << "Winner: " << values[parents[i]].getName() << endl << endl;
		leavesLeft--;
	}
}

template<typename T>
void CompleteBinTreeParentList<T>::tournament()
{
	int elementsLeft = n;                 //The number of elements which have not been looked at yet.
	int firstLeaf = elementsLeft / 2;     //The index of the first leaf.
	int lastLeaf = elementsLeft - 1;      //The index of the last leaf.
	T winner;                             //The element which is the winner.

	if (values[firstLeaf] == T())
	{
		cerr << "There are no leaves!" << endl;
		return;
	}

	//While we have not reached the root continue with the tournament
	while (firstLeaf != lastLeaf)
	{
		//For each pair of leaves, conduct a battle between them and store the winner in their parent
		for (int i = firstLeaf; i <= lastLeaf; i += 2)
		{
			winner = fight(values[i], values[i + 1]);
			values[parents[i]] = winner;
		}

		elementsLeft /= 2;

		//The index of the next first leaf
		firstLeaf = elementsLeft / 2;

		//The index of the next last leaf
		lastLeaf = elementsLeft - 1;
	}
}

Participant fight(Participant &p1, Participant &p2)
{
	int power1 = p1.getPower();
	int power2 = p2.getPower();

	//The number of balls to choose from
	int sum = power1 + power2;

	unsigned int seed = time(0);
	srand(seed);

	// A random chosen ball
	int ball = rand() % sum + 1;

	// Decide who the winner is
	if (ball <= power1)
		return p1;
	else
		return p2;
}

#endif

