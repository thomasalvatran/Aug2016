//http://www.dreamincode.net/forums/topic/225956-c-how-to-find-the-shortest-path-in-an-adjacency-matrix/
//METHOD 2: USING CTOR
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;
// const int t = 100;
// template <class T, site_t nSize>
 enum vName { Pierre, Pendleton, Phoenix, Pueblo, Peoria, Pittsburgh, Pensacola, Princeton };
            /* 0,         1,         2.      3,       4.      5,         6,           7,        8 */
 const char *vN[] = { "Pierre", "Pendleton", "Phoenix", "Pueblo", "Peoria", "Pittsburgh", "Pensacola", "Princeton" };
class graph 
{
public:
  struct edge
  {
   int distance;
   string name;
   bool connection;
  }_edge;

 const int v;
 // struct edge **adj; //cannot adj[v][v] using ctor to initialize this 2 dimensions array 
 // vector<graph::edge> adj(3)(3);
 edge **adj;
 //struct edge adj[3][3];
  graph(int); 
  ~graph();      
//  void vertices ( int ver );
  void add(int distance , int v1 , int v2, string s1, string s2);
  void del(int v1 ,int v2);   
  void display(); 
  // int dijkstra(int i, int j, vector< vector<graph::edge>> x);
  // int dijkstra(int i, int j, vector<vector<graph::edge>> adj);
  // int dijkstra(int i, int j, graph::edge **x);
  int dijkstra(int i, int j, graph::edge **x);
};

// graph::graph(int ver) : v(ver) , adj(new edge*[ver]), adj2(new vector<edge>*[ver])
graph::graph(int ver) : v(ver)  
{
  adj = new edge*[v];
 for (int i = 0; i < v; i++)
    adj[i] = new edge[v];  //a row has 3 colums 
  // adj = new edge*[v];
 //for (int i = 0; i < v; i++)
 //   adj[i] = new edge[v];  //a row has 3 colums 

 //initialize value of adj[i][j]
  for (int i = 0 ; i < v ; i++)
  {
    for ( int j = 0 ; j < v ; j++)
    {
      adj[i][j].distance = 0;
      adj[i][j].connection = false;
    }
  }          
}

 //initialize **adj to 2 dimensions array   
 // adj = new edge*[v];
 // for (int i = 0; i < v; i++)
 //    adj[i] = new edge[v];  //a row has 3 colums 

 //initialize value of adj[i][j]
  // for (int i = 0 ; i < v ; i++)
  // {
  //   for ( int j = 0 ; j < v ; j++)
  //   {
  //     adj[i][j].distance = 0;
  //     adj[i][j].connection = false;
  //   }
  // }   
  //vector< vector<graph::edge> > adj(v);
 // for_each(adj.begin(), adj.end(), [](auto v){ v.distance = 0;  });       
// }
graph::~graph()
{
  // for (int i = 0; i < v; ++i)
  //   delete [] adj[i];
  // delete [] adj;
  cout << "Dtor delete adj create in heap using new adj = new edge*[v] " << endl;
}
// void graph:: vertices ( int ver )
// {
//   v = ver;
// }
 void graph::add(int distance , int v1 , int v2, string s1, string s2)
//void graph::add(int distance , graph v1 , graph v2, string s1, string s2)
{

 if ( v1 <= v-1 && v2 <= v-1 )
 {
   if ( v1 != v2 )
   {
     if (adj[v1][v2].connection == false )
     {
       adj[v1][v2].distance = distance;
       adj[v1][v2].name = s1; //undirect assign both if vertex 1 is connected to vertex 2 then
       adj[v2][v1].name = s2; //vertex 2 connected vertex 1
       adj[v1][v2].connection = true;

     }
     else cout << "Edge already exist" << endl;
   }
   else cout << "Vertex 1 is equal to Vertex 2" << endl;
 }
 else cout << "Vertices out of Limit!" << endl;
}

void graph::del(int v1 , int v2)
{
 if (adj[v1][v2].connection == true)
 {
   adj[v1][v2].distance = 0;

   adj[v1][v2].connection = false;
   cout << "Deletion of edge is successful" << endl;      
 }
 else cout << "Deletion unsucessful" << endl;
}

void graph::display()
{
 for ( int i = 0 ; i < v ; i++ )
 {
   for ( int j = 0 ; j < v ; j++ )
   {
     if ( adj[i][j].connection == false )
       continue;
     else
     {
       cout << "Vertex: " << i << " Vertex: " << j << " Distance: " << adj[i][j].distance 
       << "->" << adj[i][j].name << " - " << adj[j][i].name << endl;
     }
   }
 }
}

// Function to print shortest path from source to j
// using parent array
void printPath(vector<int> shortest, int j)
{
  // Base Case : If j is source
  if (shortest[j] == -1)
    return;

  printPath(shortest, shortest[j]);

  printf("%d(%s) ", j, vN[j]);
}

// A utility function to print the constructed distance
// array
void printSolution(int src, vector<int> dist, int n, vector<int> shortest)
{
  // int src = 1;
  printf("Vertex\t\t\t\t\t\t           Distance\t\t\tPath");
  for (int i = 1; i < n; i++)
  {
    printf("\n%d(%s) -> %d(%s)  \t\t\t\t %d\t\t\t\t%d(%s) ", src, vN[src], i, vN[i], dist[i], src, vN[src]);
    printPath(shortest, i);
  }
  printf("\n");
} 

const int inf = 1 << 30;
int graph::dijkstra(int A, int B, graph::edge **adj)
//int graph::dijkstra(int s, int d, graph t)
//int graph::dijkstra(int s, int d, vector<vector <graph::edge> > adj)
{
  int n = sizeof(adj); // n = 8
  vector<int> dist(n, inf);
  vector<bool> vis(n, false);
  vector<int> shortest(n, -1);
  
  printf("n = %d from %d(%s) to %d(%s)\n", n, A,vN[A], B, vN[B]);                         
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
      if (adj[cur][j].distance == 0) //skip if it does not connected 0 or inf.
         continue;
      int path = dist[cur] + adj[cur][j].distance;
      if (path < dist[j]) {
        dist[j] = path;
        shortest[j] = cur;  //for shortest path row and col j(row) cur(col)
      }
    }
   }
  for_each(dist.begin(), dist.end(), [](int i) { printf("%d ", i);  });
  printf("\tdist \n");
  for_each(shortest.begin(), shortest.end(), [](int i) { printf("%d ", i);  });
  printf("\t\tshortest vertex \n");
  printSolution(A, dist, n, shortest);
  return dist[B];
}
int main()
{
  graph t(8);
 
  
  cout << vN[Phoenix] << endl;

  //t.vertices(3);
  t.add(4,1,2,"Pendleton", "Phoenix");
  t.add(8,1,3,"Pendleton", "Pueblo");
  t.add(5,7,2,"Pensacola", "Phoenix");
  t.add(5,4,5,"Peoria", "Pittsburgh");
  t.add(3,4,3,"Peoria", "Pueblo");
  t.add(4,2,4,"Phoenix", "Peoria");
  t.add(10,2,5,"Phoenix", "Pittsburgh");
  t.add(3,2,3,"Phoenix", "Pueblo");
  t.add(2,0,1,"Pierre", "Pendleton");
  t.add(4,5,6,"Pittsburgh", "Pensacola");
  t.add(2,6,5,"Princeton", "Pittsburgh");
  t.add(3,3,0,"Pueblo", "Pierre");
  t.add(5,6,7,"Pensacola", "Princeton");

  

  t.display();

  // for(int i = 0; i < t.v; i++)
  // {
  //   //cout << "row " << i << " : ";
  //   for(int j = 0; j < t.v; j++)
  //     cout << vN[i] << " " << vN[j] << " : "<< t.adj[i][j].distance  << endl;
    
  // }
   cout << "col  :  0  1  2  3  4  5  6  7  8" << endl;
  for(int i = 0; i < t.v; i++)
  {
    cout << "row " << i << " : ";
    for(int j = 0; j < t.v; j++)
    {
      cout << t.adj[i][j].distance << "  " ;
      
    }
    cout << endl;
    
  }

     int distance = t.dijkstra(0, 6, t.adj);
     if (!distance)
      printf("Not exist! \n");
     else
      printf("shortest path %d\n", distance);

  return 0;
}
