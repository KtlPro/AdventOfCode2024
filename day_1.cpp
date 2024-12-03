#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    using namespace std;
    ifstream file("input.txt");
    if (!file)
    {
        return 1;
    }

    // current line of input
    string line;

    // vectors for storing the two lists of numbers
    vector<int> list_a;
    vector<int> list_b;

    while (getline(file, line))
    {
        // split the line into tokens
        vector<std::string> tokens;
        istringstream iss(line);
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(tokens));

        string token_a = tokens[0];
        string token_b = tokens[1];

        // convert the tokens to integers and add them to the lists
        list_a.push_back(stoi(token_a));
        list_b.push_back(stoi(token_b));
    }

    // sort the lists
    sort(list_a.begin(), list_a.end());
    sort(list_b.begin(), list_b.end());

    // Part A - calculate the total distance between the two lists
    int total_distance = 0;

    for (int i = 0; i < list_a.size(); i++)
    {
        int distance = abs(list_b[i] - list_a[i]);
        total_distance += distance;
    }

    cout << "Total distance: " << total_distance << endl;

    // Part B - calculate the similarity score between the two lists
    int similarity_score = 0;

    for (int i = 0; i < list_a.size(); i++)
    {
        int location_number = list_a[i];
        int number_of_occurrences = count(list_b.begin(), list_b.end(), location_number);

        similarity_score += (location_number * number_of_occurrences);
    }

    cout << "Similarity score: " << similarity_score << endl;

    return 0;
}