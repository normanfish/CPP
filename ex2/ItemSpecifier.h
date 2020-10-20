//
// Created by noam on 9/2/18.
//

#ifndef EX2_ITEMSPECIFIER_H
#define EX2_ITEMSPECIFIER_H

#include <string>

#define NUM_TYPES 6

using namespace std;

/**
 * ItemSpecifier class - contains all the types of Items available for sale, and can return the
 * name of the item based on a list of characteristics/parameters
 */
class ItemSpecifier
{
private:
	//an array containing the defining and unique characteristic of each item sold, so we know
	// how to dynamically read an item from the input and return its type
	string _allTypes[NUM_TYPES];
public:
	/**
	 * class c'tor
	 */
	ItemSpecifier ();

	/**
	 * returns the type of item based on the characteristic received (simply checks the internal
	 * "alltypes" array).
	 * @param characteristic - the characteristic of the item we wish to identify
	 * @return the name of the item based on it's corresponding characteristic, and if none were
	 * found,, and empty string.
	 */
	string returnType (string characteristic) const;
};


#endif //EX2_ITEMSPECIFIER_H
