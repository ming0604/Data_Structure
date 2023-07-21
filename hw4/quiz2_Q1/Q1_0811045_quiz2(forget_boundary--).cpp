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

int** vomitAndCrawl(int length, Snake* head) {
    int** terrarium = new int*[length];
    for(int i=0; i<length; i++)
    {
        terrarium[i] = new int[length];
        for(int j=0; j<length; j++)
        {
            terrarium[i][j] = -1;
        }
    }

    int right=0,left=1,up=2,down=3;
    int r_boundary=length,l_boundary=0,u_boundary=-1,d_boundary=length;
    int direction=down,now_col=0,now_row=-1;
    Snake* now=head;
    bool endflag=true;

    while(endflag)
    {
        switch(direction)
        {
            case 0:
                now_col++;
                while(now_col<r_boundary)
                {
                    if(now!=nullptr)
                    {
                        terrarium[now_row][now_col]=now->ratWeight;
                        now=now->nextRat;
                        now_col++;
                    }
                    else
                    {
                        endflag=false;
                        break;
                    }
                }
                now_col--;
                direction=up;
                break;

            case 1:
                now_col--;
                while(now_col>l_boundary)
                {
                    if(now!=nullptr)
                    {
                        terrarium[now_row][now_col]=now->ratWeight;
                        now=now->nextRat;
                        now_col--;
                    }
                    else
                    {
                        endflag=false;
                        break;
                    }
                }
                now_col++;
                direction=down;
                break;

            case 2:
                now_row--;
                while(now_row>u_boundary)
                {
                    if(now!=nullptr)
                    {
                        terrarium[now_row][now_col]=now->ratWeight;
                        now=now->nextRat;
                        now_row--;
                    }
                    else
                    {
                        endflag=false;
                        break;
                    }
                }
                now_row++;
                direction=left;
                break;

            case 3:
                now_row++;
                while(now_row<d_boundary)
                {
                    if(now!=nullptr)
                    {
                       terrarium[now_row][now_col]=now->ratWeight;
                        now=now->nextRat;
                        now_row++;
                    }
                    else
                    {
                        endflag=false;
                        break;
                    }

                }
                now_row--;
                direction=right;

                break;
        }
    }

    return terrarium;
}

// You MUST NOT modify this!
int main()
{
    int length, numOfRats;
    cin >> length >> numOfRats;

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

    int** terrarium = vomitAndCrawl(length, head);

    for(int i=0; i<length; i++)
    {
        for(int j=0; j<length; j++)
        {
            cout << terrarium[i][j];
            if(j < length-1)
                cout << " ";
        }
        if(i < length-1)
            cout << "\n";
    }

    return 0;
}

