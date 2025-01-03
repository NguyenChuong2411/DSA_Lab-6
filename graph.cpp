#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
#include <climits>
using namespace std;

class Graph
{
private:
    unordered_map<int, vector<pair<int, int>>> adjList; // Adjacency List with weights
    vector<vector<int>> adjMatrix;                      // Adjacency Matrix
    int numVertices;

public:
    Graph() : numVertices(0) {}

    // Add a vertex
    void addVertex()
    {
        numVertices++;

        // Add a new row and column in the adjacency matrix
        for (auto &row : adjMatrix)
        {
            row.push_back(INT_MAX);
        }
        adjMatrix.push_back(vector<int>(numVertices, INT_MAX));
        for (int i = 0; i < numVertices; ++i)
        {
            adjMatrix[i][i] = 0; // Distance to itself is zero
        }
    }

    // Add an edge with weight
    void addEdge(int u, int v, int weight)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Invalid edge! Vertex does not exist.\n";
            return;
        }

        // Update adjacency list
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Assuming undirected graph

        // Update adjacency matrix
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // Assuming undirected graph
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

    // Print adjacency matrix
    void printAdjMatrix()
    {
        cout << "Adjacency Matrix:\n";
        for (const auto &row : adjMatrix)
        {
            for (const auto &val : row)
            {
                if (val == INT_MAX)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << val << " ";
                }
            }
            cout << endl;
        }
    }

    // Perform Dijkstra's algorithm
    void dijkstra(int start)
    {
        vector<int> distances(numVertices, INT_MAX);
        set<pair<int, int>> minHeap;

        distances[start] = 0;
        minHeap.insert({0, start});

        while (!minHeap.empty())
        {
            int u = minHeap.begin()->second;
            minHeap.erase(minHeap.begin());

            for (const auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distances[u] + weight < distances[v])
                {
                    minHeap.erase({distances[v], v});
                    distances[v] = distances[u] + weight;
                    minHeap.insert({distances[v], v});
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
};

int main()
{
    Graph g;

    // Add vertices
    g.addVertex();
    g.addVertex();
    g.addVertex();

    // Add edges with weights
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 7);

    // Print adjacency list and matrix
    g.printAdjList();
    g.printAdjMatrix();

    // Perform Dijkstra's algorithm
    g.dijkstra(0);
    system("pause");
    return 0;
}
