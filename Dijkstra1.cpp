//https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm
//http://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
#include <cstdio>
#include <vector>
#include <algorithm>
//#include <limits.h>
// #include <deque>

using namespace std;
const int inf = 1 << 30; //or INT_MAX in limits.h

// Function to print shortest path from source to j
// using parent array
void printPath(vector<int> shortest, int j)
{
  // Base Case : If j is source
  if (shortest[j] == -1)
    return;

  printPath(shortest, shortest[j]);

  printf("%d ", j);
}

// A utility function to print the constructed distance
// array
void printSolution(vector<int> dist, int n, vector<int> shortest)
{
  int src = 0;
  printf("Vertex\t  Distance\tPath");
  for (int i = 1; i < n; i++)
  {
    printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
    printPath(shortest, i);
  }
  printf("\n");
}


// given adjacency matrix adj, finds shortest path from A to B
int dijk(int A, int B, vector< vector<int> > adj) {
  const int n = adj.size();
  vector<int> dist(n, inf);
  vector<bool> vis(n, false);
  vector<int> shortest(n, -1);

  printf("n = %d from %d to %d\n", n, A, B);

  dist[A] = 0;

  for(int i = 0; i < n; ++i) {
    int cur = -1;
    for(int j = 0; j < n; ++j) {
      if (vis[j]) continue;
      if (cur == -1 || dist[j] < dist[cur]) {
        cur = j;
      }
    }

    vis[cur] = true;
    for(int j = 0; j < n; ++j) {
      if (adj[cur][j] == 0)  //not connected no loop itself
        continue;
      int path = dist[cur] + adj[cur][j];
      if (path < dist[j]) {
        dist[j] = path;
        shortest[j] = cur;  //for shortest path row and col j(row) cur(col)
      }
    }
  }

  for_each(dist.begin(), dist.end(), [](int i) { printf("%d ", i);  });
  printf("\tdist\n");
  for_each(shortest.begin(), shortest.end(), [](int i) { printf("%d ", i);  });
  printf("\tshortest vertex\n");
  printSolution(dist, n, shortest);
  return dist[B];
}

int main() {
  
  vector<vector<int>> adj{{0, 4, 0, 0, 0, 0, 0, 8, 0}, //adjcency matric with weight/distance
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 0, 10, 0, 2, 0, 0},
                       {0, 0, 0, 14, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}
                      };
  // vector<vector<int>> adj{{0, 2,  2, 5},
  //                         {2, 0,  3, 0},
  //                         {2, 3,  0, 1},
  //                         {5, 0,  1, 0},
  //                         };
  printf("read\n");
  for (int i = 0; i < adj.size(); i++)
  {
  printf("\n");
    for (int j = 0; j < adj.size(); j++)
      printf("%d ", adj[i][j]);
  }
  printf("\n");

  int distance = dijk(0, 3, adj);
  if (!distance)
   printf("Not exist! \n");
  else
    printf("shortest path %d\n", distance);
   
}
