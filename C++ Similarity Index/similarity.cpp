#include<bits/stdc++.h>
#include <cmath>
#include "cosine.h"
#include "edit.h"
#include "jaro.h"
#include "jaccard.h"
using namespace std;

int main() {
    char filename1[100], filename2[100];
    cout << "Enter file filename1: ";
    cin >> filename1;
    cout << "Enter file filename2: ";
    cin >> filename2;
    string str1;
    string str2;
    string buffer;
    ifstream input1(filename1);
    while (getline(input1, buffer))
        str1 += (buffer + '\n');
    ifstream input2(filename2);
    while (getline(input2, buffer))
        str2 += (buffer + '\n');

    //cosine
    unordered_map<string, int>freq1;
    unordered_map<string, int>freq2;
    countOccurences(freq1, str1);
    countOccurences(freq2, str2);
    double mod1 = sqrt(sum(freq1));
    double mod2 = sqrt(sum(freq2));
    double dotsum = dotprod(freq1, freq2);
    double cosSim = dotsum / (mod1 * mod2);
    cout << "cosine similarity: " << cosSim << endl;

    //jaccard
    const double M = max(str1.size(), str2.size());
    const double jaccard_dist = jaccard(str1, str2) / M;
    const double jacSim = (1 - jaccard_dist);
    cout << "jaccard similarity: " << jacSim << endl;

    //jaro
    const double maximum = max(str1.size(), str2.size());
    const double index = jaro(str1, str2);
    cout << "jaro-winkler similarity: " << jaro_winkler(str1, str2) << endl;

    //edit
    const double maxi = max(str1.size(), str2.size());
    const double editDist = editDistance(str1, str2) / maxi;
    const double editSim = (1 - editDist);
    cout << "edit_distance similarity: " << editSim << endl;

    // average
     double average = (cosSim + jacSim + jaro_winkler(str1, str2) + editSim ) / 4;
     cout << "Average: " << round(average) << endl;

    // Decision
    if (average >= 1)
    {
        cout << "Plagiarised" << endl;
    }

    else 
    cout << "Not Plagiarised" << endl;


    return 0;
}


