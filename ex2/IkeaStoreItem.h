//
// Created by noam on 9/2/18.
//

#ifndef EX2_IKEASTOREITEM_H
#define EX2_IKEASTOREITEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include "ItemSpecifier.h"

/**
 * the Master class of all the items in the store
 */

using namespace std;

/**
 * an enum that holds whether a certain items measuring unit is by unit or by meter square.
 */
enum UnitMeasurement :
		int
{
	UNIT = 0 ,
	METERSQ
};

/**
 * The base Ikea Store item class, from which all other derive from.
 */
class IkeaStoreItem
{
public:

	/**
	 * a static function, that checks a string and returns if it holds and int or not
	 * @param s the string to check
	 * @return true if the string only holds digits, and false otherwise
	 */
	static bool isInt (string &s)
	{
		for (char c:s)
		{
			if (! isdigit (c))
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * a static function, that checks a string and returns if it holds a double or not
	 * @param s the string to check
	 * @return true if the string only holds digits and at most one period, and false otherwise.
	 */
	static bool isDouble (string &s)
	{
		int pointCounter = 0;
		for (char c:s)
		{
			if (c == '.')
			{
				pointCounter ++;
				continue;
			}
			if (! isdigit (c))
			{
				return false;
			}
		}
		return pointCounter < 2;
	}

	/**
	 *
	 * @return the id number of the item
	 */
	int getIdNum () const;

	/**
	 *
	 * @return the name of the item
	 */
	const string &getName () const;

	/**
	 *
	 * @return the item's price
	 */
	double getPricePerUnit () const;

	/**
	 * class c'tor
	 * @param idNum the id number
	 * @param name the item's name
	 * @param pricePerUnit the item's price
	 * @param quantity the quantity in stock
	 */
	IkeaStoreItem (int idNum , const string &name , double pricePerUnit , double quantity);

	/**
	 *
	 * @return the quantity currently in stock
	 */
	double getQuantity () const;

	/**
	 * sets the quantity
	 * @param quantity the new quantity
	 */
	void setQuantity (double quantity);

	/**
	 * the "==" operator
	 * @param other the other ikea item to compare to
	 * @return true if the items' name AND id number (both!) match
	 */
	bool operator== (IkeaStoreItem &other)
	{
		return (_idNum == other . _idNum && _name == other . _name);
	}

	/**
	 * a virtual function that is mean to be overriden by each particular item, that prints the
	 * items
	 */
	virtual void printItem ();

	/**
	 * class d'tor
	 */
	virtual ~IkeaStoreItem ();

	/**
	 *
	 * @return the item's measuring unit (UNIT or METERSQ)
	 */
	UnitMeasurement getMu () const;

	//class variables
protected:
	int _idNum;
	string _name;
	double _pricePerUnit;
	double _quantity;
	UnitMeasurement _mu;
};

/**
 * Fabric item
 */
class Fabrics :
		public IkeaStoreItem
{
public:
	/**
	 * class c'tor
	 * @param idNum id number
	 * @param name name
	 * @param pricePerUnit price
	 * @param quantity quantity
	 * @param weight weight
	 */
	Fabrics (
			int idNum , const string &name , double pricePerUnit , double quantity ,
			double weight);

	void printItem () override;

protected:
	double _weight; // weight of the fabric
};

/**
 * Sweets and Candy Items
 */
class Sweets :
		public IkeaStoreItem
{
public:
	/**
	 * class c'tor
	 * @param idNum id number
	 * @param name name
	 * @param pricePerUnit price
	 * @param quantity quantity in stock
	 * @param calories calories
	 */
	Sweets (
			int idNum , const string &name , double pricePerUnit , double quantity ,
			double calories);

	void printItem () override;

protected:
	double _calories; // the calories in the sweets (oh no!)
};

/**
 * Furniture item
 */
class Furniture :
		public IkeaStoreItem
{
public:


	void printItem () override;

	/**
	 * class c'tor
	 * @param idNum is number
	 * @param name name
	 * @param pricePerUnit price
	 * @param quantity quantity in stock
	 * @param dimensions dimensions of the furniture
	 * @param color color
	 * @param material material made of
	 */
	Furniture (
			int idNum , const string &name , double pricePerUnit , double quantity ,
			const string &dimensions , const string &color , const string &material);

protected:
	string _dimensions; // dimensions of the furniture
	string _color; // color
	string _material; // material made out of
};

/**
 * Kitchenware
 */
class Kitchen :
		public IkeaStoreItem
{
public:
	/**
	 * clas c'tor
	 * @param idNum id number
	 * @param name name
	 * @param pricePerUnit price
	 * @param quantity quantity
	 * @param dimensions the dimensions
	 * @param capacity capacity of the item
	 */
	Kitchen (
			int idNum , const string &name , double pricePerUnit , double quantity ,
			const string &dimensions , double capacity);


	void printItem () override;

protected:
	string _dimensions;
	double _capacity;

};

/**
 * Art
 */
class Art :
		public IkeaStoreItem
{

public:
	/**
	 * class c'tor
	 * @param idNum id number
	 * @param name name
	 * @param pricePerUnit price
	 * @param quantity quantity in store
	 * @param author the author
	 * @param yearOfPublication year of publication
	 * @param length length
	 */
	Art (
			int idNum , const string &name , double pricePerUnit , double quantity ,
			const string &author , int yearOfPublication , int length);


	void printItem () override;

protected:
	string _author;
	int _yearOfPublication;
	int _length;


};

#endif //EX2_IKEASTOREITEM_H
