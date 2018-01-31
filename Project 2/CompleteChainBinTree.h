#ifndef COMPLETE_CHAIN_BIN_TREE_H
#define COMPLETE_CHAIN_BIN_TREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> // Supports rand and srand.
#include <ctime> // Supports time function.
#include <cmath>
#include "Participant.h"

using namespace std;



template <typename T>
class CompleteChainBinTree
{
private:
	int rootIndex;
	int elemCounter;
	vector<T> values; //values of elements
	vector<int> leftHeirs; //indices of left heirs
	vector<int> rightHeirs; //indices of right heirs

	void cr(const int index);
	void pr(const int root, unsigned spaces);
	void printSpaces(unsigned n) const;

public:
	CompleteChainBinTree();

	bool empty() const;
	T getRootValue() const;
	void create();
	void print();
	void addLeaf(T leaf);

	void createEmptyTreeWithSizeOf(int n);
	void tournament();
	void printAllBattles();
	void findPath(string const& name);


};

template <typename T>
CompleteChainBinTree<T>::CompleteChainBinTree() : rootIndex(-1)
{ }

template <typename T>
bool CompleteChainBinTree<T>::empty() const
{
	return rootIndex == -1;
}

template <typename T>
T CompleteChainBinTree<T>::getRootValue() const
{
	if (rootIndex != -1)
		return values[rootIndex];
	else
	{
		cerr << "No Root!";
		return T();
	}
}

template <typename T>
void CompleteChainBinTree<T>::cr(int index)
{
	T x;
	char s;
	cout << "Value: ";
	cin >> x;

	values.push_back(x);
	leftHeirs.push_back(2 * index + 1);
	rightHeirs.push_back(2 * index + 2);

	elemCounter++;
	cout << "Next element - y/n? ";
	cin >> s;
	if (s == 'y') cr(index + 1);
	if (s == 'n') cout << "The tree is ready!" << endl;
}

template <typename T>
void CompleteChainBinTree<T>::create()
{
	elemCounter = 0;
	rootIndex = 0;
	cr(rootIndex);
}

template <typename T>
void CompleteChainBinTree<T>::printSpaces(unsigned n) const
{
	for (unsigned i = 0; i < n; ++i)
	{
		cout << " ";
	}

}

template <typename T>
void CompleteChainBinTree<T>::pr(int root, unsigned spaces) // prints hierarchically
{
	if (rootIndex == -1)
	{
		cerr << "Empty Tree!" << endl;
		return;
	}

	// prevents from printing 'elements' after the last one in the array
	if (root > elemCounter - 1) // because every element is at index <its order number - 1>
		return;

	printSpaces(spaces);
	cout << values[root];
	cout << endl;

	pr(leftHeirs[root], spaces + 3);
	pr(rightHeirs[root], spaces + 3);
}

template <typename T>
void CompleteChainBinTree<T>::print()
{
	pr(rootIndex, 0);
	cout << endl;
}

template <typename T>
void CompleteChainBinTree<T>::addLeaf(T leaf)
{
	if (empty())
	{
		rootIndex = 0;
	}

	values.push_back(leaf);

	//where its heirs will be (one day)
	leftHeirs.push_back(2 * elemCounter + 1);
	rightHeirs.push_back(2 * elemCounter + 2);

	elemCounter++;

}


/***************************** TASKS 5, 6, 7, 8 *****************************/

///// TASK 6

//external function
int randomPowerOfTwoLessThan(int ceil)
{
	srand((unsigned int)time(nullptr));	// Set random seed.

										// gives number which is 2 to the power of 0-30
	int number = pow(2, rand() % 31);

	// if it is greater than we want, then generates new one
	while (number > ceil)
	{
		number = pow(2, rand() % 31);
	}
	return number;
}

/*
DISCLAIMER: We took a decision to extract from the file not just a random number of participants (leaves for the tree)
but instead a number – still random – which is any power of two less than the total number of participants present in the file.
The reason behind this is the fact that only when the leaves are 2^x in number we have a properly functioning complete binary
tree for the purposes of single-elimination kind of tournament. Otherwise there always will appear a player who does not have
an opponent, which leads to his trouble-free classification for the next round, until the final match-up -  a case that is not
fair to all the other players (this case is explained in detail in the last messages in our random channel)
*/
//external function
vector<Participant> choosePatricipantsFromFile()
{
	vector<Participant> chosenParticipants;

	ifstream in("participants.txt", ios::in);

	if (!in)
	{
		cerr << "File couldn't be opened!" << endl;
		return chosenParticipants;
	}

	if (in.is_open())
	{
		// saving all potentional participants in an auxiliary vector
		vector<Participant> allWilling;
		Participant temp;
		while (in >> temp)
		{
			allWilling.push_back(temp);
		}

		//defining the number of actual participants and adding them to the vector of chosen ones
		int numberOfWilling = allWilling.size();
		int actualParticipants = randomPowerOfTwoLessThan(numberOfWilling);

		vector<int> luckyIndices;
		vector<bool> takenParticipants;
		takenParticipants.resize(numberOfWilling, 0);

		srand((unsigned int)time(nullptr));	// Set random seed.

		while (luckyIndices.size() < actualParticipants)
		{
			// Get random index in the interval 0 - (numberOfWilling -1)
			int index = (rand() % numberOfWilling);
			if (takenParticipants[index] == false)
			{
				luckyIndices.push_back(index);
				takenParticipants[index] == true;
			}
		}

		for (int i = 0; i < actualParticipants; i++)
		{
			chosenParticipants.push_back(allWilling[luckyIndices[i]]);
		}
	}

	in.close();

	return chosenParticipants;
}


///// TASK 5

template<typename T> // method
void CompleteChainBinTree<T>::createEmptyTreeWithSizeOf(int n)
{
	if (empty())
	{
		rootIndex = 0;

		values.resize(n, T());
		leftHeirs.resize(n, -1);
		rightHeirs.resize(n, -1);

		for (int i = 0; i < n; i++)
		{
			leftHeirs[i] = 2 * i + 1;
			rightHeirs[i] = 2 * i + 2;
		}

		elemCounter = n;
	}
	else
	{
		cerr << "ERROR: Trying to create an empty tree with given size, but the tree already has elements!" << endl;
		return;
	}
}

template <typename T> // external function
void filltree(vector<T> leaves, CompleteChainBinTree<T> &battleTree)
{
	int numLeaves = leaves.size();
	if (numLeaves == 0)
	{
		cerr << "The vector leaves is empty!" << endl;
		return;
	}

	/* When the last level is full, then we can say that the number
	of elements in the tree other than the leaves is equal to <numLeaves - 1>  */
	int numOfNonLeafElems = numLeaves - 1;

	battleTree.createEmptyTreeWithSizeOf(numOfNonLeafElems);

	int allreadyInTree = 0;
	int toBeInTree = numLeaves;

	srand((unsigned int)time(nullptr));	// Set random seed.

	while (allreadyInTree < toBeInTree)
	{
		// Get random index in the interval 0 - (numLeaves -1)
		int index = (rand() % numLeaves);

		battleTree.addLeaf(leaves[index]);
		allreadyInTree++;
		leaves.erase(leaves.begin() + index);
		numLeaves--;
	}
}


///// TASK 7 

template <typename T> // method
void CompleteChainBinTree<T>::tournament()
{
	if (empty())
	{
		cerr << "ERROR: No players for this tournament!";
		return;
	}

	if (values.size() == 1)
	{
		return;
	}

	int n = elemCounter; // the number of all elements of the tree

						 // m is initially the first position in the last line which means (n-1)/2
						 // m is always the first position in the current line, starting from the bottom line and going upwards
	for (int m = (n - 1) / 2; m > 0; m /= 2)
	{
		for (int i = m; i <= 2 * m; i += 2) // 2*m gives us the last position in the current line
		{
			// the element at index (i-1)/2 is the parent of elements at indices i and i+1
			int parentIndex = (i - 1) / 2;
			values[parentIndex] = winner(values[i], values[i + 1]);
			// so there goes the winner
		}
	}

}

// external function
Participant winner(Participant &first, Participant &second)
{
	int whiteBalls = first.getPower();
	int blackBalls = second.getPower();

	int balls = whiteBalls + blackBalls;

	srand((unsigned int)time(nullptr));	// Set random seed.

										// randomly choosing a ball
	int pickedBall = rand() % balls + 1;

	// checking if the generated number is in the whites' or in the blacks' range
	if (pickedBall <= whiteBalls)
		return first;
	else
		return second;
}


///// TASK 8

template<typename T>// method
void CompleteChainBinTree<T>::findPath(string const& name)
{
	//in case of unfilled tree
	if (empty())
	{
		cerr << "Unfilled tree. No players to search from." << endl;
		return;
	}

	int elems = values.size();
	bool foundPlayer = false;
	int indexOfPlayer;

	//searching for that participant in the leaves
	for (int i = (elems - 1) / 2; i <= elems - 1; i++)
	{
		if (values[i].getName() == name)
		{
			indexOfPlayer = i;
			foundPlayer = true;
		}
	}

	cout << "Battles of " << name << ":" << endl;

	//in case of incorrect name
	if (foundPlayer == false)
	{
		cerr << name << " does not participate in the tournament!" << endl;
		return;
	}

	vector<string> opponents;

	// if an element is at position i, its parent will be at position (i-1)/2
	int parentOfPlayer = (indexOfPlayer - 1) / 2;
	do
	{
		if (values[leftHeirs[parentOfPlayer]].getName() != name)
			opponents.push_back(values[leftHeirs[parentOfPlayer]].getName());

		if (values[rightHeirs[parentOfPlayer]].getName() != name)
			opponents.push_back(values[rightHeirs[parentOfPlayer]].getName());

		parentOfPlayer = (parentOfPlayer - 1) / 2; // go to the higher level
		if (parentOfPlayer == 0) break;

	} while (values[parentOfPlayer].getName() == name); //while the player continues to win, get his opponents

	for (int i = 0; i < opponents.size(); i++)
	{
		cout << name << " vs. " << opponents[i] << endl;
	}

}

template <typename T> //method
void CompleteChainBinTree<T>::printAllBattles()
{
	int round = 1;

	int n = elemCounter; // the number of all elements of the tree

						 // m is initially the first position in the last line which means (n-1)/2
						 // m is always the first position in the current line, starting from the bottom line and going upwards
	for (int m = (n - 1) / 2; m > 0; m /= 2)
	{
		cout << "Round " << round << ":" << endl;

		for (int i = m; i <= 2 * m; i += 2) // 2*m gives us the last position in the current line
		{
			// the element at index (i-1)/2 is the parent of elements at indices i and i+1
			int parentIndex = (i - 1) / 2;

			cout << "Battle: " << values[i].getName() << " vs. " << values[i + 1].getName()
				<< " Wins: " << values[parentIndex].getName() << endl;
		}

		cout << endl;
		round++;
	}

	cout << "GRAND CHAMPION: " << values[0].getName() << endl;
	cout << endl;
}


#endif