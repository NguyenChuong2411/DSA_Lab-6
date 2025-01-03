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

    // Add a directed edge
    void addEdge(int u, int v)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Invalid edge! Vertex does not exist.\n";
            return;
        }
        adjList[u].push_back(v);
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

    // PageRank algorithm
    void pageRank(double dampingFactor = 0.85, int iterations = 100)
    {
        vector<double> rank(numVertices, 1.0 / numVertices);
        vector<double> newRank(numVertices, 0.0);

        for (int iter = 0; iter < iterations; ++iter)
        {
            fill(newRank.begin(), newRank.end(), (1.0 - dampingFactor) / numVertices);

            for (int u = 0; u < numVertices; ++u)
            {
                int outDegree = adjList[u].size();
                if (outDegree > 0)
                {
                    double distribute = rank[u] * dampingFactor / outDegree;
                    for (int v : adjList[u])
                    {
                        newRank[v] += distribute;
                    }
                }
                else
                {
                    double distribute = rank[u] * dampingFactor / numVertices;
                    for (int v = 0; v < numVertices; ++v)
                    {
                        newRank[v] += distribute;
                    }
                }
            }

            rank = newRank;
        }

        cout << fixed << setprecision(6);
        cout << "PageRank Values:\n";
        for (int i = 0; i < numVertices; ++i)
        {
            cout << "Vertex " << i << ": " << rank[i] << endl;
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

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    // Print adjacency list
    g.printAdjList();

    // Perform PageRank
    g.pageRank();
    system("pause");
    return 0;
}
