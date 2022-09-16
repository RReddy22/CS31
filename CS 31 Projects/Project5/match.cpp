#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;

//max length of a word and of a doc
const int MAX_WORD_LENGTH = 20;
const int DOC_MAX_LENGTH = 250;

//make everything that is uppercase into lowercase
void lowerCase(char word[], int &notInAlphabet) {

    int i = 0;
    for (i = 0; word[i] != '\0'; ++i) {
    
        if (!(isalpha(word[i]))) { //checks if the element in the array is alphabetical
            notInAlphabet++;
            break;
        }
        word[i] = tolower(word[i]);
        
    }
    word[i] = '\0';
    
}


//remove rules as desired (whenever something is not in clean form)
void removeRule(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int nRules, int pos) {

    int i = pos;
    while (i < nRules - 1) {
        strcpy(wordin[i], wordin[i+1]); //removes the rule in the first array and sets it equal to the element that is 1 greater than it
        strcpy(wordout[i], wordout[i+1]); //removes the rule in the second array and sets it equal to the element that is 1 greater than it
        ++i;
    
    }

}

//main function that cleans up 2 different arrays' rules
int cleanupRules(char wordin[][MAX_WORD_LENGTH+1], char wordout[][MAX_WORD_LENGTH+1], int nRules) {

    if (nRules < 0) { //
        nRules = 0;
    }
    
    int notInAlphabet = 0;
    int i = 0;
    
    while (i < nRules) {
    
        lowerCase(wordin[i], notInAlphabet);
        lowerCase(wordout[i], notInAlphabet);
        
        if (notInAlphabet > 0 || strcmp(wordin[i],"") == 0) {
            removeRule(wordin, wordout, nRules, i);
            --i;
            --nRules;
            notInAlphabet = 0;
            
        }
        ++i;
        

    }
    
    //2 for-loops for the 2d arrays
    for (i = 0; i < nRules; ++i) {
        for (int j = i+1; j < nRules; ++j) {
            
            //1 word rule
            if (strlen(wordout[i]) == 0) {
                if ((strcmp(wordin[i], wordin[j])) == 0) {
                    removeRule(wordin, wordout, nRules, j);
                    --j;
                    --nRules;
                }
            }
            
            
            //2 word rule
            if (strlen(wordin[i]) > 0 && strlen(wordout[i]) > 0) {
                
                //checks for if win = wout
                if (strcmp(wordin[i], wordout[i]) == 0) {
                    removeRule(wordin, wordout, nRules, i);
                    --i;
                    --nRules;
                }
            
                //checks for if there are multiple rules with the same win or wout????
                if (strcmp(wordin[i], wordin[j]) == 0 && strcmp(wordout[i], wordout[j]) == 0) {
                    removeRule(wordin, wordout, nRules, j);
                        --nRules;
                        --j;
                }
                
            }
        
        }

    }
    
    return nRules;
}

bool checkDocument (const char wordin[], const char document[]) {
    
    int index = 0;
            
            //loops through up to the length of the document
            for (int j = 0; j < strlen(document); ++j) {
            
                //checks for if the word in the index equals the document's element
                if (wordin[index] == tolower(document[j])) {
                    if (index == 0) {
                        if (j == 0) { //since j = 0, it cannot go into j - 1
                            ++index;
                        } else if (!(isalpha(document[j-1]))) {
                            ++index;
                        }
                    
                    //checks if the document's element is alphabetical at the end
                    } else if ((index == strlen(wordin) - 1) && ((j == strlen(document) - 1) || !(isalpha(document[j+1])))) {
                        return true;
                        
                    //checks if index is greater than -
                    } else if (index > 0){
                        ++index;
                    } else {
                        index = 0;
                    }
                    
                } else {
                    index = 0;
                }
            }
            return false;

}

int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH+1], const char wordout[][MAX_WORD_LENGTH+1], int nRules) {

    char copy[DOC_MAX_LENGTH] = "";
    
    //initialize so you can add the null byte after the loop
    int i = 0;
    for (i = 0; i < strlen(document); ++i) {
        if (isalpha(document[i]) || document[i] == ' ') {
            strncat(copy, (document + i), 1);
        }
    }
    copy[i] = '\0';

    int matched = 0;
    
   // char copy[DOC_MAX_LENGTH];
   // strcpy(copy,document);

    
    for (int i = 0; i < nRules; ++i) {
        
        //1 word rule
        if (strcmp(wordout[i],"") == 0) {
            if (checkDocument(wordin[i], copy) == true) {
                ++matched;
            }
            
        //2 word rule
        } else {
            if (checkDocument(wordin[i], copy) == true && checkDocument(wordout[i], copy) == false) {
                ++matched;
            }
            
        }
        
    }
    return matched;
                   
}


int main() {

    const int TEST1_NRULES = 3;
    char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"family", "unhappy", "horse"};
    char test1wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "",       "horse",   "",};
    
    assert(cleanupRules(test1win, test1wout, 3) == 3); //checks to make sure cleanup rules returns the correct value (general)
    assert(cleanupRules(test1win, test1wout, 2) == 2); //checks to make sure cleanup rules returns the correct value (general)
    
    char test2win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"", "unhappy", "horse"};
    char test2wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "hi",       "horse",   "",};
    
    assert(cleanupRules(test2win, test2wout, 3) == 2); //checks to make sure it can handle an empty string
    
    /*char test3win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"", "unhappy", "horse"};
    char test3wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "hi",       "horse",   "",};
    
    assert(cleanupRules(test3win, test3wout, 2) == 1); //empty string with smaller nRules than there are positons */
    
    char test4win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"hi", "unhappy", "horse"};
    char test4wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "hi",       "horse",   "",};
    
    assert(cleanupRules(test4win, test4wout, 3) == 2); //same win and wout
    

    char test5win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"", "unhappy", "horse"};
    char test5wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "hi", "unhappy",   ""};
    
    assert(cleanupRules(test5win, test5wout, 3) == 1); //checks to make sure it can handle an empty string followed by win=wout
    
    char test6win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"hello", "unhapp4y", "horse"};
    char test6wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "hi",       "horse",   "",};
    
    assert(cleanupRules(test6win, test6wout, 3) == 2); //checks to see if a non-alpha character is not included in the # of rules
    
    char test7win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"43dh", "unhapp4y", "horse"};
    char test7wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "hi",       "horse",   "",};
    
    assert(cleanupRules(test7win, test7wout, 3) == 1); //checks to see if mutliple non-alpha character is not included in the # of rules
    
    
    //determineScore TESTS
    
    char test8win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {"hello", "hi", "bye"};
    char test8wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = { "",       "",   "",};
    
    assert(determineScore("Hi my name is Rahul", test8win, test8wout, 3) == 1);
    assert(determineScore("Hihello bye", test8win, test8wout, 3) == 1);
    
    
    
            char test9win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
                "family", "unhappy", "horse",
            };
            char test9wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
                "",       "horse",   "",
            };
            assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.",
                        test9win, test9wout, TEST1_NRULES) == 2);
            assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
                        test9win, test9wout, TEST1_NRULES-1) == 0);
            assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.",
                        test9win, test9wout, TEST1_NRULES) == 1);
            assert(determineScore("A horse!  A horse!  My kingdom for a horse!",
                        test9win, test9wout, TEST1_NRULES) == 1);
            assert(determineScore("horse:stable ratio is 10:1",
                        test9win, test9wout, TEST1_NRULES) == 0);
            assert(determineScore("**** 2020 ****",
                        test9win, test9wout, TEST1_NRULES) == 0);
            cout << "All tests succeeded" << endl;
    
    cout << "Success" << endl;
}




