/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    // first we open the file and declare a string for a word and its key
    ifstream words(filename);
    string word;
    string keyWord;
    
    // if the file opened properly
    if(words.is_open())
    {
        // Reads a line from words into word until the file ends
        while(getline(words, word))
        {
            // copy the word into the keyWord, then alphabetize it
            keyWord = word;
            std::sort(keyWord.begin(), keyWord.end());
            string key = keyWord;
            dict[key].push_back(word);
            
            }
        }
    }

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    // string to hold the key for a given word
    string keyWord;
    string word;

    for(auto& key_val : words)
    {
        word = key_val;
        keyWord = word;
        std::sort(keyWord.begin(), keyWord.end());
        string key = keyWord;
        dict[key].push_back(word);
    }
    
    
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    string keyWord = word;
    std::sort(keyWord.begin(), keyWord.end());
    auto anagram = dict.find(keyWord);
    if(anagram != dict.end())
    {
        return anagram->second;
    }
    return vector< string >();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector <string > > retval;
    for(auto& key_val : dict)
    {
        if(((key_val.second).size())>= 2)
        {
            retval.push_back(key_val.second);
        }
    }
    return retval;
    
}

