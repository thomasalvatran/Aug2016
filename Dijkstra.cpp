//----------------------/home/tovantran/Ctest/Dijkstra.cpp
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

class DistanceToCity
{
    string name;
    int distance;
public:
    DistanceToCity(){}
    DistanceToCity(string n, int d): name(n), distance(d){}
    bool operator < (const DistanceToCity right) const { return right.distance < distance; }
    string getName() const { return name; }
    void setName(const string &value) { name = value;}
    int getDistance() const { return distance;}
    void setDistance(int value) { distance = value;}
};

class DistanceFinder
{
public:
    multimap<string, DistanceToCity> cities;
    multimap<string, DistanceToCity> :: iterator Citr, stop, p;
    void setDistance(string from, string to, int distance)
    {
        cities.insert(make_pair(from, DistanceToCity(to, distance)));
    }                                                                       /*pass as ref*/
    priority_queue<DistanceToCity> findDistance(string start, map<string, int> &shortest)
    {
        priority_queue<DistanceToCity> que, que1;
        que.push(DistanceToCity(start, 0));
        while(!que.empty())
        {
            DistanceToCity new_city = que.top();
            que.pop();
            if (shortest.count(new_city.getName()) == 0) //not visited
            {
                int d = new_city.getDistance();
                shortest[new_city.getName()] = d; //visited ??
                que1.push(DistanceToCity(new_city.getName(), d));
                p = cities.lower_bound(new_city.getName());
                stop = cities.upper_bound(new_city.getName());
                while (p != stop)
                {
                    DistanceToCity next_destination = p->second;
                    int total_distance = d + next_destination.getDistance();
                    que.push(DistanceToCity(next_destination.getName(), total_distance));
                    p++;
                }
            }
        }
        return que1;
    }
};
void print(DistanceFinder d)
{ 
//for loop with iterator  
//multimap<string, DistanceToCity>::iterator i;
//for (i = d.cities.begin(); i != d.cities.end(); ++i)
//    cout << i->first << " " << i->second.getName() << " " << i->second.getDistance() << endl;

//Lambda multimap iterator
for_each(d.cities.begin(), d.cities.end(),[](pair<string, DistanceToCity> i){
    cout << i.first <<" "<< i.second.getName() << " " << i.second.getDistance() << endl;
});
}
//std::for_each(begin(v), end(v), [&sum](int x) { sum += x; });
//auto comp = []( const int& a, const int& b ){return a.size > b.size;};
template <typename T1, typename T2> //Functor for a pair
struct less_second {
    typedef pair<T1, T2> type; //????Review???? September 08 2016 (Thursday)
    bool operator ()(type const& a, type const& b) const {
        return a.second < b.second;
    }
};

int main()
{
    DistanceFinder d;
    d.setDistance("Pendleton", "Phoenix", 4);
    d.setDistance("Pendleton", "Pueblo", 8);
    d.setDistance("Pensacola", "Phoenix", 5);
    d.setDistance("Peoria", "Pittsburgh", 5);
    d.setDistance("Peoria", "Pueblo", 3);
    d.setDistance("Phoenix", "Peoria", 4);
    d.setDistance("Phoenix", "Pittsburgh", 10);
    d.setDistance("Phoenix", "Pueblo", 3);
    d.setDistance("Pierre", "Pendleton", 2);
    d.setDistance("Pittsburgh", "Pensacola", 4);
    d.setDistance("Princeton", "Pittsburgh", 2);
    d.setDistance("Pueblo", "Pierre", 3);
    print(d); printf("%s\n","-----" );
    //1
    map<string, int> shortest;

    priority_queue<DistanceToCity> pq = d.findDistance("Pierre", shortest);
    while(!pq.empty())
    {
        DistanceToCity p = pq.top();
        pq.pop();
        cout << p.getName() << " " << p.getDistance() << endl;
    }
    // for(priority_queue<int>::iterator it = pq.begin(); it != pq.end(); i++)
    // {
    //     cout << *it << endl;
    // }
    //2
    cout << "-------1------" << endl;
    map<string, int> :: iterator current = shortest.begin();
    map<string, int> :: iterator stop = shortest.end();
    while (current != stop)
    {
        pair<string, int> p = *current;
        cout << "Distance to " << p.first << " is " << p.second << "\n";
        ++current;
    }
    // 2 & 3 & 4
    cout << "------2------" << endl;
    map<string ,int>::iterator itr; //pair
    for(itr = shortest.begin(); itr != shortest.end(); itr++) 
        cout << itr->first << " " << itr->second << endl;
    cout << "------3------" << endl;

    for_each(shortest.begin(), shortest.end(), [](const std::map<string, int>::value_type &n){
        cout << n.first <<" " << n.second << endl; //pair inside
        });

    cout << "------4-----" << endl;
    
    for_each(shortest.begin(), shortest.end(), [](pair<string, int> n){
      cout << n.first << " " << n.second << endl; //pair inside
    });
    cout << "------5-----" << endl;

    for_each(begin(shortest), end(shortest), [](const std::pair<string, int> &n){
        cout << n.first <<" " << n.second << endl; //pair inside
    });

     cout << "------6-----" << endl;

    for_each(begin(shortest), end(shortest), [](const unordered_map<string, int>::value_type &n){
        cout << n.first <<" " << n.second << endl; //pair inside
    });

    cout << "------7-----" << endl;
    vector<pair<string, int>> mapcopy(shortest.begin(), shortest.end());
    sort(mapcopy.begin(), mapcopy.end(), less_second<string, int>());
    for (auto n: mapcopy)
    {
        cout << n.first << " " << n.second << endl;
    }
    cout << "------8-----" << endl;
    reverse(mapcopy.begin(), mapcopy.end());

    for_each(mapcopy.begin(), mapcopy.end(), [](pair<string, int> n){
      cout << n.first << " " << n.second << endl; //pair inside
    });

   // for_each(mapcopy.begin(), mapcopy.end(), [](pair<string, int>)

    // for_each(mapcopy.begin(), mapcopy.end(), []( int n){
    //     cout << n << endl;
    // });
    // for_each(pq(begin), pq(end), [](int x){
    //     cout << x.first << endl; //pair inside
    // });

    // auto cmp = [](pair<string, int> const &a, pair<string, int> const &b)
    // {
    //     return a.second == b.second;
    // }
    //sort(shortest.begin(), shortest.end());
    //vector<pair<int, string>> shortest;
    //Sort using vector
    
    // sort(shortest.begin(), shortest.end(), [](const shortest &a, const shortest &b)->bool
    // {
    //     return a.shortest > b.shortest;
    // });
    return 0;
}

