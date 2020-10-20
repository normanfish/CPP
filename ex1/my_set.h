//
// Created by noam on 8/28/18.
//

#ifndef EX1_MY_SET_H
#define EX1_MY_SET_H


#include "big_integer.h"

/**
 * a class that represents a mathematical set of large integer types. there can only be one of each
 * number
 */
class my_set
{
public:
	/**
	 * destructor
	 */
	virtual ~my_set ();

	/**
	 * default c'tor. creates and empty set
	 */
	my_set ();

	/**
	 * c'tor with an number to be put in the set. creates a set of size 1.
	 * @param initial the number we wish to insert
	 */
	my_set (const my_set &initial);

	/**
	 * the << operator
	 * @param os an instance of the class ostream that we will load the text to.
	 * @param set the set we wish to print or output
	 * @return the << operator of the set, ready to print
	 */
	friend ostream &operator<< (ostream &os, const my_set &set);

	/**
 	* the = operator
	* @param rhs the right hand side of the = equation
 	* @return the new object, changed to rhs
 	*/
	my_set &operator= (const my_set &rhs);

	/**
	 * receives a big integer type and checks if the set contains it
	 * @param val the big integer
	 * @return true if the set contains val, and false otherwise
	 */
	bool is_in_set (const big_integer &val) const;

	/**
	 * adds a number to the set
	 * @param val the big_integer we wish to add
	 * @return true if we added successfully to the set, and false otherwise (for instance if
	 * it already exists in the set)
	 */
	bool add (const big_integer &val);

	/**
	 * removes a number from the set
	 * @param val the big_integer we wish to remove
	 * @return true if val was in the set and was removed successfully, and false otherwise.
	 */
	bool remove (const big_integer &val);

	/**
	 * sums the numbers in the set
	 * @return the sum of numbers in the set
	 */
	big_integer sum_set ();

	/**
	 * the binary - operator
	 * @param rhs the right hand side of the - sign
	 * @return the result of this - rhs
	 */
	my_set operator- (const my_set &rhs);

	/**
	 * mathematical "OR" of 2 sets
	 * @param rhs the right hand side of the | operator
	 * @return this OR rhs
	 */
	my_set operator| (const my_set &rhs);

	/**
	 * mathematical "AND" set operator
	 * @param rhs the right hand side
	 * @return this AND rhs
	 */
	my_set operator& (const my_set &rhs);


private:
	/**
	 * implementing the Node class for use in my_set class (which is essentially a linked list)
	 * we implement it here for the sake of information hiding
	 */
	class Node
	{
	public:
		//the data of the node
		big_integer _data;
		//the pointer to the next node
		Node *_next;

		/**
		 * class c'tor, initializes the node to initial and sets next to null
		 * @param initial the number we wish to give to the new node
		 */
		Node (const big_integer &initial)
		{
			_data = initial;
			_next = nullptr;
		}

		/**
		 * default c'tor, sets the node's value at 0
		 */
		Node ()
		{
			_next = nullptr;
		}

		/**
		 * copy c'tor
		 * @param ptr the node to copy it's number and next node from
		 */
		Node (Node *ptr)
		{
			_data = ptr -> _data;
			_next = ptr -> _next;
		}

		/**
		 * the = operator
		 * @param rhs the right hand side of the operator
		 * @return the new Node, after having copied from the old node
		 */
		Node &operator= (const Node &rhs)
		{
			_data = rhs . _data;
			_next = rhs . _next;
			return *this;
		}

		/**
		 * class d'tor
		 */
		~Node ()
		{
			delete _next;
		}
	};


private:
	//the head to the linked list of big_integers
	Node *_head;
	//the size of the list
	size_t _size;
};


#endif //EX1_MY_SET_H
