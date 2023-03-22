#include <iostream>
#include <string>
#include <vector>
#include "owner.h"

using namespace std;

Owner::Owner()
{
}

Owner::Owner(const string &name, float balance)
{
    this->name = name;
    this->balance = balance;
}

void Owner::print_info()
{
}

string &Owner::get_name()
{
    return name;
}

void Owner::add_property(Property *property)
{
    properties.push_back(property);
}

void Owner::buy(Property *property, Owner *seller)
{
    float value = property->valuate();
    std::vector<Property *>::iterator itr = seller->properties.begin();
    bool has_property = false;
    std::cout << "[BUY] Property: " << property->get_name() << " Value: " << value << "$ " 
    << seller->get_name() << "--->" << this->get_name() << std::endl;
    for (; itr != seller->properties.end(); itr++)
    {
        if (*itr == property)
        {
            has_property = true;
            break;
        }
    }
    if (this->balance < value)
    {
        std::cout << "[ERROR] Unaffordable  property" << std::endl;
    }
    else if (!has_property)
    {
        std::cout << "[ERROR] Transaction  on  unowned  property" << std::endl;
    }
    else
    {
        this->balance -= value;
        seller->balance += value;
        seller->properties.erase(itr);
        property->set_owner(this);
    }
}

void Owner::sell(Property *property, Owner *owner)
{
    float value = property->valuate();
    std::vector<Property *>::iterator itr = this->properties.begin();
    bool has_property = false;
    std::cout << "[SELL] Property: " << property->get_name() << " Value: " << value 
    << "$ " << this->get_name() << "--->" << owner->get_name() << std::endl;
    for (; itr != this->properties.end(); itr++)
    {
        if (*itr == property)
        {
            has_property = true;
            break;
        }
    }
    if (owner->balance < value)
    {
        std::cout << "[ERROR] Unaffordable  property" << std::endl;
    }
    else if (!has_property)
    {
        std::cout << "[ERROR] Transaction  on  unowned  property" << std::endl;
    }
    else
    {
        this->balance += value;
        owner->balance -= value;
        this->properties.erase(itr);
        property->set_owner(owner);
    }
}

void Owner::list_properties()
{
    std::vector<Property *>::iterator itr = properties.begin();
    int i;
    std::cout << "Properties of " << name << ":" << std::endl;
    std::cout << "Balance: " << balance << "$" << std::endl;
    for (i = 1; itr != properties.end(); itr++, i++)
    {
        std::cout << i << ". " << (*itr)->get_name() << std::endl;
    }
}