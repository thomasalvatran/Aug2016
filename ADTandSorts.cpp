//mycodeschool Binary search tree
//AllSort + ADT
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <array>
#include <stdlib.h>
#include <limits.h>
#include <functional>
#include <stack>
#include <list>  //Queue class for radixsort
#include <queue> //queue for radixsortSTL
#include <stack>
#include <deque>
#include <iomanip> //setw
using namespace std;

int rand_int(int a, int b)
{
    return (a + rand()) % b;
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

void swap(int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void insertSort(int a[], int n)
{
    int i, j, value;
    for (i =0; i < n; i++)
    {
        value = a[i];
        for (j = i; j > 0 && value < a[j -1]; j--)
            a[j] = a[j -1];
        a[j] = value;
    }
}
/* void bubbleSort(int *a, int n)
   void bubbleSort(int (&a)[4])
*/
void bubbleSort(int a[], int n)  // n -1 last elements amd 
{
   int i, j;
   for (i = 1; i < n; i++)
       for (j = n-1; j >= i; j--)
           if (a[j] < a[j -1])
               swap(a, j, j-1);
}

void selectSort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i; j < n; j++)
            if (a[j] < a[min])
                min = j;
            swap(a, i, min); //swap even the same

            // if (a[j] < a[min])
            // {
            //     min = j;
            //     swap(a, i, min); //swap only min change
            // }
    }
}
//http://geeksquiz.com/quick-sort/
int partition(int a[], int l, int r)
{
    int p = a[l];
//    while (l < r)
//    {
//        while (a[l] < p)
//            l++;
//        while (a[r] > p)
//            r--;
//        if (l < r)
//            swap (a, l, r);
//    }
    while (l < r)
    {
        while (a[l] < p)
            l++;
        while (a[r] > p)
            r--;
        if (l < r)
            swap(a, l, r);
    }
        return r;
}

void quickSort(int a[],  int l, int r)
{
    int m;
    if (l < r)
    {
        m = partition(a, l, r);
        quickSort(a, l, m -1);
        quickSort(a, m + 1, r);
    }

}
//youtube
void shellSort(int a[], int n)
{
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
            // {
                swap(a, j, j + gap);
            // }
}
//http://geeksquiz.com/merge-sort/
//youtube mycodeschool
void merge(int a[], int l, int m, int r) {
  int n = r - l + 1;
  int t[n];
  int i1 = l;
  int i2 = m + 1;
  int j = 0;
  while (i1 <= m && i2 <= r) {
    if (a[i1] < a[i2]) {
      t[j] = a[i1];
      i1++;
    } else {
      t[j] = a[i2];
      i2++;
    }
    j++;
  }//left over
  while (i1 <= m) {
    t[j] = a[i1];
    i1++;
    j++;
  }
  while (i2 <= r) {
    t[j] = a[i2];
    i2++;
    j++;
  }
  for (j = 0; j < n; j++)
    a[l + j] = t[j];
}

void mergeSort(int a[], int l, int r)
{
   if (l >= r)
       return;
   int m = (l + r) / 2;
   mergeSort(a, l, m);   // divide into sub-list and then a into l and r
   mergeSort(a, m + 1, r);
   merge(a, l, m, r);     //merge l and r
}
//Data Structure Adam book p. 143
template<class T>
class Queue {
public:
    Queue() {
    }
    void clear() {
        lst.clear();
    }
    bool isEmpty() const {
        return lst.empty();
    }
    T& front() {
        return lst.front();
    }
    T dequeue() {
        T el = lst.front();
        lst.pop_front();
        return el;
    }
    void enqueue(const T& el) {
        lst.push_back(el);
    }
private:
    list<T> lst;
};
//user customer class Queue
void radixSort(int data[], int n) {
register int d, j, k, factor;
const int radix = 10;
const int digits = 10; // the maximum number of digits for a long
Queue<long> queues[radix]; // integer; this user defined Queue
for (d = 0, factor = 1; d < digits; factor *= radix, d++) 
{
    for (j = 0; j < n; j++)
        queues[(data[j] / factor) % radix].enqueue(data[j]); //() priorities 2 / priotities 4 from left
    for (j = k = 0; j < radix; j++)
        while (!queues[j].isEmpty())  //user defined isEmpty
            data[k++] = queues[j].dequeue();
    }
}
//std::queue from STL
void radixSortSTL(int data[], int n) {
register int d, j, k, factor;
const int radix = 10;
const int digits = 10; // the maximum number of digits for a long
queue<long> queues[radix]; // queue retains order FIFO
for (d = 0, factor = 1; d < digits; factor *= radix, d++) 
{
    for (j = 0; j < n; j++)
        queues[data[j] /factor % radix].push(data[j]);
    for (j = k = 0; j < radix; j++)
        while (!queues[j].empty()) //true if the underlying container is empty, false otherwise 
        {
            data[k++] = queues[j].front(); 
            queues[j].pop();
        }
    }
}   

//std::list from STL
void radixsortList(int data[], int n) {
register int d, j, k, factor;
const int radix = 10;
const int digits = 10; // the maximum number of digits for a long
list<long> lst[radix]; // list retains order FIFO
for (d = 0, factor = 1; d < digits; factor *= radix, d++) 
{
    for (j = 0; j < n; j++)
        lst[data[j] /factor % radix].push_back(data[j]);
    for (j = k = 0; j < radix; j++)
        while (!lst[j].empty())  //true if the underlying container is empty, false otherwise 
        {
            data[k++] = lst[j].front(); 
            lst[j].pop_front();
        }
    }
}

void isPrime(int n)
{
    int flag = 0, i;
    for (i = 2; i <= n/2; i++)
    {
        flag = 0;
        if (n % 2 == 0)
        {
            flag = 1;
            break;
        }
    }
    cout << (flag == 0 ? "Prime" : "Not Prime") << endl;
}
//find nth prime number N
//    1 2   3   4th prime
//0 1 2 3 4 5 6 7
void findPrime(int n)
{
     long a = 0, count = 0;
     while (count < n)
     {
         long b = 2;
         int prime = 1;// to check if found a prime
         
         if(a % b == 0)
             prime = 0;
         b++;            // divider 2, 3, 4 i.e. 9/2 9/3, 9/4
         if(prime)
             count++; //it is a prime move the next prime digit
         a++;         //move to next digit to check
     }
         printf("%ld st prime no. : %ld\n",count, --a);
//     return 0;
}

int factorial(int n)
{
    if (n > 1)
     return n * factorial(n - 1);
    else
     return n;
}

int factor (int n)
{
    int temp = 1;
    for (int i = 1; i <= n; i++)
        temp *= i;
    return temp;
}

int fibonacci (int n)
{
    if (n > 2)
        return fibonacci( n -1 ) + fibonacci(n - 2);
    else
        return n;
}

//1 1 2 3 5 8 13
int fibo (int n)
{
    int prev1, prev2, temp;
    if (n > 1)
    {
        prev1 = prev2 = 1;
        for (int i = 2; i <= n; i++)
        {
            temp = prev1 + prev2;
            prev2 = prev1;
            prev1 = temp;
        }
        return temp;
    }
    return n;
}

// int f[] = new int[max];
int *f = new int[10];
int fibocache(int i) 
{
    if (i == 0) return 0;
    if (i == 1) return 1;
    if (i > 2)
    {
    if (f[i] != 0) return f[i]; // Return cached result.
        f[i] = fibocache(i - 1) + fibocache(i - 2); // Cache result
        return f[i];
    }
}

function<int(int)> fib = [](int x) { return x < 2 ? 1 : fib(x -1 ) + fib(x - 2);};

/**********************Queue ADT Array *****************************/
//Data Structure from Mark. Queue (FIFO) using vector. std::vector
#ifdef INCLUDE //dummy
    #include <iostream>
    #include <stdio.h>
    #include <vector>
    #include <algorithm>
#endif
using namespace std;

#define SIZ 5
const int SIZE = 5;
int Array[SIZE];  //array is ambiguous

int rear = 0, front = 0;

bool isFull()
{
    return (rear + 1) % SIZE == front; //to prevent rear and front equal
}
bool isEmpty()
{
    return (rear == 0 && front == 0);
}
void enqueueArray(int data)
{
    if(isFull())
    {
        cout << "Queue is full for data " << data << endl;
        return;
    }
    rear = (rear + 1) % SIZE;
    Array[rear] = data;
}
void dequeueArray()
{
    if (isEmpty())
    {
        cout << "Queue is empty " << endl;
        return;
    }
    front = (front + 1) % SIZE;
    // front = front++;
    // front %= SIZE;
                // Tail = Queue->Tail++;
                // Queue->Tail %= MAX_LEN_OF_MLME_QUEUE;  // Queue->Tail = (tail + 1) % MAX_LEN_OF_MLINE_QUEUE
                //Queue->Tail = (Queue->Tail + 1) % MAX_LEN_OF_MLME_QUEUE;
                // Queue->Num++;
}
#define RING_SIZE SIZE //this is not ring buffer(no circulate)
void dequeueArray1()
{
    //front = front + 1; //for sure
    // front = front++;  //BAD increment before not after
    front = ++front;    //front changed
    if (front >= RING_SIZE)
        front = 0;
}
// Returns element at front of queue. 
int Front()
{
    if(front == -1)
    {
        cout<<"Error: cannot return front from empty queue\n";
        return -1; 
    }
    // return Array[front];
    return Array[(front +1) % SIZE];  //correct way from Mark book
}
// https://gist.github.com/mycodeschool/7331785
void printArray()
{
    int count = (SIZE + rear - front) % SIZE + 1;
    for (int i = 1, index; i < count; i++)
    {
        index = (front + i) % SIZE;
        cout << Array[index] << "[" << index << "] ";
    }
    cout << "\n";
}
/***********************Queue LinkedList ***************************/
struct Node
{
    int data;
    struct Node *next = NULL;
};
struct Node *rearLL = NULL, *frontLL = NULL;
void enqueueLinkedList(int data)
{
    struct Node *temp = new Node;
    temp->data = data;
    temp->next = NULL;
    if (rearLL == NULL && frontLL == NULL)
    {
        rearLL = frontLL = temp;
        return;
    }
    rearLL->next = temp;
    rearLL = temp;
}
void dequeueLinkedList()
{
    if (frontLL == NULL)
    {
        cout << "Queue is empty" << endl;
        return;
    }
    else if (frontLL == rearLL)
        frontLL = rearLL = NULL;
    else
        frontLL = frontLL->next;
}
void printLinkedList() // front ->>next ->next.......rear 
{
    Node *temp = frontLL;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

void swapNode (Node *first, Node *second)
{
    int tmpValue = first->data;  //swap data
    first->data = second->data;
    second->data = tmpValue;

    // Node *tmp = first;  //swap node
    // first = second;
    // second = temp;
}

void sortLinkedList()
{
    Node *temp = NULL, *temp1 = NULL;
    bool isSwapped;
    do {
        isSwapped = false;
        temp = frontLL;
        while (temp->next != temp1 )  //bubble sort temp1 = 0 
          {
            if (temp->data > temp->next->data)
            {
                swapNode(temp, temp->next);
                isSwapped = true;
                // printLinkedList();
            }
            temp = temp->next;
          }
          temp1 = temp;  //temp = 0 now is temp = temp->next don't search again
    } while(isSwapped);
    // printLinkedList();
}

/***********************Queue ADT BST in LinkedList *****************************/
struct BstNode
{
    bool visited = false;
    int data;
    struct BstNode *left = 0, *right = 0;
};
BstNode *root = NULL; //root is global

BstNode* createNode(int data)
{
    BstNode *temp = new BstNode;
    temp->data = data;
    temp->left = temp->right = 0;
    return temp;
}
BstNode* insertNode(BstNode *root, int data);
BstNode* enqueueTree(BstNode *root, int data)
{
    root = insertNode(root, data);
    return root;
}
BstNode* dequeueMinTree(BstNode* root) //smallest in balance tree
{
     BstNode *temp = root, *prev;
   if (root == NULL || root ->left == 0)
      return root;
   
    while (temp->left != 0) //check last node
    {
        prev = temp;
        temp = temp->left;
    }
    if (temp->left == 0 && temp->right == 0) // no left no right
    {    
        delete temp;                  //delete node
        prev->left = 0;               //cut the link
    }
    else if (temp->left != 0)         //has left
    {
        // delete temp->left;          
        // prev->left->left = 0;
         prev->left = temp->left;
        delete temp;   
    }
    else if (temp->right != 0)         //has right
    {
        // delete temp->right;
        // prev->left->right = 0;
         prev->left = temp->right;
        delete temp;
    }
    return root;
}

BstNode* dequeueMaxTree(BstNode *root)
{
    BstNode *temp = root, *prev = 0;
    while (temp->right != 0)
    {
        prev = temp;
        temp = temp->right;
    }
    if (temp->right == 0 && temp->left == 0)
    {
        delete temp;
        prev->right = NULL;
    }
    else if (temp->left != 0)
    {
        delete temp->left;
        prev->right->left = 0;
    }
    else if (temp->right !=0)
    {
        temp->right = 0;
        temp->right->right = 0;
    }
    return root;
}

//Method 1: use global root
void insertNodeGlobal(int data)
{
    BstNode *temp = root, *prev = 0;
    if (root == NULL)
    {
        root = createNode(data);
        printf("Create root\n");
        return;
    }
    while (temp)
    {
        prev = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (data < prev->data)
        prev->left = createNode(data);
    else
        prev->right = createNode(data);

}
//Method 2 use reference
void insertNodeRef(BstNode **root, int data)
{
    BstNode *temp = *root, *prev = 0;
    if (*root == NULL)
    {
        *root = createNode(data);
        printf("Create root\n");
        return;
    }
    while (temp)
    {
        prev = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (data < prev->data)
        prev->left = createNode(data);
    else
        prev->right = createNode(data);

}
//Method 3: Normal pass by pointer in C
BstNode* insertNode(BstNode *root, int data)
{
    BstNode *temp = root, *prev = 0;
    if (root == NULL)
    {
        root = createNode(data);
        printf("Create root 1\n");
        return root;
    }
    while (temp)                  // find empty tree
    {
        prev = temp;              //store prev tree
        if (data < temp->data)
          temp = temp->left;
        else
          temp = temp->right;
    }  
    if (data < prev->data)
        prev->left = createNode(data);
    else
        prev->right = createNode(data);

    // cout << "prev " << prev << endl; //both the same
    // cout << "root " << prev << endl; // prev = temp and BstNode* temp = root
    return root;
}
//Method 4: recursive
BstNode* insertNodeRecursive(BstNode *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
        printf("Create root 1\n");
        return root;
    }
    if (data <= root->data)
        root->left = insertNodeRecursive(root->left, data);
    else 
        root->right = insertNodeRecursive(root->right, data);
    return root;
}


void printTree(BstNode *root)
{
    if (root)
    {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}
//printTree using stack
//http://articles.leetcode.com/binary-search-tree-in-order-traversal/
void in_order_traversal_iterative(BstNode *root)
{
    cout << "in_order_traversal_iterative" << endl;
    stack<BstNode*> s;
    s.push(root);
    if (!s.empty())
    {
        BstNode *top = s.top();
        if (top != NULL)
        {
            if (!top->visited)
            {
               s.push(top->left); 
            } else {
                cout << top->data << " ";
                s.pop();
                s.push(top->right);
            }
        } else {
            s.pop();
            if (!s.empty())
                s.top()->visited = true;
        }
    }
} 

void printTreeStack(BstNode *root)
{
  stack<BstNode*> s;
  BstNode *current = root;
  while (!s.empty() || current) 
  {
    if (current) {
      s.push(current);
      current = current->left;
    } else {
      current = s.top();
      s.pop();
      cout << current->data << " ";
      current = current->right;
    }
  }
}

BstNode* deleteTree(BstNode* root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
        root = NULL;
    }
    return root;
}
int findMax(BstNode* root)
{
    BstNode *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }
    while (temp->right != NULL)
        temp = temp->right;
    return temp->data;
}

int findMin(BstNode *root)
{
    if (root == NULL)
    {
        cout << "Empty tree" << endl;
        return -1;
    }
    BstNode *temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->data;
}

BstNode * findMinRecursive( BstNode *t ) /*const*/
{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
       return t;
   return findMinRecursive( t->left );
}

BstNode* findMinNode(BstNode *root)
{
    BstNode *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return 0;
    }
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

BstNode* findMaxNode(BstNode *root)
{
    BstNode *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return 0;
    }
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}

BstNode* removeNode(BstNode* root, int data)
{
    if (root == NULL)
        return root;
    else if (data < root->data)
        root->left = removeNode(root->left, data);
    else if (data > root->data)
        root->right = removeNode(root->right, data);
    else
    { // 3 cases
        if (root->left == NULL && root->right == NULL)  
        {  /*no child*/
            delete root;
            root = NULL;
        }
        else if (root->left == NULL)                    
        {  /*one child left or right*/
            BstNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            BstNode *temp = root;
            root = root->left;
            delete temp;
        }
        else                                               
        {   /*2 children*/
                BstNode *temp = findMinNode(root->right);  //Min in right mycodeschool
                root->data = temp->data;                   // adjust root->data
                root->right = removeNode(root->right, temp->data);

                // BstNode *temp = findMaxNode(root->left);
                // root->data = temp->data;
                // root->right = removeNode(root->right, temp->data);
        }
    }
    return root;
}

vector<int> vec; //global
void treetoBST(BstNode *root)
{
    if (root)
    {
        treetoBST(root->left);
        vec.push_back(root->data); //push end vector
        treetoBST(root->right);
    }
}
int binsearch(int x, vector<int> v, int n)
{
    int low = 0, mid = 0;
    int high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ( x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1; //not found
}
bool binsearchRecursive(BstNode *root, int data)
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data <= root->data)
        return binsearchRecursive(root->left, data);
    else
        return binsearchRecursive(root->right, data);
}

bool isSubtreeLesser(BstNode* root, int data)
{
    if (root == NULL)
        return true;
    else if (root->data <= data
        && isSubtreeLesser(root->left, data)
        && isSubtreeLesser(root->right, data))
        return true;
    else
        return false;
}
bool isSubtreeGreater(BstNode* root, int data)
{
    if (root == NULL)
        return true;
    else if (root->data > data
        && isSubtreeGreater(root->left, data)
        && isSubtreeGreater(root->right, data))
        return true;
    else
        return false;
}
//mycodeschool
bool isBinarySearchTree(BstNode *root)
{
    if (root == NULL)
        return true;
    if (isSubtreeLesser(root->left, root->data)
       && isSubtreeGreater(root->right, root->data)  
       && isBinarySearchTree(root->left)            
       && isBinarySearchTree(root->right))          
       return true;
    else
        return false;
}
//find Max in left tree //find Min in right tree //range min - max
//better only change in range
bool isBinarySearchTreeUpperLower(BstNode *root, int lower, int upper)
{
    if (root == NULL)
        return true;
    if (root->data > lower
       && root->data < upper          //range check infinite -> 7
       && isBinarySearchTreeUpperLower(root->left, lower, root->data)
       && isBinarySearchTreeUpperLower(root->right, root->data, upper))
       return true;
    else
        return false;
}

bool isBSTUpperLower(BstNode *root)
{

    return isBinarySearchTreeUpperLower(root, INT_MIN, INT_MAX); //- + infinite

}
//mycodeschool 
//expensive traversal without range
bool isBST(BstNode* root)
{
    if (root == NULL)
        return true;
    if (isSubtreeLesser(root->left, root->data)
        && isSubtreeGreater(root->right, root->data)
        && isBinarySearchTree(root->left)
        && isBinarySearchTree(root->right))
        return true;
    else
        return false;

}
bool searchNode(BstNode *root, int data)
{
    return binsearchRecursive(root, data);
}
struct // lesser
{
    bool operator()(int a, int b)
    {
      return a < b;
    }
} customless;
/*bool comp(int a, int b)*/
int comp(int a, int b)
{
    return a < b;
}

//http://en.cppreference.com/w/cpp/algorithm/sort
void sortArray(int a[])
{
   //Method 1: Sorting an array using STL
   sort(a, a+SIZE); //sort array
   std::array<int, SIZE -1> arr ; //convert array to template array
   //Method 1: Sorting template array using greater
   for (int i = 1; i < SIZE; i++)
       arr[i-1] = a[i];
    sort(arr.begin(), arr.end(), greater<int>()); //sort template
    for (int a : arr)
    {
        cout << a << " ";
    }
    cout << '\n';
    //Method 2: Sorting template array using custom
    sort(arr.begin(), arr.end(), customless); //struct
    sort(arr.begin(), arr.end(), comp);       //function thinking in C++ media
    for (int a : arr)
    {
        cout << a << " ";
    }
    //Method 3: Sorting template array using lambda
    cout << '\n';
    // sort using a lambda expression
    std::sort(arr.begin(), arr.end(), [](int a, int b) {
        cout << "lambda compare " << a << " " << b << " " << endl;
       return b < a;
     });
    for (int a : arr) {
       std::cout << a << " ";
    }
    std::cout << '\n';
}

void print(Node *head) //pass by pointer by copy
{                       //head is not changed in main
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head ->next;
    }
    printf("\n");
}

//tortoise and hare
//won't work if insert at tail
bool isCirculate(Node *head)  
{
    Node *slow, *fast;
    //slow = head;
    fast = head->next;

    while (true)
    {
    if (!fast || !fast->next)    //Not circulate linked list
        return false;
    else if (fast < slow || fast->next < slow)
        return true;
    else
    {
        slow = slow->next;
        fast = fast->next;
    } 
}
}
//good from geeksforgeeks.org/check-if-a-linked-list-is-circulate-linked-list
bool isCirculation(Node *head)  
{
    //An empty linked list is circular
    if (head == NULL)
        return true;
    // next of head
    Node *node = head->next; //node is head->next
    while (node != NULL && node != head) //This loop will stop if 
        node = node ->next;              //(1) ciculatar (2) not circulate
    return (node == head);  //true is circulate false is not
}

int main()
{
    isPrime(9);
    cout << "Factorial(4) " << factorial(4) << endl;
    cout << "Fibonacci(5) " << fibonacci(5) << endl;
    cout <<  "*********** Sorting ***********" << endl;
    int a[4];
    srand(time(0));
    for (int i = 0; i < 3; i++)
        a[i] = rand_int(1, 10);
    radixSortSTL(a, 4);
    // insertSort(a, 4);
    // print(a, 4);
    //mergeSort(a, 0, 3);   //array pass by ref therefore change outside effect inside
    print(a, 4);
    cout <<  "***********Queue Array ***********" << endl;
    enqueueArray(12);
    enqueueArray(4);
    // enqueueArray(5);
    enqueueArray(15);
    enqueueArray(15);
    printArray();
    cout <<  "***********Queue Linked List ***********" << endl;
    enqueueLinkedList(22);
    enqueueLinkedList(22);
    enqueueLinkedList(23);
    enqueueLinkedList(29);
    enqueueLinkedList(124);
    enqueueLinkedList(24);
    printLinkedList();
    dequeueLinkedList();
    printLinkedList();
    bool isSwapped;         //Sort a linked list
    Node *temp = NULL;
    do 
    {
        temp = frontLL;
        isSwapped = false;
        while (temp->next != NULL)
        {
            if (temp->data > temp->next->data)
            {
                swapNode(temp, temp->next);
                isSwapped = true;
            }
            temp = temp->next;
        }
    }while (isSwapped);
    printLinkedList();
    cout <<  "***********Queue Tree as LinkedList***********" << endl;
    insertNodeGlobal(100); //Method 0: global no return
    insertNodeGlobal(90);
    insertNodeGlobal(110);
    insertNodeRef(&root, 77); //Method 1: ref no return
    insertNodeRef(&root, 177);
    root = insertNode(root, 88); //Method 2: normal
    root = insertNode(root, 880);
    root = insertNode(root, 353);
    root = insertNodeRecursive(root, 99); //Method 3: recursive
    root = insertNodeRecursive(root, 999);
    root = enqueueTree(root, 55);
    root = enqueueTree(root, 555);
    root = enqueueTree(root, 555);
    removeNode(root, 88);
    printTree(root);
    printf("\n");
    printf("Max is %d\n", findMax(root));
    printf("Min is %d\n", findMin(root));
    dequeueMinTree(root);
    dequeueMaxTree(root);
    printTree(root);
    printf("\n");
    printTreeStack(root);
    printf("\n");
    dequeueMaxTree(root);
    printTree(root);
    printf("\n");
//    root = deleteTree(root);
//    printTree(root);
//    printf("\n");
    root = removeNode(root, 555);
    printTree(root);
    printf("\n");
    printf("Vector..\n");
    treetoBST(root);
    printf("%s", "Tree Sort: " );
    for_each(vec.begin(), vec.end(), [](int i){
        printf("%d ", i);
    });
    printf("\n");
    int data = 100;
    cout << (binsearch(data, vec, vec.size()) ? "Found" : "Not found") << endl;
    cout << (binsearchRecursive(root, data)) << endl;
    cout << (isBSTUpperLower(root) ? "BST" : "Not BST") << endl;  //range
    cout << (isBST(root) ? "BST" : "Not BST") << endl;            //no range

    printArray();
    //mergeSort(Array, 0, 4);
    //shellSort(Array, 4);
    //quickSort(Array, 0, 4);
    //bubbleSort(Array, 4);
    //insertSort(Array, 4);
    //selectSort(Array, 4);
    printArray();
    sortArray(Array);

    cout <<  "*********** More Linked List ***********" << endl;

     Node *head= NULL, *tmp = NULL;

     // head = new Node; No need
     // head->data = 1;
     // head->next = 0;
     // tmp = head;

     temp = new Node;
     head = temp;       //save head

     temp->data = 1;    //insert after at the end
     temp->next = 0;

     temp->next = new Node;
     temp = temp->next;
     temp->data = 2;

     temp->next = new Node;
     temp = temp->next; //blank
     temp->data = 3;

     temp->next = new Node;
     temp = temp->next;
     temp->data = 4;
     temp->next = 0;      //last node
    
      temp = new Node;    //insert before head
      temp->data = 100;
      temp->next = head;
      head = temp;

      temp = new Node;     //insert after head
      temp->data = 99;
      temp->next = head->next;
      head->next = temp;
      print(head);

    temp = head;
    // Node *prev;
    while (temp != NULL && temp->data != 2)
    {
        // prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        printf("No node with 2\n");
    Node *temp1 = new Node;
    temp1->data = 1000;        //insert at node 2
    temp1->next = temp->next;

    temp->next = temp1;
    print(head);

    temp = head;
    while (temp->next != NULL)  //advance one
        temp = temp->next;      //node after last node

    temp1 = new Node;
    temp1->data = 11111;
    temp1->next = 0;    //11111 is last node
    temp->next = temp1; //temp is last node
    print(head);

    temp = head;        //remove head
    head = head->next;
    free(temp);
    print(head);

    temp = head;        //remove at the end;
    while (temp->next->next != 0)
        temp = temp->next;

    temp->next = 0;
    free(temp->next);
    print(head);

    temp = head;
    while (temp->next != 0) //remove at the end using prev is temp1
    {
        temp1 = temp;
        temp = temp->next;
    }
    temp1->next = 0;
    free(temp);
    print(head);
    // temp1->next = head;
    cout << boolalpha << (isCirculate(head) == true ? "Circulate " : "Not circulate") << endl;
    isCirculation(head) ? cout << "Yes\n" : cout << "No\n";

    cout << "***array, stack, vector, queue, dequeue, list ***" << endl;  
    #define N 5
    int arrays[N];
    vector<int> vectors(N);  //int a[N]
    queue<int> queues;
    list<int> lists;
    stack<int> stacks;
    deque<int> deques;
    srand(time(0));
    
    arrays[0] = 63; stacks.push(63); vectors.push_back(63); vectors[0] = 63; deques.push_back(63); queues.push(63); lists.push_back(63);
    arrays[1] = 15; stacks.push(15); vectors.push_back(15); vectors[1] = 15; deques.push_back(15); queues.push(15); lists.push_back(15);
    arrays[2] = 33; stacks.push(33); vectors.push_back(33); vectors[2] = 33; deques.push_back(33); queues.push(33); lists.push_back(33);
    arrays[3] = 36; stacks.push(36); vectors.push_back(36); vectors[3] = 36; deques.push_back(36); queues.push(36); lists.push_back(36);
    arrays[4] = 26; stacks.push(26); vectors.push_back(26); vectors[4] = 26; deques.push_back(26); queues.push(26); lists.push_back(26);
    
    for (int i = 0; i < N; i++)
        cout << arrays[i] << " ";
    cout << " arrays(retain order)" << endl;
    while(stacks.empty() == 0)
    {
        cout << stacks.top() << " ";
        stacks.pop();
    }
    cout << " stacks(not retain order but reverse order)" << endl;
    
    while(vectors.size() != 0)
    {
        cout << vectors.back() << " "; 
        vectors.pop_back();
    }
    cout << " vectors(not retain)" << endl;

    for (int n: deques)
        cout << n << " ";
    cout << " deques(can retain not retain) can work queues or stacks" << endl;

    while(deques.size() != 0)
    {
        cout << deques.back() << " ";
        deques.pop_back();
    }
    cout << " deques pop_back (not retain order) " << endl;

    while(queues.size() != 0)
    {
        cout << queues.front() << " "; 
        queues.pop();
    }
    cout << " queues(retain order)" << endl;

    while(lists.size() != 0)
    {
        cout << lists.front() << " "; 
        lists.pop_front();
    }
    cout << " lists retain order put in but it is a linkedlist " << endl;

    cout << setw(80) << "no std::tree C++ STL does not provide any tree container only in Java !" << endl;

}



