#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
using namespace std;

class Graph
{
private:
    unordered_map<int, vector<int>> adjList; // Adjacency List
    vector<vector<int>> adjMatrix;           // Adjacency Matrix
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
            row.push_back(0);
        }
        adjMatrix.push_back(vector<int>(numVertices, 0));
    }

    // Add an edge
    void addEdge(int u, int v)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Invalid edge! Vertex does not exist.\n";
            return;
        }

        // Update adjacency list
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Assuming undirected graph

        // Update adjacency matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // Assuming undirected graph
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

    // Print adjacency matrix
    void printAdjMatrix()
    {
        cout << "Adjacency Matrix:\n";
        for (const auto &row : adjMatrix)
        {
            for (const auto &val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    // Recursive DFS helper
    void dfsRecursiveHelper(int v, set<int> &visited)
    {
        cout << v << " ";
        visited.insert(v);

        for (int neighbor : adjList[v])
        {
            if (visited.find(neighbor) == visited.end())
            {
                dfsRecursiveHelper(neighbor, visited);
            }
        }
    }

    // Perform DFS (Recursive)
    void dfsRecursive(int start)
    {
        set<int> visited;
        cout << "DFS (Recursive): ";
        dfsRecursiveHelper(start, visited);
        cout << endl;
    }

    // Perform DFS (Iterative)
    void dfsIterative(int start)
    {
        set<int> visited;
        stack<int> s;
        s.push(start);

        cout << "DFS (Iterative): ";
        while (!s.empty())
        {
            int v = s.top();
            s.pop();

            if (visited.find(v) == visited.end())
            {
                cout << v << " ";
                visited.insert(v);
            }

            for (auto it = adjList[v].rbegin(); it != adjList[v].rend(); ++it)
            {
                if (visited.find(*it) == visited.end())
                {
                    s.push(*it);
                }
            }
        }
        cout << endl;
    }

    // Perform BFS
    void bfs(int start)
    {
        set<int> visited;
        queue<int> q;
        vector<int> traversalOrder;

        q.push(start);
        visited.insert(start);

        cout << "BFS: ";
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
            traversalOrder.push_back(v);

            for (int neighbor : adjList[v])
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main()
{
    Graph g;

    // Add vertices
    g.addVertex();
    g.addVertex();
    g.addVertex();

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(0, 2);

    // Print adjacency list and matrix
    g.printAdjList();
    g.printAdjMatrix();

    // Perform DFS
    g.dfsRecursive(0);
    g.dfsIterative(0);

    // Perform BFS
    g.bfs(0);
    system("pause");
    return 0;
}
