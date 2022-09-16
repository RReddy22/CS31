#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

//checks if  all the characters are only numbers and letters
bool hasOnlyNumbersAndLetters(string pollData) {

    for (int i = 0; i < pollData.size(); ++i) {
    
        if (!isalpha(pollData.at(i)) && !isdigit(pollData.at(i))) {
            return false;
        }
    }
    return true;
             
}
             
//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.
bool isValidUppercaseStateCode(string stateCode) {
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//checks if each state forecast is valid
bool isValidStateForecast (string pollData) {
    
    for (int j = 0; j < pollData.size(); ++j) {
    
    //checks if votes contain greater than 2 digits
        string votes = "";
        
        //
        while (isdigit(pollData.at(j))) {
            votes = votes + pollData.at(j);
            ++j;
        }
        
        //checks to make sure that digits are 2 elements or less of the string
        if (votes.size() >= 3) {
            return false;
        }
               
        if (!isalpha(pollData.at(j))) {
            return false;
        }
        
        //sets string to empty
        string code = "";
        
        //converts state code into upper case
        while (j < pollData.size() && isalpha(pollData.at(j))) {
            code += toupper(pollData.at(j));
            ++j;
        }
        
        if (code.size() != 3) {
            return false;
        }
        string stateCode = code.substr(0,2);
        
        //checks if the state code is valid
        if (!isValidUppercaseStateCode(stateCode)) {
            return false;
        }
                    
    }
    return true;
}

//required function that checks if the parameter, pollData, is a poll data string
bool isSyntacticallyCorrect(string pollData) {
    
    if (pollData == "") {
        return true;
    }
        
        if (!hasOnlyNumbersAndLetters(pollData)) {
            return false;
        }
        
        if (!isValidStateForecast(pollData)) {
            return false;
        }

        return true;
    
}


int tallyVotes(string pollData, char party, int& voteTally) {
    //checks if pollData has the correct syntax
    if (!isSyntacticallyCorrect(pollData)) {
        return 1;
    }
    
    //checks if the party character is a letter
    if (!isalpha(party)) {
        return 2;
    }
    
    //checks if the votes are zero for a state forecast
    string votes = "";
    for (int k = 0; k < pollData.size(); ++k) {
    
        if (isdigit(pollData.at(k))) {
            votes = votes + pollData.at(k);
        }
        
        if (isalpha(pollData.at(k))) {
            while(k < pollData.size() && isalpha(pollData.at(k))) {
                ++k;
            }
            voteTally = stoi(votes);
            if (voteTally == 0) {
                return 3;
            }
            --k;
            votes = "";
        }
        
        
    }
    
    //sets voteTally equal to 0 if none of the above situations occur
    voteTally = 0;
    votes = "";
    for (int k = 0; k < pollData.size(); ++k) {
        if (isalpha(pollData.at(k))) {
            while(k < pollData.size() && isalpha(pollData.at(k))) {
            
                if (pollData.at(k) == toupper(party) || pollData.at(k) == tolower(party)) {
                    voteTally = voteTally + stoi(votes);
                }
                
                ++k;
            }

        }
        votes = "";
        while (k < pollData.size() && isdigit(pollData.at(k))) {
            votes = votes + pollData.at(k);
            ++k;
        }
        --k;
        
        
    }
    return 0;
}

int main() {
        assert(isSyntacticallyCorrect("38TXR55CAD"));
	    assert(!isSyntacticallyCorrect("38MXR55CAD"));
	    int votes;
	    votes = -999;    // so we can detect whether tallyVotes sets votes
	    assert(tallyVotes("38TXR55CAD6Msr29nYd06UTL", 'd', votes) == 0  &&  votes == 84);
	    votes = -999;    // so we can detect whether tallyVotes sets votes
	    assert(tallyVotes("38TXR55CAD", '%', votes) == 2  &&  votes == -999);
	    cout << "All tests succeeded" << endl;
}
