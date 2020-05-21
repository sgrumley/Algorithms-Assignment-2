#include <bits/stdc++.h>

using namespace std;

void readWordsFromFile(int wl, vector<string>& wordList, string s, string e) {
    string   word;
    ifstream dictionary;
    vector<char> uniqueChars;

    dictionary.open("test.txt");

    for (int i = 0; i < wl; i++) {
        if (find(uniqueChars.begin(), uniqueChars.end(), s[i]) == uniqueChars.end()) {
            uniqueChars.push_back(s[i]);
        }

        if (find(uniqueChars.begin(), uniqueChars.end(), e[i]) == uniqueChars.end()) {
            uniqueChars.push_back(e[i]);
        }
    }

    // for (auto elem: uniqueChars) {
    //     cout << elem << " ";
    // } cout << "f" << endl;

    while (!dictionary.eof()) {
        getline(dictionary, word);

        if (word.length() == wl) {
            int c = 0;

            for (int i = 0; i < word.length(); i++) {
                if (find(uniqueChars.begin(), uniqueChars.end(), word[i]) != uniqueChars.end()) {
                    c++;
                } else {
                    break;
                }
            }

            if (c == wl) {
                wordList.push_back(word);
            }
        }
    }
}

int wordLadder(string start, string target, vector<string>& D, int wl) {
    if (find(D.begin(), D.end(), target) == D.end()) {
        return 0;
    }

    int level = 0;
    queue<string> Q;
    Q.push(start);

    while (!Q.empty()) {
        ++level;

        // Current size of the queue
        int sizeofQ = Q.size();

        for (int i = 0; i < sizeofQ; ++i) {
            // Remove the first word from the queue
            string word = Q.front();
            Q.pop();

            // For every character of the word
            for (int pos = 0; pos < wl; ++pos) {
                char orig_char = word[pos];

                // Replace the current character with every possible lowercase alphabet
                for (char c = 'a'; c <= 'z'; ++c) {
                    word[pos] = c;

                    if (word == target) {
                        return level + 1;
                    }

                    D.erase(remove(D.begin(), D.end(), word), D.end());
                    Q.push(word);
                }
                word[pos] = orig_char;
            }
        }
    }

    return 0;
}

int main() {
    // main
    int wl              = 4;
    string startingWord = "fool";
    string endingWord   = "sage";
    vector<string> wordList;

    readWordsFromFile(wl, wordList, startingWord, endingWord);

    int path = wordLadder(startingWord, endingWord, wordList, wl);
    cout << path << endl;
}
