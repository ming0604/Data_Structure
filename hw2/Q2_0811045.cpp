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

void number_of_term(int*,int*);
void addterms(float, int);
void multiply_poly(int, int, int, int, int);
int AddForMul(int, int, int, int);
void set_temp(float, int, int);

int main()
{   
    int starta, startb, finisha, finishb, temp_position;
    int m, n, tempexp;
    float tempcoef;
    
    number_of_term(&m,&n);
    starta=0;
    finisha=starta+m-1;
    startb=finisha+1;
    finishb=startb+n-1;
    temp_position=m+n;

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
    multiply_poly(starta, startb, finisha, finishb, temp_position);

    return 0;
}


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

void set_temp(float tc, int te ,int tp)
{
    terms[tp].coef=tc;
    terms[tp].expon=te;
}


int AddForMul(int sa, int st, int fa, int ft)
{   
    float AddCoef;
    int SameExp,finishr,count=0;

    while(sa<=fa && st<=ft)
    {
        if(terms[sa].expon>terms[st].expon)
        {   
            addterms(terms[sa].coef,terms[sa].expon);
            sa++;
        }

        else if (terms[sa].expon<terms[st].expon)
        {   
            addterms(terms[st].coef,terms[st].expon);
            st++;
        }
        
        else
        {   
            AddCoef=terms[sa].coef+terms[st].coef;
            SameExp=terms[sa].expon;
            addterms(AddCoef,SameExp);
            sa++;
            st++;
        }
        count++;
    }    

    //Add the remaining terms of B 
    if(sa>fa && st<=ft)
    {   
        for(int i=st; i<=ft; i++)
        {
            addterms(terms[i].coef,terms[i].expon);
            count++;      
        }
    }
    //Add the remaining terms of A
    else if(st>ft && sa<=fa)
    {
        for(int i=sa; i<=fa; i++)
        {
            addterms(terms[i].coef,terms[i].expon);
            count++; 
        }        
    }

    return count;
}
void multiply_poly(int sa, int sb, int fa, int fb, int tp)
{   
    int tempexp,start_result,finish_result,startadd,result_poly_terms;
    float tempcoef;

    //Make a place for temp
    avail++;  
    start_result=avail;

    //Multiply every term of A and B 
    for(int i=sa; i<=fa; i++)
    {
        for (int j=sb; j<=fb; j++)
        {
            tempcoef= terms[i].coef * terms[j].coef;
            tempexp= terms[i].expon + terms[j].expon;

            //The first term of result
            if(i==sa&&j==sb)
            {
                addterms(tempcoef, tempexp);
                finish_result=avail-1;
            }

            //Add the new multiply term to the result-polynomial
            else
            {
                set_temp(tempcoef, tempexp, tp);
                startadd=avail;
                result_poly_terms= AddForMul(start_result, tp, finish_result, tp);

                finish_result=start_result+result_poly_terms-1;
                for (int k=start_result; k<=finish_result; k++)
                {   
                    terms[k].coef=terms[startadd].coef;
                    terms[k].expon=terms[startadd].expon;
                    startadd++;
                }
                avail=finish_result+1;
            }
        }

    }

    //output the result polynomial
    for (int i=start_result; i<=finish_result; i++)
    {
        cout<<terms[i].coef<<" "<<terms[i].expon<<endl;
    }

}