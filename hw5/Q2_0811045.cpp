#include <iostream>
#include <queue>
#include <math.h>

using namespace std;

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

// node
treeNode *CreateNode(int data)
{
    treeNode *temp = new treeNode;
    temp->data = data;
    temp->left = temp->right = nullptr;
    return temp;
}

treeNode *InsertLevelOrder(treeNode *node, int data)
{
    if (node == nullptr)
    {
        node = CreateNode(data);
        return node;
    }

    std::queue<treeNode *> q;
    treeNode *current = node;

    while (current)
    {
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        else
        {
            current->left = CreateNode(data);
            return current->left;
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
        else
        {
            current->right = CreateNode(data);
            return current->right;
        }
        current = q.front();
        q.pop();
    }
    return nullptr;
}

// hint: you can use InsertLevelOrder()
// reference of level-order insertion:
// http://alrightchiu.github.io/SecondRound/binary-tree-jian-li-yi-ke-binary-tree.html#func2
// you can modify this function
treeNode *input()
{
    treeNode *root = CreateNode(0);
    treeNode *red = InsertLevelOrder(root, 1);
    treeNode *black = InsertLevelOrder(root, 1);
    int number_of_round, current_round, total_move, TeamInitiativeFlag;           //team red=0, team black=1
    int *move;

    cin >> number_of_round;
    total_move = 4*(1-pow(2,number_of_round))/(1-2);                       //use geometric series formula to count the total number of moves
    move = new int[total_move];
    for(int i=0; i<total_move; i++)
    {
        cin>> move[i];
    }

    current_round=1;
    TeamInitiativeFlag=0;                                           //team red first;
    int first_index_of_current_round=0;                        
    int i;
    int red_start,black_start,red_end,black_end;
    while(current_round!=number_of_round+1)
    {   
        first_index_of_current_round = 4*(1-pow(2,current_round-1))/(1-2);
        switch (TeamInitiativeFlag)
        {   
            // team red has initiative
            case 0:
                red_start = first_index_of_current_round;
                red_end = red_start+pow(2,current_round);
                black_start = red_end;
                black_end = black_start+pow(2,current_round);

                // put red team move into the tree
                for(i=red_start; i<red_end; i++)
                {
                    InsertLevelOrder(red, move[i]);
                }
                // put black team move into the tree
                for(i=black_start; i<black_end; i++)
                {
                    InsertLevelOrder(black, move[i]);
                }
                TeamInitiativeFlag=1;
                current_round++;
                break;

            // team black has initiative
            case 1:
                black_start = first_index_of_current_round;
                black_end = black_start+pow(2,current_round);
                red_start = black_end;
                red_end = red_start+pow(2,current_round);

                // put red team move into the tree
                for(i=red_start; i<red_end; i++)
                {
                    InsertLevelOrder(red, move[i]);
                }
                // put black team move into the tree
                for(i=black_start; i<black_end; i++)
                {
                    InsertLevelOrder(black, move[i]);
                }
                TeamInitiativeFlag=0;
                current_round++;
                break;
        }
    }
    return root;
}

bool CanGoHome(treeNode *root)
{
    queue<treeNode*> redq;
    queue<treeNode*> blackq;
    treeNode *red = root->left;
    treeNode *black = root->right;
    redq.push(red);
    blackq.push(black);

    treeNode *now_red=nullptr;
    treeNode *now_black=nullptr;
    bool gohome_flag=false;
    while(!redq.empty() || !blackq.empty())
    {
        now_red=redq.front();
        now_black=blackq.front();
        redq.pop();
        blackq.pop();
        
        if(now_red->data == now_black->data)
        {   
            //push red from left to right
            if(now_red->left != nullptr)
            {
                redq.push(now_red->left);
            }
            if(now_red->right != nullptr)
            {
                redq.push(now_red->right);
            }
            
            //push black from right to left
            if(now_black->right != nullptr)
            {
                blackq.push(now_black->right);
            }
            if(now_black->left != nullptr)
            {
                blackq.push(now_black->left);
            }
        }
        else 
        {   
            gohome_flag=true;
            break;
        }
    }

    return gohome_flag;
}

// DO NOT modify main function
int main()
{
    treeNode *root = input();
    if (CanGoHome(root))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}
