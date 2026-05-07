#include <omp.h>
#include <iostream>
#include <stack>

using namespace std;

int main() {

    int n = 5;

    int graph[5][5] = {
        {0,1,1,0,0},
        {1,0,0,1,0},
        {1,0,0,1,1},
        {0,1,1,0,0},
        {0,0,1,0,0}
    };

    bool visited[5] = {false};

    stack<int> s;

    int start = 0;

    s.push(start);

    cout << "DFS Traversal: ";

    while (!s.empty()) {

        int node = s.top();
        s.pop();

        if (!visited[node]) {

            visited[node] = true;

            cout << node << " ";

            #pragma omp parallel for
            for (int i = n - 1; i >= 0; i--) {

                if (graph[node][i] == 1 && !visited[i]) {

                    #pragma omp critical
                    {
                        if (!visited[i]) {
                            s.push(i);
                        }
                    }
                }
            }
        }
    }

    return 0;
}