//
// Created by noam on 8/25/18.
//

#ifndef EX1_BIG_INTEGER_H
#define EX1_BIG_INTEGER_H

#include <string>
#include <ostream>

using namespace std;

/**
 *  a class that represents a large integer number
 */
class big_integer
{
public:

	/**
	 * default class c'tor - sets the number to 0
	 */
	big_integer ();

	/**
	 * copy c'tor
	 * @param lhs a big_integer type to copy from
	 */
	big_integer (const big_integer &lhs);

	/**
	 * c'tor from integer
	 * @param num an int that will be the the big_integer's value
	 */
	big_integer (int num);

	/**
	 * string c'tor checks if the string represents and int, and if not, sets the value to 0
	 * @param string1 the string
	 */
	big_integer (std::string string1);

	/**
	 *
	 * @return the absolute value of the number
	 */
	const string &getNum () const;

	/**
	 * sets the number from num parameter
	 * @param num then umber to assign to big_integer
	 */
	void setNum (const string &num);

	/**
	 * change the sign of the number
	 * @param isNegative true if negative, false 0 or positive
	 */
	void setIsNegative (bool isNegative);

	/**
 	*
 	* @return true if the number is negative, and false otherwise
 	*/
	bool isNegative () const;

	/**
	 * [] operator, returns the digit at the i-th place
	 * @param index the index of the digit we would like to get
	 * @return the digit at the specified index, and 0 if index is out of range
	 */
	int operator[] (size_t index) const;

	/**
	 * = operator
	 * @param rhs the other number that we assign from
	 * @return basicly returns rhs, which is the new number
	 */
	big_integer &operator= (const big_integer &rhs);

	/**
	 * + operator
	 * @param rhs the right hand side of the + side
	 * @return the result of the this + rhs
	 */
	big_integer operator+ (const big_integer &rhs);

	/**
	 * += operator
	 * @param rhs the right hand side of the +=
	 * @return this+=rhs
	 */
	big_integer &operator+= (const big_integer &rhs);

	/**
	 * - operator
	 * @param rhs the right hand side of the -
	 * @return the result of this - rhs
	 */
	big_integer operator- (const big_integer &rhs);

	/**
	 * -= operator
	 * @param rhs the right hand side of the -=
	 * @return this-=rhs
	 */
	big_integer &operator-= (const big_integer &rhs);

	/**
	 * * operator
	 * @param rhs the right hand side of the *
	 * @return the result of this*rhs
	 */
	big_integer operator* (const big_integer &rhs);

	/**
	 * *= operator
	 * @param rhs the right hand side of the *=
	 * @return this*=rhs
 	*/
	big_integer &operator*= (const big_integer &rhs);

	/**
	 * / operator
	 * @param rhs the right hand side of the /
	 * @return the result of this/rhs (integer division!)
	 */
	big_integer operator/ (const big_integer &rhs);

	/**
	 * /= operator
	 * @param rhs the right hand side of the /=
	 * @return this/=rhs
	 */
	big_integer &operator/= (const big_integer &rhs);

	/**
	 * modulos operator (%)
	 * @param rhs the right hand side of the %
	 * @return this%rhs
	 */
	big_integer operator% (const big_integer &rhs);

	/**
	 * smaller than operator
	 * @param rhs the right hand side of the <
	 * @return true if this<rhs, and false otherwise
	 */
	bool operator< (const big_integer &rhs) const;

	/**
	 * bigger than operator
	 * @param rhs the right hand side of the >
	 * @return true if this>rhs, and false otherwise
	 */
	bool operator> (const big_integer &rhs) const;

	/**
	 * smaller or equal than operator
	 * @param rhs the right hand side of the <=
	 * @return true if this<=rhs, and false otherwise
	 */
	bool operator<= (const big_integer &rhs) const;

	/**
	 * greater or equal than operator
	 * @param rhs the right hand side of the >=
	 * @return true if this>=rhs, and false otherwise
	 */
	bool operator>= (const big_integer &rhs) const;

	/**
	 * == operator
	 * @param rhs the right side of the == operator
	 * @return true if the number represented by this equals rhs, and false otherwise
	 */
	bool operator== (const big_integer &rhs) const;

	/**
	 * != operator
	 * @param rhs the right hand side of the !=
	 * @return true if the number represented by this does not equal rhs, and false otherwise
	 */
	bool operator!= (const big_integer &rhs) const;

	/**
	 * unitary - operator
	 * @return the inverse of this
	 */
	big_integer operator- ();

	/**
	 *
	 * @return the absolute value of the number represented
	 */
	const big_integer abs () const;

	/**
	 * the output stream operator
	 * @param os the output stream instance to which we will write the wanted print format
	 * @param integer the number we wish to print
	 * @return the << operator
	 */
	friend ostream &operator<< (ostream &os, const big_integer &integer);

private:
	//a string representing the value of the num (no sign)
	std::string _num;
	//if the number is negative or not
	bool _isNegative;
};


#endif //EX1_BIG_INTEGER_H
