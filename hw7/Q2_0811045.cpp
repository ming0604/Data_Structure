#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct edge
{
    int vertex1;
    int vertex2;
    int cost;

}edge;

bool compare(edge a, edge b);
vector<edge> input(int S);
int FindSetRoot(int* parent, int v);
void SetUnion(int* parent, int u, int v);
int min_noise(int C, int C1, int C2, vector<edge> eg);


int main()
{       
    int C,S,Q,C1,C2,noise;
    cin >> C >> S >> Q;
    
    //input edges
    vector<edge> edges=input(S);

    //find the minimum noise
    int answers[Q];
    for(int i=0 ;i<Q; i++)
    {   
        cin >> C1 >> C2;
        answers[i]=min_noise(C, C1, C2, edges);
    }

    //output
    for(int i=0; i<Q; i++)
    {   
        if(answers[i]!=-1)               //-1 means no path      
        {
            if(i!=Q-1)
            {
                cout << answers[i] << endl; 
            }
            else
            {
                cout << answers[i]; 
            }
        }
        else
        {
            if(i!=Q-1)
            {
                cout << "no path" << endl; 
            }
            else
            {
                cout << "no path"; 
            }
        }
    }

    return 0;
}


bool compare(edge a, edge b)
{
    return a.cost<b.cost;
}

vector<edge> input(int S)
{
    vector<edge> e;
    int C1,C2,cost;
    edge temp;

    for(int i=0; i<S; i++)
    {   
        cin >> C1 >> C2 >> cost;
        temp.vertex1=C1;
        temp.vertex2=C2;
        temp.cost=cost;
        e.push_back(temp);
    }

    sort(e.begin(),e.end(),compare);

    return e;
}

int FindSetRoot(int* parent, int v)
{
    if(parent[v]!=v)
    {   
        int root=FindSetRoot(parent,parent[v]);
        parent[v]=root;
        return root;
    }

    else
    {
        return v;
    }
}

void SetUnion(int* parent, int u, int v)
{
    int uroot=FindSetRoot(parent,u);
    int vroot=FindSetRoot(parent,v);
    
    if(uroot==vroot)
    {
        return;
    }
    else
    {
        parent[uroot]=vroot;
    }
}

int min_noise(int C, int C1, int C2, vector<edge> eg)
{   
    int vertice_set[C];
    int u,v,ans=-1;                                 //ans=-1 means no path
    //Initialize the set, and every vertex is a set;
    for(int i=0; i<C; i++)
    {
        vertice_set[i]=i;
    }

    for(int i=0; i<eg.size(); i++)
    {
        u=(eg[i].vertex1)-1;
        v=(eg[i].vertex2)-1;
        SetUnion(vertice_set,u,v);

        if(FindSetRoot(vertice_set,C1-1)==FindSetRoot(vertice_set,C2-1))
        {
            ans=eg[i].cost;
            break;
        }
    }

    return ans;
}
