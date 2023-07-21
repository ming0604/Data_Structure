#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void input_leaves_rows_cols(int*,int*);
void input_leaves_status(int, int, int** );
int maxjump(int, int, int** );



int main()
{   
    int leaves_rows, leaves_cols, max_jump;
    input_leaves_rows_cols(&leaves_rows,&leaves_cols);
    int leaves[leaves_rows][leaves_cols];

    // Preprocessing from the 2D-array in order to let it can be passed to a function
    int* leavesrowspointer[leaves_rows];  
    for (int i = 0; i < leaves_rows; i++)
    {
        leavesrowspointer[i]=leaves[i];    
    }
    
    input_leaves_status(leaves_rows, leaves_cols, leavesrowspointer);
    max_jump = maxjump(leaves_rows, leaves_cols, leavesrowspointer);
    cout << "maximum jump: " << max_jump;


    return 0;
}


//enter the rows and cols of leaves
void input_leaves_rows_cols(int *rows, int *cols)
{   while(1)
    {
        cout << "Enter the rows and cols of leaves(each from 1 to 1000): ";
        cin >> *rows >> *cols;

        if(1<=*rows && *rows<=1000 && 1<=*cols && *cols<=1000)
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
void input_leaves_status(int leaves_rows, int leaves_cols, int **leaves)
{
    int valid=1;
    while (valid)
    {
        cout << "Enter the status of leaves(-1 or 0 or 1): ";

        // input leaves status one by one
        for(int i=0; i<leaves_rows; i++)
        {
            for(int j=0; j<leaves_cols; j++)
            {
                cin >> leaves[i][j];
                
            }    
        } 

        //check if there are some invalid status
        int invalid=0;
        for (int i=0;  i<leaves_rows ; i++)
        {   
            for(int j=0; j<leaves_cols; j++)
            {
                if(leaves[i][j]==-1 || leaves[i][j]==0 || leaves[i][j]==1)
                {
                    if (i == leaves_rows-1 && j == leaves_cols-1 && invalid==0)
                    {   
                        valid=0;                              //finish input leaves status, so let while loop do not operate 
                    }
                
                }
                else
                {   
                    invalid=1; 
                }                 
            }    
        }

        if(invalid==1)
        {
            cout << "Invalid status!(if you enter a wrong size of the array, please restart the code.)" << endl;
        }
    }        
}

//count the maximum jump 
int maxjump(int rows, int cols, int **leaves)
{
    int closest_male_index=-1 , now_counting_female_index=-1;
    vector<int> jump;  
    //vector jump stores every number of jumps from one male frog to one female frog

    int max_jump_left , max_jump_right , max_jump_up , max_jump_down , max_jump;

    //find max number of the jumps which is from left to right
    for(int i=0; i<rows; i++)
    {   
        closest_male_index=-1 , now_counting_female_index=-1;
        for (int j = 0; j < cols; j++)
        {   
            switch (leaves[i][j])
            {
            case 1:
                closest_male_index=j;
                break;

            case 0:
                break;

            case -1:
                now_counting_female_index=j;
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
    
    for(int i=0; i<rows; i++)
    {   
        closest_male_index=-1 , now_counting_female_index=-1;
        for(int j=cols-1; j>=0; j--)
        {
            switch (leaves[i][j])
            {
            case 1:
                closest_male_index=j;
                break;

            case 0:
                break;

            case -1:
                now_counting_female_index=j;
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



    //find max number of the jumps which is from up to down
    for(int i=0; i<cols; i++)
    {   
        closest_male_index=-1 , now_counting_female_index=-1;
        for (int j = 0; j < rows; j++)
        {
            switch (leaves[j][i])
            {
            case 1:
                closest_male_index=j;
                break;

            case 0:
                break;

            case -1:
                now_counting_female_index=j;
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
        

    }

    if(jump.size()==0)
    {
        max_jump_up=0;
    }
    else
    {
        max_jump_up = *max_element(jump.begin(), jump.end());
    }
    
    jump.clear();



    //find max number of the jumps which is from down to up
    for(int i=0; i<cols; i++)
    {   
        closest_male_index=-1 , now_counting_female_index=-1;
        for (int j = rows-1; j >= 0; j--)
        {
            switch (leaves[j][i])
            {
            case 1:
                closest_male_index=j;
                break;

            case 0:
                break;

            case -1:
                now_counting_female_index=j;
                if(closest_male_index == -1) 
                {   
                    jump.push_back(0);
                    closest_male_index=-1 , now_counting_female_index=-1;                //clear for next count
                    break;
                } 
                else
                {
                    jump.push_back(closest_male_index - now_counting_female_index-1);
                    closest_male_index=-1 , now_counting_female_index=-1;               //clear for next count
                    break;
                }     
            }            
        }
        

    }

    if(jump.size()==0)
    {
        max_jump_down=0;
    }
    else
    {
        max_jump_down = *max_element(jump.begin(), jump.end());
    }
    
    jump.clear();



    //Comparing max_jump_left,max_jump_right,max_jump_up and max_jump_down
    int max_jump_array[4] = {max_jump_left, max_jump_right, max_jump_up, max_jump_down};
    int temp_max=max_jump_array[0];
    for (int i = 0; i < 4; i++)
    {  
        if (max_jump_array[i]>temp_max)
        {
            temp_max=max_jump_array[i];
        }
            
    }
    max_jump=temp_max;

    return max_jump;    

}