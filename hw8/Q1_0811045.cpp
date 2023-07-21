#include <iostream>
#include <queue>
using namespace std;

typedef struct node
{
    int vertex;
    struct node *next;
}adjlist;

adjlist* CreateNode(int vertex);
void input_edge(adjlist** graph, int a, int b);
bool topological_sort(adjlist** graph, int n);
int main()
{
    int num_actions, num_prerequisites, a, b;
    cin >> num_actions >> num_prerequisites;   

    //create adjacency list
    adjlist* graph[num_actions];
    for (int i=0; i<num_actions; i++)
    {
        graph[i] = nullptr;

    }

    //insert edges
    for(int i=0; i<num_prerequisites; i++)
    {
        cin >> a >> b;
        input_edge(graph,a,b);
    }

    //output if the recipe can be a topological sort
    if(topological_sort(graph,num_actions))
    {
        cout << "true";
    }
    else
    {
        cout << "false";
    }
    return 0;
}

adjlist* CreateNode(int vertex)
{
    adjlist* temp = new adjlist;
    temp->vertex = vertex;
    temp->next = nullptr;
    return temp;
}

void input_edge(adjlist** graph, int a, int b)
{
    adjlist* temp = CreateNode(a);

    if(graph[b] == nullptr)
    {
        graph[b] = temp;
    }

    else
    {   
        adjlist* current = graph[b];
        while(current->next != nullptr)
        {
            current = current->next;
        }
        current->next = temp;
    }
    
}

bool topological_sort(adjlist** graph, int n)
{   
    int count_in[n];
    queue<int> q;
    adjlist* temp=nullptr;
    for(int i=0; i<n; i++)
    {
        count_in[i] = 0;
    }

    //count indegree of each vertex
    for(int i=0; i<n; i++)
    {   
        temp = graph[i];
        while(temp!= nullptr)
        {
            count_in[temp->vertex]++;
            temp = temp->next;
        }
    }

    //find the zero indegree vertices and put them into queue
    for(int i=0; i<n; i++)
    {
        if(count_in[i] == 0)
        {
            q.push(i);
        }
    }

    //topological sort
    for(int i=0; i<n; i++)
    {   
        if(q.empty())
        {
            return false;
        }

        else
        {
            int current = q.front();
            q.pop();

            //decrease indegree of the successor vertices
            temp = graph[current];
            while(temp!=nullptr)
            {
                count_in[temp->vertex]--;
                //if the indegree of the successor vertex becomes 0, put it into queue
                if(count_in[temp->vertex]==0)
                {
                    q.push(temp->vertex);
                }

                temp = temp->next;
            }
        }
    }
    return true;
}