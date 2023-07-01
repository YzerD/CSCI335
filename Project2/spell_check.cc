// Yzer De Gula
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.
/**
  @param    : The string we want to remove punctucation from
  @return   : Return the modified string that has its puncutation removed
**/
string removePunctuation (string &s)
{
  // Declare a string to store our result
  string result = "";

  // For every character in our string
  for (char c : s)
  {
    // If the character IS NOT punctuation
    if (!ispunct(c))
    {
      // Add it to our result string
      result += c;
    }
  }
  // Set the string to result and return it
  s = result;
  return s;
}

/**
  @param    : The string we want to make all lowercase
  @return   : The string that has been made all lowercase
**/
string convertToLowercase (string &s)
{
  // Declare a string to store our result
  string result = "";

  // For every character in our string
  for (char c : s)
  {
    // Add the lowercase character to the result string
    result += tolower(c);
  }
  // Set the string to result and return it
  s = result;
  return s;
}

// Creates and fills double hashing hash table with all words from
// dictionary_file
/**
  @param    : The dictionary file we want to insert into our Hash Table
  @return   : Return the Hash Map that has all the dictionary words stored
**/
HashTableDouble<string> MakeDictionary(const string &dictionary_file) 
{
  // Declare a Hash Table to store our dictionary
  HashTableDouble<string> dictionary_hash;

  // Declare an input stream for the dictionary file
  ifstream dictionary(dictionary_file);
  // Declare a string variable that we'll use to go through the file
  string s;

  // If the file fails to open
  if (dictionary.fail())
  {
    // Display an error message and exit 
    cerr << "File cannot be opened for reading.\n";
    exit(1);
  }

  // While there is still some words in the file
  while (dictionary >> s)
  {
    // Insert it into our Hash Table
    dictionary_hash.Insert(s);
  }

  // After we're done with this file close it
  dictionary.close();

/*
    cout << "\nDictionary:\n";
    cout << "number_of_elements: " << dictionary_hash.getCurrentSize() << std::endl;
    cout << "size_of_table: " << dictionary_hash.getTableSize() << std::endl;
    cout << "load_factor: " << dictionary_hash.getLoadFactor() << std::endl;
    cout << "collisions: " << dictionary_hash.getCollisions() << std::endl;
    cout << "avg_collisions: " << dictionary_hash.getAverageCollisions() << std::endl;
    cout << endl;
*/

  // Return the map with the dictionary stored
  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) 
{
  // Declare an input stream for our document file
  ifstream document(document_file);
  // Decalre a string variable that we'll use to go through the file
  string s;

  // If the file fails to open
  if (document.fail())
  {
    // Display and error message and exit
    cerr << "File cannot be opened for reading.\n";
    exit(1);
  }

  // While there are still some words in the file
  while (document >> s)
  {
    // Remove punctuation and make it lowercase
    removePunctuation(s);
    convertToLowercase(s);

    // If the word is misspelt 
    if (!dictionary.Contains(s))
    {
      // Display that it is misspelt
      cout << s << " is INCORRECT" << endl; 
      
      // Case A: Adding one character in any possible position
      /*
        Since strings are stored as an array of chars, I think we can have a double
        for loop, one iterating over the entire length of the word and another 
        starting from 'a' up to and including 'z'. We can also have a var that stores
        our corrections because in the display we want the word that we're trying to
        correct with the correction, so seperating these is essential. As we are 
        iterating through we check to see if for that first position if any character 
        can be inserted to have a match in our table.If so display it. We can use the
        insert method with 3 parameters, with the parameters being 
        insert(position, size, val). We would want the position to be the location in
        the string for that iteration, size as 1 since we only want to change 1 char,
        and val would be char since that's the value we want to insert at that position.
      */

      // For the length of the entire string
      for (size_t i = 0; i <= s.length(); i++)
      {
        // For the length of the entire lowercase alphabet
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
          // Declare a correction string variable that is set to the word
          string correction = s;
          // Check if at that current index any char would match a word 
          // in the dictionary
          correction.insert(i, 1, ch);

          // If it does display it, otherwise go onto the next iteration.
          if (dictionary.Contains(correction))
          {
            cout << "** " << s << " -> " << correction  << " ** case A" << endl;
          }
        }
      }

      // Case B: Removing one character from the word
      /*
        For this one it's not as complex as the first one, instead of inserting
        we're erasing and we don't need to iterate over the entire lowercase
        alphabet. So we can just do erase(position) over the length of the entire
        word. Then we would check if that correction is in the dictionary, if so,
        display it, if not move onto the next iteration.
      */

      // For the length of the string 
      for (size_t i = 0; i < s.length(); i++)
      {
        // Declare a string variable correction that is set to the word
        string correction = s;
        // EDIT: Error found in that it was deleting everything after the
        // current iteration, not removing one char, hence the addition
        // of the ", 1" to insert since we want to remove only one char
        correction.erase(i, 1);

        // And that word is present in our dictionary, display it.
        // Otherwise, continue onto the next iteration
        if (dictionary.Contains(correction))
        {
          cout << "** " << s << " -> " << correction << " ** case B" << endl;
        }
      }

      // Case C: Swapping adjacent characters in the word
      /*
        In this case, I think we can use the swap() function to check for any
        corrections that could be present in the dictionary. I think we would
        need to iterate up to the end of the word - 1 because I think we can
        check the current index and the next one, and if that word is in the
        dictionary, display it, if not go onto the next iteration. 
      */

      // Iterating up to but not including the last char in the word
      for (size_t i = 0; i < s.length() - 1; i++)
      {
        // Declare a string varible correction that is set to the word
        string correction = s;

        // If we swap the current char to the one in front of it
        swap(correction[i], correction[i + 1]);

        // And that word is present in our dictionary, display it.
        // Otherwise, continue onto the next iteration
        if (dictionary.Contains(correction))
        {
          cout << "** " << s << " -> " << correction << " ** case C" << endl;
        }
      }
    }
    // Otherwise, the word is spelt correctly and in our dictionary, and we display it
    else
    {
      cout << s << " is CORRECT" << endl;
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}