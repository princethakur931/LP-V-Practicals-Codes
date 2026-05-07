#include <omp.h>
#include <iostream>
#include <queue>

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

    queue<int> q;

    int start = 0;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {

            if (graph[node][i] == 1 && !visited[i]) {

                #pragma omp critical
                {
                    if (!visited[i]) {
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
        }
    }

    return 0;
}