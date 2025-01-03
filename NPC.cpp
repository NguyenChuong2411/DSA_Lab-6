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

class GridGraph
{
private:
    vector<vector<int>> grid; // 2D grid for the game environment
    int rows, cols;

    struct Node
    {
        int x, y, cost;
        bool operator>(const Node &other) const
        {
            return cost > other.cost;
        }
    };

public:
    GridGraph(int r, int c) : rows(r), cols(c)
    {
        grid.resize(rows, vector<int>(cols, 0));
    }

    void setObstacle(int x, int y)
    {
        if (x >= 0 && x < rows && y >= 0 && y < cols)
        {
            grid[x][y] = 1; // Mark as obstacle
        }
    }

    void printGrid()
    {
        for (const auto &row : grid)
        {
            for (int cell : row)
            {
                cout << (cell == 1 ? "#" : ".") << " ";
            }
            cout << endl;
        }
    }

    vector<pair<int, int>> getNeighbors(int x, int y)
    {
        vector<pair<int, int>> neighbors;
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (const auto &dir : directions)
        {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0)
            {
                neighbors.push_back({nx, ny});
            }
        }

        return neighbors;
    }

    void aStarPathfinding(pair<int, int> start, pair<int, int> goal)
    {
        auto heuristic = [&](int x1, int y1, int x2, int y2)
        {
            return abs(x1 - x2) + abs(y1 - y2);
        };

        priority_queue<Node, vector<Node>, greater<>> pq;
        vector<vector<int>> cost(rows, vector<int>(cols, INT_MAX));
        vector<vector<pair<int, int>>> parents(rows, vector<pair<int, int>>(cols, {-1, -1}));

        pq.push({start.first, start.second, 0});
        cost[start.first][start.second] = 0;

        while (!pq.empty())
        {
            Node current = pq.top();
            pq.pop();

            if (current.x == goal.first && current.y == goal.second)
            {
                break;
            }

            for (const auto &neighbor : getNeighbors(current.x, current.y))
            {
                int nx = neighbor.first;
                int ny = neighbor.second;
                int newCost = cost[current.x][current.y] + 1;

                if (newCost < cost[nx][ny])
                {
                    cost[nx][ny] = newCost;
                    parents[nx][ny] = {current.x, current.y};
                    pq.push({nx, ny, newCost + heuristic(nx, ny, goal.first, goal.second)});
                }
            }
        }

        if (cost[goal.first][goal.second] == INT_MAX)
        {
            cout << "No path found from start to goal.\n";
            return;
        }

        // Trace the path
        vector<pair<int, int>> path;
        for (pair<int, int> at = goal; at != make_pair(-1, -1); at = parents[at.first][at.second])
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "Path found: \n";
        for (const auto &p : path)
        {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
};

int main()
{
    int rows = 5, cols = 5;
    GridGraph gameGrid(rows, cols);

    // Set obstacles
    gameGrid.setObstacle(1, 1);
    gameGrid.setObstacle(1, 2);
    gameGrid.setObstacle(1, 3);

    // Print the grid
    cout << "Game Grid:\n";
    gameGrid.printGrid();

    // Perform A* Pathfinding
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};
    gameGrid.aStarPathfinding(start, goal);
    system("pause");
    return 0;
}
