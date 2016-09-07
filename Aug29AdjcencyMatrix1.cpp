//http://www.dreamincode.net/forums/topic/225956-c-how-to-find-the-shortest-path-in-an-adjacency-matrix/
//METHOD 2: USING CTOR
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int inf = 1 << 30;
// const int t = 100;
// template <class T, site_t nSize>
class graph 
{
  struct edge
  {
   int distance;
   int name;
   bool connection;
  };

public:
 const int v;
 struct edge **adj; //cannot adj[v][v] using ctor to initialize this 2 dimensions array 
  graph(int); 
  ~graph();      
//  void vertices ( int ver );
  void add(int distance , int v1 , int v2);
  void del(int v1 ,int v2);   
  void display(); 
  //int dijkstra(int i, int j, graph::edge **x);
};

// graph::graph(int ver) : v(ver) , adj(new edge*[ver]), adj2(new vector<edge>*[ver])
graph::graph(int ver) : v(ver)  
{
 //initialize **adj to 2 dimensions array   
 adj = new edge*[v];
 for (int i = 0; i < v; i++)
    adj[i] = new edge[v];  //a row has 3 colums 

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
graph::~graph()
{
  for (int i = 0; i < v; ++i)
    delete [] adj[i];
  //delete [] adj;
  cout << "Dtor delete adj create in heap using new adj = new edge*[v] " << endl;
}
// void graph:: vertices ( int ver )
// {
//   v = ver;
// }
void graph::add(int distance , int v1 , int v2)
{
 if ( v1 <= v-1 && v2 <= v-1 )
 {
   //if ( v1 != v2 ) //allow loop connected itself
   //{
     if (adj[v1][v2].connection == false )
     {
       adj[v1][v2].distance = distance;

       adj[v1][v2].connection = true;

     }
     else cout << "Edge already exist" << endl;
   //}
   //else cout << "Vertex 1 is equal to Vertex 2" << endl;
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
       cout << "Vertex: " << i << " Vertex: " << j << " Distance: " << adj[i][j].distance  << endl;
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

//int graph::dijkstra(int s, int d, graph::edge **adj)
int dijkstra(int A, int B, graph t)
{
  
  // size_t n = sizeof(adj) / sizeof(adj[0]);
  // vector<int> dist(n);
  // vector<bool> vis(n);

  // // graph::edge &p = **adj;
  int n = t.v;
  
  // vector <vector<graph>> vec = {vector<graph>(begin(t.adj[0]), end(t.adj[0])),
  //                               vector<graph>(begin(t.adj[1]), end(t.adj[1]))}; 
  vector<int> dist(t.v, inf);
  vector<bool> vis(t.v, false);
  vector<int> shortest(t.v, -1);
  // for (int i = 0; i < n; i++)
  //     for (int j = 0; j < n; j++)
  //       // vec.push_back(adj[i][j]);
  //       cout << i << " " << j << " : " << " distance "<< t.adj[i][j].distance << " connect "<< t.adj[i][j].connection << endl;
  //       // for (int i = 0; i < n ; i++)
  //       //  cout << i << " : " << " distance "<< adj.distance << " connect "<< adj.connection << endl;

  // return 0;
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
      if (t.adj[cur][j].distance == 0) //skip if it does not connected 0 or inf.
         continue;
      int path = dist[cur] + t.adj[cur][j].distance;
      if (path < dist[j]) {
        dist[j] = path;
        shortest[j] = cur;  //for shortest path row and col j(row) cur(col)
      }
    }
   }
  for_each(dist.begin(), dist.end(), [](int i) { printf("%d ", i);  });
  printf("\tdist \n");
  for_each(shortest.begin(), shortest.end(), [](int i) { printf("%d ", i);  });
  printf("\tshortest vertex \n");
  printSolution(dist, n, shortest);
  return dist[B];
}
int main()
{
  graph t(4);
 
  //t.vertices(3);
  t.add(2,0,1);  //how to represent in array proority queues is one
  t.add(2,0,2);  //undirect add(2, 0, 1) will have add(2, 1, 0) same weight
  t.add(2,1,0);
  t.add(3,1,2);
  t.add(2,2,0);
  t.add(3,2,1);
  //t.add(1,2,3);
  t.add(1,3,2);
  t.add(5,0,3);
  t.add(5,3,0);

  // t.add(0,0,0); // no need
  // t.add(0,1,1);
  // t.add(0,2,2);
  // t.add(0,3,3);
 
  // t.add(13,0,3);
  // t.add(13,3,0);
  

  t.display();


  cout << "ver  :  0   1   2   3" << endl;
  for(int i = 0; i < t.v; i++)
  {
    cout << "ver " << i << " : ";
    for(int j = 0; j < t.v; j++)
    {
      cout << t.adj[i][j].distance << "\t";
      
    }
    cout << endl;
    
  }
      //t.dijkstra(0, 1, t.adj);
      int distance = dijkstra(0, t.v -1 , t);
      if (!distance)
        printf("Not connected from 0 to %d\n", t.v -1);
      else
        printf("shortest path %d\n", distance);


  return 0;
}
