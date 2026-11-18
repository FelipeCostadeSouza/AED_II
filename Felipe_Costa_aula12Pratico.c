#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

//Foi usado o código BFS do GeeksforGeeks
//BFS como dito na atividade teórica, é superior a DFS em encontrar o menor caminho
struct Coords {
    int r, c;
};

void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}
bool bfs_shortest_path(vector<vector<int>>& adj, int src, int dest, vector<int>& parent) {
    int V = adj.size();
    vector<bool> visited(V, false);
    queue<int> q;

    visited[src] = true;
    q.push(src);
    parent[src] = -1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == dest) {
            return true;
        }

        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                parent[x] = curr; 
                q.push(x);
            }
        }
    }
    
    return false; 
}

int main() {
    vector<string> maze = {
        "S.#....",
        "#...#.#",
        "#..#...",
        "..#####",
        ".#.....",
        ".#.#..#",
        "....#.E"
    };

    int N = maze.size();
    int M = maze[0].size();


    vector<vector<int>> idMap(N, vector<int>(M, -1));
    vector<Coords> coordMap;
    
    int vertexCount = 0;
    int src = -1, dest = -1;
  
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (maze[r][c] != '#') {
                idMap[r][c] = vertexCount;
                coordMap.push_back({r, c});
                
                if (maze[r][c] == 'S') src = vertexCount;
                if (maze[r][c] == 'E') dest = vertexCount;
                
                vertexCount++;
            }
        }
    }

    vector<vector<int>> adj(vertexCount);
    int dr[] = {-1, 1, 0, 0}; 
    int dc[] = {0, 0, -1, 1}; 

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (idMap[r][c] != -1) {
                int u = idMap[r][c];
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                  
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M && idMap[nr][nc] != -1) {
                        int v = idMap[nr][nc];
                        if (u < v) {
                            addEdge(adj, u, v);
                        }
                    }
                }
            }
        }
    }

    vector<int> parent(vertexCount, -1);
    bool found = bfs_shortest_path(adj, src, dest, parent);

    if (!found) {
        cout << "O labirinto e insoluvel." << endl;
    } else {
        vector<Coords> path;
        int curr = dest;
        while (curr != -1) {
            path.push_back(coordMap[curr]);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        cout << "Labirinto solucionado com sucesso!" << endl;
        cout << "Tamanho total do caminho (passos/vertices): " << path.size() << endl;
        cout << "Sequencia exata de coordenadas (linha, coluna):" << endl;
        for (const auto& p : path) {
            cout << "(" << p.r << ", " << p.c << ") ";
        }
        cout << endl;
    }

    return 0;
}
