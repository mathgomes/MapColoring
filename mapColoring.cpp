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
bool isInVector(string a, vector<pair<string,int> > &states) {

    for( unsigned int j = 0; j < states.size(); j++) {

        if(get<0>(states[j]) == a) {
            return true;
        }
    }
    return false;
}
int main() {


    int countriesNumber;
    char heuristic;
    char c;
    cin >> countriesNumber;
    cin >> heuristic;

    // ou usar stringstream
    string line;
    string mainState;
    pair<string,int> neighbour;
    vector < pair < string, int > > neighbourStates;
    int i = 0;
    cin.ignore();
    for ( int j =0; j < countriesNumber; j ++) {

        getline(cin,line);
        stringstream ss(line);
        getline(ss, mainState, ':');

        while(getline(ss, get<0>(neighbour), ',')) {
            get<0>(neighbour).erase(
                remove_if(get<0>(neighbour).begin(),get<0>(neighbour).end(), &isCommaOrSpaceOrDot),get<0>(neighbour).end()
            );
            if(!isInVector(get<0>(neighbour),neighbourStates)) {
                get<1>(neighbour) = neighbourStates.size();
                neighbourStates.push_back(neighbour);
            }
        }
    }
    for ( unsigned int i =0; i< neighbourStates.size(); i ++) {
        cout << "\n" << get<0>(neighbourStates[i]) << ", " << get<1>(neighbourStates[i]) << "\n";
    }

    return 0;
}
