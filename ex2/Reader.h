//
// Created by noam on 9/2/18.
//
#ifndef EX2_READER_H
#define EX2_READER_H


#include <fstream>
#include <iostream>
#include <vector>
#include "ItemSpecifier.h"

using namespace std;

/**
 * Reader class - handles reading a file for updating the stock
 */
class Reader
{
private:
	ifstream _reader; // the input reader
	/* a flag denoting if the contents read from the files we according to the format specified
	 * */
	bool _validInput;
	ItemSpecifier _itemFinder; // an item of type ItemFinder that contains the different items
	// for sale
public:
	/**
	 * class c'tor - receives the file's name we wish to read and gets the reader reader
	 * @param fileName the file we wish to read
	 */
	Reader (string &fileName);

	/**
	 * reads one item from the file, according to the specified format (from the first row
	 * of the new item till the deliminator "-----"
	 * @param characteristics a vector which will contain the characteristics of the item we are
	 * about to read, (such as "weight" and "calories"). The function changes the vector
	 * to hold the characteristics of the item just read
	 * @return the name of the item we read, according to it's characteristics, and an empty
	 * string in case the item read does not fit any of the known input formats
	 */
	string readItemFromFile (vector<string> &characteristics);

	/**
	 * checks if the last item we read completed in a successful read
	 * @return true if the last item was read successfully and false otherwise
	 */
	bool isValidInput () const;

	/**
	 * checks if we have reached the end of the file
	 * @return true if we have reached the end of the file, and false otherwise
	 */
	bool endOfFile ();
};


#endif //EX2_READER_H
