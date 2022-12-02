// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <deque>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool verify(const string& result, const set<string>& dict);
bool verifyFloating(const string& word, const string& floating);
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, string word, set<string>& words, deque<char> options, unsigned int place);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		int stars = 0;
		string word = in;
		set<string> words;
		deque<char> options;
		for (int i = 0; i < floating.length(); i++){
			options.push_back(floating[i]);
		}
		for(int i = 0; i < in.length(); i++){
			if(!isalpha(in[i])){
				stars++;
			}
		}
		stars -= floating.length();
		for(int i = 0; i < stars; i++){
			options.push_back('*');
		}
		if(in.length() == 0){
			return words;
		}
		wordleHelper(in, floating, dict, word, words, options, 0);
		return words;



}

// Define any helper functions here

void wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict, string word, set<string>& words, deque<char> options, unsigned int place)
{
	if(place == in.length()){
		if(dict.find(word) != dict.end()){
			words.insert(word);
		}
		return;
	}
	if(isalpha(in[place])){
		word[place] = in[place];
		wordleHelper(in, floating, dict, word, words, options, place + 1);
	}
	else
	{
	for(int i = 0; i < options.size(); i++){
			char c = options.front();
			options.pop_front();
			if(c != '*'){
				word[place] = c;
				wordleHelper(in, floating, dict, word, words, options, place + 1);
			}
			else{
				for(int i = 97; i < 123; i++){
					word[place] = (char)i;
					wordleHelper(in, floating, dict, word, words, options, place + 1);
				}
			}
			options.push_back(c);
		}
	}
}