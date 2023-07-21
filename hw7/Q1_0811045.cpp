#include <iostream>
#define max_noise 100000

using namespace std;

void input_cost(int**cost, int C, int S);
int** min_noise(int** cost,int C);

int main()
{       
    int C,S,Q;
    cin >> C >> S >> Q;

    int** cost = new int*[C];
    for(int i=0; i<C; i++)
    {   
        cost[i] = new int[C];
        for(int j=0; j<C; j++)
        {   
            if(i==j)
            {
                cost[i][j]=0;
            }
            else
            {
                cost[i][j]=max_noise;
            }
        }
    }
    
    //input noise data
    input_cost(cost,C,S);

    //find the minimum noise
    int C1,C2;
    int** distance = min_noise(cost,C);
    int min_noise_output[Q];
    for(int i=0; i<Q; i++)
    {   
        cin >> C1 >> C2;
        min_noise_output[i]=distance[C1-1][C2-1];
    }

    //Output the answers
    for(int i=0; i<Q; i++)
    {   
        if(min_noise_output[i]!=max_noise)
        {
            if(i!=Q-1)
            {
                cout << min_noise_output[i] << endl; 
            }
            else
            {
                cout << min_noise_output[i]; 
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


void input_cost(int**cost, int C, int S)
{   
    int vertex1=0,vertex2=0,d=0;
    for(int i=0; i<S ;i++)
    {
        cin >> vertex1 >> vertex2 >> d;
        cost[vertex1-1][vertex2-1]=d;
        cost[vertex2-1][vertex1-1]=d;
    }
}

int** min_noise(int** cost,int C)
{
    int** distance = new int*[C];
    for(int i=0; i<C; i++)
    {   
        distance[i] = new int[C];
        for(int j=0; j<C; j++)
        {
            distance[i][j]=cost[i][j];
        }
    }

    for(int k=0; k<C; k++)
    {
        for(int i=0; i<C; i++)
        {
            for(int j=0; j<C; j++)
            {
                if(distance[i][k] + distance[k][j] < distance[i][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    return distance;
}