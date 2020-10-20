//
// Created by noam on 9/2/18.
//

#include "IkeaStoreItem.h"
/**
 * IkeaStoreItem class implementation
 */
/**
 * splits a string (holding the dimensions of an item) into 3 separate words (the x,y and z axis)
 * and stores them in an array
 * @param s the string we wish to extract from the dimensions
 * @param arr the array in which we will store the dimensions
 */
void stringSplit (string &s , string arr[3])
{
	stringstream stream (s);
	string buffer;
	int i = 0;
	while (stream >> buffer)
	{
		arr[i] = buffer;
		i ++;
	}
}

int IkeaStoreItem::getIdNum () const
{
	return _idNum;
}

IkeaStoreItem::IkeaStoreItem (
		int idNum , const string &name , double pricePerUnit , double quantity)
		: _idNum (idNum) , _name (name) , _pricePerUnit (pricePerUnit) , _quantity (quantity)
{
	_mu = UNIT;
}

double IkeaStoreItem::getQuantity () const
{
	return _quantity;
}

void IkeaStoreItem::setQuantity (double quantity)
{
	_quantity = quantity;
}


void IkeaStoreItem::printItem ()
{

	cout << "Item: " << _idNum << endl << "Name: " << _name << endl << "Quantity: "
	     << _quantity << endl << "Price: " << _pricePerUnit << endl;
}

UnitMeasurement IkeaStoreItem::getMu () const
{
	return _mu;
}

const string &IkeaStoreItem::getName () const
{
	return _name;
}

double IkeaStoreItem::getPricePerUnit () const
{
	return _pricePerUnit;
}

IkeaStoreItem::~IkeaStoreItem () = default;


Fabrics::Fabrics (
		int idNum , const string &name , double pricePerUnit , double quantity , double weight)
		: IkeaStoreItem (idNum , name , pricePerUnit , quantity) , _weight (weight)
{}


void Fabrics::printItem ()
{
	cout << "Item: " << _idNum << endl << "Name: " << _name << endl
	     << fixed << setprecision (2) << "Quantity: "
	     << _quantity << endl << "Price: " << _pricePerUnit << endl <<
	     "Weight: " << _weight
	     << endl;
}


Sweets::Sweets (
		int idNum , const string &name , double pricePerUnit , double quantity , double calories)
		: IkeaStoreItem (idNum , name , pricePerUnit , quantity) , _calories (calories)
{
	_mu = METERSQ;
}


void Sweets::printItem ()
{
	cout << "Item: " << _idNum << endl << "Name: " << _name << fixed << setprecision (2) << endl <<
	     "Quantity: "
	     << _quantity << endl << "Price: " << _pricePerUnit << endl
	     << "Calories: " << _calories
	     << endl;
}


void Furniture::printItem ()
{
	string temp[3];
	stringSplit (_dimensions , temp);
	cout << "Item: " << _idNum << endl << "Name: " << _name << endl << "Quantity: "
	     << (int) _quantity << endl << fixed << setprecision (2) << "Price: " << _pricePerUnit <<
	     endl
	     << "Dimensions: " <<
	     stod (temp[0]) << " " << stod (temp[1]) << " " << stod (temp[2])
	     << endl << "Material: " <<
	     _material << endl << "Color: " << _color << endl;
}

Furniture::Furniture (
		int idNum , const string &name , double pricePerUnit , double quantity ,
		const string &dimensions , const string &color , const string &material)
		: IkeaStoreItem (idNum , name , pricePerUnit , quantity) , _dimensions (dimensions) ,
		  _color (color) , _material (material)
{
	_mu = UNIT;
}


void Kitchen::printItem ()
{
	string temp[3];
	stringSplit (_dimensions , temp);
	cout << "Item: " << _idNum << endl << "Name: " << _name << endl << "Quantity: "
	     << (int) _quantity << endl << fixed << setprecision (2) << "Price: " << _pricePerUnit
	     << endl
	     << "Dimensions: " <<
	     stod (temp[0]) << " " << stod (temp[1]) << " " << stod (temp[2]) << endl << "Capacity: "
	     << _capacity << endl;
}

Kitchen::Kitchen (
		int idNum , const string &name , double pricePerUnit , double quantity ,
		const string &dimensions , double capacity) : IkeaStoreItem (idNum , name , pricePerUnit ,
                                                                     quantity) ,
                                                      _dimensions (dimensions) ,
                                                      _capacity (capacity)
{
	_mu = UNIT;
}


Art::Art (
		int idNum , const string &name , double pricePerUnit , double quantity ,
		const string &author ,
		int yearOfPublication , int length) : IkeaStoreItem (idNum , name , pricePerUnit ,
                                                             quantity) , _author (author) ,
                                              _yearOfPublication (yearOfPublication) ,
                                              _length (length)
{
	_mu = UNIT;
}


void Art::printItem ()
{
	cout << "Item: " << _idNum << endl << "Name: " << _name << endl << "Quantity: "
	     << (int) _quantity << endl << fixed << setprecision (2) << "Price: " << _pricePerUnit <<
	     endl << "Author: " << _author << fixed << setprecision (0)
	     << endl << "Year of publication: " << _yearOfPublication << endl << "Length: " << _length
	     << endl;
}