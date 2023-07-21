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

Snake* delete_node(Snake* head, int del_position)
{   
    if(del_position==0)   //There is no node before the node which I want to delete.
    {
        delete head;
        head=nullptr;
    }
    else
    {   
        Snake* trail=head;
        Snake* del_node=head;
        for (int i=0; i<del_position; i++)
        {
            del_node=del_node->nextRat;
        }
        
        for(int i=0; i<del_position-1; i++)
        {   
            trail=trail->nextRat;
        }

        trail->nextRat = del_node->nextRat;
        delete del_node;
    }
    
    return head;
}

Snake* digestMiddle(Snake* head) {
    int remainRat=0,middle;
    Snake* temp = head;
    if (temp==nullptr)
    {
        return temp;
    }
    
    else
    {
        //Count the number of ramainimg rats
        while (1)
        {
            remainRat++;
            temp=temp->nextRat;

            if(temp==nullptr)
            {
                break;
            }
        }

        //Count the middle
        middle=(remainRat/2);
        temp=delete_node(head,middle);
        return temp;
    }
}

int** vomitAndCrawl(int rows, int cols, Snake* head, int digestInterval) {
    int count=0, digest_count=0, arraysize, now_row=0, now_col=-1, direction,i;
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
                        digest_count++;
                        count++;
                        if(digest_count==digestInterval)
                        {
                            now=digestMiddle(now->nextRat);
                            digest_count=0;
                        }
                        else
                        {
                            now=now->nextRat;
                        }
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
                        digest_count++;
                        count++;
                        if(digest_count==digestInterval)
                        {
                            now=digestMiddle(now->nextRat);
                            digest_count=0;
                        }
                        else
                        {
                            now=now->nextRat;
                        }
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
                        digest_count++;
                        count++;
                        if(digest_count==digestInterval)
                        {
                            now=digestMiddle(now->nextRat);
                            digest_count=0;
                        }
                        else
                        {
                            now=now->nextRat;
                        }
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
                        digest_count++;
                        count++;
                        if(digest_count==digestInterval)
                        {
                            now=digestMiddle(now->nextRat);
                            digest_count=0;
                        }
                        else
                        {
                            now=now->nextRat;
                        }
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
    int rows, cols, numOfRats, digestInterval ;
    cin >> rows >> cols >> numOfRats ;

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

    cin >> digestInterval;

    int** terrarium = vomitAndCrawl(rows, cols, head, digestInterval);

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

