//
// Created by noam on 9/3/18.
//

/**
 * ikea.cpp - a simple, textual, stock handling interface for an IKEA store.
 */

#include "Reader.h"
#include "ItemSpecifier.h"
#include "IkeaStoreItem.h"
#include <limits>
#include <algorithm>
#include <cassert>

#define EXIT 7
#define ID_PLACE 0
#define NAME_PLACE 1
#define QUANTITY_PLACE 2
#define PRICE_PLACE 3
#define CALORIES_PLACE 4
#define WEIGHT_PLACE 4
#define DIMENSIONS_PLACE 4
#define MATERIAL_PLACE 5
#define COLOR_PLACE 6
#define CAPACITY_PLACE 5
#define AUTHOR_PLACE 4
#define YEAR_PLACE 5
#define LENGTH_PLACE 6
#define BAD_USER_COMMAND "Not valid input."
#define BAD_FILE "Could not open file."
#define BAD_COMMANDS_IN_FILE "Please check the file for updating the stock is in the correct "\
"format"
#define FILE_ENTER_MESSAGE "please enter file path: "
#define SEARCH_NAME_MESSAGE "please enter product name: "
#define SEARCH_ID_MESSAGE "please enter catalog id: "
#define DEL "-----"
#define NOT_FOUND "\nItem not found"
#define ITEM_ALREADY_EXISTS "Tried to add an item that already exists in the file"
#define SELL_ID_MESSAGE "please enter catalog number: "
#define SELL_BY_FOOTAGE "Please enter desired quantity: "
#define SELL_BY_UNIT "Please enter number of items: "
#define NOT_AN_PINT_INPUT "Please enter a whole positive number. Returning to Menu."
#define NOT_A_PDOUBLE_INPUT "Please enter a positive number. Returning to Menu."
#define NOT_AN_INT_INPUT "\nNot valid input."
#define INVENTORY "\nNot enough stock to sell."

typedef IkeaStoreItem *Ikeaptr; //useful typedef

/**
 * frees the memory used to house the items
 * @param vec a vector holding the items currently in stock
 */
void freeVector (vector<Ikeaptr> &vec);

/**
 * prints the user interface menu
 */
void printMenu ();

/**
 * checks if a number is a valid chooice number (1-7)
 * @param choice the number to check
 * @return true if the number is in the range, and false otherwise
 */
bool inRange (int choice);

/**
 * checks the user's choice, and calls the appropriate function
 * @param choice the user's choice
 * @param items a vector of current items in the store, to be passed on
 * @return true if the choice is legal and the user request was handles successfully, and false
 * otherwise
 */
bool handleUserInput (int choice , vector<Ikeaptr> &items);

/**
 * asks the user for an id number of an item, and prints the item of the matching number from
 * the catalog. if no such item exists, an error message is printed.
 * @param items a vector containing the items in the store
 */
void printItemByNumber (vector<Ikeaptr> &items);

/**
 * asks the user for a name of an item, and prints all of the item of the same name from
 * the catalog, sorted by their id number. if no such item exists, an error message is printed.
 * @param items a vector containing the items in the store
 */
void printItemByName (vector<Ikeaptr> &items);

/**
 * prints the entire stock of the store by alphabetical order
 * @param items a vector containing all of the items in the store
 */
void printStockByName (vector<Ikeaptr> &items);

/**
 * prints the entire stock of the store, by by numerical order.
 * @param items a vector containing all of the items in the store
 */
void printStockByNumber (vector<Ikeaptr> &items);

/**
 * receives a number from the user of the item we wish to sell and it's amount. Then, removes
 * the items sold from inventory.
 * @param items a vector containing all of the items in the store
 */
void sellItem (vector<Ikeaptr> &items);

/**
 * a comparison function, that orders two items by their id number (used  for sorting)
 * @param first the first item to be compared
 * @param second the second item to be compared
 * @return true if the first item has a smaller id number than the second item and false otherwise
 */
bool orderByNum (const Ikeaptr &first , const Ikeaptr &second);

/**
 * a comparison function, that orders two items lexicographically (used  for sorting)
 * @param first the first item to be compared
 * @param second the second item to be compared
 * @return true if the first item has a lexicographically earlier name than the second item, and
 * false otherwise
 */
bool orderByName (const Ikeaptr &first , const Ikeaptr &second);

/**
 * an internal helper function of "sellItem", that sells an item measured by unit (deals with ints)
 * @param item the item we wish to sell
 * @return true if there is enough stock and the item exists, and false otherwise
 */
bool sellUnit (Ikeaptr &item);

/**
 * an internal helper function of "sellItem", that sells an item measured by meter squared (deals
 * with double values)
 * @param item the item we wish to sell
 * @return true if there is enough stock and the item exists, and false otherwise
 */
bool sellMeter (Ikeaptr &item);

/**
 * receives from the user the name of a file from which we wish to update the stock from, and
 * updates the stock accordingly.
 * @param items a vector holding the inventory of the store, which we will update from the file
 * read
 * @return true if the file reading went smoothly, and no duplicate items were found in the
 * file, and false otherwise
 */
bool addToStock (vector<Ikeaptr> &items);

/**
 * this function calls the corresponding functions that create an item, based on the type of the
 * string "type"
 * @param items a vector containing the current inventory
 * @param params a list of the parameters of the item that was just read from the file
 * @param type the type of item we wish to add
 * @return true if adding the item to the inventory went smoothly, and false otherwise
 */
bool addItemToCatalog (vector<Ikeaptr> &items , vector<string> &params , string &type);

/**
 * constructs a "normal" ikea item from the parameters in "param", and adds it to the catalog
 * @param items a vector of the current inventory
 * @param params the parameters of the new normal item we wish to add
 * @param flag false if item already exists, and we updates the new stock, and true otherwise
 * @return true if the parameters for the type are correct, and the addition to the inventory
 * was successful, and false otherwise.
 */
bool addNormal (vector<Ikeaptr> &items , vector<string> &params , bool &flag);

/**
 * constructs a new ikea furniture item from the parameters in "param", and adds it to the catalog
 * @param items a vector of the current inventory
 * @param params the parameters of the new normal item we wish to add
 * @return true if the parameters for the furniture type are correct, and the addition to the
 * inventory was successful, and false otherwise.
 */
bool addFurniture (vector<Ikeaptr> &items , vector<string> &params);

/**
 * constructs a new art ikea item from the parameters in "param", and adds it to the catalog
 * @param items a vector of the current inventory
 * @param params the parameters of the new normal item we wish to add
 * @return true if the parameters for the art type are correct, and the addition to the inventory
 * was successful, and false otherwise.
 */
bool addArt (vector<Ikeaptr> &items , vector<string> &params);

/**
 * constructs a new kitchen ikea item from the parameters in "param", and adds it to the catalog
 * @param items a vector of the current inventory
 * @param params the parameters of the new normal item we wish to add
 * @return true if the parameters for the kitchen type are correct, and the addition to the
 * inventory was successful, and false otherwise.
 */
bool addKitchen (vector<Ikeaptr> &items , vector<string> &params);

/**
 * constructs a new sweets ikea item from the parameters in "param", and adds it to the catalog
 * @param items a vector of the current inventory
 * @param params the parameters of the new normal item we wish to add
 * @return true if the parameters for the sweets type are correct, and the addition to the
 * inventory was successful, and false otherwise.
 */
bool addSweets (vector<Ikeaptr> &items , vector<string> &params);

/**
 * constructs a new fabric ikea item from the parameters in "param", and adds it to the catalog
 * @param items a vector of the current inventory
 * @param params the parameters of the new normal item we wish to add
 * @return true if the parameters for the fabric type are correct, and the addition to the
 * inventory was successful, and false otherwise.
 */
bool addFabrics (vector<Ikeaptr> &items , vector<string> &params);

/**
 * checks if an item with a certain id and name exists in the inventory
 * @param id the id of an item we wish to search
 * @param name the name of the item we wish to search
 * @param items the inventory of items
 * @return 0 if another item exists with the same id but a different name, 1 if the item exists
 * with both a similar name and id, and 2 if the item doesn't exist
 */
int isInItems (int id , string &name , vector<Ikeaptr> &items);

/**
 * returns the last word in a string
 * @param s the string we wish to retrieve the last word from
 * @return the last word in the string
 */
string lastWordInString (string &s)
{
	//performing an impromptu right trim to the string s
	while (s . back () == ' ' && ! s . empty ())
	{
		s . pop_back ();
	}
	size_t lastSpace = s . find_last_of (' ');
	return s . substr (lastSpace + 1);
}


int main ()
{
	vector<Ikeaptr> items;
	int choice = 0;
	printMenu ();
	cin >> choice;
	while (choice != EXIT)
	{
		if (! inRange (choice))
		{

			cerr << BAD_USER_COMMAND << endl;
			printMenu ();
			//flush the stream
			cin . clear ();
			cin . ignore (numeric_limits<streamsize>::max () , '\n');
			//get a new number
			cin >> choice;
			continue;
		}
		handleUserInput (choice , items);
		printMenu ();
		cin >> choice;
	}
	cout << endl;
	freeVector (items);
	return 0;
}


void printMenu ()
{
	cout << "1. Input stock from file" << endl << "2. Find item by catalog number" << endl\
 << "3. Find item by name" << endl << "4. Print stock by catalog number" << endl\
 << "5. Print stock by name" << endl << "6. Sell item" << endl << "7. Exit" << endl;
}

bool inRange (int choice)
{
	return choice < 8 && choice > 0;
}

bool handleUserInput (int choice , vector<Ikeaptr> &items)
{
	switch (choice)
	{
		case 1:
		{
			return addToStock (items);
		}
		case 2:
		{
			printItemByNumber (items);
			return true;
		}
		case 3:
		{
			printItemByName (items);
			return true;
		}
		case 4:
		{
			printStockByNumber (items);
			return true;
		}
		case 5:
		{
			printStockByName (items);
			return true;
		}
		case 6:
		{
			sellItem (items);
			return true;
		}
		default:
		{
			return true;
		}
	}
}

bool addToStock (vector<Ikeaptr> &items)
{
	cout << FILE_ENTER_MESSAGE << endl;
	string filename;
	cin >> filename;
	Reader reader (filename);
	if (! reader . isValidInput ())
	{
		cerr << BAD_FILE << endl;
		return false;
	}
	vector<string> params;
	string type;
	do
	{
		type = reader . readItemFromFile (params);
		if (! addItemToCatalog (items , params , type))
		{
			cerr << BAD_COMMANDS_IN_FILE << endl;
			return true;
		}
	} while (! reader . endOfFile ());
	return true;
}

void printItemByNumber (vector<Ikeaptr> &items)
{
	cout << SEARCH_ID_MESSAGE;
	int id = 0;
	if (! (cin >> id))
	{
		//flush the stream
		cin . clear ();
		cin . ignore (numeric_limits<streamsize>::max () , '\n');
		cerr << NOT_AN_INT_INPUT << endl;
		cout << endl;
		//return back to menu
		return;
	}
	for (const Ikeaptr &iter:items)
	{
		if (iter -> getIdNum () == id)
		{
			iter -> printItem ();
			cout << DEL << endl << endl;
			return;
		}
	}
	cerr << NOT_FOUND << endl;
	cout << endl;
}

void printItemByName (vector<Ikeaptr> &items)
{
	bool found = false;
	cout << SEARCH_NAME_MESSAGE;
	string name;
	//flush the stream
	cin . clear ();
	cin . ignore (numeric_limits<streamsize>::max () , '\n');
	//get the name
	getline (cin , name);
	stable_sort (items . begin () , items . end () , orderByNum);
	for (Ikeaptr &iter:items)
	{
		if ((*iter) . getName () == name || (*iter) . getName () == name + " ")
		{
			iter -> printItem ();
			cout << DEL << endl;
			found = true;
		}
	}
	if (! found)
	{
		cerr << NOT_FOUND << endl;
		cout << endl;
	}
}

void printStockByName (vector<Ikeaptr> &items)
{
	stable_sort (items . begin () , items . end () , orderByNum);
	stable_sort (items . begin () , items . end () , orderByName);
	for (Ikeaptr &item:items)
	{
		item -> printItem ();
		cout << DEL << endl;
	}
	cout << endl;
}

void printStockByNumber (vector<Ikeaptr> &items)
{
	stable_sort (items . begin () , items . end () , orderByNum);
	for (Ikeaptr &item:items)
	{
		item -> printItem ();
		cout << DEL << endl;
	}
	cout << endl;
}

void sellItem (vector<Ikeaptr> &items)
{
	int id = 0;
	cout << SELL_ID_MESSAGE;
	string amount;
	if (! (cin >> id))
	{
		//flush the stream
		cin . clear ();
		cin . ignore (numeric_limits<streamsize>::max () , '\n');
		cerr << NOT_AN_INT_INPUT << endl;
		cout << endl;
		//return back to menu
		return;
	}
	for (Ikeaptr &item:items)
	{
		if (item -> getIdNum () == id)
		{
			if (item -> getMu () == UNIT)
			{
				if (sellUnit (item))
				{
					item -> printItem ();
					cout << DEL << endl;
				}

				return;
			}
			else
			{
				if (sellMeter (item))
				{
					item -> printItem ();
					cout << DEL << endl;
				}
				return;
			}
		}
	}
	cerr << NOT_FOUND << endl;
	cout << endl;
}

bool orderByNum (const Ikeaptr &first , const Ikeaptr &second)
{
	return first -> getIdNum () < second -> getIdNum ();
}

bool orderByName (const Ikeaptr &first , const Ikeaptr &second)
{
	return first -> getName () < second -> getName ();
}

bool sellUnit (Ikeaptr &item)
{
	cout << SELL_BY_UNIT;
	int unit = 0;
	if (! (cin >> unit))
	{
		//flush the stream
		cin . clear ();
		cin . ignore (numeric_limits<streamsize>::max () , '\n');
		cerr << NOT_AN_PINT_INPUT << endl;
		//return back to menu
		return false;
	}
	if (unit < 0)
	{
		cerr << NOT_AN_PINT_INPUT << endl;
		//return back to menu
		return false;
	}
	if (item -> getQuantity () < unit)
	{
		cout << endl << endl;
		cerr << INVENTORY << endl;
		//return back to menu
		return false;
	}
	item -> setQuantity (item -> getQuantity () - unit);
	return true;
}

bool sellMeter (Ikeaptr &item)
{
	cout << SELL_BY_FOOTAGE;
	double metersq = 0;
	if (! (cin >> metersq))
	{
		//flush the stream
		cin . clear ();
		cin . ignore (numeric_limits<streamsize>::max () , '\n');
		cerr << NOT_A_PDOUBLE_INPUT << endl;
		//return back to menu
		return false;
	}
	if (metersq < 0)
	{
		cerr << NOT_A_PDOUBLE_INPUT << endl;
		//return back to menu
		return false;
	}
	if (item -> getQuantity () < metersq)
	{
		cout << endl << endl;
		cerr << INVENTORY << endl;
		//return back to menu
		return false;
	}
	item -> setQuantity (item -> getQuantity () - metersq);
	return true;
}

bool addItemToCatalog (vector<Ikeaptr> &items , vector<string> &params , string &type)
{
	if (type == "Normal")
	{
		bool alreadyExists;
		return addNormal (items , params , alreadyExists);
	}
	if (type == "Art")
	{
		return addArt (items , params);
	}
	if (type == "Furniture")
	{
		return addFurniture (items , params);
	}
	if (type == "Sweets")
	{
		return addSweets (items , params);
	}
	if (type == "Fabrics")
	{
		return addFabrics (items , params);
	}
	if (type == "Kitchen")
	{
		return addKitchen (items , params);
	}
	return false;
}

int isInItems (int id , string &name , vector<Ikeaptr> &items)
{
	for (Ikeaptr &item:items)
	{
		if (item -> getIdNum () == id && item -> getName () != name)
		{
			//this means the item number exists in the catalogue but under a different name!
			//we will return an error later
			return 0;
		}
		if (item -> getIdNum () == id && item -> getName () == name)
		{
			//the item already exists in the catalogue, and we should just increase the quantity
			return 1;
		}
	}
	//we have not found the item in the catalog, we'll create a new entry
	return 2;
}

bool addNormal (vector<Ikeaptr> &items , vector<string> &params , bool &flag)
{
	flag = true;
	int id;
	double quantity = 0 , price = 0;
	string name = params . at (NAME_PLACE);
	if (! IkeaStoreItem::isInt (params . at (ID_PLACE)))
	{
		cerr << BAD_COMMANDS_IN_FILE << endl;
		return false;
	}
	id = stoi (params . at (ID_PLACE));
	if (isInItems (id , name , items) == 0)
	{
		cerr << ITEM_ALREADY_EXISTS << endl;
		return false;
	}
	if (! IkeaStoreItem::isDouble (params . at (QUANTITY_PLACE)) ||
	    ! IkeaStoreItem::isDouble (params . at (PRICE_PLACE)))
	{
		cerr << BAD_COMMANDS_IN_FILE << endl;
		return false;
	}
	quantity = stod (params . at (QUANTITY_PLACE));
	price = stod (params . at (PRICE_PLACE));
	if (isInItems (id , name , items) == 1)
	{
		for (Ikeaptr item:items)
		{
			if (item -> getIdNum () == id && item -> getName () == name)
			{
				item -> setQuantity (item -> getQuantity () + quantity);
				flag = false;
				return true;
			}
		}
	}
	assert(isInItems (id , name , items) == 2);
	items . push_back (new IkeaStoreItem (id , name , price , quantity));
	return true;
}

bool addFurniture (vector<Ikeaptr> &items , vector<string> &params)
{
	string dimensions , color , material;
	bool alreadyExists;
	if (! addNormal (items , params , alreadyExists))
	{
		return false;
	}
	//if the item already exists and we successfully added it to stock, we can exit.
	if (! alreadyExists)
	{
		return true;
	}
	dimensions = params . at (DIMENSIONS_PLACE);
	color = params . at (COLOR_PLACE);
	material = params . at (MATERIAL_PLACE);
	Ikeaptr toInsert = items . back ();
	items . pop_back ();
	items . emplace_back (new Furniture (toInsert -> getIdNum () , toInsert -> getName () ,
	                                     toInsert -> getPricePerUnit () ,
	                                     toInsert -> getQuantity () , dimensions , color ,
	                                     material));
	delete (toInsert);
	return true;
}

bool addArt (vector<Ikeaptr> &items , vector<string> &params)
{
	int yearOfPublication , length;
	string author = params . at (AUTHOR_PLACE);
	bool alreadyExists;
	if (! addNormal (items , params , alreadyExists))
	{
		return false;
	}
	if (! alreadyExists)
	{
		return true;
	}
	string tempYear = params . at (YEAR_PLACE);
	tempYear = lastWordInString (tempYear);
	if (! IkeaStoreItem::isInt (tempYear) || ! IkeaStoreItem::isInt (params . at (LENGTH_PLACE)))
	{
		cerr << BAD_COMMANDS_IN_FILE << endl;
		return false;
	}
	yearOfPublication = stoi (tempYear);
	length = stoi (params . at (LENGTH_PLACE));
	Ikeaptr toInsert = items . back ();
	items . pop_back ();
	items . emplace_back (
			new Art (toInsert -> getIdNum () , toInsert -> getName () , toInsert -> getPricePerUnit
					         () ,
			         toInsert -> getQuantity () , author , yearOfPublication , length));
	delete (toInsert);
	return true;

}

bool addKitchen (vector<Ikeaptr> &items , vector<string> &params)
{
	double capacity;
	string dimensions = params . at (DIMENSIONS_PLACE);
	bool alreadyExists;
	if (! addNormal (items , params , alreadyExists))
	{
		return false;
	}
	if (! alreadyExists)
	{
		return true;
	}
	if (! IkeaStoreItem::isDouble (params . at (CAPACITY_PLACE)))
	{
		cerr << BAD_COMMANDS_IN_FILE << endl;
		return false;
	}
	capacity = stod (params . at (CAPACITY_PLACE));
	Ikeaptr toInsert = items . back ();
	items . pop_back ();
	items . push_back (new Kitchen (toInsert -> getIdNum () , toInsert -> getName () , toInsert ->
			                                getPricePerUnit () ,
	                                toInsert -> getQuantity () , dimensions , capacity));
	delete (toInsert);
	return true;

}

bool addSweets (vector<Ikeaptr> &items , vector<string> &params)
{
	double calories;
	bool alreadyExists;
	if (! addNormal (items , params , alreadyExists))
	{
		return false;
	}
	if (! alreadyExists)
	{
		return true;
	}
	if (! IkeaStoreItem::isDouble (params . at (CALORIES_PLACE)))
	{
		cerr << BAD_COMMANDS_IN_FILE << endl;
		return false;
	}
	calories = stod (params . at (CALORIES_PLACE));
	Ikeaptr toInsert = items . back ();
	items . pop_back ();
	items . emplace_back (
			new Sweets (toInsert -> getIdNum () , toInsert -> getName () , toInsert ->
					            getPricePerUnit () ,
			            toInsert
					            -> getQuantity () , calories));
	delete (toInsert);
	return true;
}

bool addFabrics (vector<Ikeaptr> &items , vector<string> &params)
{
	double weight;
	bool alreadyExists;
	if (! addNormal (items , params , alreadyExists))
	{
		return false;
	}
	if (! alreadyExists)
	{
		return true;
	}
	if (! IkeaStoreItem::isDouble (params . at (WEIGHT_PLACE)))
	{
		cerr << BAD_COMMANDS_IN_FILE << endl;
		return false;
	}
	weight = stod (params . at (WEIGHT_PLACE));
	Ikeaptr toInsert = items . back ();
	items . pop_back ();
	items . emplace_back (
			new Fabrics (toInsert -> getIdNum () , toInsert -> getName () , toInsert ->
					getPricePerUnit
					() , toInsert -> getQuantity () , weight));
	delete (toInsert);
	return true;
}

void freeVector (vector<Ikeaptr> &vec)
{
	for (Ikeaptr ptr:vec)
	{
		delete (ptr);
	}
}
