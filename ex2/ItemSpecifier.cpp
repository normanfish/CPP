//
// Created by noam on 9/2/18.
//

#include "ItemSpecifier.h"

/**
 * ItemSpecifier class - Implementation
 */
static string allTypesInArray[NUM_TYPES] = {"Normal" , "Art" , "Sweets" , "Fabrics" , "Furniture" ,
                                            "Kitchen"};

enum Item :
		int
{
	Normal = 0 ,
	Art ,
	Sweets ,
	Fabrics ,
	Furniture ,
	Kitchen
};


ItemSpecifier::ItemSpecifier ()
{
	_allTypes[Normal] = "Price";
	_allTypes[Art] = "Length";
	_allTypes[Sweets] = "Calories";
	_allTypes[Fabrics] = "Weight";
	_allTypes[Furniture] = "Color";
	_allTypes[Kitchen] = "Capacity";
}

string ItemSpecifier::returnType (string characteristic) const
{
	for (int i = 0; i < NUM_TYPES; i ++)
	{
		if (characteristic == _allTypes[i])
		{
			return allTypesInArray[i];
		}
	}
	return "";
}
