#include <bits/stdc++.h>

using namespace std;

vector<vector<bool> >readWordsFromFile(vector<string>& movies, vector<string>& actors, int& kb) {
    string   line;
    ifstream dictionary;

    vector<pair<int, int> > edge;


    dictionary.open("bacon2.txt");


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

    // for (int i = 0; i < movies.size(); i++) {
    //     cout << " id: " << i << " Movie: " << movies[i]  << endl;
    // } cout << endl;

    // for (int i = 0; i < actors.size(); i++) {
    //     cout << " id: " << i << " Actor: " << actors[i]  << endl;
    // } cout << endl;
    // cout << endl;
    // cout << "Number of Movies: " << movies.size() << " Number of Actors " << actors.size() << endl;
    vector<vector<bool> > graph(movies.size(), vector<bool>(actors.size(), false));

    /* -----------------------------------------------Data dump---------------------------------------------------- */

    for (int i = 0; i < edge.size(); i++) {
        graph[edge[i].first][edge[i].second] = true;
    } // cout << endl;
    return graph;
}

// Find actors with bacon factor 1
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
            if ((graph[common][j] == true) && (j != kb) && (find(maxFactor.begin(), maxFactor.end(), j) == maxFactor.end())) {
                maxFactor.push_back(j);
            }
        }
    }

    cout << endl << "Highest Factor of 1" << " for the following actors:" << endl;

    for (int i = 0; i < maxFactor.size(); i++) {
        cout << actors[maxFactor[i]] << ", ";
    }
    cout << endl << endl;
}

// Find minimum links between actors
int minLinkFactor(vector<string>& movies, vector<string>& actors, vector<vector<bool> >& graph,  string startingActor,  string goalActor) {
    queue<int> commonMovies;
    int saPos, gaPos;

    // find the id's of each actor
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i].compare(startingActor) == 0) {
            saPos = i;
        }

        if (actors[i].compare(goalActor) == 0) {
            gaPos = i;
        }

        // could put a break when they have both been found
    }


    queue<int>  relatedActors;
    queue<int>  relatedMovies;
    vector<int> movieRemoveList;
    vector<int> actorRemoveList;
    int c = 0;

    relatedActors.push(saPos);


    while (!relatedActors.empty()) {
        int nQ = relatedActors.size();
        c++;

        // cout << "Depth: " << c << endl;

        for (int x = 0; x < nQ; x++) {
            int currentActor = relatedActors.front();
            relatedActors.pop();

            for (int i = 0; i < movies.size(); i++) {
                if ((graph[i][currentActor] == true) && (find(movieRemoveList.begin(), movieRemoveList.end(), i) == movieRemoveList.end())) {
                    relatedMovies.push(i);

                    // cout << "Movie: " << movies[i] << endl;
                    movieRemoveList.push_back(i);
                }
            }

            int nQ = relatedMovies.size();

            while (!relatedMovies.empty()) {
                int currentMovie = relatedMovies.front();
                relatedMovies.pop();

                if (graph[currentMovie][gaPos] == true) {
                    return c;
                }

                for (int j = 0; j < actors.size(); j++) {
                    if ((graph[currentMovie][j] == true) && (find(actorRemoveList.begin(), actorRemoveList.end(), j) == actorRemoveList.end())) {
                        relatedActors.push(j);

                        // cout << "Actor: " << actors[j] << endl;
                        actorRemoveList.push_back(j);
                    }
                }
            }
        }
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

    // printGraph(graph, movies, actors);
    cout << kb << endl;

    // Part C prints all actors with the highest factor
    actorFactor(movies, actors, graph, kb);

    // Part A Finds the bacon Factor of a given actor
    // Answer should be 2
    string startActor = "Kevin Bacon (I)";

    // bacon1.txt
    // string startActor1 = "Willie Allemang";
    // bacon2.txt
    string goalActor = "Peter Crafts";

    int bflnk = minLinkFactor(movies, actors, graph, startActor, goalActor);
    cout << goalActor << " Has a Bacon Factor of  " << bflnk << endl << endl;

    // Part B Finds the minimum links between two given actors
    // answer should be 3
    // bacon1.txt
    // string startActor1 = "Willie Allemang";
    // string goalActor1  = "Matin Azizpour";

    // bacon2.txt
    string startActor1 = "Brad Pitt";
    string goalActor1  = "Taylor Fry";


    int minlnk = minLinkFactor(movies, actors, graph, startActor1, goalActor1);
    cout << "There are " << minlnk << " Minimum Links between " << startActor1 << " and " << goalActor1 << endl << endl;
}
