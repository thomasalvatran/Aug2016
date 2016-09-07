//http://www.dreamincode.net/forums/topic/225956-c-how-to-find-the-shortest-path-in-an-adjacency-matrix/
//METHOD 1: USING TEMPLATE
#include <iostream>
using namespace std;
// const int t = 100;
// template <class T, site_t nSize>
template<int nSize> 
class graph 
{
  struct edge
  {
   int distance;
   int name;
   bool connection;
  };

public:
 struct edge adj[nSize][nSize];

  graph(); 
  ~graph();      
  void vertices ( int ver );
  void add(int distance , int v1 , int v2);
  void del(int v1 ,int v2);   
  void display();  
};

template<int nSize> 
graph<nSize>::graph()
{        
  for (int i = 0 ; i < nSize ; i++)
  {
    for ( int j = 0 ; j < nSize ; j++)
    {
      adj[i][j].distance = 0;
      adj[i][j].connection = false;
    }
  }          
}
template<int nSize>
graph<nSize>::~graph()
{
  // for (int i = 0; i < nSize; ++i)
  //   delete [] adj[i];
  // delete [] adj;
  cout << "adj created in stack with template<nSize> not in heap NO NEW" << endl;
}
// void graph:: vertices ( int ver )
// {
//   v = ver;
// }
template<int nSize> 
void graph<nSize>::add(int distance , int v1 , int v2)
{
 if ( v1 <= nSize -1 && v2 <= nSize -1 )
 {
   if ( v1 != v2 )
   {
     if (adj[v1][v2].connection == false )
     {
       adj[v1][v2].distance = distance;

       adj[v1][v2].connection = true;

     }
     else cout << "Edge already exist" << endl;
   }
   else cout << "Vertex 1 is equal to Vertex 2" << endl;
 }
 else cout << "Vertices out of Limit!" << endl;
}

template<int nSize> 
void graph<nSize>::del(int v1 , int v2)
{
 if (adj[v1][v2].connection == true)
 {
   adj[v1][v2].distance = 0;

   adj[v1][v2].connection = false;
   cout << "Deletion of edge is successful" << endl;      
 }
 else cout << "Deletion unsucessful" << endl;
}

template<int nSize> 
void graph<nSize>::display()
{
 for ( int i = 0 ; i < nSize ; i++ )
 {
   for ( int j = 0 ; j < nSize ; j++ )
   {
     if ( adj[i][j].connection == false )
       continue;
     else
     {
       cout << "Vertex: " << i << " Vertex: " << j << " Distance: " << adj[i][j].distance << endl;
     }
   }
 }
}

int main()
{
  // graph<int, 3> t(3);
  graph<3> t;

  //t.vertices(3);
  t.add(2,0,1);
  t.add(4,1,2);
  t.add(8,0,2);

  t.display();


    // system("pause");
  return 0;
}
