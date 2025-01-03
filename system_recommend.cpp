#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
#include <climits>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

class RecommendationSystem
{
private:
    unordered_map<int, vector<int>> userItemGraph; // User-Item Interaction Graph
    int numUsers;
    int numItems;

public:
    RecommendationSystem() : numUsers(0), numItems(0) {}

    // Add a user
    void addUser()
    {
        numUsers++;
    }

    // Add an item
    void addItem()
    {
        numItems++;
    }

    // Add a user-item interaction
    void addInteraction(int user, int item)
    {
        if (user >= numUsers || item >= numItems)
        {
            cout << "Invalid interaction! User or Item does not exist.\n";
            return;
        }
        userItemGraph[user].push_back(item);
    }

    // Print user-item interactions
    void printInteractions()
    {
        cout << "User-Item Interactions:\n";
        for (const auto &pair : userItemGraph)
        {
            cout << "User " << pair.first << ": ";
            for (int item : pair.second)
            {
                cout << item << " ";
            }
            cout << endl;
        }
    }

    // Recommend items using collaborative filtering
    void recommendItems(int user)
    {
        if (user >= numUsers)
        {
            cout << "Invalid user!\n";
            return;
        }

        unordered_map<int, int> itemScores; // Item -> Score

        // For each item interacted by the target user, find similar users
        for (int item : userItemGraph[user])
        {
            for (const auto &pair : userItemGraph)
            {
                if (pair.first == user)
                    continue;

                if (find(pair.second.begin(), pair.second.end(), item) != pair.second.end())
                {
                    for (int otherItem : pair.second)
                    {
                        if (find(userItemGraph[user].begin(), userItemGraph[user].end(), otherItem) == userItemGraph[user].end())
                        {
                            itemScores[otherItem]++;
                        }
                    }
                }
            }
        }

        // Sort items by score
        vector<pair<int, int>> scoredItems(itemScores.begin(), itemScores.end());
        sort(scoredItems.begin(), scoredItems.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.second > b.second; });

        cout << "Recommended items for user " << user << ":\n";
        for (const auto &item : scoredItems)
        {
            cout << "Item " << item.first << " with score " << item.second << endl;
        }
    }
};

int main()
{
    RecommendationSystem rs;

    // Add users
    rs.addUser();
    rs.addUser();
    rs.addUser();

    // Add items
    rs.addItem();
    rs.addItem();
    rs.addItem();
    rs.addItem();

    // Add interactions
    rs.addInteraction(0, 0);
    rs.addInteraction(0, 1);
    rs.addInteraction(1, 1);
    rs.addInteraction(1, 2);
    rs.addInteraction(2, 0);
    rs.addInteraction(2, 2);
    rs.addInteraction(2, 3);

    // Print interactions
    rs.printInteractions();

    // Recommend items for a user
    rs.recommendItems(0);
    system("pause");
    return 0;
}
