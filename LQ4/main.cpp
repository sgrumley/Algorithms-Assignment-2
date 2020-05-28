#include <bits/stdc++.h>

using namespace std;

void readWordsFromFile(int wl, vector<string>& wordList, string s, string e) {
    string   word;
    ifstream dictionary;
    vector<char> uniqueChars;
    vector<char> alpha;

    dictionary.open("dictionary.txt");

    for (int i = 0; i < wl; i++) {
        if (find(uniqueChars.begin(), uniqueChars.end(), s[i]) == uniqueChars.end()) {
            uniqueChars.push_back(s[i]);
        }

        if (find(uniqueChars.begin(), uniqueChars.end(), e[i]) == uniqueChars.end()) {
            uniqueChars.push_back(e[i]);
        }
    }


    while (!dictionary.eof()) {
        getline(dictionary, word);

        if (word.length() == wl) {
            int c = 0;

            for (int i = 0; i < word.length(); i++) {
                if (find(uniqueChars.begin(), uniqueChars.end(), word[i]) != uniqueChars.end()) {
                    c++;
                } else {
                    // break;
                }
            }

            if (c >= 1) {
                wordList.push_back(word);
            }

            // wordList.push_back(word);
        }
    }

    sort(alpha.begin(), alpha.end());

    for (auto elem : alpha) {
        cout << elem << ", ";
    }
    cout << "Amount of words: " << wordList.size() << endl;
}

int wordLadder(string startWord, string goalWord, vector<string>& dictionary, int wl) {
    int changes = 0;
    queue<string> possibleWords;

    possibleWords.push(startWord);

    // first try to change each letter to the goal word and check if it's a word
    for (int pos = 0; pos < wl; pos++) {
        string tmp = startWord;
        tmp[pos] = goalWord[pos];

        if (find(dictionary.begin(), dictionary.end(), tmp) != dictionary.end()) {
            changes++;
        }

        if ((tmp == goalWord)  && (changes == wl - 1)) {
            return changes;
        }
    } cout << endl;

    changes = 0;

    // secondly bruteforce approach
    while (!possibleWords.empty()) {
        changes++;

        // iterating through current size of queue maintains BFS
        int nQ = possibleWords.size();

        for (int i = 0; i < nQ; ++i) {
            // Remove the first word from the queue
            string word = possibleWords.front();
            possibleWords.pop();

            // For every character of the word
            for (int pos = 0; pos < wl; ++pos) {
                char orig_char = word[pos];

                // Replace the current character with every possible lowercase alphabet
                for (char c = 'a'; c <= 'z'; ++c) {
                    word[pos] = c;


                    if (word == goalWord) {
                        return changes;
                    }

                    auto found = find(dictionary.begin(), dictionary.end(), word);

                    if (found != dictionary.end()) {
                        possibleWords.push(word);
                        dictionary.erase(found);
                    }
                }
                word[pos] = orig_char;
            }
        }
    }

    return 0;
}

int main() {
    string startWord = "lead";
    string goalWord  = "gold";

    cout << "Starting word: '" << startWord << "' Goal word: '" << goalWord << "'" << endl;

    int wl = goalWord.length();
    vector<string> wordList;

    readWordsFromFile(wl, wordList, startWord, goalWord);

    int path = wordLadder(startWord, goalWord, wordList, wl);
    cout << "Minimum path: " << path << endl << endl;

    startWord = "hide";
    goalWord  = "seek";
    cout << "Starting word: '" << startWord << "' Goal word: '" << goalWord << "'" << endl;
    vector<string> wordList1;

    readWordsFromFile(wl, wordList1, startWord, goalWord);

    path = wordLadder(startWord, goalWord, wordList, wl);
    cout << "Minimum path: " << path << endl << endl;
}
