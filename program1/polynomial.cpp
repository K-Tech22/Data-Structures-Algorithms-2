#include <iostream>
using namespace std;

#include "polynomial.h"

// Operator << ostream
ostream &operator<<(ostream &output, const Polynomial &p)
{
    Polynomial::Term *curr = p.head->next;
    if (curr->coeff != 1)
    {
        output << curr->coeff << "x^" << curr->power;
    }
    else
    {
        output << "x";
    }
    curr = curr->next;

    while (curr != p.head)
    {
        if (curr->coeff == 1)
        {
            if (curr->power > 1 || curr->power < 0)
            {
                output << " + "
                       << "x^" << curr->power;
            }
            else if (curr->power == 1)
            {
                output << " + "
                       << "x";
            }
        }
        else if (curr->coeff > 1)
        {
            if (curr->power > 1 || curr->power < 0)
            {
                output << " + " << curr->coeff << "x^" << curr->power;
            }
            else if (curr->power == 1)
            {
                output << " + " << curr->coeff << "x";
            }
        }
        else if (curr->coeff < 0)
        {
            if (curr->power == 1)
            {
                output << curr->coeff << "x";
            }
            else if (curr->power > 1 || curr->power < 0)
            {
                output << curr->coeff << "x^" << curr->power;
            }
        }
        else if (curr->coeff == 0)
        {
            continue;
        }

        curr = curr->next;
    }
    return output;
}

// Default constructor
Polynomial::Polynomial()
{
    this->size = 0;
    Term *newHead = new Term;
    newHead->coeff = 0.0;
    newHead->power = 0;
    this->head = newHead;
    this->head->next = this->head;
    this->head->prev = this->head;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial &p)
{
    this->head = p.head;
    this->size = p.size;

    if (p.head->next != NULL)
    {

        Term *Prev = this->head;

        Term *pCurr = p.head->next;

        while (pCurr != p.head)
        {

            Term *curr = pCurr;

            Prev->next = curr;
            curr->prev = Prev;

            pCurr = pCurr->next;
            Prev = Prev->next;
        }
    }
}

// Destructor
Polynomial::~Polynomial()
{
    if (head != NULL && head->next != NULL)
    {
        Term *curr = head->next;
        while (curr != head)
        {
            Term *temp = curr->next;
            delete curr;
            curr = temp;
        }
        delete head;
    }
}

// degree: returns the degree of the polynomial
// Preconditions: the polynomial should not be empty and no parameter is required
// Postconditions: returns the highest degree of the polynomial
int Polynomial::degree() const
{
    // Returns -1 if polynomial has no terms
    if (head->next == NULL)
    {
        return -1;
    }
    // Returns first term's power
    return head->next->power;
}

// coefficient: returns the coefficient of the term with the given power
// Preconditions: The term must be in the polynomial and it should not be empty, the power must be an int
// Postconditions: Returns the coefficient if the power is in the polynomial
double Polynomial::coefficient(const int power) const
{
    // If there are terms in the polynomial
    if (head->next != NULL)
    {
        Term *curr = head->next;
        while (curr != head)
        {
            // Returns coefficient if power is found in the polynomial
            if (curr->power == power)
            {
                return curr->coeff;
            }
            curr = curr->next;
        }
    }
    // Returns 0.0 if power is not found in the polynomial
    return 0.0;
}

// changeCoefficient: changes the coefficient of a term in the polynomial or adds the term if power not in polynomial
// Preconditions: newCoefficient should be a double and power must be an int
// Postconditions: inserts the term in the polynomial if power is present otherwise calls insert function with the term whose power is greater
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
    // If it is the first term, term is added after head
    if (size == 0 && newCoefficient != 0)
    {
        return insert(NULL, newCoefficient, power);
    }

    Term *curr = new Term;

    curr = head->next;

    while (curr->next != head)
    {
        // If power is found in the polynomial
        if (curr->power == power)
        {
            if (newCoefficient != 0)
            {
                // Current coefficient is replaced or added
                curr->coeff += newCoefficient;
            }
            else
            {
                // If coefficient is 0, term is removed
                return remove(curr);
            }
            return true;
        }
        // If power is greater than the current term's power, insert function is called
        else if (power > curr->power)
        {
            return insert(curr, newCoefficient, power);
        }
        curr = curr->next;
    }
    // If power does not exist, insert is called
    return insert(NULL, newCoefficient, power);
}

// operator+: returns a new polynomial with the sum of two other
// Preconditions: two polynomials should be present
// Postconditions: sum of two given polynomials
Polynomial Polynomial::operator+(const Polynomial &p) const
{
    Polynomial pX;

    // If there are multiple terms in this->polynomial
    if (this->head->next != NULL)
    {
        Term *curr = this->head->next;

        // Iterates through the list
        while (curr != this->head)
        {
            // Calls change coefficient function
            pX.changeCoefficient(curr->coeff, curr->power);
            curr = curr->next;
        }
    }
    // If there are multiple terms in the other polynomial
    if (p.head->next != NULL)
    {
        Term *pcurr = p.head->next;

        pcurr = p.head->next;

        // Iterates through the list
        while (pcurr != p.head)
        {
            // Calls change coefficient function
            pX.changeCoefficient(pcurr->coeff, pcurr->power);
            pcurr = pcurr->next;
        }
    }
    return pX;
}

// operator-: returns a new polynomial with the difference of two other
// Preconditions: two polynomials should be present
// Postconditions: difference of two given polynomials
Polynomial Polynomial::operator-(const Polynomial &p) const
{
    Polynomial pX;

    // If there are multiple terms in this->polynomial
    if (head->next != NULL)
    {
        Term *curr = head->next;

        // Iterates through the list
        while (curr != head)
        {
            // Calls change coefficient function
            pX.changeCoefficient(curr->coeff, curr->power);
            curr = curr->next;
        }
    }

    // If there are multiple terms in the other polynomial
    if (p.head->next != NULL)
    {
        Term *pCurr = p.head->next;

        // Iterates through the list
        while (pCurr != p.head)
        {
            // Calls change coefficient function with multiplying -1 to find the difference
            pX.changeCoefficient(pCurr->coeff * -1, pCurr->power);
            pCurr = pCurr->next;
        }
    }
    return pX;
}

// operator==: returns true if two polynomials are equal
// Preconditions: two polynomials should be present
// Postconditions: terms of each polynomial should match
bool Polynomial::operator==(const Polynomial &p) const
{
    // If the size is not equal, returns false
    if (this->size != p.size)
    {
        return false;
    }

    Term *pcurr = p.head->next;
    Term *curr = this->head->next;

    // Iterating through two lists at the same time
    while (pcurr != p.head && curr != head)
    {
        // Returns false if the term's coefficients and powers don't match
        if (pcurr->coeff != curr->coeff && pcurr->power != curr->power)
        {
            return false;
        }
        pcurr = pcurr->next;
        curr = curr->next;
    }

    return true;
}

// operator!=: returns true if two polynomials are not equal
// Preconditions: two polynomials should be present
// Postconditions: terms of each polynomial should not match
bool Polynomial::operator!=(const Polynomial &p) const
{
    // If the sizes are different, returns true
    if (this->size != p.size)
    {
        return true;
    }
    Term *pcurr = p.head->next;
    Term *curr = this->head->next;

    // Iterating through the lists at the same time
    while (pcurr != p.head && curr != this->head)
    {
        // If the term's coefficients and powers do not match return true
        if (pcurr->coeff != curr->coeff && pcurr->power != curr->power)
        {
            return true;
        }
        pcurr = pcurr->next;
        curr = curr->next;
    }

    return false;
}

// operator=: returns a new polynomial which is same as the given one
// Preconditions: the polynomial should be present and must have terms
// Postconditions: returns this->polynomial which is same as the parameter
Polynomial &Polynomial::operator=(const Polynomial &p)
{
    this->head = new Term;
    Term *pcurr = p.head->next;

    // Iterating through the list
    while (pcurr != p.head)
    {
        Term *thisT = new Term;
        thisT->coeff = pcurr->coeff;
        thisT->power = pcurr->power;
        // Calls changeCoefficient function with the given coeff & power
        this->changeCoefficient(thisT->coeff, thisT->power);
    }
    return *this;
}

// operator+=: returns this->polynomial which is added with the other polynomial
// Preconditions: two polynomials should be present & other polynomial must be the parameter
// Postconditions: addition of two polynomials
Polynomial &Polynomial::operator+=(const Polynomial &p)
{
    if (p.head->next != NULL)
    {
        Term *pCurr = p.head->next;
        while (pCurr != p.head)
        {
            this->changeCoefficient(pCurr->coeff, pCurr->power);
            pCurr = pCurr->next;
        }
    }
    return *this;
}

// operator-=: returns this->polynomial which is substracted with the other polynomial
// Preconditions: two polynomials should be present & other polynomial must be the parameter
// Postconditions: subtraction of two polynomials
Polynomial &Polynomial::operator-=(const Polynomial &p)
{
    if (p.head->next != NULL)
    {
        Term *pCurr = p.head->next;
        while (pCurr != p.head)
        {
            this->changeCoefficient(pCurr->coeff * -1, pCurr->power);
            pCurr = pCurr->next;
        }
    }
    return *this;
}

// insert: returns true if the term is added before the given term in the parameter successfully
// Preconditions: the term should be given in the parameter, along with a double coefficient and an int power
// Postconditions: adds the term into the polynomial in a sorted order.
bool Polynomial::insert(Term *pos, const double newCoefficient, const int power)
{
    Term *term = new Term;
    term->coeff = newCoefficient;
    term->power = power;

    // returns false if newCofficient is 0
    if (newCoefficient == 0)
    {
        return false;
    }

    // Term is added after head if its the first term
    if (size == 0)
    {
        head->next = term;
        term->prev = head;

        term->next = head;
        head->prev = term;
        // Size incremented
        size++;

        return true;
    }

    Term *curr = head->next;

    Term *pcurr = head;
    // Iterating through the list
    while (curr != head)
    {
        // If power is found
        if (curr->power == power)
        {
            // coefficient is added or replaced
            curr->coeff += newCoefficient;
            return true;
        }
        // If curr is equal to pos, term is added between them
        if (curr == pos)
        {
            pcurr->next = term;
            term->prev = pcurr;

            term->next = pos;
            pos->prev = term;
            // Size incremented
            size++;

            return true;
        }
        // If power is greater than current term's power, term is added before current term
        else if (power > curr->power)
        {
            pcurr->next = term;
            term->prev = pcurr;

            term->next = curr;
            curr->prev = term;
            // Size incremented
            size++;

            return true;
        }
        // If nothing is found and the term next to current term is head, new term is added before head as the last term
        else if (curr->next == head)
        {
            curr->next = term;
            term->prev = curr;

            term->next = head;
            head->prev = term;
            // Size incremented
            size++;

            return true;
        }
        curr = curr->next;
        pcurr = pcurr->next;
    }

    return false;
}

// remove: removes the term from the polynomial
// Preconditions: the term must be present in the polynomial and it should not be the head. The parameter is the term that needs to be removed
// Postconditions: true if term is removed successfully
bool Polynomial::remove(Term *pos)
{
    Term *curr = head->next;
    // Iterating through the polynomial
    while (curr != head)
    {
        // If term is found
        if (curr == pos)
        {
            Term *prevCurr = curr->prev;
            Term *nextCurr = curr->next;
            // prev term is pointed to the term's next term
            prevCurr->next = nextCurr;
            nextCurr->prev = prevCurr;
            // Size decremented
            --size;
            return true;
        }
        curr = curr->next;
    }
    return false;
}