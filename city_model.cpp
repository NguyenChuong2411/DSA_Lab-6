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
    unordered_map<int, vector<pair<int, int>>> adjList; // Adjacency List with weights
    int numVertices;

public:
    Graph() : numVertices(0) {}

    // Add a vertex
    void addVertex()
    {
        numVertices++;
    }

    // Add an undirected edge with weight
    void addEdge(int u, int v, int weight)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Invalid edge! Vertex does not exist.\n";
            return;
        }
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
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

    // Find traffic bottlenecks using edge betweenness
    void findTrafficBottlenecks()
    {
        map<pair<int, int>, int> edgeBetweenness;

        for (int i = 0; i < numVertices; ++i)
        {
            vector<int> distances(numVertices, INT_MAX);
            vector<int> paths(numVertices, 0);
            vector<vector<int>> predecessors(numVertices);

            distances[i] = 0;
            paths[i] = 1;
            queue<int> q;
            q.push(i);

            while (!q.empty())
            {
                int current = q.front();
                q.pop();

                for (const auto &neighbor : adjList[current])
                {
                    int next = neighbor.first;
                    int weight = neighbor.second;

                    if (distances[next] > distances[current] + weight)
                    {
                        distances[next] = distances[current] + weight;
                        q.push(next);
                        predecessors[next].clear();
                        predecessors[next].push_back(current);
                        paths[next] = paths[current];
                    }
                    else if (distances[next] == distances[current] + weight)
                    {
                        predecessors[next].push_back(current);
                        paths[next] += paths[current];
                    }
                }
            }

            vector<double> dependency(numVertices, 0);
            stack<int> s;
            for (int j = 0; j < numVertices; ++j)
            {
                s.push(j);
            }

            while (!s.empty())
            {
                int node = s.top();
                s.pop();

                for (int pred : predecessors[node])
                {
                    double fraction = (double)paths[pred] / paths[node];
                    dependency[pred] += fraction * (1 + dependency[node]);

                    pair<int, int> edge = {min(pred, node), max(pred, node)};
                    edgeBetweenness[edge] += dependency[node];
                }
            }
        }

        cout << "Traffic Bottlenecks (Edge Betweenness):\n";
        for (const auto &entry : edgeBetweenness)
        {
            cout << "Edge " << entry.first.first << " - " << entry.first.second << ": " << entry.second << endl;
        }
    }

    // Suggest optimal traffic light timings
    void suggestTrafficLightTimings()
    {
        cout << "Traffic Light Timing Suggestions:\n";
        for (int i = 0; i < numVertices; ++i)
        {
            int degree = adjList[i].size();
            cout << "Node " << i << ": " << degree * 10 << " seconds green time." << endl;
        }
    }

    // Find alternative routes using Dijkstra's algorithm
    void findAlternativeRoutes(int start, int end)
    {
        vector<int> distances(numVertices, INT_MAX);
        distances[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start});

        vector<int> parents(numVertices, -1);

        while (!pq.empty())
        {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentNode == end)
            {
                break;
            }

            for (const auto &neighbor : adjList[currentNode])
            {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;
                int newDist = currentDist + edgeWeight;

                if (newDist < distances[nextNode])
                {
                    distances[nextNode] = newDist;
                    parents[nextNode] = currentNode;
                    pq.push({newDist, nextNode});
                }
            }
        }

        if (distances[end] == INT_MAX)
        {
            cout << "No route found from " << start << " to " << end << ".\n";
        }
        else
        {
            cout << "Alternative route from " << start << " to " << end << " (distance: " << distances[end] << "):\n";
            vector<int> route;
            for (int at = end; at != -1; at = parents[at])
            {
                route.push_back(at);
            }
            reverse(route.begin(), route.end());

            for (size_t i = 0; i < route.size(); ++i)
            {
                if (i > 0)
                    cout << " -> ";
                cout << route[i];
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;

    // Add vertices
    for (int i = 0; i < 6; ++i)
    {
        g.addVertex();
    }

    // Add roads (edges with weights)
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 4);
    g.addEdge(4, 5, 1);

    // Print adjacency list
    g.printAdjList();

    // Identify traffic bottlenecks
    g.findTrafficBottlenecks();

    // Suggest traffic light timings
    g.suggestTrafficLightTimings();

    // Find alternative routes
    g.findAlternativeRoutes(0, 5);
    system("pause");
    return 0;
}
