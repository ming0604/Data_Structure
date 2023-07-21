#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define MAX_TERMS 100 
/*size of terms array*/
typedef struct{
    float coef;
    int expon;
}polynomial;
polynomial terms [MAX_TERMS];
int avail = 0;

void addpoly(int, int, int, int, int);
void number_of_term(int*,int*);
void addterms(float, int);

int main()
{   
    int starta, startb, finisha, finishb, start_result;
    int m, n, tempexp;
    float tempcoef;
    number_of_term(&m,&n);
    starta=0;
    finisha=starta+m-1;
    startb=finisha+1;
    finishb=startb+n-1;
    start_result=m+n;
    //input the terms of A and B
    for(int i=0; i<(m+n); i++)
    {   
        cin >> tempcoef >> tempexp;
        if(-1000<=tempexp && tempexp<=1000 && -1000<=tempcoef && tempcoef<=1000)
        {
            addterms(tempcoef, tempexp);
        }
        else
        {
            cout << "The number is out of range, please input again!" << endl;
            i=-1;
            avail=0;
        }        
    }
    
    addpoly(starta, startb, finisha, finishb, start_result);

    return 0;
}

//input the number of terms of polynomials A and B( 1 <= m <= 99, 1 <= n <= 99)
void number_of_term(int*m,int*n)
{   
    int flag=1;
    while(flag)
    {
        cin >>*m >>*n;
        if(1<=*m && *m<=99 && 1<=*n && *n<=99)
        {
            flag=0;
        }
        
        else
        {
            cout <<"The number of terms out of range" <<endl;
        }
    } 
}

void addterms(float coef, int exp)
{
    if(avail>=MAX_TERMS)
    {
        cout << "Can't add more terms!" << endl;
    }
    else
    {
        terms[avail].coef=coef;
        terms[avail].expon=exp;
    }
    avail++;
}


void addpoly(int sa, int sb, int fa, int fb, int sr)
{   
    float AddCoef;
    int SameExp,finishr;

    while(sa<=fa && sb<=fb)
    {
        if(terms[sa].expon>terms[sb].expon)
        {   
            addterms(terms[sa].coef,terms[sa].expon);
            sa++;
        }

        else if (terms[sa].expon<terms[sb].expon)
        {   
            addterms(terms[sb].coef,terms[sb].expon);
            sb++;
        }
        
        else
        {   
            AddCoef=terms[sa].coef+terms[sb].coef;
            SameExp=terms[sa].expon;
            addterms(AddCoef,SameExp);
            sa++;
            sb++;
        }
    
    }    

    //Add the remaining terms of B 
    if(sa>fa && sb<=fb)
    {   
        for(int i=sb; i<=fb; i++)
        {
            addterms(terms[i].coef,terms[i].expon);      
        }
    }
    //Add the remaining terms of A
    else if(sb>fb && sa<=fa)
    {
        for(int i=sa; i<=fa; i++)
        {
            addterms(terms[i].coef,terms[i].expon); 
        }        
    }

    //show the result of A add B
    finishr=avail-1;
    for (int i=sr; i<=finishr; i++)
    {
        cout<<terms[i].coef<<" "<<terms[i].expon<<endl;
    }
    
}
