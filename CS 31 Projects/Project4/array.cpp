#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

//adds a particular string to a aprticular element in the array "a[]"
//and returns that array element's index
int appendToAll(string a[], int n, string value) {

    //if n is negative, then return -1
    if (n < 0) {
        return -1;
    }
    
    //iterate through the array and add the string variable value to it
    for (int i = 0; i < n; ++i) {
        a[i] += value;
    }

    return n;
}


//returns the position of the element that matches the string target
//otherwise it returns -1
int lookup(const string a[], int n, string target) {
    
    //iterate through the array
    for (int i = 0; i < n; ++i) {
    
        if (a[i] == target) { // if an element in the array equals the target string
            return i;         //then, return the element's number (i)
        }
    
    }

    return -1; //if target is not found, then return -1
}

//returns the index of the largest string in terms of alphabetical order
int positionOfMax(const string a[], int n) {
    
    if (n <= 0 ) {
        return -1;
    }
    
    string maxString = a[0]; //set a string equal to the first element to use later
    int maxStringPosition = 0; //initialize position that we will return later
    
    for (int i = 0; i < n; ++i) {
        if (a[i] > maxString) {
            maxString = a[i]; //set string equal to the element that is greater than the maxString from before
            maxStringPosition = i; //set position equal to the index of the element that is being iterated through
        }
    }
    
    return maxStringPosition;
}

//takes all elements to the left of the a[pos] and moves them to the left
//puts a[pos] back into its original position after
//returns pos
int rotateLeft(string a[], int n, int pos) {
    
    //n and pos cannot be negative and n must be larger than p
    //also n cannot be 0
    if (n == 0 || pos < 0 || n < 0 || pos >= n) {
        return -1;
    }
    
    string tempString = a[pos]; //sets temporary string to hold a[pos] before the for loop
    for (int i = pos; i < n - 1; ++i) {
        a[i] = a[i+1];
    }
    
    a[n-1] = tempString; //make the last element in the original array = tempString
        
    return pos;
    
}

//counts the number of consecutive sequences with 1 or more identical items
//and returns that number back
int countRuns(const string a[], int n) {

    if (n < 0) {
        return -1;
        
    } else if (n == 0) {
        return 0;
    }

    string temporaryString = a[0]; //set temporaryString equal to the first element
    int count = 1; //the count must be at least 1 for a valid array
    
    for (int i = 1; i < n; ++i) {
    
        if (a[i] == temporaryString) {
            continue; //do not increment count if the element being iterated through in the array is equal to temporary string
        }
        
        ++count;
        temporaryString = a[i]; //reset temporaryString to the element being iterated through if it is not equal to the previous temporary string
        
    }
    return count;
    
}

//reverse the prder of the array's elements and return n
int flip(string a[], int n) {

    if (n < 0) {
        return -1;
    }

    string tempVal;
    
    for (int i = 0; i < n/2; ++i) { //iterate through only half the array
        tempVal = a[i]; //temporary variable set to first half of the array's elements
        a[i] = a[n - i - 1];
        a[n - 1 - i] = tempVal; //set second half of the array's elements = temporary variable
    }
    
    return n;

}

//return position of corresponding elements in a1 and a2 that are not equal
//if arrays are equal up until either or both run out, then return the value that is less or equal
int differ(const string a1[], int n1, const string a2[], int n2) {

    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    
    int lower = 0;
    //figuring out which is smaller to use for the for loop
    if (n1 <= n2) {
        lower = n1;
    } else {
        lower = n2;
    }
    
    
    //iterating up until the lesser of n1 or n2
    for (int i = 0; i < lower; ++i) {
        if (a1[i] != a2[i]) {
            return i; //return the element index that is being iterated through if the strings are not equal
        }
    }
    
    return lower; //if one or both strings are iterated through up to lower, then return lower
}

//return a1's index in the subsequence where all the n2 elements appear in a1 in the same order
int subsequence(const string a1[], int n1, const string a2[], int n2) {

    int inARow = 0; //use for incrementing the counter inside the two while loops later on
    
    //either n1 or n2 cannot be negative
    //also n2 cannot be greater than n1
    if (n2 > n1 || n1 < 0 || n2 < 0) {
        return -1;
    }
    
    else if (n2 == 0) {
        return 0;
    }
        
    //iterate through both a1 and a2 arrays using 2 while loops
    int i = 0;
    while (i < n1) {
    
        int j = 0;
        while (j < n2) {
        
            if (a1[i] == a2[j]) { //compares 1st array element with 2nd array's elements
                inARow++; //increment the counter if the elements are equal
                
                if (inARow == n2) {
                    return 1 + i - inARow;
                } else {
                    ++i;
                }
                
            } else {
                inARow = 0;
            }
            ++j; //increment j from the second while loop
        }
        ++i; //increment i from the first while loop
    }
    return -1;
}

//returns the smallest possible position in the a1 array that is equal to any of the n2 elements in the a2a array
int lookupAny(const string a1[], int n1, const string a2[], int n2) {

    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    
    for (int i = 0; i < n1; ++i) {
        if (lookup(a2, n2, a1[i]) != -1) { //use the lookup function and loop through it using the a1 elements as the target strings
            return i;
        }
    }
    
    return -1;
}

//rearranges the array's elements so that everything < divider comes before all other elements and everything > divider comes after all other elements
int divide(string a[], int n, string divider) {

   if (n < 0)
		return -1; // returns -1 if argument is invalid

    //bubble sort using 2 for loops
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (a[j] > a[j + 1]) {
				string temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n; ++i) { //iterate through array to see if the element is greater than divider
		if ((a[i] >= divider))
			return i;
	}

	return n; //if all a[i] are smaller than divider, return n
}


int main() {

    //appendToAll TESTS
    string f[3] = { "fought", "fight", "fire" };
	assert(appendToAll(f, 3, "!") == 3 && f[0] == "fought!" && f[2] == "fire!"); //checks spceific cases to see if the function returns the right appended strings
    
    string words[7] = { "hi", "bye", "hello", "goodbye", "greetings", "hiya", "hola" };
    assert(appendToAll(words, 2, "!!!") == 2);//checks to see if the appendToAll function returns the right value  as expected
    assert(appendToAll(words, -3, "!") == -1); //checks to see if the appendToAll function returns -1 when n is negative
    assert(appendToAll(words, 0, "!") == 0);  //checks to see if the appendToAll function returns 0 with a 0 value
    
    
    
    //positionOfMax TESTS
    assert(positionOfMax(words, 7) == 6); //checks to see if the positionOfMax function works and returns correct position
    assert(positionOfMax(words, 4) == 0); //checks to see if the positionOfMax function works and returns correct position when only part of the array is checked
    assert(positionOfMax(words, -4) == -1); //checks to see if the positionOfMax function returns -1 when n is negative
    assert(positionOfMax(words, 0) == -1); //checks to see if the positionOfMax function returns -1 when n is 0
    
    
    
    //lookup TESTS
    string names[7] = {"jose", "john", "joe", "james", "jorge", "bob", "maddie" };
	assert(lookup(names, 7, "john") == 1); //checks to see if the lookup function does what it is supposed to
	assert(lookup(names, 7, "jose") == 0); //checks to see if the lookup function does what it is supposed to
	assert(lookup(names, 2, "ed") == -1); //checks to see if the lookup function returns -1 when no such string is in the array
    assert(lookup(names, 2, "maddie") == -1); //checks to see if the lookup function returns -1 when the string is in the array butout of bounds in terms of the parameter
    assert(lookup(names, -3, "john") == -1);  //checks to see if the lookup function returns -1 n is negative
    assert(lookup(names, 0, "john") == -1); //checks to see if the lookup function returns -1 when n is 0
    
    
    
    //rotateLeft TESTS
    string colleges[4] = {"usc", "ucla", "stanford", "caltech"};
    assert(rotateLeft(colleges, 4, 1) == 1); //checks if the rotateLeft function returns pos
    assert(rotateLeft(colleges, 3, 1) == 1); //checks if the rotateLeft function returns pos when n is less than the total number of elements
    assert(rotateLeft(colleges, 4, 1) == 1); //checks if the rotateLeft function returns pos
    assert(rotateLeft(colleges, 4, 1) == 1 && colleges[1] == "ucla" && colleges[3] == "stanford"); //checks specific cases within the rotate left function
    assert(rotateLeft(colleges, 4, 4) == -1); //checks if -1 is returned when pos >= n
    assert(rotateLeft(colleges, 0, 4) == -1); //checks -1 is returned when n=0
    
    

    //countRuns TESTS
    string names2[4] = { "reed", "bob", "tony", "harold"};
    assert(countRuns(names2, 4) == 4); //checks if the countRuns function works as specified
    assert(countRuns(names2, 3) == 3); //checks if the countRuns function works as specified when you make the int parameter less elements
    assert(countRuns(names2, 0) == 0); //checks if the countRuns function returns 0 when n is 0
    assert(countRuns(names2, -3) == -1); //checks if the countRuns function return -1 when n is negative
    
    string pokerHands[5] = {"highCard", "pair", "pair", "twoPair", "twoPair"};
    assert(countRuns(pokerHands, 5) == 3); //checks if countRuns function works when there are a few repeated strings
    assert(countRuns(pokerHands, 0) == 0); //checks if countRuns returns 0 when n is 0
    
    
    
    //flip TESTS
    string states[3] = { "az", "ca", "dc" };
    
    //checks to see if  array is reversed and  elements are in their newly assigned places
	assert(flip(states, 3) == 3 && states[0] == "dc" && states[2] == "az");
    
    string folks[6] = { "donald", "mike", "", "susan", "sara", "jamie" };
    assert(flip(folks, 4) == 4 && folks[0] == "susan" && folks[2] == "mike"); //checks to see if flip returns 4 since the array now has  "susan" at 0 and "mike" at 2
    assert(flip(folks, -4) == -1); //checks to see if flip returns -1 since n is -4
    assert(flip(folks, 0) == 0); //checks if flip returns 0 when n is 0
    
    
    
    //differ TESTS
    string name[6] = { "donald", "mike", "", "susan", "sara", "jamie" };
    string group[5] = { "donald", "mike", "jamie", "", "susan" };
    assert(differ(name, 6, group, 5) == 2);  //checks if the differ function returns 2 like it should
    assert(differ(name, 2, group, 1) == 1);  //checks if the differ function returns 1 like it should
    assert(differ(name, 0, group, 4) == 0); //checks if the differ function returns 0 when one of either n1 or n2 is 0
    assert(differ(name, 0, group, -3) == -1); //checks if the differ function returns -1 when one of either n1 or n2 is negative
    assert(differ(name, 0, group, 0) == 0); //checks if the differ function returns 0 when BOTH n1 or n2 are 0
    
    
    
    //subsequence TESTS
    string v[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
    string e[4] = { "joe", "susan", "", "kamala" };
    
    assert(subsequence(v, 7, e, 4) == 2); //makes sure that subsequence works as specified
    assert(subsequence(v, 7, e, 0) == 0); //makes sure that subsequence returns 0 when n2 is 0
    assert(subsequence(v, 0, e, 0) == 0); //makes sure that subsequence returns 0 when both n1 and n2 are 0
    assert(subsequence(v, -1, e, 3) == -1); //makes sure that subsequence returns -1 when either n1 or n2 is negative
    assert(subsequence(v, 2, e, 3) == -1); //makes sure that subsequence returns -1 when n1 < n2
    
    
    
    
    //lookupAny TESTS
    string nam[6] = { "kamala", "mark", "sara", "martha", "donald", "lindsey" };
    string set1[4] = { "jamie", "donald", "martha", "mark" };
    assert(lookupAny(nam, 6, set1, 4) == 1);  //checks if lookupAny returns 1 since a1 has "mark"
    assert(lookupAny(nam, 6, set1, 0) == -1); //checks if lookupAny returns -1 when n2 is 0
    assert(lookupAny(nam, 0, set1, 6) == -1); //checks if lookupAny returns -1 when n1 is 0
    
    string set2[2] = { "susan", "joe" };
    assert(lookupAny(nam, 6, set2, 2) == -1);  //checks if lookupAny returns -1 since a1 has none
    
    string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey"};
    string n[3] = { "lindsey", "joe", "mike" };
    assert(lookupAny(h, 7, n, 3) == 2); //checks to see if lookup returns 2 in this case
    
    
    
    //divide TESTS
    string candidate[6] = { "jamie", "lindsey", "mark", "susan", "joe", "donald" };
    assert(divide(candidate, 6, "kamala") == 3);  //checks to see if divide  returns 3
    string candidate2[4] = { "mark", "sara", "lindsey", "mike" };
    assert(divide(candidate2, 4, "mike") == 2);  //checks to see if divide  returns 3
    assert(divide(candidate2, -3, "mike") == -1);  //checks to see if divide  returns -1 when a negative n number is entered
    assert(divide(candidate2, 1, "zaza") == 1);  //checks to see if divide  returns n when the entire array is smaller than the divider
    assert(divide(candidate2, 0, "zaza") == 0); //checks to see if divide returns 0 when n = 0
    
       
    cout << "success" << endl;
}




