/* 
Name: Queenie Leung, NSHE 1007386899, CS 302 1004, Ast 5
Description: Spell checker program
             
Input:  user inputs a .txt file name and it reads the file
    
Output: is any misspelled words and suggestions based on the dictionary usa.txt
if there are any suggestions otherwise no suggestions. 
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>//to use sort function


using namespace std;

//******FUNCTIONS******//

/*
FUNCTION_IDENTIFIER: vector<string> downloadDictionary(const string& filename)
parameters: const string& fileName
return value: returns words vector that now has all the unique words
description: Load a dictionary file that contains around 60,000 words 
in the american english dictionary into an vector words, 
the dictionary file is called "usa.txt" and you can hard code this in your
program

*/

// Loads words from a file into a vector of strings
vector<string> downloadDictionary(const string& fileName) {
    string word;
   
    ifstream infile(fileName);
    vector<string> words;

    if (infile.is_open())  //check if file is open
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
            // Add word to vector
            words.push_back(word);
        }

        infile.close();//close the file since you are done reading in
    }
    else 
    {   //else print error as user probably entered invalid file name
        std::cout << "Error opening file " << fileName << endl;
    }

    //returns words vector that now has all the unique words
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

// Loads unique words from a file into a vector of strings
vector<string> loadWordsFromFile(const string& fileName) {
    string word;
    ifstream infile(fileName);

    vector<string> words, wordAlreadySeen; //vector string "words" and "wordAlreadySeen"

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


            // Add word to vector if not seen before
            if (find(wordAlreadySeen.begin(), wordAlreadySeen.end(), word) 
                == wordAlreadySeen.end()) 

                //wordAlreadySeen.begin() points first element in vector words
                // wordAlreadySeen.end() points to last element of words vector
                //, word) is the word to find in words if found 
                //if not found find(wordAlreadySeen.begin(), wordAlreadySeen.end(), word) will return 
                //wordAlreadySeen.end() thus == to wordAlreadySeen.end()
            {
                //add word to vector if not seen before
               wordAlreadySeen.push_back(word);   
            }
            // Add word to vector if not seen before
            if(find(words.begin(),words.end(),word)==words.end())
                //words.begin() points first element in vector words
                // words.end() points to last element of words vector
                //, word) is the word to find in words if found 
                //if not found find(words.begin(), words.end(), word) will return 
                //words.end() thus == to words.end()
            {
                words.push_back(word);
            }
        }

        infile.close();//input file closed as all words should of been read already
                       //don't wanna leave open
    }
    else 
    {   //error if the file is not read user most likely put in
        //invalid input file name
        std::cout << "Error opening file " << fileName << endl;
    }
     //returns words vector that now has all the unique words
    return words;
}

/*
FUNCTION_IDENTIFIER: std::vector<string> 
                     allSuggestedWords(const std::string &stringWord)
parameters: const string &stringWord
return value: Generates a vector of strings containing all suggested words
description: Generates a vector of strings 
that should contain all suggested words does the first case of diff nth char
then the diff letters added to every nth position
*/

std::vector<string> allSuggestedWords(const std::string &stringWord)
{
    vector<string> words, wordAlreadySeen;
    
    // Add the original word to seen so that it's excluded from the suggested words
    wordAlreadySeen.push_back(stringWord);
    
    // Case 1: Different nth characters
    //loops thru each character of stringWord -- pre incremented
    for (int i = 0; i < stringWord.length(); ++i)
    {
        for (char c = 'A'; c <= 'Z'; ++c)
        {
            //string suggested = stringWord.substr(0, i) + c + stringWord.substr(i + 1);
            if (c != stringWord[i]) //checks of char c is != stringWord element [i]
            {
                string suggestedWord = stringWord; //sets stringWord to suggested
                suggestedWord[i] = c;             //i is now replaced with current char of c

                //checks of suggested is equal to wordAlreadySeen.end()
                if (find(wordAlreadySeen.begin(), wordAlreadySeen.end(), suggestedWord) == wordAlreadySeen.end())
                {   // then adds to the suggested to wordAlreadySeen vector
                    wordAlreadySeen.push_back(suggestedWord);
                }
                // Check if suggested is not the same as original word (check for dups)
                if (find(words.begin(), words.end(), suggestedWord) == words.end())
                {
                    // then adds to the words vector since its not the same
                    words.push_back(suggestedWord);
                }
            }
        }
    }
    // Case 2: Different letters added in every nth position
    for (int i = 0; i <= stringWord.length(); ++i) 
    {
        for (char c = 'A'; c <= 'Z'; ++c) 
        {
            //string suggestedWord = stringWord.substr(0, i) + c + stringWord.substr(i);
            string suggestedWord = stringWord; //sets stringWord to suggested
            suggestedWord.insert(i, 1, c);     //i is the position at which the char is inserted
                                           //1 is the # of times the char needs to be inserted
                                           //c is the char that needs to be inserted at the position
            
            //checks if the suggested word is already in vector to avoid duplicates
            if (find(wordAlreadySeen.begin(), wordAlreadySeen.end(), suggestedWord) == wordAlreadySeen.end())
            { 
                  //adds suggested to wordAlreadySeen vector
                wordAlreadySeen.push_back(suggestedWord);
            }

            // Check if suggested is not the same as original word
            if (find(words.begin(), words.end(), suggestedWord) == words.end())
                {
                    // then adds to the words vector since its not the same
                    words.push_back(suggestedWord);
                }
              
        }
    }
    
    // Sort the suggested words
    sort(words.begin(), words.end());//given from PDF to make sure its in order
                                     //using the algorithm library

    return words;
}


int main()
{
    string filename;
    //std::cout << endl;
    std::cout << "\nEnter filename: ";
    cin >> filename;
  
    //function downloadDictionary to vector string words
    vector<string> dictionary = downloadDictionary("usa.txt");
    //function loadwordsfromfile to vector string words
    vector<string> words = loadWordsFromFile(filename);
    
    //itereates over each string in words vector. 
    //const auto& is reference to "word" to each string in vector
    //std::cout << endl;

    for(const auto& word : words) 
    {
        // Process word if not in the dictionary
        if (find(dictionary.begin(), dictionary.end(), word) == dictionary.end()) {
            std::cout << endl;
            std::cout << word << " is misspelled\n\n";
            //std::cout << endl;
            
            //creates a string vector called validWordSugg
            vector<string> validWordSugg;

            //iterates over each suggested word for the misspelled
            for(auto& suggestedWord: allSuggestedWords(word)) 
            {
                // if suggested word is in the dictionary, add it to validSuggestedWords
                if (find(dictionary.begin(), dictionary.end(), suggestedWord) 
                   != dictionary.end()) 
                    {
                        //adds the suggestedWord to validWordSugg if 
                         //its found in the dictionar
                        validWordSugg.push_back(suggestedWord);
                    }
            }
            
            //checks if the validWordSugg is an empty vector
            if(validWordSugg.size() == 0) 
            {
                //if the vectory is 0 there are no valid
                //suggestions and prints no suggestions
                //cout << endl;
                std::cout << "No suggestions\n";
            }
            else 
            {
                //this sorts the validWordSugg vector in alphabetical order
                sort(validWordSugg.begin(), validWordSugg.end()); 
                //prints "Suggested words"
                std::cout << "Suggested words" << endl;
                //cout << endl;
                
                //iterates over each element in validWordSugg vector
                //using a range-based FOR loop. 
                //const auto& declares a constant ref to each element of
                //the vector to read the elements value
                for(auto &suggestedWord: validWordSugg) 
                {
                    //cout << endl;
                    //print each suggested word
                    std::cout << suggestedWord << endl;
                }
               // std::cout << endl;
            }
             //std::cout << endl;
        }
         // cout << endl;
        // Do nothing if word is in the dictionary
    }
    
    return 0;
}
