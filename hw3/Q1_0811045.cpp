#include <iostream>
#include <cstdlib>
#include <fstream>

#define MAX_STACK_SIZE 100
using namespace std;

typedef struct{
    int data[MAX_STACK_SIZE];
    int top=-1;
}stack_int;

bool stack_full(stack_int*);
bool stack_empty(stack_int*);
void push(stack_int*,int);
int pop(stack_int*);
void input_points(int,int[]);
void spans(int,int[]);

int main()
{
    int days;
    //The number of days should be in the range 0<N<=100
    while(1)
    {
        cin >> days;
        if (0<days && days<=100)
        {
            break;
        }
    }

    int points[days];
    input_points(days,points);   //enter the daily points
    spans(days,points);

    return 0;
}

bool stack_full(stack_int*stack)
{
    if(stack->top >= MAX_STACK_SIZE-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool stack_empty(stack_int*stack)
{
    if(stack->top < 0)
    {
        return true;
    }
    else
    {
        return false;
    }   

}

void push(stack_int*stack,int element)
{
    if(stack_full(stack))
    {
        cout << "error" << endl;
    }

    else
    {
        stack->top++;
        stack->data[stack->top]=element;
    }

}

int pop(stack_int*stack)
{
    if(stack_empty(stack))
    {
        cout << "error" << endl;
        return 0;
    }

    else
    {
        int temp;
        temp=stack->data[stack->top];
        stack->top --;
        return temp;
    }    

}

void input_points(int days,int points[])
{   
    for (int i=0; i<days; i++)
    {
        cin >> points[i];
    }
}

void spans(int days,int points[])
{
    stack_int count_spans;
    int spans[days],top_index;

    for(int i=0; i<days; i++)
    {   
        while(1)
        {   
            if(stack_empty(&count_spans)==false)
            {   
                top_index=count_spans.data[count_spans.top];
                if(points[top_index]<points[i] || points[top_index]==points[i])
                {
                    pop(&count_spans);
                }

                else
                {
                    spans[i]=i-top_index;
                    push(&count_spans,i);
                    break;
                }
            }

            else
            {
                spans[i]=i+1;
                push(&count_spans,i);
                break;
            }
        }
    }

    //output the result
    for(int i=0; i<days; i++)
    {   
        if(i!=days-1)
        {
            cout<< spans[i]<< " ";
        }
        else
        {
            cout<< spans[i];
        }
    }
}