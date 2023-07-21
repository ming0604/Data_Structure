#include <iostream>
#include <vector>

using namespace std;

void input_tree(int N, int *tree);
void find_target(int *tree, vector<int> *target, int index, int previous, int distance, int N);
void find_target_array(int flag, int N, int distance, int *tree);
void bubble_sort(vector<int>& t, int size);

int main()
{   
    int nodes,FlagNodeValue,distance;
    int tree[500];

    cin >> nodes;
    input_tree(nodes,tree);
    cin >> FlagNodeValue >> distance;
    find_target_array(FlagNodeValue,nodes,distance, tree);

    return 0;
}


void input_tree(int N, int *tree)
{
    for(int i=0; i<N; i++)
    {
        cin >> tree[i];
    }
}

void bubble_sort(vector<int>& t, int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(t[j]>t[j+1])
            {
                int temp=t[j];
                t[j]=t[j+1];
                t[j+1]=temp;
            }
        }
    }

}

void find_target(int *tree, vector<int> *target, int index,int previous, int distance, int N)
{   
    if(distance==0)
    {
        target->push_back(tree[index]);
        return;
    }
    int left_child_index,right_child_index,parent_index;
    left_child_index=2*index+1;
    right_child_index=2*index+2;
    if(index==0)
    {
        parent_index=-1;
    }
    else
    {
        parent_index=(index-1)/2;
    }
    
    if(left_child_index<N && tree[left_child_index]!=-1 && tree[left_child_index]!=previous)
    {   
        find_target(tree,target,left_child_index,tree[index],distance-1,N);
    }

    if(right_child_index<N && tree[right_child_index]!=-1 && tree[right_child_index]!=previous)
    {
        find_target(tree,target,right_child_index,tree[index],distance-1,N);
    }
 
    if(0<=parent_index && parent_index<N && tree[parent_index]!=-1 && tree[parent_index]!=previous)
    {
        find_target(tree,target,parent_index,tree[index],distance-1,N);
    }
}


void find_target_array(int flag, int N, int distance, int *tree) 
{   
    //Find the current node index;
    int current_node_index;
    for(int i=0; i<N; i++)
    {
        if(tree[i]==flag)
        {
            current_node_index=i;
            break;
        }
    }

    //Find 
    vector<int> targets;
    int previous=-2;           //there are no previous value of the initial, so let it be a value that won,t in the array.
    find_target(tree,&targets,current_node_index,previous,distance,N);

    
    int targets_size = targets.size();
    if(targets_size!=0)
    { 
        //sort
        bubble_sort(targets, targets_size);
        
        //output
        for(int i=targets_size-1; i>=0 ;i--)
        {   
            if(i==targets_size-1)
            {
                cout << targets[i];
            }

            else
            {
                cout << " " << targets[i];
            }
        }
    } 
    //If there are no value that meet the needs.
    else                                     
    {
        cout << "Null";
    }

}