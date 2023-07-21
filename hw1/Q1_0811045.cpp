#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


void input_leaves_num(int*);
void input_leaves_status(int, int[]);
int maxjump(int, int[]);

int main()
{   
    int leaves_num,max_jump;
    int leaves[1000];
    input_leaves_num(&leaves_num);
    input_leaves_status(leaves_num, leaves);
    max_jump = maxjump(leaves_num,leaves);
    cout << "maximum jump: " << max_jump;


    return 0;
}


//enter the number of leaves
void input_leaves_num(int *leavesnum)
{
    while(1)
    {
        cout << "Enter the number of leaves(from 1 to 1000): ";
        cin >> *leavesnum;

        if(1<= *leavesnum && *leavesnum<=1000)
        {
            break;
        }

        else
        {
            cout << "Invalid number!"<< endl;
        }
    }
}


//enter the status of the leaves
void input_leaves_status(int leaves_num, int leaves[])
{
    int valid=1;
    while (valid)
    {
        cout << "Enter the status of leaves(-1 or 0 or 1): ";

        // input leaves status one by one
        for(int i=0; i<leaves_num; i++)
        {
            cin >> leaves[i];
        } 

        //check if there are some invalid status
        int invalid=0;
        for (int j = 0;  j<leaves_num ; j++)
        {
           if(leaves[j]==-1 || leaves[j]==0 || leaves[j]==1)
            {
                if (j == leaves_num-1 && invalid==0)
                {   
                    valid=0;                      //finish input leaves status, so let while loop do not operate 
                }
                
            }
            else
            {   
                invalid=1; 
            }  
        }
        if(invalid==1)
        {
             cout << "Invalid status!" << endl;
        }
    }        
}

//count the maximum jump 
int maxjump(int n,int leaves[])
{   
    int closest_male_index=-1 , now_counting_female_index=-1;
    vector<int> jump;                                             //vector jump stores every number of jumps from one male frog to one female frog
    int max_jump_left , max_jump_right , max_jump;

    //find max number of the jumps which is from left to right
    for(int i=0; i<n; i++)
    {
        switch (leaves[i])
        {
        case 1:
            closest_male_index=i;
            break;

        case 0:
            break;

        case -1:
            now_counting_female_index=i;
            if(closest_male_index == -1) 
            {   
                jump.push_back(0);
                closest_male_index=-1 , now_counting_female_index=-1;                //clear for next count
                break;
            } 
            else
            {
                jump.push_back(now_counting_female_index - closest_male_index-1);
                closest_male_index=-1 , now_counting_female_index=-1;               //clear for next count
                break;
            }     
        }
    }

    if(jump.size()==0)
    {
        max_jump_left=0;
    }
    else
    {
        max_jump_left = *max_element(jump.begin(), jump.end());
    }
    
    jump.clear();


    //find max number of the jumps which is from right to left  
    closest_male_index=-1 , now_counting_female_index=-1;  
    for(int i=n-1; i>=0; i--)
    {
        switch (leaves[i])
        {
        case 1:
            closest_male_index=i;
            break;

        case 0:
            break;

        case -1:
            now_counting_female_index=i;
            if(closest_male_index == -1) 
            {   
                jump.push_back(0);
                closest_male_index=-1 , now_counting_female_index=-1;
                break;
            } 
             
            else
            {
                jump.push_back(closest_male_index - now_counting_female_index-1);
                closest_male_index=-1 , now_counting_female_index=-1;
                break;
            }     
        }
    }
    if(jump.size()==0)
    {
        max_jump_right=0;
    }
    else
    {
        max_jump_right = *max_element(jump.begin(), jump.end());
    }
    jump.clear();
    

    //Comparing max_jump_left to max_jump_right
    if(max_jump_left > max_jump_right)
    {
        max_jump = max_jump_left;
    }

    else if (max_jump_right > max_jump_left)
    {
        max_jump = max_jump_right;
    }

    else            //max_jump_right = max_jump_left
    {
        max_jump = max_jump_right;
    }
    
    return max_jump;
}