#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>

using namespace std;

vector<vector<int>> graph;
vector<int> visited;


void addEdge(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);   // Undirected graph
}

void parallelBFS(int start)
{
    queue<int> q;

    q.push(start);
    visited[start] = 1;

    cout << "\nBFS Traversal: ";

    double start_time = omp_get_wtime();

    while(!q.empty())
    {
        int node = q.front();
        q.pop();

        cout << node << " ";

        #pragma omp parallel for
        for(int i = 0; i < graph[node].size(); i++)
        {
            int neighbor = graph[node][i];

            #pragma omp critical
            {
                if(!visited[neighbor])
                {
                    visited[neighbor] = 1;
                    q.push(neighbor);
                }
            }
        }
    }

    double end_time = omp_get_wtime();

    cout << "\nExecution Time: "
         << end_time - start_time << " seconds\n";
}

int main()
{
    omp_set_num_threads(4);

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    graph.resize(vertices);
    visited.resize(vertices, 0);

    cout << "Enter edges:\n";

    for(int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;

        addEdge(u, v);
    }

    parallelBFS(0);

    return 0;
}

//g++ -fopenmp BFS.cpp -o bfs

//.\bfs.exe