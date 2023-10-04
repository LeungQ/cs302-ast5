/* 
Name: Queenie Leung, NSHE 1007386899, CS 302 1004, Ast 5
Description: Spell checker program
             
Input:  user inputs a .txt file name and it reads the file
    
Output: is any misspelled words and suggestions based on the dictionary usa.txt
if there are any suggestions otherwise no suggestions. 

Part A
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  //to use sort function
#include <unordered_map> //dictionary file usa.txt

using namespace std;

//******FUNCTIONS******//

/*
FUNCTION_IDENTIFIER: unordered_map<string, bool> 
                    downloadDictionary(const string& fileName)
parameters: const string& fileName
return value: if words is true or false
description: Load a dictionary file that contains around 60,000 words 
in the american english dictionary into an std::unordered_map, 
the dictionary file is called "usa.txt" and you can hard code this in your
program
*/

// Loads words from a file into an unordered_map
//unordered_map<string (key), bool (value)
std::unordered_map<std::string, bool> downloadDictionary(const std::string& fileName) 
{
    string word;
    ifstream infile(fileName);
    unordered_map<string, bool> words;
    
    
    if (infile.is_open())       //check if file is open
    {
        while (infile >> word) //while infile is being read into word
        {
            // Convert word to uppercase
            for(int i = 0; i < word.length(); i++)
            {
                word[i] = toupper(word[i]); //using function toupper
                                            //to change words to uppercase
                                            //so results are in uppercase
                                            //like from PDF
            }

            // Add word to "words" map since it is in the usa.txt file
            words[word] = true;//so word read is the key and value is true
        }

        infile.close(); //close the file since you are done reading in
    }
    else 
    {   //else print error as user probably entered invalid file name
        cout << "Error opening file " << fileName << endl;
    }

    return words;
}

/*
FUNCTION_IDENTIFIER: vector<string> 
                    loadWordsFromFile(const string& fileName)
parameters: passes in const string& filename
return value: returns the unique words loaded from a vector of strings
description: Loads unique words from a file into a vector of strings
does not add words already seen or added to the words vector already
*/


std::vector<string> loadWordsFromFile(const std::string& fileName) {
    string word;
    ifstream infile(fileName);
    unordered_map<string, bool> wordAlreadySeen; //keep track of whether a word
                                      //has already been added to "words" vector
    vector<string> words;   //vector string "words"

    if (infile.is_open()) //checks if the file is open
    {
        while (infile >> word) //while it is open reads infile into word
        {
           
            // Convert word to uppercase
            for(int i = 0; i < word.length(); i++)
            {
                word[i] = toupper(word[i]); //using function toupper
                                            //to change words to uppercase
            }

           //checks if the 'word' is already present in the wordAlreadySeen map or not
            if (wordAlreadySeen[word] == false)
            {   
                //if the wordAlreadySeen then set to true and add to 
                wordAlreadySeen[word] = true;

            }

            //checks if the word is not already present in the "words" vector
            //to add it to the end of the vector
            //first occurence in the words vector
            if(find(words.begin(), words.end(), word) == words.end())
            {
                 // Add word to vector if not seen before
                words.push_back(word);
            }
        }

        infile.close(); //input file closed as all words should of been read already
    }                   //don't wanna leave open
    else 
    {   //error if the file is not read user most likely put in
        //invalid input file name
        cout << "Error opening file " << fileName << endl;
    }

    //returns words vector that now has all the unique words
    return words;
}


/*
FUNCTION_IDENTIFIER: vector<string> 
                     allSuggestedWords(const string &stringWord)
parameters: const string &stringWord
return value: a vector of suggested words
description: Generates a vector of strings 
that should contain all suggested words does the first case of diff nth char
then the diff letters added to every nth position
*/

std::vector<string> allSuggestedWords(const std::string &stringWord)
{
    vector<string> words;
    unordered_map<string, bool> wordAlreadySeen; //keep track of seen word

    // Add the original word to seen so that it's excluded from the suggested words
    wordAlreadySeen[stringWord] = true;

    // Case 1: Different nth characters
    //loops thru each character of stringWord -- pre incremented
    for (int i = 0; i < stringWord.length(); ++i)
    {
        for (char c = 'A'; c <= 'Z'; ++c) //nested loop to go thru A to Z
        {
            if (c != stringWord[i]) //checks of char c is != stringWord element [i]
            {
                string suggestedWord = stringWord; //sets stringWord to suggested
                suggestedWord[i] = c;             //i is now replaced with current char of c

                //checks of suggested is equal to wordAlreadySeen.end()
                // if suggested word is not already in the wordAlreadySeen map
                if (wordAlreadySeen.find(suggestedWord) == wordAlreadySeen.end())
                {
                    //set the suggested word to true and adds suggested to wordAlreadySeen map
                    wordAlreadySeen[suggestedWord] = true;

                    // Check if suggested is not the same as original word (check for dups)

                    if (suggestedWord != stringWord) 
                    {
                        // then adds to the words vector since its not the same
                        words.push_back(suggestedWord);
                    }
                }
            }
        }
    }

    // Case 2: Different letters added in every nth position
    //loops thru each character of stringWord -- pre incremented
    for (int i = 0; i <= stringWord.length(); ++i) 
    {
        for (char c = 'A'; c <= 'Z'; ++c) //nested loop to go thru A to Z
        {
            string suggested = stringWord; //sets stringWord to suggested
            suggested.insert(i, 1, c);     //i is the position at which the char is inserted
                                           //1 is the # of times the char needs to be inserted
                                           //c is the char that needs to be inserted at the position
            
            //checks if the suggested word is already on the map to avoid duplicates
            if (wordAlreadySeen.find(suggested) == wordAlreadySeen.end())
            {
                //set the suggested word to true and adds suggested to wordAlreadySeen map
                wordAlreadySeen[suggested] = true;
               
                //checks if the new word generated is not already in the wordAlreadySeen map
                if (suggested != stringWord) // Check if suggested is not the same as original word
                {
                    // then adds to the words vector since its not the same
                    words.push_back(suggested);
                }
            }
        }
    }
        // Sort the suggested words    
    sort(words.begin(), words.end()); //given from PDF to make sure its in order
                                     //using the algorithm library

    return words;
}

/*************************************************************************/
// MAIN STARTS HERE //
/*************************************************************************/

int main()
{
    string fileName;
    cout << endl;
    cout << "Enter filename: ";
    cin >> fileName;

    //declares an unordered map of strings to booleans called dictionary and 
    //assigns the result of the func to call to downloadDictionary with arg "usa.txt"
    //returns an unorder_map of bool value
    unordered_map<string, bool> dictionary = downloadDictionary("usa.txt");
    
    //function loadwordsfromfile to vector string words
    vector<string> words = loadWordsFromFile(fileName);

    cout << endl;

    //itereates over each string in words vector. 
    //const auto& is reference to "word" to each string in vector
    for (const auto& word : words) 
    {
        //check if string word is not in dictionary map
        if (dictionary.find(word) == dictionary.end()) 
        {
            //it outputs the wrod if its not found in dictionary
            //thus it is misspelled.
            cout << word << " is misspelled\n";
            cout << endl;

            //creates a string vector called validWordSugg
            vector<string> validWordSugg;

            //iterates over each suggested word for the misspelled
            for (const auto& suggestedWord : allSuggestedWords(word)) 
            {
                //checks if the suggested word is not at the end of the map
                if (dictionary.find(suggestedWord) != dictionary.end()) 
                {
                    //adds the suggestedWord to validWordSugg if 
                    //its found in the dictionary
                    validWordSugg.push_back(suggestedWord);
                }
            }

            //checks if the validWordSugg is an empty vector
            if (validWordSugg.empty()) 
            {
                //if the vectory is empty there are no valid
                //suggestions and prints no suggestions
                //cout << endl; //DEBUG
                cout << "No suggestions\n";
            } 
            //else if not empty vector 
            else 
            {   
                //this sorts the validWordSugg vector in alphabetical order
                sort(validWordSugg.begin(), validWordSugg.end()); 
                //prints "Suggested words"
                cout << "Suggested words" << endl;
                //cout << endl; //DEBUG
                
                //iterates over each element in validWordSugg vector
                //using a range-based FOR loop. 
                //const auto& declares a constant ref to each element of
                //the vector to read the elements value
                for (const auto& suggestedWord : validWordSugg)
                {
                    //cout << endl; //DEBUG
                    //print each suggested word
                    cout << suggestedWord << endl;
                }
               // cout << endl; //DEBUG
            }

            cout << endl;
        }
    }

    return 0;
}

/*************************************************************************/
// MAIN ENDS HERE //
/*************************************************************************/

//I spent most of the time figuring out how to load the dictionary
//then was worried that I was not hashing correctly
//then i did not know unordered_map was not an standard library
//but a way to call key value for hashing 
//there was a lot i did not know -- I am not sure if this was covered
//in class... but hashing was not fun... 
//sorry for all the comments as I was on medication it is hard to remember
//and even harder to code 
