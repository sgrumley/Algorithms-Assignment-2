#include <bits/stdc++.h>

using namespace std;

void readWordsFromFile(unordered_map<string, list<string> >& movies, vector<string>& kbMovies) {
    string   line;
    ifstream dictionary;


    dictionary.open("bacon2.txt");


    while (!dictionary.eof()) {
        string actor, movie;
        getline(dictionary, actor, '|');
        getline(dictionary, movie);

        // add the word to the start array based on the second and third characters
        if (movies.count(movie) == 1) {
            // append word to value
            movies[movie].push_back(actor);
        } else {
            // create key and value
            list<string> tmp;
            tmp.push_back(actor);
            movies.insert(pair<string, list<string> >(movie, tmp));
        }

        // if start doesn't have any keys
        if (movies.size() == 0) {
            // append the word to both disctionaries
            list<string> tmp;
            tmp.push_back(actor);
            movies.insert(pair<string, list<string> >(movie, tmp));
        }

        if (actor.compare("Kevin Bacon (I)") == 0) {
            kbMovies.push_back(movie);
        }
    }
}

void bFactor(unordered_map<string, list<string> >& movies, vector<string>& kbMovies) {
    for (int i = 0; i < kbMovies.size(); i++) {
        cout << kbMovies[i] << ':' << endl;

        for (auto v : movies[kbMovies[i]]) {
            cout << v << ", ";
        }
    }
}

int main() {
    // main
    unordered_map<string, list<string> > movies;
    vector<string> kbMovies;

    readWordsFromFile(movies, kbMovies);
    bFactor(movies, kbMovies);
}
