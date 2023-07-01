// Yzer De Gula
#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
#include "linear_probing.h"
#include "double_hashing.h"

#include "quadratic_probing.h"

using namespace std;


// You can add more functions here

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) 
{
    hash_table.MakeEmpty();
    /** 
    I think first we have to read the words from the words_filename and insert
    them into our Hash Map. We can do this using streams. From there, I think we
    can declare a string that we can use to go through the file. We can have it
    set up using a while loop and check while there is some input in the file,
    add it to the map. But there has to be a way to figure out how to stop the 
    while loop or it will go on forever. Looking through the words.txt file, 
    all the words we want to insert have some alphanumeric character(s), with 
    no breaks in between words. In addition, the very last line in the file is
    empty, so I think within our while loop, if the length of the input line is
    greater than 0, then we insert it. 
    **/

    // Declare an input stream for the words file
    ifstream word_file(words_filename);
    // Declare a string variable that we'll use to go through the file
    string s;

    // If the file fails to open
    if (word_file.fail())
    {
        // Display an error message and exit 
        cerr << "File cannot be opened for reading.\n";
        exit(1);
    }

    // While there is still some words in the file
    while (word_file >> s)
    {
        // Insert it into our Hash Table
        hash_table.Insert(s);
    }

    // After we're done with this file close it
    word_file.close();

    /*
    After inserting all the elements in the words file, we can then print out
    the table's statistics: number of elements, size of table, load factor,
    number of collisions, average number of collisions.
    */

    cout << "number_of_elements: " << hash_table.getCurrentSize() << std::endl;
    cout << "size_of_table: " << hash_table.getTableSize() << std::endl;
    cout << "load_factor: " << hash_table.getLoadFactor() << std::endl;
    cout << "collisions: " << hash_table.getCollisions() << std::endl;
    cout << "avg_collisions: " << hash_table.getAverageCollisions() << std::endl;

    cout << std::endl;

    /*
    After we displayed all of our hash table's statistics we can then load in
    the query words from the query_filename and then search for the word in 
    our hash table.
    */

    // Declare another input stream for our query file
    ifstream query_file(query_filename);

    // While there is still some words in the file
    while (query_file >> s)
    {
        // If the word is in our Hash Table, display that it was found
        if (hash_table.Contains(s))
        {
            cout << s << " Found " << hash_table.getNumberOfProbes(s) << std::endl;
        }
        // Otherwise, display that it wasn't found
        else
        {
            cout << s << " Not_Found " << hash_table.getNumberOfProbes(s) << std::endl;
        }
    }

    // After we're done with this file close it
    query_file.close();

    cout << std::endl;
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in main
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) 
    {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") 
    {
    //cout << "Linear Probing:\n";
      // Uncomment below when you have implemented linear probing.
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    } 
    else if (param_flag == "quadratic") 
    {
    //cout << "\nQuadratic Probing:\n";

	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    } 
    else if (param_flag == "double") 
    {
    //cout << "\nDouble Hashing:\n";
	cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.

	HashTableDouble<string> double_probing_table;
	TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    } 
    else 
    {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}