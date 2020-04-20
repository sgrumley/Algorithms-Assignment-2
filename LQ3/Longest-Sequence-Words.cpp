#include <bits/stdc++.h>

using namespace std;

string firstValue;

void printMap(unordered_map<string, vector<string> >dict) {
    cout << "----------------------------------------------" << endl;

    for (unordered_map<string, vector<string> >::iterator ii = dict.begin(); ii != dict.end(); ++ii) {
        cout << (*ii).first << ": ";
        vector<string> inVect = (*ii).second;

        for (unsigned j = 0; j < inVect.size(); j++) {
            cout << inVect[j] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------" << endl;
}

// pass in string and variables to assign chars to
// TODO Look at overloading to return 1 or both strings
void getWordChars(string word, string& s, string& f) {
    // string s, s2, f, f2;
    string s2, f2;
    int    wl   = word.length();
    int    pos1 = wl - 2;
    int    pos2 = wl - 3;

    s  = word.at(1);
    s2 = word.at(2);
    f  = word.at(pos2);
    f2 = word.at(pos1);
    s.append(s2);
    f.append(f2);
}

void readWordsFromFile(int wl, unordered_map<string, vector<string> >& start, unordered_map<string, vector<string> >& finish) {
    string   word;
    ifstream dictionary;
    int i    = 0;
    int test = 0;

    dictionary.open("dictionary.txt");

    while (!dictionary.eof()) {
        getline(dictionary, word);

        if (word.length() == wl) {
            string s, f;
            getWordChars(word, s, f);

            // add the word to the start array based on the second and third characters
            if (start.count(s) == 1) {
                // append word to value
                start[s].push_back(word);
            } else {
                // create key and value
                vector<string> initialVector;
                initialVector.push_back(word);
                start.insert(pair<string, vector<string> >(s, initialVector));
            }

            // add the word to the start array based on the second and third last characters
            if (finish.count(f) == 1) {
                // append word to value
                finish[f].push_back(word);
            } else {
                // create key and value
                vector<string> initialVector;
                initialVector.push_back(word);
                finish.insert(pair<string, vector<string> >(f, initialVector));
            }

            // if start doesn't have any keys it means finish doesnt weither so add to both
            if (start.size() == 0) {
                // append the word to both disctionaries
                vector<string> initialVector;
                initialVector.push_back(word);
                start.insert(pair<string, vector<string> >(s, initialVector));
                initialVector.push_back(word);
                finish.insert(pair<string, vector<string> >(f, initialVector));
            }
            i++;
        }

        if ((i == 10) && (test == 1)) {
            break;
        }
    }
}

string nextBestWord(string word, unordered_map<string, vector<string> >& start, unordered_map<string, vector<string> >& finish) {
    string s, f, sTemp, fTemp, wordTemp;
    int    max = 0;
    string rfTemp, rsTemp;

    getWordChars(word, s, f);


    // cout << "possible next words: " << endl;

    for (auto& words : start[f]) {
        getWordChars(words, sTemp, fTemp);

        // cout << words << " ";

        if (finish[fTemp].size() > max) { // && (firstValue.compare(words) != 0)) {
            max      = start[fTemp].size();
            wordTemp = words;
            rfTemp   = fTemp;
            rsTemp   = sTemp;


            // save index or reference to linked list
        }
    } // cout << endl;
    cout << "current word: " << word << endl;
    cout << "best word: " << wordTemp << endl;

    start[rsTemp].erase(remove(start[rsTemp].begin(), start[rsTemp].end(), wordTemp), start[rsTemp].end());
    finish[rfTemp].erase(remove(finish[rfTemp].begin(), finish[rfTemp].end(), wordTemp), finish[rfTemp].end());

    // start[]

    // cout << "Start--:" << endl;

    // printMap(start);
    // cout << "Finish:--" << endl;

    // printMap(finish);

    // auto sitr = find(start[s].begin(), start[s].end(), wordTemp);

    // if (sitr != start[s].end()) {
    //     cout << "found and deleted" << endl;
    //     start[s].erase(sitr);
    // }
    // auto fitr = find(finish[f].begin(), finish[f].end(), wordTemp);

    // if (fitr != finish[f].end()) {
    //     cout << "found and deleted" << endl;
    //     finish[f].erase(fitr);
    // }

    // remove via index or reference
    // find the value you in start

    return wordTemp;
}

string startValues(unordered_map<string, vector<string> >& start, unordered_map<string, vector<string> >& finish) {
    // find the largest length of a vector for finish
    int maxLength = 0;
    string bestStartingWord, s, f;

    for (auto& dict : finish) {
        if (dict.second.size() > maxLength) {
            maxLength        = dict.second.size();
            bestStartingWord = dict.first;
        }
    }
    bestStartingWord = finish[bestStartingWord].at(0);
    getWordChars(bestStartingWord, s, f);
    cout << "Best chars to start on: " << bestStartingWord << " - " << maxLength << endl;
    start[s].erase(remove(start[s].begin(), start[s].end(), bestStartingWord), start[s].end());
    finish[f].erase(remove(finish[f].begin(), finish[f].end(), bestStartingWord), finish[f].end());
    return bestStartingWord;
}

void createSequence(unordered_map<string, vector<string> >& start, unordered_map<string, vector<string> >& finish, string currentWord, int wordLength) {
    vector<string> sequence;
    vector<string> maxSequence;
    string s, f;
    bool   init = true;
    int    k    = 0;

    while (sequence.size() >= 1 || init == true) {
        init = false;

        getWordChars(currentWord, s, f);

        cout << "current word " << currentWord  << " " << sequence.size() << " " << start[f].size() << " " << maxSequence.size() << endl;

        // If there is no key and the sequence is larger than 1

        // if ((start.count(f) < 1) && (sequence.size() > 1)) {
        //     // migth be able to remove
        //     cout << "Backtrack started" << endl;
        //     currentWord = sequence.back();
        //     sequence.pop_back();
        //     f = s;
        // } else {
        //     break;
        // }
        if (start.count(f) < 1)  {
            if (sequence.size() > 1) {
                // cout << "Backtrack started" << endl;
                sequence.pop_back();
                currentWord = sequence.back();
                getWordChars(currentWord, s, f);
            } else {
                break;
            }

            // migth be able to remove
        }

        // Backtrack while there is no values in the list for the next node and
        // there is nothing in the list

        while (start[f].size() == 0) {
            // if the current sequence is greater than 1


            if (sequence.size() > 1) {
                // if this is the longest sequence recorded,
                if (sequence.size() > maxSequence.size()) {
                    // copy list to keep track of longest list
                    // copy(sequence.begin(), sequence.end(), back_inserter(maxSequence));
                    maxSequence = sequence;
                }

                sequence.pop_back();
                currentWord = sequence.back();
                getWordChars(currentWord, s, f);
            } else {
                break;
            }
        }

        // if a next node is available, make the move
        // if corresponding characters is a key in the dictionary and the key has
        // value in the list
        auto found = start.find(f);

        if ((found != start.end()) && (start[f].size() != 0)) {
            // add current node to sequence list and move to next node
            sequence.push_back(currentWord);

            currentWord = nextBestWord(currentWord, start, finish);
        } else {
            // else there was no move available, break
            break;
        }

        // k++;

        // if (k > 5) break;
    }

    // print sequence
    cout << "Seq of length: " << sequence.size() << endl;
    cout << "Maximum Seq of length: " << maxSequence.size() << endl;

    // for (auto& elem : sequence) {
    //     cout << elem << "->" << " ";
    // } cout << endl;
}

int main() {
    int wordLength = 6;
    vector<string> words;
    unordered_map<string, vector<string> > start;
    unordered_map<string, vector<string> > finish;

    // returns a list of words from the dictionary of wordlength
    readWordsFromFile(wordLength, start, finish);

    // cout << "Start:" << endl;

    // printMap(start);
    // cout << "Finish:" << endl;

    // printMap(finish);

    // string startWord;

    // returns the best word to start on
    firstValue = startValues(start, finish);

    // cout << "Start:" << endl;

    // printMap(start);
    // cout << "Finish:" << endl;

    // printMap(finish);

    // cout << "Starting word: " << firstValue << endl;

    // string s, f;
    // getWordChars(firstValue, s, f);

    // return the longest sequence found
    createSequence(start, finish, firstValue, wordLength);

    // start[s].erase(remove(start[s].begin(), start[s].end(), firstValue), start[s].end());
    // finish[f].erase(remove(finish[f].begin(), finish[f].end(), firstValue), finish[f].end());
}
