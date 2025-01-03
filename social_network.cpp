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

class Graph
{
private:
    unordered_map<int, vector<int>> adjList; // Adjacency List
    int numVertices;

public:
    Graph() : numVertices(0) {}

    // Add a vertex
    void addVertex()
    {
        numVertices++;
    }

    // Add an undirected edge
    void addEdge(int u, int v)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Invalid edge! Vertex does not exist.\n";
            return;
        }
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Print adjacency list
    void printAdjList()
    {
        cout << "Adjacency List:\n";
        for (const auto &pair : adjList)
        {
            cout << pair.first << ": ";
            for (const auto &neighbor : pair.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Find degree centrality
    void degreeCentrality()
    {
        vector<pair<int, int>> centrality;
        for (const auto &pair : adjList)
        {
            centrality.emplace_back(pair.first, pair.second.size());
        }

        sort(centrality.begin(), centrality.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });

        cout << "Degree Centrality:\n";
        for (const auto &entry : centrality)
        {
            cout << "Node " << entry.first << ": " << entry.second << endl;
        }
    }

    // Community detection using connected components
    void detectCommunities()
    {
        vector<bool> visited(numVertices, false);
        vector<vector<int>> communities;

        for (int i = 0; i < numVertices; ++i)
        {
            if (!visited[i])
            {
                vector<int> community;
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();
                    community.push_back(node);

                    for (int neighbor : adjList[node])
                    {
                        if (!visited[neighbor])
                        {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }

                communities.push_back(community);
            }
        }

        cout << "Communities Detected:\n";
        for (const auto &community : communities)
        {
            cout << "Community: ";
            for (int node : community)
            {
                cout << node << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;

    // Add vertices
    g.addVertex();
    g.addVertex();
    g.addVertex();
    g.addVertex();
    g.addVertex();
    g.addVertex();

    // Add friendships (edges)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    // Print adjacency list
    g.printAdjList();

    // Find degree centrality
    g.degreeCentrality();

    // Detect communities
    g.detectCommunities();
    system("pause");
    return 0;
}
