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
#include <functional>
using namespace std;

class NetworkGraph
{
private:
    unordered_map<int, vector<pair<int, int>>> adjList; // Device connections with weights
    int numDevices;

public:
    NetworkGraph() : numDevices(0) {}

    // Add a device
    void addDevice()
    {
        numDevices++;
    }

    // Add a connection between devices
    void addConnection(int u, int v, int weight)
    {
        if (u >= numDevices || v >= numDevices)
        {
            cout << "Invalid connection! Device does not exist.\n";
            return;
        }
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    // Print network topology
    void printTopology()
    {
        cout << "Network Topology:\n";
        for (const auto &pair : adjList)
        {
            cout << "Device " << pair.first << ": ";
            for (const auto &neighbor : pair.second)
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Find critical connections (bridges) in the network
    void findCriticalConnections()
    {
        vector<int> discovery(numDevices, -1);
        vector<int> low(numDevices, -1);
        vector<bool> visited(numDevices, false);
        int timer = 0;
        vector<pair<int, int>> criticalConnections;

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
                        criticalConnections.push_back({u, v});
                    }
                }
                else
                {
                    low[u] = min(low[u], discovery[v]);
                }
            }
        };

        for (int i = 0; i < numDevices; ++i)
        {
            if (!visited[i])
            {
                dfs(i, -1);
            }
        }

        cout << "Critical Connections in the Network:\n";
        for (const auto &connection : criticalConnections)
        {
            cout << "Connection " << connection.first << " - " << connection.second << endl;
        }
    }

    // Optimize network topology using Minimum Spanning Tree (Prim's Algorithm)
    void optimizeTopology()
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<bool> inMST(numDevices, false);
        vector<int> key(numDevices, INT_MAX);
        vector<int> parent(numDevices, -1);

        key[0] = 0;
        pq.push({0, 0});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (const auto &neighbor : adjList[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v])
                {
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "Optimized Network Topology (MST):\n";
        for (int i = 1; i < numDevices; ++i)
        {
            cout << "Connection " << parent[i] << " - " << i << " with weight " << key[i] << endl;
        }
    }
};

int main()
{
    NetworkGraph network;

    // Add devices
    for (int i = 0; i < 6; ++i)
    {
        network.addDevice();
    }

    // Add connections
    network.addConnection(0, 1, 4);
    network.addConnection(0, 2, 3);
    network.addConnection(1, 2, 1);
    network.addConnection(1, 3, 2);
    network.addConnection(3, 4, 5);
    network.addConnection(4, 5, 6);

    // Print network topology
    network.printTopology();

    // Find critical connections
    network.findCriticalConnections();

    // Optimize network topology
    network.optimizeTopology();
    system("pause");
    return 0;
}
