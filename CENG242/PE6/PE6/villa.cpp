#include <iostream>
#include "villa.h"
#include "owner.h"

using namespace std;

Villa::Villa(const string &property_name, int area, Owner *owner, int number_of_floors, bool having_garden)
{
    this->property_name = property_name;
    this->area = area;
    this->owner = owner;
    this->number_of_floors = number_of_floors;
    this->having_garden = having_garden;
    if (owner)
        owner->add_property(this);
}

float Villa::valuate()
{
    float value = area * 10 * number_of_floors;
    if (having_garden)
        value *= 2;
    return value;
}