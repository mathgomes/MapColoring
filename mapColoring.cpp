#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include <vector>
#include <utility>
using namespace std;

bool isCommaOrSpaceOrDot(char c) {

    switch(c) {
    //case ',':
    case '.':
    case ' ':
        return true;
    default:
        return false;
    }
}
pair<string,int> searchInVector(pair<string,int> state, vector<pair<string,int> > &states, int *statesRead) {

    for( unsigned int j = 0; j < states.size(); j++) {

        if(get<0>(states[j]) == get<0>(state)) {
            cout << "Estado "<<  get<0>(state) << " ja existe, retorne\n";
            return states[j];
        }
    }
    get<1>(state) = states.size();
    states.push_back(state);
    cout << "Estado "<<  get<0>(state) << " nao existe " << "tamanho do vetor " << states.size() << " indice do vertice " << get<1>(state) << "\n";
    *statesRead = *statesRead + 1;
    return state;
}
bool** allocateGraph(int vertexNum) {
    bool **Graph = new bool*[vertexNum];
    for (int i = 0; i < vertexNum ; ++i) {
        Graph[i] = new bool[vertexNum];
    }
    for( int i = 0; i < vertexNum; i ++) {
        for( int j = 0; j < vertexNum; j ++) {
            Graph[i][j] = false;
        }
    }
    return Graph;
}
void addEdge(bool **Graph, int source, int destiny) {

    Graph[source][destiny] = true;
    Graph[destiny][source] = true;
}
void printfGraph(bool **Graph, int vertexNum) {
    cout << "\n";
    for (int i = 0; i < vertexNum; ++i) {
        for (int j = 0; j < vertexNum; ++j) {

           cout << Graph[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {


    int countriesNumber;
    char heuristic;
    cin >> countriesNumber;
    cin >> heuristic;

    string line;
    pair<string,int> mainState;
    pair<string,int> neighbour;
    vector < pair < string, int > > States;
    stringstream ss1;
    stringstream ss2;
    string neighbourLine;
    int statesRead = 0;

    bool **Country = allocateGraph(countriesNumber);

    cin.ignore();
    while( statesRead < countriesNumber ) {

        getline(cin,line);
        ss1 << line;
        getline(ss1, get<0>(mainState), ':');
        get<0>(mainState).erase(
            remove_if(get<0>(mainState).begin(),get<0>(mainState).end(), &isCommaOrSpaceOrDot),get<0>(mainState).end()
        );
        mainState = searchInVector(mainState,States,&statesRead);

        while (getline(ss1, neighbourLine, '.')) {

            ss2 << neighbourLine;
            while(getline(ss2, get<0>(neighbour), ',')) {

                get<0>(neighbour).erase(
                    remove_if(get<0>(neighbour).begin(),get<0>(neighbour).end(), &isCommaOrSpaceOrDot),get<0>(neighbour).end()
                );
                neighbour = searchInVector(neighbour,States,&statesRead);
                cout << "Adicionar aresta entre " << get<0>(mainState) << " " << get<1>(mainState) << "   " << get<0>(neighbour) << " " << get<1>(neighbour) << "\n";
                addEdge(Country,get<1>(mainState),get<1>(neighbour));
            }
            ss2.clear();
        }
        ss1.clear();

    }


    for ( unsigned int i = 0; i < States.size(); i ++) {
        cout << "\n" << get<0>(States[i]) << ", " << get<1>(States[i]) << "\n";
    }
    printfGraph(Country,countriesNumber);


    switch(heuristic) {

    case 'a':
        // backtracking comum

        break;
    case 'b':

        // backtracking + forward checking
        break;
    case 'c':
        // backtracking + fc + mrv

        break;
    case 'd':
        // bt + fc + mrv + grau

        break;

    }


    system("PAUSE");
    return 0;
}
