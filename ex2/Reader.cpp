//
// Created by noam on 9/2/18.
//
/**
 * Reader class - Implementation
 */
#include "Reader.h"
#include <string>
#include <sstream>
#include <iostream>

#define DEL_IN_LINE ':'
#define DEL_BETWEEN_LINES "-----"
#define DEL_BETWEEN_LINES_OTHER "-----\r"

/**
 * returns the number of words (seperated by a space) in a string
 * @param s the string
 * @return the number of words in s
 */
int numWords (const string &s);

/**
 * receives a string and removes the first ":" from the string
 * @param s the string
 */
void removeDel (string &s)
{
	size_t place = s . find (DEL_IN_LINE);
	if (! s . empty () && s . size () > place)
	{
		s . replace (place , 1 , " ");
	}
};

Reader::Reader (string &fileName)
{
	_reader . open (fileName);
	if (! _reader)
	{
		_validInput = false;
		_reader . close ();
		return;
	}
	_validInput = true;
}

string Reader::readItemFromFile (vector<string> &characteristics)
{
	//clear the previous item's characteristics
	characteristics . clear ();
	_validInput = true;
	string paramName , paramValue , line;
	//read the first line
	getline (_reader , line);

	//while we have not reached a deliminator or the end of the file, keep reading
	while (line != DEL_BETWEEN_LINES && ! endOfFile () && line != DEL_BETWEEN_LINES_OTHER)
	{
		//make a copy of the line read so we don't change it
		string lineCopy = string (line);
		//extract the data from the line we read in paramName in paramValue
		removeDel (lineCopy);
		stringstream stream (lineCopy);
		stream >> paramName >> paramValue;
		//in case the value of the characteristic has more than one word, we'll add the rest
		//of the words
		if (numWords (lineCopy) > 2)
		{
			paramValue = lineCopy . substr (lineCopy . find (paramValue));
		}
		//check if we read an empty line
		if (paramValue . empty ())
		{
			_validInput = false;
			return "";
		}
		//add the value of the parameter (or characteristic of the ikea item)
		characteristics . push_back (paramValue);
		getline (_reader , line);
	}
	//figure out what item we read by the characteristics we read (using the "ItemSpecifier"
	// class).
	string type = _itemFinder . returnType (paramName);
	//check if something went wrong along the way
	if (type . empty ())
	{
		_validInput = false;
		return "";
	}
	return type;
}

/**
 *
 * @return true if the last item read was successful, and false otherwise
 */
bool Reader::isValidInput () const
{
	return _validInput;
}

/**
 *
 * @return true if we have reached the end of the file, and false otherwise
 */
bool Reader::endOfFile ()
{
	return _reader . peek () == EOF;
}

int numWords (const string &s)
{
	int count = 0;
	string temp;
	stringstream stream (s);
	while ((stream >> temp))
	{
		count ++;

	}
	return count;
}
