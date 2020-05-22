#include <bits/stdc++.h>

using namespace std;

void readWordsFromFileMapped(unordered_map<string, list<string> >& movies, vector<string>& kbMovies) {
    string   line;
    ifstream dictionary;


    dictionary.open("bacon1.txt");

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

vector<vector<bool> >readWordsFromFile(vector<string>& movies, vector<string>& actors, int& kb) {
    string   line;
    ifstream dictionary;

    // vector<vector<bool> >   graph;
    vector<pair<int, int> > edge;


    dictionary.open("bacon0.txt");

    // /int kb;

    while (!dictionary.eof()) {
        string actor, movie;
        getline(dictionary, actor, '|');
        getline(dictionary, movie);

        // check if the movie exists in movies
        int actorPos = -1;
        int moviePos = -1;

        for (int i = 0; i < actors.size(); i++) {
            if (actors[i].compare(actor) == 0) {
                actorPos = i;
                break;
            }
        }

        for (int i = 0; i < movies.size(); i++) {
            if (movies[i].compare(movie) == 0) {
                moviePos = i;
                break;
            }
        }

        if (actorPos == -1) {
            actors.push_back(actor);
            actorPos = actors.size() - 1;
        }

        if (moviePos == -1) {
            movies.push_back(movie);
            moviePos = movies.size() - 1;
        }

        if (actor.compare("Kevin Bacon (I)") == 0) {
            kb = actorPos;
        }

        pair<int, int> tmp(moviePos, actorPos);
        edge.push_back(tmp);
    }

    /* -----------------------------------------------Data dump---------------------------------------------------- */
    for (int i = 0; i < movies.size(); i++) {
        cout << " id: " << i << " Movie: " << movies[i]  << endl;
    } cout << endl;

    for (int i = 0; i < actors.size(); i++) {
        cout << " id: " << i << " Actor: " << actors[i]  << endl;
    } cout << endl;
    cout << endl;
    cout << "Number of Movies: " << movies.size() << " Number of Actors " << actors.size() << endl;
    vector<vector<bool> > graph(movies.size(), vector<bool>(actors.size(), false));

    /* -----------------------------------------------Data dump---------------------------------------------------- */

    for (int i = 0; i < edge.size(); i++) {
        cout << edge[i].first << " " << edge[i].second << endl;
        graph[edge[i].first][edge[i].second] = true;
    } cout << endl;
    return graph;
}

void actorFactor(vector<string>& movies, vector<string>& actors, vector<vector<bool> >& graph, int kb) {
    vector<int> maxFactor;
    queue<int>  commonMovies;

    for (int i = 0; i < movies.size(); i++) {
        if (graph[i][kb] == true) {
            commonMovies.push(i);
        }
    }

    while (!commonMovies.empty()) {
        int common = commonMovies.front();
        commonMovies.pop();

        for (int j = 0; j < actors.size(); j++) {
            if ((graph[common][j] == true) && (j != kb)) {
                maxFactor.push_back(j);
            }
        }
    }

    cout << "Highest Factor of " << " for the following actors:" << endl;

    for (int i = 0; i < maxFactor.size(); i++) {
        cout << actors[maxFactor[i]] << endl;
    }
    cout << endl << endl;
}

int minLinkFactor(vector<string>& movies, vector<string>& actors, vector<vector<bool> >& graph,  string startActor,  string goalActor) {
    queue<int> commonMovies;
    int saPos, gaPos;
    vector<int> movieRemoveList;

    // find the id's of each actor
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i].compare(startActor) == 0) {
            saPos = i;
        }

        if (actors[i].compare(goalActor) == 0) {
            gaPos = i;
        }

        // could put a break when they have both been found
    }

    // push starting actor into queue
    commonMovies.push(saPos);

    int c = 0;

    while (!commonMovies.empty()) {
        int common = commonMovies.front();
        commonMovies.pop();

        // add common movies into queue
        for (int i = 0; i < movies.size(); i++) {
            if ((graph[i][saPos] == true) && (find(movieRemoveList.begin(), movieRemoveList.end(), i) == movieRemoveList.end())) {
                cout << i << " ";
                commonMovies.push(i);
                cout << "Actor: " << movies[i] << endl;
                movieRemoveList.push_back(i);
            }
        } cout << endl;

        int nQ = commonMovies.size();
        c++;

        // iterate over elements added
        // for (int i = 0; i < nQ; ++i) {
        // for those common movies check if the goal actor is in that movie
        cout << "Movie: " << movies[common] << endl;

        for (int j = 0; j < actors.size(); j++) {
            if (graph[common][gaPos] == true) {
                return c;
            }
        }

        // }
    }
    return 0;
}

void printGraph(vector<vector<bool> >& graph, vector<string>& movies, vector<string>& actors) {
    for (int i = 0; i < actors.size(); i++) {
        for (int j = 0; j < movies.size(); j++) {
            cout << graph[i][j] << " ";
        } cout << endl;
    }
}

int main() {
    // main
    // unordered_map<string, list<string> > movies;
    vector<string> movies;
    vector<string> actors;
    vector<vector<bool> > graph;
    int kb;

    graph = readWordsFromFile(movies, actors, kb);

    printGraph(graph, movies, actors);

    // Part C prints all actors with the highest factor
    actorFactor(movies, actors, graph, kb);

    // Part A Finds the bacon Factor of a given actor
    // Answer should be 2
    string startActor = "Kevin Bacon (I)";
    string goalActor  = "Willie Allemang";
    int    bflnk      = minLinkFactor(movies, actors, graph, startActor, goalActor);
    cout << goalActor << "Has a Bacon Factor of  " << bflnk << endl << endl;

    // Part B Finds the minimum links between two given actors
    // answer should be 3
    string startActor1 = "Willie Allemang";
    string goalActor1  = "Matin Azizpour";

    // int    minlnk      = minLinkFactor(movies, actors, graph, startActor, goalActor);
    // cout << "There are " << minlnk << "Minimum Links between " << startActor1 << " and " << goalActor1 << endl << endl;
}
