/** CS515 Lab 2
File: myfun.cpp
Name: Biao Zhang
Section: 01
Date: 9/18/2020
Collaboration Declaration:
Lab Partner: None
Collaboration: None
*/

#include <iostream>
#include <cstdlib>
#include <ctype.h>
using namespace std;

/*  Interprets an integer value in a byte string pointed to by str.
    Function discards any whitespace characters until first non-whitespace
    character is found. Then it takes as many characters as possible to
    form a valid integer number representation and converts them to integer value.
    The valid integer value consists of the following parts:
        (optional) plus or minus sign
        numeric digits
 
    Parameters
        str	 -	 pointer to the null-terminated char string to be interpreted 
    
    Return value: Integer value corresponding to the contents of str on success. 
        If the converted value falls out of range of corresponding return type, 
        the return value is undefined. ???
        If no conversion can be performed, 0 is returned.
 
*/

int myatoi(const char * ptr) {
    char prevchar = ' ';
    char currchar = ptr[0];
    bool ispositive = true;
    int result = 0;
    int i = 0;

    while(currchar != '\0'){

        if(isspace(currchar) && isspace(prevchar)) {
            prevchar = ptr[i];
            ++i;
            currchar = ptr[i];
            continue;
        }

        if((currchar == '+' || currchar == '-' || isdigit(currchar))
          && isspace(prevchar)) {
            if(currchar == '-')
                ispositive = false;
            else if(currchar == '+')
                ispositive = true;
            else
                result = currchar - '0';
        } else if (isdigit(currchar) && (prevchar == '+' || prevchar == '-'))
            result = currchar - '0';
        else if (isdigit(currchar) && isdigit(prevchar))
            result = result * 10 + currchar - '0';
        else
            break;

        prevchar = ptr[i];
        ++i;
        currchar = ptr[i];
    }

    if (!ispositive)
        result = result * (-1);

    return result;
} 


// DO NOT ADD MAIN() FUNCTION IN THIS FILE