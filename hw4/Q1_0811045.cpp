#include <iostream>

using namespace std;

// You MUST NOT modify this!
struct Snake {
    int ratWeight;
    Snake *nextRat;
    Snake() : ratWeight(0), nextRat(nullptr) {}
    Snake(int x) : ratWeight(x), nextRat(nullptr) {}
    Snake(int x, Snake *nextRat) : ratWeight(x), nextRat(nextRat) {}
};

int** vomitAndCrawl(int rows, int cols, Snake* head) {
    int count=0, arraysize, now_row=0, now_col=-1, direction,i;
    int right=0, left=1, up=2, down=3;
    int right_boundary=cols, left_boundary=-1, top_boundary=0, bottom_boundary=rows;
    bool flag=true;
    Snake* now=head;

    int** vomit= new int*[rows];
    for(i=0; i<rows; i++)
    {
        vomit[i]= new int[cols];
    }

    arraysize = rows*cols;
    direction = 0;
    while(flag)
    {
        switch (direction)
        {
            case 0:
                now_col++;
                for(i=now_col; i<right_boundary; i++)
                {   
                    if(now!=nullptr)
                    {
                        vomit[now_row][i]= now->ratWeight;
                        now=now->nextRat;
                        count++;
                        now_col=i;
                    }
                    else
                    {
                        vomit[now_row][i]= -1;
                        count++;
                        now_col=i;
                    }  
                }
                right_boundary--;
                direction=3;
                break;

            case 1:
                now_col--;
                for(i=now_col; i>left_boundary; i--)
                {   
                    if(now!=nullptr)
                    {
                        vomit[now_row][i]= now->ratWeight;
                        now=now->nextRat;
                        count++;
                        now_col=i;
                    }
                    else
                    {
                        vomit[now_row][i]= -1;
                        count++;
                        now_col=i;
                    }  
                }
                left_boundary++;
                direction=2;               
                break;

            case 2:
                now_row--;
                for(i=now_row; i>top_boundary; i--)
                {   
                    if(now!=nullptr)
                    {
                        vomit[i][now_col]= now->ratWeight;
                        now=now->nextRat;
                        count++;
                        now_row=i;
                    }
                    else
                    {
                        vomit[i][now_col]= -1;
                        count++;
                        now_row=i;
                    }  
                }
                top_boundary++;
                direction=0;
                break;

            case 3:
                now_row++;
                for(i=now_row; i<bottom_boundary; i++)
                {   
                    if(now!=nullptr)
                    {
                        vomit[i][now_col]= now->ratWeight;
                        now=now->nextRat;
                        count++;
                        now_row=i;
                    }
                    else
                    {
                        vomit[i][now_col]= -1;
                        count++;
                        now_row=i;
                    }  
                }
                bottom_boundary--;
                direction=1;
                break;
        }

        if(count==arraysize)
        {
            flag=false;
        }
    }

    return vomit;
}

// You MUST NOT modify this!
int main()
{
    int rows, cols, numOfRats;
    cin >> rows >> cols >> numOfRats;

    Snake* head = new Snake();
    Snake* current = head;

    for(int i=0; i<numOfRats ; i++)
    {
        cin >> current->ratWeight;
        if(i < numOfRats - 1)
        {
            Snake* nextRat = new Snake();
            current->nextRat = nextRat;
            current = current->nextRat;
        }
    }

    int** terrarium = vomitAndCrawl(rows, cols, head);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            cout << terrarium[i][j];
            if(j < cols-1)
                cout << " ";
        }
        if(i < rows-1)
            cout << "\n";
    }

    return 0;
}

