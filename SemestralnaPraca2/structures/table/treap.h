#pragma once

#include "binary_search_tree.h"
#include <random>

namespace structures
{
	/// <summary> Prvok treap-u. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TreapItem : public TableItem<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		/// <param name = "priority"> Priorita. </param>
		TreapItem(K key, T data, int priority);

		/// <summary> Getter atributu priorita. </summary>
		/// <returns> Priorita. </returns>
		int getPriority();

		/// <summary> Nastavi minimalnu prioritu. </summary>
		void minimizePriority();
	private:
		/// <summary> Kluc prvku. </summary>
		int priority_;
	};

	/// <summary> Treap. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Treap : public BinarySearchTree<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Treap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Treap, z ktoreho sa prevezmu vlastnosti. </param>
		Treap(const Treap<K, T>& other);

		/// <summary> Destruktor. </summary>
		~Treap();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Binarny vyhladavaci strom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		BinarySearchTree<K, T>& operator=(const BinarySearchTree<K, T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Treap, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		virtual Treap<K, T>& operator=(const Treap<K, T>& other);

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>  
		bool insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>  
		T remove(const K& key) override;

	private:
		/// <summary> Generator nahodnej priority. </summary>
		std::default_random_engine* generator_;

		/// <summary> Skontroluje, ci je haldove usporiadanie prvkov okolo vrcholu OK. </summary>
		/// <param name = "node"> Vrchol, ktoreho susedstvo sa kontroluje. </param>
		/// <returns> true, ak je haldove usporiadanie prvkov okolo vrcholu OK, false inak. </returns>
		bool isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Vytiahne prioritu z vrcholu stromu. </summary>
		/// <param name = "node"> Vrchol, ktoreho priorita ma byt zistena. </param>
		/// <returns> Priorita vrcholu. Ak je vrchol nullptr, vrati -1. </returns>
		int extractPriority(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi lavu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks> 
		/// Musi byt pravym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane lavym synom tohto vrchola.
		/// Potencialny lavy syn tohto vrchola sa stane pravym synom otca.
		/// </remarks>
		void rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi pravu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks> 
		/// Musi byt lavym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane pravym synom tohto vrchola.
		/// Potencialny pravy syn tohto vrchola sa stane lavym synom otca.
		/// </remarks>
		void rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline TreapItem<K, T>::TreapItem(K key, T data, int priority) :
		TableItem<K, T>(key, data),
		priority_(priority)
	{
	}

	template<typename K, typename T>
	inline int TreapItem<K, T>::getPriority()
	{
		return priority_;
	}

	template<typename K, typename T>
	inline void TreapItem<K, T>::minimizePriority()
	{
		priority_ = INT_MAX;
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap() :
		BinarySearchTree<K, T>(),
		generator_(new std::default_random_engine())
	{
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap(const Treap<K, T>& other) :
		Treap()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline Treap<K, T>::~Treap()
	{
		delete generator_;
		generator_ = nullptr;
	}

	template<typename K, typename T>
	inline Structure * Treap<K, T>::clone() const
	{
		return new Treap<K, T>(*this);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>& Treap<K, T>::operator=(const BinarySearchTree<K, T>& other)
	{
		return *this = dynamic_cast<const Treap<K, T>&>(other);
	}

	template<typename K, typename T>
	inline Treap<K, T>& Treap<K, T>::operator=(const Treap<K, T>& other)
	{
		if (this != &other)
		{
			BinarySearchTree<K, T>::operator=(other);
			*generator_ = *other.generator_;
		}
		return *this;
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::insert(const K & key, const T & data)
	{
		TreapItem<K, T>* treapItem = new TreapItem<K, T>(key, data, (*generator_)());
		typename BinarySearchTree<K, T>::BSTTreeNode* treeNode = new BSTTreeNode(treapItem);

		if (tryToInsertNode(treeNode))
		{
			int parentPriority = extractPriority(treeNode->getParent());

			while (parentPriority != INT_MIN && parentPriority > treapItem->getPriority())
			{
				bool resetRoot = treeNode->getParent()->isRoot();

				if (treeNode->isLeftSon())
				{
					rotateRightOverParent(treeNode);
				}
				else
				{
					rotateLeftOverParent(treeNode);
				}

				if (resetRoot)
				{
					binaryTree_->replaceRoot(treeNode);
				}

				parentPriority = extractPriority(treeNode->getParent());
			}
			return true;
		}
		else
		{
			delete treapItem;
			delete treeNode;

			return false;
			//throw std::logic_error("Key already present in the table!");
		}
	}

	template<typename K, typename T>
	inline T Treap<K, T>::remove(const K & key)
	{
		bool found = false;

		typename BinarySearchTree<K, T>::BSTTreeNode* nodeToRemove = findBSTNode(key, found);

		if (found)
		{
			TreapItem<K, T>* treapItem = dynamic_cast<TreapItem<K, T>*>(nodeToRemove->accessData());
			treapItem->minimizePriority();

			int leftSonPriority = extractPriority(nodeToRemove->getLeftSon());
			int rightSonPriority = extractPriority(nodeToRemove->getRightSon());

			while (leftSonPriority != INT_MIN || rightSonPriority != INT_MIN)
			{
				BinarySearchTree<K, T>::BSTTreeNode* rotateSon = nullptr;

				if (leftSonPriority != INT_MIN && rightSonPriority != INT_MIN)
				{
					rotateSon = leftSonPriority < rightSonPriority ? nodeToRemove->getLeftSon() : nodeToRemove->getRightSon();
				}
				else
				{
					rotateSon = leftSonPriority != INT_MIN ? nodeToRemove->getLeftSon() : nodeToRemove->getRightSon();
				}

				bool resetRoot = nodeToRemove->isRoot();

				if (rotateSon->isLeftSon())
				{
					rotateRightOverParent(rotateSon);
				}
				else
				{
					rotateLeftOverParent(rotateSon);
				}

				if (resetRoot)
				{
					binaryTree_->replaceRoot(rotateSon);
				}

				leftSonPriority = extractPriority(nodeToRemove->getLeftSon());
				rightSonPriority = extractPriority(nodeToRemove->getRightSon());
			}

			extractNode(nodeToRemove);

			T result = nodeToRemove->accessData()->accessData();
			delete nodeToRemove->accessData();
			delete nodeToRemove;
			size_--;
			return result;
		}
		else
		{
			throw std::logic_error("Key not found!");
		}
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node)
	{
		if (node != nullptr)
		{
			int priority = extractPriority(node);
			int priorityParent = extractPriority(node->getParent());
			int priorityLeftSon = extractPriority(node->getLeftSon());
			int priorityRightSon = extractPriority(node->getRightSon());

			return (priorityParent == -1 || priorityParent <= priority) &&
				(priorityLeftSon == -1 || priorityLeftSon >= priority) &&
				(priorityRightSon == -1 || priorityRightSon >= priority);
		}
		else
		{
			return true;
		}
	}

	template<typename K, typename T>
	inline int Treap<K, T>::extractPriority(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		return node != nullptr ?
			dynamic_cast<TreapItem<K, T>*>(node->accessData())->getPriority() :
			INT_MIN;
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		if (node->isRightSon())
		{
			typename BinarySearchTree<K, T>::BSTTreeNode* leftSon = node->changeLeftSon(nullptr);
			typename BinarySearchTree<K, T>::BSTTreeNode* parent = node->getParent();
			typename BinarySearchTree<K, T>::BSTTreeNode* grandParent = parent->getParent();

			parent->setRightSon(nullptr); // zrusi vazbu medzi vrcholom node a otcom

			if (grandParent != nullptr)
			{
				// node a stary otec budu spravne spojeny, otcov parent bude null
				if (parent->isLeftSon())
				{
					grandParent->setLeftSon(node);
				}
				else
				{
					grandParent->setRightSon(node);
				}
			}

			// otec ide dolava 
			node->setLeftSon(parent);
			// lavy podstrom vrcholu node bude pravym podstromom otca
			parent->setRightSon(leftSon);
		}
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		if (node->isLeftSon())
		{
			typename BinarySearchTree<K, T>::BSTTreeNode* rightSon = node->changeRightSon(nullptr);
			typename BinarySearchTree<K, T>::BSTTreeNode* parent = node->getParent();
			typename BinarySearchTree<K, T>::BSTTreeNode* grandParent = parent->getParent();

			parent->setLeftSon(nullptr); // zrusi vazbu medzi vrcholom node a otcom

			if (grandParent != nullptr)
			{
				// node a stary otec budu spravne spojeny, otcov parent bude null
				if (parent->isLeftSon())
				{
					grandParent->setLeftSon(node);
				}
				else
				{
					grandParent->setRightSon(node);
				}
			}

			// otec ide doprava
			node->setRightSon(parent);
			// pravy podstrom vrcholu node bude lavym podstromom otca
			parent->setLeftSon(rightSon);
		}
	}
}