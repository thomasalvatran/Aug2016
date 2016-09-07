//http://www.dreamincode.net/forums/topic/225956-c-how-to-find-the-parent-path-in-an-adjacency-matrix/
//METHOD 2: USING CTOR
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iomanip> //setw for space

using namespace std;
// const int t = 100;
// template <class T, site_t nSize>
 enum vName { Pierre, Pendleton, Phoenix, Pueblo, Peoria, Pittsburgh, Pensacola, Princeton };
            /* 0,         1,         2.      3,       4.      5,         6,           7,        8 */
 const char *vN[] = { "Pierre", "Pendleton", "Phoenix", "Pueblo", "Peoria", "Pittsburgh", "Pensacola", "Princeton" };

class graph 
{
  struct edge
  {
   int distance;
   string name;
   bool connection;
  }_edge;

public:
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
  for (int i = 0; i < v; ++i)
    delete [] adj[i];          //delete row[] the col[] will be deleted as well
  delete [] adj;
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

// Function to print parent path from source to j
// using parent array
void printPath(vector<int> parent, int j)
{
  // Base Case : If j is source
  if (parent[j] == -1)
    return;

  printPath(parent, parent[j]);

  printf("%d(%s) ", j, vN[j]);
}

// A utility function to print the constructed distance
// array
void printSolution(int src, vector<int> dist, int n, vector<int> parent)
{
  // int src = 1;
  printf("Vertex\t\t\t\t           Distance\t\tPath");
  for (int i = 1; i < n; i++)
  {
    printf("\n%d(%s) -> %d (%-11s)\t%d\t\t\t%d(%s) ", src, vN[src], i, vN[i], dist[i], src, vN[src]);
    printPath(parent, i);
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
  vector<int> parent(n, -1);
  
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
        parent[j] = cur;  //for parent path row and col j(row) cur(col)
      }
    }
   }
  for_each(dist.begin(), dist.end(), [](int i) { printf("%d ", i);  });
  printf("\tdist \n");
  for_each(parent.begin(), parent.end(), [](int i) { printf("%d ", i);  });
  printf("\t\tparent vertex \n");
  printSolution(A, dist, n, parent);
  return dist[B];
}
int main()
{
  graph t(8);

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
      printf("parent path %d\n", distance);

  return 0;
}
// Vertex: 0 Vertex: 1 Distance: 2->Pierre - Pendleton
// Vertex: 1 Vertex: 2 Distance: 4->Pendleton - Phoenix
// Vertex: 1 Vertex: 3 Distance: 8->Pendleton - Pueblo
// Vertex: 2 Vertex: 3 Distance: 3->Phoenix - Pueblo
// Vertex: 2 Vertex: 4 Distance: 4->Phoenix - Peoria
// Vertex: 2 Vertex: 5 Distance: 10->Phoenix - Pittsburgh
// Vertex: 3 Vertex: 0 Distance: 3->Pueblo - Pierre
// Vertex: 4 Vertex: 3 Distance: 3->Peoria - Pueblo
// Vertex: 4 Vertex: 5 Distance: 5->Peoria - Pittsburgh
// Vertex: 5 Vertex: 6 Distance: 4->Pittsburgh - Princeton
// Vertex: 6 Vertex: 5 Distance: 2->Princeton - Pittsburgh
// Vertex: 6 Vertex: 7 Distance: 5->Pensacola - Princeton
// Vertex: 7 Vertex: 2 Distance: 5->Pensacola - Phoenix
// col  :  0  1  2  3  4  5  6  7  8
// row 0 : 0  2  0  0  0  0  0  0  
// row 1 : 0  0  4  8  0  0  0  0  
// row 2 : 0  0  0  3  4  10  0  0  
// row 3 : 3  0  0  0  0  0  0  0  
// row 4 : 0  0  0  3  0  5  0  0  
// row 5 : 0  0  0  0  0  0  4  0  
// row 6 : 0  0  0  0  0  2  0  5  
// row 7 : 0  0  5  0  0  0  0  0  
// n = 8 from 0(Pierre) to 6(Pensacola)
// 0 2 6 9 10 15 19 24   dist 
// -1 0 1 2 2 4 5 6    parent vertex 
// Vertex                   Distance   Path
// 0(Pierre) -> 1 (Pendleton  )  2     0(Pierre) 1(Pendleton) 
// 0(Pierre) -> 2 (Phoenix    )  6     0(Pierre) 1(Pendleton) 2(Phoenix) 
// 0(Pierre) -> 3 (Pueblo     )  9     0(Pierre) 1(Pendleton) 2(Phoenix) 3(Pueblo) 
// 0(Pierre) -> 4 (Peoria     )  10    0(Pierre) 1(Pendleton) 2(Phoenix) 4(Peoria) 
// 0(Pierre) -> 5 (Pittsburgh )  15    0(Pierre) 1(Pendleton) 2(Phoenix) 4(Peoria) 5(Pittsburgh) 
// 0(Pierre) -> 6 (Pensacola  )  19    0(Pierre) 1(Pendleton) 2(Phoenix) 4(Peoria) 5(Pittsburgh) 6(Pensacola) 
// 0(Pierre) -> 7 (Princeton  )  24    0(Pierre) 1(Pendleton) 2(Phoenix) 4(Peoria) 5(Pittsburgh) 6(Pensacola) 7(Princeton) 
// parent path 19
// Dtor delete adj create in heap using new adj = new edge*[v] 
// [Finished in 1.0s]