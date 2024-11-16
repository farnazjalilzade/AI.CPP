#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Node {
public:
    int id;
    vector<pair<int, int>> route;
    int costSum;

    Node(int i, vector<pair<int, int>> r, int c) {
        id = i;
        route = r;
        costSum = c;
    }
};

class Problem {
public:
    vector<vector<int>> matrix;
    int target;

    Problem(vector<vector<int>> m, int t) {
        matrix = m;
        target = t;
    }

    bool isGoal(int current) {
        return current == target;
    }
};

class BFS {
public:
    void search(Problem p, int start) {
        int n = p.matrix.size();
        vector<bool> visit(n, false);
        queue<Node> q;
        q.push(Node(start, {{start, 0}}, 0));
        visit[start] = true;

        cout << "BFS Order: ";
        while (!q.empty()) {
            Node now = q.front();
            q.pop();
            cout << now.id << " (cost: " << now.costSum << ") ";

            if (p.isGoal(now.id)) {
                cout << "\nBFS Path: ";
                for (auto r : now.route) {
                    cout << r.first << "(cost: " << r.second << ") ";
                }
                cout << "\nTotal Cost: " << now.costSum << endl;
                return;
            }

            for (int j = 0; j < n; j++) {
                if (p.matrix[now.id][j] > 0 && !visit[j]) {
                    visit[j] = true;
                    vector<pair<int, int>> newRoute = now.route;
                    newRoute.push_back({j, p.matrix[now.id][j]});
                    q.push(Node(j, newRoute, now.costSum + p.matrix[now.id][j]));
                }
            }
        }
        cout << "\nNo solution found using BFS.\n";
    }
};

class DFS {
public:
    void search(Problem p, int start) {
        int n = p.matrix.size();
        vector<bool> visit(n, false);
        stack<Node> st;
        st.push(Node(start, {{start, 0}}, 0));

        cout << "DFS Order: ";
        while (!st.empty()) {
            Node now = st.top();
            st.pop();

            if (visit[now.id]) continue;
            visit[now.id] = true;
            cout << now.id << " (cost: " << now.costSum << ") ";

            if (p.isGoal(now.id)) {
                cout << "\nDFS Path: ";
                for (auto r : now.route) {
                    cout << r.first << "(cost: " << r.second << ") ";
                }
                cout << "\nTotal Cost: " << now.costSum << endl;
                return;
            }

            for (int j = n - 1; j >= 0; j--) {
                if (p.matrix[now.id][j] > 0 && !visit[j]) {
                    vector<pair<int, int>> newRoute = now.route;
                    newRoute.push_back({j, p.matrix[now.id][j]});
                    st.push(Node(j, newRoute, now.costSum + p.matrix[now.id][j]));
                }
            }
        }
        cout << "\nNo solution found using DFS.\n";
    }
};

int main() {
    vector<vector<int>> graph = {
        {0, 3, 1, 0},
        {3, 0, 4, 0},
        {0, 4, 0, 5},
        {0, 0, 5, 0}
    };

    int goal = 3;
    Problem prob(graph, goal);
    int startPoint = 0;

    BFS bfsAlgo;
    cout << "Running BFS:\n";
    bfsAlgo.search(prob, startPoint);

    DFS dfsAlgo;
    cout << "\nRunning DFS:\n";
    dfsAlgo.search(prob, startPoint);

    return 0;
}