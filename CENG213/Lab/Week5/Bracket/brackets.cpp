#include "Stack.h"
/*
A bracket is considered to be any one of the following characters: (, ), {, }, [, or ].
Two brackets are considered to be a matched pair if an opening bracket (i.e., (, [, or {) occurs to the left of a 
closing bracket (i.e., ), ], or }) of the exact same type. There are three types of matched pairs of brackets: [], {}, and ().
A matching pair of brackets is not balanced if the set of brackets it encloses are not matched. For example, {[(])} is 
not balanced because the contents in between { and } are not balanced. The pair of square brackets encloses a single, 
unbalanced opening bracket, (, and the pair of parentheses encloses a single, unbalanced closing square bracket, ].
By this logic, we say a sequence of brackets is balanced if it contains no unmatched brackets.
Write a function that accepts a string of brackets and determines whether the sequence of brackets is balanced or not. 
If the string is balanced, return YES. Otherwise, return NO.

Example: 
"{()}[]" -> YES (Balanced)
"{[(])}" -> No (Not Balanced)
*/

bool areBracketsBalanced(string expr) {
    int len = expr.length(), i;
    char currChr, prevElement;
    Stack<char> stack;
    for (i = 0; i < len; i++)
    {
        prevElement = '\0';
        currChr = expr[i];
        if (!stack.isEmpty())
        {
            prevElement = stack.peek();
        }
        if (currChr == '(' || currChr == '{' || currChr == '[')
        {
            stack.push(currChr);
        }
        else
        {
            if (prevElement == '\0')
            {
                cout << "case 1 \n"; 
                return false;
            }
            else
            {
                if (currChr == ')')
                {
                    if (prevElement == '(')
                    {
                        stack.pop();
                    }
                    else
                    {
                        cout << "case 2 \n"; 
                        return false;
                    }
                }
                else if (currChr == '}')
                {
                    if (prevElement == '{')
                    {
                        stack.pop();
                    }
                    else
                    {
                        cout << "case 3 \n"; 
                        return false;
                    }
                }
                else if (currChr == ']')
                {
                    if (prevElement == '[')
                    {
                        stack.pop();
                    }
                    else
                    {
                        cout << "case 4 \n"; 
                        return false;
                    }
                }
            }
        }
    }
    if (!stack.isEmpty())
    {
        cout << "case 5 \n"; 
        return false;
    }
    else
    {
        return true;
    }
}

int main() {
    string expr = "{()}[]";

    if (areBracketsBalanced(expr))
        cout << "Balanced";
    else
        cout << "Not Balanced";

    return 0;
}