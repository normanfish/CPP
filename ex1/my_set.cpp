//
// Created by noam on 8/28/18.
//

#include <iostream>
#include "my_set.h"

/**
 * the implementation of my_set
 */

my_set::my_set ()
{
	_head = new Node;
	_size = 0;
}

my_set::my_set (const my_set &initial)
{
	_head = new Node;
	_size = 0;
	Node *ptr = initial . _head;
	for (size_t i = 0; i < initial . _size; i ++)
	{
		this -> add (ptr -> _data);
		ptr = ptr -> _next;
	}
}


bool my_set::is_in_set (const big_integer &val) const
{
	Node *ptr = _head;
	for (size_t i = 0; i < _size; i ++)
	{
		if (ptr -> _data == val)
		{
			return true;
		}
		ptr = ptr -> _next;
	}
	return false;
}

bool my_set::add (const big_integer &val)
{
	if (is_in_set (val))
	{
		return false;
	}
	if (_size == 0)
	{
		_head -> _data = val;
		_size ++;
		return true;
	}
	Node *temp = new Node (val);
	temp -> _next = _head;
	_head = temp;
	_size ++;
	temp = nullptr;
	return true;
}

bool my_set::remove (const big_integer &val)
{
	if (! is_in_set (val) || _size == 0)
	{
		return false;
	}
	if (_head -> _data == val)
	{
		if (_size != 1)
		{
			Node *temp = _head;
			_head = _head -> _next;
			delete (temp);
		}
		_size --;
		return true;
	}
	Node *ptr = _head;
	while (ptr -> _next -> _data != val)
	{
		ptr = ptr -> _next;
	}
	Node *temp = ptr -> _next;
	ptr -> _next = ptr -> _next -> _next;
	delete temp;
	_size --;
	return true;
}

big_integer my_set::sum_set ()
{
	big_integer sum;
	Node *ptr = _head;
	for (size_t i = 0; i < _size; i ++)
	{
		sum += ptr -> _data;
		ptr = ptr -> _next;
	}
	return sum;
}

my_set my_set::operator- (const my_set &rhs)
{
	Node *ptr = _head;
	my_set toReturn;
	for (size_t i = 0; i < _size; i ++)
	{
		if (! rhs . is_in_set (ptr -> _data))
		{
			toReturn . add (ptr -> _data);
		}
		ptr = ptr -> _next;
	}
	return toReturn;
}

my_set my_set::operator| (const my_set &rhs)
{
	Node *ptr = _head;
	my_set toReturn;
	for (size_t i = 0; i < _size; i ++)
	{
		toReturn . add (ptr -> _data);
		ptr = ptr -> _next;
	}
	ptr = rhs . _head;
	for (size_t i = 0; i < rhs . _size; i ++)
	{
		toReturn . add (ptr -> _data);
		ptr = ptr -> _next;
	}
	return toReturn;
}

my_set my_set::operator& (const my_set &rhs)
{
	Node *ptr = rhs . _head;
	my_set toReturn;
	for (size_t i = 0; i < rhs . _size; i ++)
	{
		if (this -> is_in_set (ptr -> _data))
		{
			toReturn . add (ptr -> _data);
		}
		ptr = ptr -> _next;
	}
	return toReturn;
}


/**
 * swaps the value of 2 big_integers
 * @param a the first big integer
 * @param b the second one
 */
void swap (big_integer &a, big_integer &b)
{
	big_integer temp (a);
	a = b;
	b = temp;
}

/**
 * sorts an array of big_integers using bubble sort (safe and simple :-))
 * @param arr the array to be sorted
 * @param size the size of the array
 */
void sortArray (big_integer arr[], size_t size)
{
	for (size_t i = 0; i < size; i ++)
	{
		for (size_t j = 0; j < size - i - 1; j ++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap (arr[j], arr[j + 1]);
			}
		}
	}
}

my_set &my_set::operator= (const my_set &rhs)
{
	delete (_head);
	_head = new Node;
	_size = 0;
	Node *ptr = rhs . _head;
	for (size_t i = 0; i < rhs . _size; i ++)
	{
		this -> add (ptr -> _data);
		ptr = ptr -> _next;
	}
	return *this;
}

ostream &operator<< (ostream &os, const my_set &set)
{
	big_integer *arr = new big_integer[set . _size];
	my_set::Node *ptr = set . _head;
	for (size_t i = 0; i < set . _size; i ++)
	{
		arr[i] = ptr -> _data;
		ptr = ptr -> _next;
	}
	sortArray (arr, set . _size);
	for (size_t i = 0; i < set . _size; i ++)
	{
		os << arr[i] << endl;
	}
	if (set . _size == 0)
	{
		os << endl;
	}
	delete[] arr;
	return os;
}

my_set::~my_set ()
{
	delete (_head);
}


