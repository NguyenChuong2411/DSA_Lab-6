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
    unordered_map<int, vector<pair<int, int>>> adjList; // Adjacency List with weights
    int numVertices;

public:
    Graph() : numVertices(0) {}

    // Add a vertex
    void addVertex()
    {
        numVertices++;
    }

    // Add a directed edge with weight
    void addEdge(int u, int v, int weight)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Invalid edge! Vertex does not exist.\n";
            return;
        }
        adjList[u].push_back({v, weight});
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
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra's algorithm using priority queue
    void dijkstra(int start)
    {
        vector<int> distances(numVertices, INT_MAX);
        distances[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDist > distances[currentNode])
            {
                continue;
            }

            for (const auto &neighbor : adjList[currentNode])
            {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (distances[currentNode] + edgeWeight < distances[nextNode])
                {
                    distances[nextNode] = distances[currentNode] + edgeWeight;
                    pq.push({distances[nextNode], nextNode});
                }
            }
        }

        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < numVertices; ++i)
        {
            if (distances[i] == INT_MAX)
            {
                cout << i << ": INF\n";
            }
            else
            {
                cout << i << ": " << distances[i] << "\n";
            }
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
                    for (const auto &neighbor : adjList[u])
                    {
                        newRank[neighbor.first] += distribute;
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

    // Add edges with weights
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);

    // Print adjacency list
    g.printAdjList();

    // Perform Dijkstra's algorithm
    g.dijkstra(0);

    // Perform PageRank
    g.pageRank();
    system("pause");
    return 0;
}
