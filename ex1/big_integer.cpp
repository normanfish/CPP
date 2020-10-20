//
// Created by noam on 8/25/18.
//

#include "big_integer.h"

#define NUM_DIGITS 10

/**
 * receives a big integer type and checks if it 0. if it is, then it changes the is_negative field
 * to false, so there will be consistency in representing 0's
 * @param num the number to check if it's a zero
 */
void makeZeroNonNegative (big_integer &num)
{
	if (num . getNum () == "0")
	{
		num . setIsNegative (false);
	}
}

/**
 * finds the largest number i such that i*denominator<remainder (used in long division)
 * @param remainder a big_integer type representing the remainder
 * @param denominator a big_integer type representing the denominator
 * @return i such as described
 */
int findMinimalQuotientDigit (big_integer &remainder, const big_integer &denominator)
{
	big_integer absDenominator = denominator . abs ();
	big_integer absRemainder = remainder . abs ();
	int i = 0;
	for (i = 0; i <= 10; i ++)
	{
		big_integer digit (i);
		if (digit * absDenominator > absRemainder)
		{
			big_integer digitMinusOne (i - 1);
			remainder -= digitMinusOne * absDenominator;
			break;
		}
	}
	return i - 1;
}

/**
 * divides the numerator by the denominator and updates the quotient and remainder variables
 * @param quotient an address of the quotient variable where we will store the division result
 * @param remainder an address of the remainder variable where we will store the remainder result
 * @param numerator the numerator
 * @param denominator the denominator
 */
void divideWithRemainder (
		big_integer &quotient, big_integer &remainder, const big_integer &numerator,
		const big_integer &denominator)
{
	remainder . setNum ("0");
	remainder . setIsNegative (false);
	quotient . setNum ("0");
	remainder . setIsNegative (false);
	big_integer base (NUM_DIGITS);
	if (denominator . getNum () == "0" || numerator . getNum () == "0")
	{
		return;
	}
	for (size_t i = 0; i < numerator . getNum () . size (); i ++)
	{
		remainder *= base;
		big_integer digit (to_string (numerator . getNum ()[i] - '0'));
		remainder += digit;
		quotient *= base;
		big_integer qDigit (findMinimalQuotientDigit (remainder, denominator));
		quotient += qDigit;
	}
	remainder . setIsNegative (numerator . isNegative ());
	quotient . setIsNegative (numerator . isNegative () != denominator . isNegative ());
}

/**
 * erases the 0's on the left side of a string that represents a number
 * @param st the string
 */
void eraseTrailingZeroes (string &st)
{
	size_t startOfZeroes = st[0] == '-' ? 1 : 0;
	size_t numZeroes = 0;
	size_t i = 0;
	while (st[startOfZeroes + i] == '0')
	{
		numZeroes ++;
		i ++;
	}
	st . replace (startOfZeroes, numZeroes, "");
}

/**
 * concatenates num times st
 * @param st the string to concatenate
 * @param num the number of times to concatenate
 * @return the concatenated string
 */
string stringMultiplication (const string &st, size_t num)
{
	string toReturn;
	for (size_t i = 0; i < num; i ++)
	{
		toReturn += st;
	}
	return toReturn;
}

/**
 * checks if a character is a digit
 * @param dig a character
 * @return true if the character holds a digit, and false otherwise
 */
bool isDigit (const char dig)
{
	const char digits[NUM_DIGITS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (char digit:digits)
	{
		if (dig == digit)
		{
			return true;
		}
	}
	return false;
}

/**
 * checks if a string represents an integer number
 * @param string1 the string to check
 * @return true if the string holds an integer and false otherwise
 */
bool isNum (const string &string1)
{
	if (string1 == "-")
	{
		return false;
	}
	for (size_t i = 0; i < string1 . length (); i ++)
	{
		if (! isDigit (string1[i]))
		{
			if (string1[i] != '-' || i != 0)
			{
				return false;
			}
		}
	}
	return true;
}

/**
 * returns the maximum between 2 unsigned integers
 * @param first the first unsigned integers
 * @param second the second unsigned integer
 * @return the maximum value of the two
 */
size_t maxSize (const size_t first, const size_t second)
{
	if (first > second)
	{
		return first;
	}
	return second;
}

/**
 * returns the i-th character from the end of a string
 * @param size the size of the string
 * @param num the string
 * @param i the i-th digit from the end we want to get
 * @return see above
 */
int getDigitInIndex (const size_t size, const string &num, size_t i)
{
	if (i > size)
	{
		return 0;
	}
	return (int) num[size - i] - '0';
}

/**
 * switches around arithmetic operations so that it will be easier for the functions to handle them
 * @param first the first big integer type
 * @param second the second big integer type
 * @return the same mathmatical value as the functions that called this function.
 */
big_integer switchAddSub (const big_integer &first, const big_integer &second)
{
	big_integer temp1 (first);
	big_integer temp2 (second);
	if (second . isNegative ())
	{

		return temp1 - (- temp2);
	}
	return temp2 - (- temp1);

}

big_integer::big_integer ()
{
	_num = "0";
	_isNegative = false;
}

big_integer::big_integer (const big_integer &lhs)
{
	_isNegative = lhs . _isNegative;
	_num = string (lhs . _num);

}

big_integer::big_integer (int num)
{
	_num = std::to_string (num);
	if (num < 0)
	{
		_num . replace (0, 1, "");
		_isNegative = true;
	}
	else
	{
		_isNegative = false;
	}
}

big_integer::big_integer (const std::string string1)
{
	if (string1 . length () == 0 || ! isNum (string1))
	{
		_num = "0";
		_isNegative = false;
		return;
	}
	_isNegative = string1[0] == '-';
	_num = string1;
	eraseTrailingZeroes (_num);
	if (_isNegative)
	{
		_num . replace (0, 1, "");
	}
	if (_num . empty ())
	{
		_num = "0";
	}
	makeZeroNonNegative (*this);
}

big_integer big_integer::operator+ (const big_integer &rhs)
{
	if (rhs . _isNegative != this -> _isNegative)
	{
		return switchAddSub (*this, rhs);
	}
	big_integer toReturn;
	int carryOver = 0;
	size_t iterations = maxSize (rhs . _num . length (), this -> _num . length ());
	for (size_t i = 0; i < iterations; i ++)
	{
		int firstsDigit = getDigitInIndex (rhs . _num . size () - 1, rhs . _num, i);
		int secondsDigits = getDigitInIndex (this -> _num . size () - 1, this -> _num, i);
		if (carryOver == 0)
		{
			carryOver = (firstsDigit + secondsDigits) / 10;
			toReturn . _num . insert (0, std::to_string ((firstsDigit + secondsDigits) % 10));
		}
		else
		{
			carryOver = (firstsDigit + secondsDigits + 1) / 10;
			toReturn . _num . insert (0, std::to_string ((firstsDigit + secondsDigits + 1) % 10));
		}
	}
	toReturn . _num . pop_back ();
	if (carryOver == 1)
	{
		toReturn . _num . insert (0, "1");
	}
	toReturn . _isNegative = rhs . _isNegative;
	return toReturn;
}

big_integer big_integer::operator- ()
{
	big_integer temp (*this);
	temp . _isNegative = ! temp . _isNegative;
	return temp;
}

big_integer &big_integer::operator+= (const big_integer &rhs)
{
	big_integer temp (*this);
	*this = temp + rhs;
	return *this;
}

big_integer big_integer::operator- (const big_integer &rhs)
{
	big_integer smaller (rhs);
	big_integer bigger (*this);
	//different sign
	if (this -> _isNegative == ! rhs . _isNegative || ! this -> _isNegative == rhs . _isNegative)
	{
		return bigger + (- smaller);
	}
	//same sign
	if (smaller . abs () > bigger . abs ())
	{
		big_integer difference (smaller - bigger);
		difference . setIsNegative (! (smaller . _isNegative && bigger . _isNegative));
		makeZeroNonNegative (difference);
		return difference;
	}
	//by this point, bigger is bigger (or equal to) smaller, let's subtract!
	int carryOver = 0, oldCarryOver = 0;
	big_integer toReturn;
	size_t iterations = bigger . getNum () . size ();
	for (size_t i = 0; i < iterations; i ++)
	{
		oldCarryOver = carryOver;
		int firstsDigit = getDigitInIndex (bigger . _num . size () - 1, bigger . getNum (), i);
		int secondsDigits = getDigitInIndex (smaller . _num . size () - 1, smaller . _num, i);
		carryOver = (firstsDigit - secondsDigits + oldCarryOver < 0) ? - 1 : 0;
		if (carryOver == - 1)
		{
			firstsDigit += 10;
		}
		toReturn . _num . insert (0, to_string (firstsDigit - secondsDigits + oldCarryOver));
	}
	toReturn . _num . pop_back ();
	eraseTrailingZeroes (toReturn . _num);
	if (toReturn . _num . empty ())
	{
		toReturn . _num = "0";
		toReturn . _isNegative = false;
	}
	toReturn . setIsNegative (bigger . _isNegative);
	makeZeroNonNegative (toReturn);
	return toReturn;
}

big_integer &big_integer::operator-= (const big_integer &rhs)
{
	big_integer temp (*this);
	*this = temp - rhs;
	return *this;
}

big_integer big_integer::operator* (const big_integer &rhs)
{
	big_integer sum;
	int carryOver = 0;
	for (size_t i = 0; i < this -> _num . size (); i ++)
	{
		carryOver = 0;
		string tempSum = stringMultiplication ("0", i);
		int multiplyingDigit = getDigitInIndex (this -> _num . size () - 1, this -> getNum (), i);
		for (size_t j = 0; j < rhs . _num . size (); j ++)
		{
			int secondDigit = getDigitInIndex (rhs . _num . size () - 1, rhs . getNum (), j);
			tempSum . insert (0, to_string ((secondDigit * multiplyingDigit + carryOver) % 10));
			carryOver = (secondDigit * multiplyingDigit + carryOver) / 10;
		}
		tempSum . insert (0, to_string (carryOver));
		big_integer temp (tempSum);
		sum += temp;
	}
	sum . _isNegative = this -> _isNegative != rhs . _isNegative;
	makeZeroNonNegative (sum);
	return sum;
}

big_integer &big_integer::operator*= (const big_integer &rhs)
{
	big_integer temp (*this);
	*this = temp * rhs;
	return *this;
}

big_integer big_integer::operator/ (const big_integer &rhs)
{
	big_integer quotient;
	big_integer remainder;
	divideWithRemainder (quotient, remainder, *this, rhs);
	makeZeroNonNegative (quotient);
	return quotient;
}

big_integer &big_integer::operator/= (const big_integer &rhs)
{
	big_integer temp (*this);
	*this = temp / rhs;
	return *this;
}

big_integer big_integer::operator% (const big_integer &rhs)
{
	big_integer quotient;
	big_integer remainder;
	divideWithRemainder (quotient, remainder, *this, rhs);
	makeZeroNonNegative (remainder);
	return remainder;
}

int big_integer::operator[] (size_t index) const
{
	return getDigitInIndex (this -> _num . size () - 1, this -> getNum (), index);
}

big_integer &big_integer::operator= (const big_integer &rhs)
{
	_num = string (rhs . _num);
	_isNegative = rhs . _isNegative;
	return *this;
}

bool big_integer::operator== (const big_integer &rhs) const
{
	return (_num == rhs . _num && _isNegative == rhs . _isNegative);
}


bool big_integer::operator!= (const big_integer &rhs) const
{
	return ! (rhs == *this);
}

bool big_integer::operator< (const big_integer &rhs) const
{
	//first, we'l make sure they are both of the same sign, otherwise, we can immediately return
	// the smaller one
	if (this -> isNegative () && ! rhs . isNegative ())
	{
		return true;
	}
	if (! this -> isNegative () && rhs . isNegative ())
	{
		return false;
	}
	// now, we know both of them have the same sign
	// the right hand side has more digits than the left hand side
	if (rhs . getNum () . size () > this -> getNum () . size ())
	{
		return ! rhs . isNegative ();
	}
	//the left hand side has more digits than the right
	if (rhs . getNum () . size () < this -> getNum () . size ())
	{
		return rhs . isNegative ();
	}
	//if we got here, then both numbers have the same amount of digits.
	for (size_t i = 0; i < rhs . getNum () . size (); i ++)
	{
		//the i-th digit if either smaller of bigger than the other number
		if (this -> getNum ()[i] < rhs . getNum ()[i])
		{
			return ! rhs . isNegative ();
		}
		if (this -> getNum ()[i] > rhs . getNum ()[i])
		{
			return rhs . isNegative ();
		}
	}
	return false;
}

bool big_integer::operator> (const big_integer &rhs) const
{
	//first, we'l make sure they are both of the same sign, otherwise, we can immediately return
	// the smaller one
	if (this -> isNegative () && ! rhs . isNegative ())
	{
		return false;
	}
	if (! this -> isNegative () && rhs . isNegative ())
	{
		return true;
	}
	// the right hand side has more digits than the left hand side
	if (rhs . getNum () . size () > this -> getNum () . size ())
	{
		return rhs . isNegative ();
	}
	//the left hand side has more digits than the right
	if (rhs . getNum () . size () < this -> getNum () . size ())
	{
		return ! rhs . isNegative ();
	}
	for (size_t i = 0; i < rhs . getNum () . size (); i ++)
	{
		//the i-th digit if either smaller of bigger than the other number
		if (this -> getNum ()[i] > rhs . getNum ()[i])
		{
			return ! rhs . isNegative ();
		}
		if (this -> getNum ()[i] < rhs . getNum ()[i])
		{
			return rhs . isNegative ();
		}
	}
	//equal numbers, return false
	return false;

}

bool big_integer::operator<= (const big_integer &rhs) const
{
	return ! (rhs < *this);
}

bool big_integer::operator>= (const big_integer &rhs) const
{
	return ! (*this < rhs);
}

ostream &operator<< (ostream &os, const big_integer &integer)
{
	if (! integer . _isNegative)
	{
		os << integer . _num;
	}
	else
	{
		os << "-" << integer . _num;
	}
	return os;
}

const string &big_integer::getNum () const
{
	return _num;
}

bool big_integer::isNegative () const
{
	return _isNegative;
}

void big_integer::setIsNegative (bool isNegative)
{
	_isNegative = isNegative;
}

void big_integer::setNum (const string &num)
{
	_num = num;
}

const big_integer big_integer::abs () const
{
	big_integer abs (*this);
	abs . setIsNegative (false);
	return abs;
}