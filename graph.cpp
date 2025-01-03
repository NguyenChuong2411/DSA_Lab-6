#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
#include <climits>
#include <map>
#include <algorithm>
#include <functional>
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

    // Find all connected components using DFS
    void findConnectedComponents()
    {
        set<int> visited;
        vector<vector<int>> components;

        for (int i = 0; i < numVertices; ++i)
        {
            if (visited.find(i) == visited.end())
            {
                vector<int> component;
                stack<int> s;
                s.push(i);

                while (!s.empty())
                {
                    int v = s.top();
                    s.pop();

                    if (visited.find(v) == visited.end())
                    {
                        visited.insert(v);
                        component.push_back(v);

                        for (const auto &neighbor : adjList[v])
                        {
                            if (visited.find(neighbor.first) == visited.end())
                            {
                                s.push(neighbor.first);
                            }
                        }
                    }
                }

                components.push_back(component);
            }
        }

        cout << "Connected Components:\n";
        for (const auto &component : components)
        {
            for (int vertex : component)
            {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }

    // Find all bridges in the graph
    void findBridges()
    {
        vector<int> discovery(numVertices, -1);
        vector<int> low(numVertices, -1);
        vector<bool> visited(numVertices, false);
        int timer = 0;
        vector<pair<int, int>> bridges;

        function<void(int, int)> dfs = [&](int u, int parent)
        {
            visited[u] = true;
            discovery[u] = low[u] = timer++;

            for (const auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                if (v == parent)
                    continue;

                if (!visited[v])
                {
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);

                    if (low[v] > discovery[u])
                    {
                        bridges.emplace_back(u, v);
                    }
                }
                else
                {
                    low[u] = min(low[u], discovery[v]);
                }
            }
        };

        for (int i = 0; i < numVertices; ++i)
        {
            if (!visited[i])
            {
                dfs(i, -1);
            }
        }

        cout << "Bridges in the graph:\n";
        for (const auto &bridge : bridges)
        {
            cout << bridge.first << " - " << bridge.second << endl;
        }
    }

    // Louvain Method for community detection
    void louvainCommunityDetection()
    {
        vector<int> community(numVertices);
        for (int i = 0; i < numVertices; ++i)
        {
            community[i] = i;
        }

        bool improvement = true;
        while (improvement)
        {
            improvement = false;
            for (int i = 0; i < numVertices; ++i)
            {
                map<int, int> neighborCommunities;
                for (const auto &neighbor : adjList[i])
                {
                    int comm = community[neighbor.first];
                    neighborCommunities[comm] += neighbor.second;
                }

                int maxCommunity = community[i];
                int maxWeight = 0;
                for (const auto &pair : neighborCommunities)
                {
                    int comm = pair.first;
                    int weight = pair.second;
                    {
                        if (weight > maxWeight)
                        {
                            maxWeight = weight;
                            maxCommunity = comm;
                        }
                    }

                    if (maxCommunity != community[i])
                    {
                        community[i] = maxCommunity;
                        improvement = true;
                    }
                }
            }

            cout << "Communities detected:\n";
            for (int i = 0; i < numVertices; ++i)
            {
                cout << "Vertex " << i << " -> Community " << community[i] << endl;
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
    g.addVertex();
    g.addVertex();

    // Add edges with weights
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 3);
    g.addEdge(1, 4, 5);

    // Print adjacency list and matrix
    g.printAdjList();
    g.printAdjMatrix();

    // Perform Dijkstra's algorithm
    g.dijkstra(0);

    // Find connected components
    g.findConnectedComponents();

    // Find bridges
    g.findBridges();

    // Perform Louvain community detection
    g.louvainCommunityDetection();
    system("pause");
    return 0;
}
