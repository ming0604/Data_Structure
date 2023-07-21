#include<iostream>

using namespace std;

int n;
int inputN();
int inputLeaves();
int FindMaxJump(int[]);

int main(int argc, char **argv){
    n = inputN();
    int leaves[n] = {0};
    for(int i = 0; i < n; i++){
        leaves[i] = inputLeaves();
    }

    cout << FindMaxJump(&leaves[0]) << endl;
    return 0;
}

//scan the size of array
int inputN(){
    int input = 0;
    cin >> input;
    if ( input >= 1 && input <= 1000){
        return input;
    }else{
        cout << "[W]input error !" << endl;
        return inputN();
    }

}

//scan the input element of the array
int inputLeaves(){
    int leavesInput = 0;
    cin >> leavesInput;
    if ( leavesInput >= -1 && leavesInput <= 1 ){
        return leavesInput;
    }else{
        cout << "[W]input error !" << endl;
        return inputLeaves();
    }

}

//find max jump
int FindMaxJump(int *leaves){
    int maleCNT = 0;
    int cnt = 0;
    int maxjump = 0;
    for(int i=0; i<n; i++){
        if(*(leaves + i) == 1){
            maleCNT ++ ;
        }
    }

    int locationMale[maleCNT] = {0};

    for(int i=0; i<n; i++){
        if(*(leaves + i) == 1){
            locationMale[cnt] = i;
            cnt++;
        }
    }

    /*
    for(int i=0; i<maleCNT; i++){
        cout << locationMale[i] << " ";
    }
    cout << endl;
    */
    
    //from left to right
    for(int i=0; i<maleCNT; i++){
        int start = locationMale[i];
        int jump = 0;
        bool flag = true;
        cnt = start;
        while(flag == true){
            if(cnt == n - 1){
                flag = false;
                //cout << "touch1" << endl;
            }else if(*(leaves + cnt + 1) == 1){
                flag = false;
                //cout << "touch2" << endl;
            }else if(*(leaves + cnt) == -1){
                jump = cnt - start - 1;
                //cout << jump << endl;
                //cout << "touch3" << endl;
                flag = false;
            }

            cnt ++;
        }

        flag = true;
        if(jump > maxjump){
            maxjump = jump;
            //cout <<"maxjump = "<<maxjump << endl;
        }
        
    }
    
    //from right to left
    for(int i=(maleCNT-1); i>=0; i--){
        int start = locationMale[i];
        int jump = 0;
        bool flag = true;
        cnt = start;
        while(flag == true){
            if(cnt == 0){
                flag = false;
                //cout << "touch1" << endl;
            }else if(*(leaves + cnt - 1) == 1){
                flag = false;
                //cout << "touch2" << endl;
            }else if(*(leaves + cnt) == -1){
                jump = start - (cnt+1);
                //cout << jump << endl;
                //cout << "touch3" << endl;
                flag = false;
            }

            cnt --;
        }

        flag = true;
        if(jump > maxjump){
            maxjump = jump;
            cout <<"maxjump = "<<maxjump << endl;
        }
        
    }

    return maxjump;
}
