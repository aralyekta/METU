#include <iostream>
#include "rational.hpp"

// Default (zero-argument) constructor
Rational::Rational()
{
    numer = denom = 0;
}

// Two argument constructor
Rational::Rational(int num, int den)
{
    numer = num;
    denom = den;
}

void Rational::setNumerator(int num)
{
    numer = num;
}

int Rational::getNumerator()
{
    return numer;
}

void Rational::setDenominator(int den)
{
    denom = den;
}

int Rational::getDenominator()
{
    return denom;
}

void Rational::print()
{
    std::cout << ((float)numer / denom) << std::endl;
}

// Returns a + b
Rational Rational::add(Rational rhs)
{
    Rational result;
    int denom1 = denom, denom2 = rhs.getDenominator();
    int numer1 = numer, numer2 = rhs.getNumerator();
    int gcd_of_two, min_num;
    if (denom1 == denom2)
    {
        result.setNumerator(numer1 + numer2);
        result.setDenominator(denom);
    }
    else
    {
        gcd_of_two = gcd(denom1, denom2);
        if (gcd_of_two == 1)
        {
            result.setNumerator(denom2 * numer1 + denom1 * numer2);
            result.setDenominator(denom1 * denom2);
        }
        else
        {
            min_num = (denom1<denom2?denom1:denom2);
            if (min_num == denom1)
            {
                result.setNumerator(numer2 + (denom2/gcd_of_two)*numer1);
                result.setDenominator(denom2);
            }
            else
            {
                result.setNumerator(numer1 + (denom1/gcd_of_two) * numer2);
                result.setDenominator(denom1);
            }
        }
    }
    
    /* TO-DO: fill add */
    
    // Simplify the result if possible. Note that we
    // are not passing "result" as an argument to
    // "simplify". Instead we are calling the "simplify"
    // function of the "result" object.
    result.simplify();
    return result;
}

// Returns a * b
Rational Rational::multiply(Rational rhs)
{
    Rational result;
    /* TO-DO: fill multiply */
    result.setNumerator(numer * rhs.getNumerator());
    result.setDenominator(denom * rhs.getDenominator());
    // Simplify the result if possible.
    result.simplify();
    return result;
}

void Rational::simplify()
{
    int gcd_of_two;
    gcd_of_two = gcd(numer, denom);
    numer /= gcd_of_two;
    denom /= gcd_of_two;
}

int Rational::gcd(int a, int b)
{
    int c;

    if(a<0)
        a = a * -1;
    if(b<0)
        b = b * -1;

    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}

int main()
{
    std::cout << "Hello Rational!" << std::endl;
    
    Rational a(1, 3); // initialized by the 2-argument constructor
    Rational b(1, 3); // initialized by the 2-argument constructor
    Rational e(1, 12);
    Rational d(1, 6);
    Rational h(1, 2);
    Rational c;       // initialized by the 0-argument constructor
    Rational f;
    Rational g;

    c = a.add(b);
    f = e.add(d);
    g = a.add(h);
    c.print();
    f.print();
    g.print();
    return 0;
}
