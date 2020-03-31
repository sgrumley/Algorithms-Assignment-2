#include <bits/stdc++.h>

using namespace std;


void printMap(map<string, vector<string> > dict){
	cout << "----------------------------------------------" << endl;
	for(map<string, vector<string> >::iterator ii=dict.begin(); ii!=dict.end(); ++ii){
       			cout << (*ii).first << ": ";
       			vector <string> inVect = (*ii).second;
       			for (unsigned j=0; j<inVect.size(); j++){
           			cout << inVect[j] << " ";
       			}
       			cout << endl;
   			}
}

void getWordChars(string word, string &s, string &f, int wl){
	//string s, s2, f, f2;
	string s2, f2;
	int pos1 = wl - 2;
	int pos2 = wl - 3;

	s 	= word.at(1);
	s2 	= word.at(2);
	f 	= word.at(pos2);
	f2 	= word.at(pos1);
	s.append(s2);
	f.append(f2);
}

void readWordsFromFile(int wl, int pos1, int pos2, map<string, vector<string> > &start, map<string, vector<string> > &finish ){
	string word; 

	ifstream dictionary;

	dictionary.open("dictionary.txt");
	int i=0;
	int test = 1;

	while(!dictionary.eof()){
		getline(dictionary, word);

		if (word.length() == wl){

			string s, f;
			
			getWordChars(word, s, f, wl);
			//cout << s << " " << word << " " << f << endl;
			// put into maps
			
			if (start.size() == 0){
				// append the word to both disctionaries
				vector<string> initialVector;
				initialVector.push_back(word);
				start.insert(pair<string, vector<string> > (s, initialVector));

				initialVector.push_back(word);
				finish.insert(pair<string, vector<string> > (f, initialVector));
			} 

			// add the word to the start array based on the second and third characters
			if (start.count(s) == 1){
				// append word to value
				start[s].push_back(word);
			} else {
				// create key and value
				vector<string> initialVector;
				initialVector.push_back(word);
				start.insert(pair<string, vector<string> > (s, initialVector));
			}
			// add the word to the start array based on the second and third last characters
			if (finish.count(f) == 1){
				// append word to value
				start[f].push_back(word);
			} else {
				// create key and value
				vector<string> initialVector;
				initialVector.push_back(word);
				finish.insert(pair<string, vector<string> > (f, initialVector));
			}
			
			
		i++;
		} 
			
		if (i == 5 && test == 1){
			break;
		}
		
	}  
   
}

string startValues(map<string, vector<string> > &start, map<string, vector<string> > &finish){
	// find the largest length of a vector for finish
	int maxLength = 0;
	string bestStartingWord;
	for(map<string, vector<string> >::iterator ii=finish.begin(); ii!=finish.end(); ++ii){

       	if ((*ii).second.size() > maxLength){
       		maxLength = (*ii).second.size();
       		bestStartingWord = (*ii).first;
       	}
   	}
   	cout << "Best chars to start on: " << bestStartingWord << " - " << maxLength << endl;
   	return bestStartingWord;
}

void createSequence(map<string, vector<string> > &start, map<string, vector<string> > &finish, string currentWord, int wordLength){
	vector<string> sequence;
	vector<string> maxSequence;
	int pos1 = wordLength - 2;
	int pos2 = wordLength - 3;
	string endCharsOfCurrentWord;
	string s,f;

	while(sequence.size() > 1){
		getWordChars(currentWord, s, f, wordLength);
		
		// If there is no corresponding key and nothing in the list to backtrack,
		if (start.count(f) < 1){
			// migth be able to remove
			if (sequence.size() > 1){
				// pop the last node off the sequence list and make it the current node (Go back a node)
			} else {
				break;
			}
		}
		// while there is no values in the list for the next node and there is nothing in the list to backtrack
		while (start[f].size() == 0){
			// if the current sequence is greater than 1
            if (sequence.size() > 1){
                // if this is the longest sequence recorded,
                if (sequence.size() > maxSequence.size()){
                    // copy list to keep track of longest list
                    //maxLengthSequence = copy.deepcopy(currentSequence)
                } else {
                	// else pop the last node off the sequence list and make it the current node (Go back a node)
                	currentWord = sequence.pop_back();
                	f = s;
                }
                
            }

        // if a next node is available, make the move
        // if corresponding characters is a key in the dictionary and the key has value in the list
            /*
        if endCharsOfCurrentNode in startDict and len(startDict[endCharsOfCurrentNode]) != 0:
            # add current node to sequence list and move to next node
            nextNode = nextBestNode(endCharsOfCurrentNode, startDict)
            currentSequence.append(currentNode)
            currentNode = nextNode
        else:
            # else there was no move available, break
            break
		}
		*/

	}
}
}

int main(){

	int wordLength = 5;
	int pos1 = wordLength - 2;
	int pos2 = wordLength - 3;
	vector<string> words;
	map<string, vector<string> >start;
	map<string, vector<string> >finish;

	readWordsFromFile(wordLength, pos1, pos2, start, finish); // returns a list of words from the dictionary of wordlength

	for (int i = 0; i<words.size();i++){
		cout << words[i] << endl;
	}

	string startVal;
	startVal = startValues(start, finish); // returns the best word to start on

	createSequence(start, finish, startVal, wordLength); // return the longest sequence found

}