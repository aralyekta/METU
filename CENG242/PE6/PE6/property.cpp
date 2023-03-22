#include <iostream>
#include "property.h"
#include "owner.h"

using namespace std;

Property::Property()
{
}

Property::Property(const string &property_name, int area, Owner *owner)
{
    this->property_name = property_name;
    this->area = area;
    this->owner = owner;
    if (owner)
        owner->add_property(this);
}

void Property::set_owner(Owner *owner)
{
    this->owner = owner;
    owner->add_property(this);
}

float Property::valuate()
{
    return 0;
}

string &Property::get_name()
{
    return property_name;
}

void Property::print_info()
{
    if (owner)
    {
        std::cout << property_name << " (" << area << " m2) Owner: " << owner->get_name() << std::endl; 
    }
    else
    {
        std::cout << property_name << " (" << area << " m2) Owner: No owner" << std::endl;
    }
}