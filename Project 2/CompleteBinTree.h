#ifndef COMPLETE_BIN_TREE_H
#define COMPLETE_BIN_TREE_H
#include<iostream>
#include<fstream>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include <cstring>
#include <time.h> 
#include <windows.h>
#include"Participant.h"
using namespace std;
template<typename T>
class CompleteBinTree
{
public:
	CompleteBinTree();

	//we can create tree with constructor with a parameter but if we want to add new leaf
	//it is mandatory to first add the element in an empty vector 
	//that later will be used in the function addChild(const T &x, vector<CompleteBinTree<T>> &q) as a second parameter
	CompleteBinTree(T r);

	// the vector`s first element always contain a tree which will be the father of the tree with root with value x
	//on each step we add elemet with value x in the end of the vector
	void addChild(const T &x, vector<CompleteBinTree<T>> &q);

	CompleteBinTree& leftTree();
	CompleteBinTree& rightTree();

	bool hasNotLeftTree();
	bool hasNotRightTree();

	T getRoot();
	T findFather(T &x);
	list<CompleteBinTree> const& getSubtrees() const;
	bool empty() const;

	bool isLeaf();
	//we can use that tree functions only if type T is Participant
	bool findPlayer(const string &name, CompleteBinTree<T>& player);
	void findPath(const string &name);
	void tournament();

	//the function is recursive
	//on each step the third parameter is a different tree
	//the function searches the tree with root with value x in the tree tr (the third parameter)
	//and when it is found the function adds the new child for that tree
	bool searchTree(T r, CompleteBinTree& newChild, CompleteBinTree& tr);
	friend ostream& operator<<(ostream& os, CompleteBinTree<T> tree)
	{
		if (tree.empty())
		{
			os << "The tree is empty!";
			return os;
		}

		os << '(' << tree.getRoot();
		for (list<CompleteBinTree<T>>::const_iterator it = tree.getSubtrees().begin();
			it != tree.getSubtrees().end(); it++)
		{
			os << ' ' << *it;
		}
		return os << ')';
	}
	vector<T> leaves();
	void printBattles(int countParticipants);

private:
	T root;
	//we have a separate variable isEmpty because otherwise it would be hard to define whether three is empty or not
	bool isEmpty;
	list<CompleteBinTree<T>> subtrees;
	void tournament(CompleteBinTree<T> &tree);
	void printBattles(list<CompleteBinTree> lt, int& round);
};

template<typename T>
CompleteBinTree<T>::CompleteBinTree()
{
	root = T();
	isEmpty = true;
}

template<typename T>
CompleteBinTree<T>::CompleteBinTree(T r)
{
	root = r;
	isEmpty = false;
}

template<typename T>
CompleteBinTree<T>& CompleteBinTree<T>::leftTree()
{
	if (empty())
		return *this;

	list<CompleteBinTree>::iterator it = subtrees.begin();
	//Checking if the tree has left subtree at all
	if (it != getSubtrees().end())
		return *it;
	else
	{
		//The left tree is empty. It has an only root
		return CompleteBinTree();
	}
}

template<typename T>
CompleteBinTree<T>& CompleteBinTree<T>::rightTree()
{
	if (empty())
		return *this;

	list<CompleteBinTree>::iterator it = subtrees.begin();

	//Checking if the tree has left subtree at all
	if (it != getSubtrees().end()) it++;

	//Checking if the tree has right subtree at all
	if (it != getSubtrees().end())
		return *it;
	else
	{
		//The left tree is empty. It has an only root
		return CompleteBinTree();
	}
}

template<typename T>
bool CompleteBinTree<T>::hasNotLeftTree() 
{
	if (empty())
		return true;

	list<CompleteBinTree>::iterator it = subtrees.begin();
	//Checking if the tree has left subtree at all
	if (it != getSubtrees().end())
		return false;
	else
		return true;
}

template<typename T>
bool CompleteBinTree<T>::hasNotRightTree() 
{
	if (empty())
		return true;

	list<CompleteBinTree>::iterator it = subtrees.begin();

	//Checking if the tree has left subtree at all
	if (it != getSubtrees().end()) it++;

	//Checking if the tree has right subtree at all
	if (it != getSubtrees().end())
		return false;
	else
		return true;
}

template<typename T>
void CompleteBinTree<T>::addChild(const T &x, vector<CompleteBinTree<T>> &q)
{
	CompleteBinTree<T> temp(x);
	if (empty())
	{
		*this = temp;
		q.push_back(*this);
		return;
	}
	else
	{
		CompleteBinTree<T> first = q.front();
		if (first.hasNotLeftTree())
		{
			first.subtrees.push_back(temp);
			searchTree(first.root, temp, *this);

			//erases first element of the vector because 
			//we are changing it - we are adding its left child
			q.erase(q.begin());

			//adds again the first element because it is already changed(row: 108)
			q.insert(q.begin(), first);
			q.push_back(temp);
			return;
		}
		else if (first.hasNotRightTree())
		{
			first.subtrees.push_back(temp);
			searchTree(first.root, temp, *this);

			//erases the first element of the vector because 
			//we are changing it - we are adding its left child
			q.erase(q.begin());

			//adds again the first element because it is already changed(row: 122)
			q.insert(q.begin(), first);
			q.push_back(temp);
			return;
		}
		if (first.hasNotLeftTree() == false && first.hasNotRightTree() == false)
		{
			q.erase(q.begin());
			first = q.front();
			first.subtrees.push_back(temp);

			//erase first first element from the vector because 
			//we change it - add his right child
			q.erase(q.begin());

			//change first element
			q.push_back(temp);
			searchTree(first.root, temp, *this);

			//add again first element because it is already changed(row: 145)
			q.insert(q.begin(), first);
		}
	}
}

template<typename T>
T CompleteBinTree<T>::getRoot()
{
	if (empty())
	{
		cerr << "The tree is empty! " << endl;
		return T();
	}
	return root;
}

template<typename T>
list<CompleteBinTree<T>> const& CompleteBinTree<T>::getSubtrees() const
{
	return subtrees;
}

template<typename T>
bool CompleteBinTree<T>::empty() const
{
	return isEmpty;
}

template<typename T>
vector<T> CompleteBinTree<T>::leaves()
{
	vector<T> leaves;
	queue<CompleteBinTree<T>> q;
	q.push(*this);

	while (!q.empty())
	{
		CompleteBinTree<T> & t = q.front();
		leaves.push_back(t.getRoot());
		for (list<CompleteBinTree<T>>::const_iterator it = t.getSubtrees().begin(); it != t.getSubtrees().end(); it++)
		{
			q.push(*it);
		}
		q.pop();
	}
	return leaves;
}

template<typename T>
bool CompleteBinTree<T>::isLeaf()
{
	if (subtrees.empty())
		return true;
	return false;
}

template<typename T>
bool CompleteBinTree<T>::searchTree(T r, CompleteBinTree& newChild, CompleteBinTree& tr)
{
	if (tr.empty()) return false;

	if (tr.root == r)
	{
		tr.subtrees.push_back(newChild);
		return true;
	}
	bool flag = tr.searchTree(r, newChild, leftTree());
	if (flag) return true;

	return tr.searchTree(r, newChild, rightTree());
	return false;
}

/***************************** TASKS 5, 6, 7, 8 *****************************/

template<typename T>
T CompleteBinTree<T>::findFather(T &x)
{
	if (root == x)
		return x;

	if (subtrees.empty()) return root;

	for (list<CompleteBinTree>::iterator i = subtrees.begin(); i != subtrees.end(); ++i)
	{
		if (i->root == x)
			return root;
		else
			return i->findFather(x);
	}
}

template<typename T>
void CompleteBinTree<T>::findPath(const string &name)
{
	//Let pl be the tree with root with name 'name' which is at the lowest level
	CompleteBinTree<Participant> pl;
	bool isFound = findPlayer(name, pl);
	if (!isFound)
	{
		cerr << "No such player in the tournament" << endl;
		return;
	}
	//names of rivals of the player that is received as a parameter
	vector<string> players;

	//if the player is in the leaf of the tree we don't know his rival
	//for that reason we use finfFather to get to his rival
	if (pl.hasNotLeftTree() && getRoot().getName() != name)
	{
		Participant rival = findFather(pl.getRoot());
		players.push_back(rival.getName());
	}

	//after the execution of the function, the vector players contains pl's rivals
	battles(pl, players, pl.getRoot().getName());

	//if we have only one element in the tree and it is the root, then this message will be shown
	int size = players.size();
	if (size == 0)
	{
		cerr << "Unfilled tree!" << endl;
		return;
	}

	//print all pl's rivals
	for (int i = 0; i < size; i++)
	{
		if (players[i] != name)
			cout << name << " vs " << players[i] << endl;
	}
}

template<typename T>
bool CompleteBinTree<T>::findPlayer(const string &name, CompleteBinTree<T>& player)
{
	queue<CompleteBinTree<Participant>> q;
	q.push(*this);

	while (!q.empty())
	{
		player = q.front();
		q.pop();

		if (player.getRoot().getName() == name)
			return true;

		if (player.getRoot().getName() == name && (player.hasNotRightTree() || player.hasNotLeftTree()))
			return true;

		if (!player.hasNotRightTree())
		{
			q.push(player.rightTree());
			q.push(player.leftTree());
		}
	}
	return false;
}

template<typename T>
void CompleteBinTree<T>::tournament()
{
	if (empty())
	{
		cerr << "No added participants for this tournament!" << endl;
		return;
	}
	tournament(*this);
}

template<typename T>
void CompleteBinTree<T>::tournament(CompleteBinTree<T> &tree)
{
	if (tree.subtrees.empty())
		return;

	if (!tree.isLeaf() && !tree.hasNotLeftTree() && !tree.leftTree().hasNotLeftTree())
	{
		tree.tournament(tree.leftTree());
		tree.tournament(tree.rightTree());
	}

	Participant first = tree.leftTree().getRoot();
	Participant second = tree.rightTree().getRoot();
	Participant winnerInBattle = champion(first, second);

	tree.root = winnerInBattle;
}

template<typename T>
void CompleteBinTree<T>::printBattles(int countParticipants)
{
	if (empty())
	{
		cerr << "No added participants for this tournament!" << endl;
		return;
	}

	if (subtrees.empty())
	{
		cout << "Only one participant! There aren't any battles!"  << endl;
		return;
	}

	int round = -1;
	while (countParticipants)
	{
		round++;
		countParticipants /= 2;
	}
	
	if (subtrees.empty())
	{
		cout << "round 1:" << getRoot() << endl;
		return;
	}
	
	printBattles(subtrees, round);
	cout << "CHAMPION: " << getRoot() << endl;

}

template<typename T>
void CompleteBinTree<T>::printBattles(list<CompleteBinTree> lt, int& round)
{
	int j = 0;
	cout << "round: " << round << endl;
	--round;

	int k = 0;
	for (list<CompleteBinTree>::iterator i = lt.begin(); i != lt.end(); ++i)
	{
		if (k == 2)
			k = 0;

		if(k == 0)
			cout << i->root << " vs ";

		if (k == 1)
			cout << i->root << endl;

		k++;
	}
		

	cout << endl;

	for (list<CompleteBinTree>::iterator i = lt.begin(); i != lt.end() && j<2; ++j)
	{
		for (list<CompleteBinTree>::iterator k = i->subtrees.begin(); k != i->subtrees.end(); ++k)
			lt.push_back(*k);

		++i;
		lt.pop_front();
	}

	if (round == 0)
		return;
	printBattles(lt, round);

}

void randomDistribution(vector<int> &arr, int n)
{
	for (int i = 0; i < n; i++)
		arr.push_back(i);

	for (int i = 0; i < n; i++)
		swap(arr[i], arr[rand() % n]);
}

void filltree(vector<Participant> &leaves, CompleteBinTree<Participant> &tree)
{
	int size = leaves.size();
	if (size == 0)
	{
		cerr << "The vector with leaves is empty!" << endl;
		return;
	}

	vector<int> indexLeaf;
	randomDistribution(indexLeaf, size);

	int index = 0;
	vector<CompleteBinTree<Participant>> q;
	Participant p;
	string name = "X";
	p.setName(name);
	p.setPower(-1);

	//The tree could not have two or more identical elements 
	//for that reason we add as x, xx, xxx and so on
	//until we get to the position where the first leaf has to be
	for (int i = 1; i < size; i++)
	{
		tree.addChild(p, q);
		p.setName(name += 'X');
	}

	for (int i = 0; i < size; i++)
	{
		index = indexLeaf[i];
		tree.addChild(leaves[index], q);
	}
}

int randomNumber(int n)
{
	if (n == 0) return 0;

	srand(time(NULL));
	int number = rand() % 1000;

	if (number > n)
		number = number - (n * (number / n));

	return number;
}

int randomPowerOfTwo(int ceil)
{
	srand((unsigned int)time(nullptr));    // Set random seed.

										   // gives number which is 2 to the power of 0-31
										   // why exactly 32? because the int type cannot handle integers >= 2^31
	int number = pow(2, rand() % 31);

	// if it is greater than we want, then generates new one
	while (number > ceil)
	{
		number = pow(2, rand() % 31);
	}
	
	return number;
}

int countParticipants()
{
	ifstream file;
	file.open("participants.txt", ios::in);
	if (!file)
		cout << "The file cannot be opened!" << endl;

	int counter = 0;
	Participant p;
	while (file >> p)
		counter++;

	file.close();
	return counter;
}

/*
DISCLAIMER: We took a decision to extract from the file not just a random number of participants (leaves for the tree)
but instead a number – still random – which is any power of two less than the total number of participants present in the file.
The reason behind this is the fact that only when the leaves are 2^x in number we have a properly functioning complete binary
tree for the purposes of single-elimination kind of tournament. Otherwise there always will appear a player who does not have
an opponent, which leads to his trouble-free classification for the next round, until the final match-up -  a case that is not
fair to all the other players (this case is explained in detail in the last messages in our random channel)
*/
vector<Participant> getParticipantsFromFile()
{
	int countAllParticipants = countParticipants();

	ifstream file;
	file.open("participants.txt", ios::in);
	if (!file)
		cout << "The file cannot be opened!" << endl;

	int n = randomPowerOfTwo(countAllParticipants);
	vector<Participant> arr;

	Participant p;
	for (int i = 0; i < countAllParticipants; i++)
	{
		file >> p;
		arr.push_back(p);
	}

	vector<int> indexLeaf;
	vector<Participant> participants;
	randomDistribution(indexLeaf, countAllParticipants);
	int index = 0;

	for (int i = 0; i < n; i++)
	{
		index = indexLeaf[i];
		participants.push_back(arr[index]);
	}

	file.close();
	return participants;
}

Participant champion(Participant &first, Participant &second)
{
	int countBlackBalls = first.getPower();
	int countWhiteBalls = second.getPower();

	int index =randomNumber(countBlackBalls + countWhiteBalls);

	if (index <= countBlackBalls)
		return first;
	else
		return second;
}

void battles(CompleteBinTree<Participant> tree, vector<string> &players, string name)
{
	if (tree.empty())
		return;

	if (tree.hasNotLeftTree() || tree.hasNotRightTree()) return;

	string left = tree.leftTree().getRoot().getName();
	string right = tree.rightTree().getRoot().getName();

	if (!(left == name) && right == name)
	{
		players.insert(players.begin(), left);
		battles(tree.rightTree(), players, name);
	}

	if (!(right == name) && left == name)
	{
		players.insert(players.begin(), right);
		battles(tree.leftTree(), players, name);
	}
}


#endif 
