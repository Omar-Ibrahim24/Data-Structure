#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *data;
    struct Node* left;
    struct Node* right;
} Node;
Node* newNode(char*x)
{
    Node* n =malloc(sizeof(Node));
    n->data=malloc(50);
    strcpy(n->data,x);
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node*root,char*x)
{
    if(root==NULL)
    {
        root=newNode(x);
    }
    else if(strcasecmp(x,root->data)<0)
    {
        root->left=insert(root->left,x);
    }
    else if(strcasecmp(x,root->data)>0)
    {
        root->right= insert(root->right,x);
    }
    return root;
}

void printPreAfter(Node* root,char*x,char*x1,char*y,char*z)
{
    if(root)
    {
        printPreAfter(root->left,x,x1,y,z);
        strcpy(x1,y);
        strcpy(y,z);
        strcpy(z,root->data);
        if(strcasecmp(x,y)==0)
        {
            printf("%s %s %s\n",y,z,x1);
            return;
        }
        printPreAfter(root->right,x,x1,y,z);
    }
}
Node* search(Node* root,char*x)
{

    if(strcasecmp(x,root->data)==0)
    {
        return root;
    }
    else if(strcasecmp(x,root->data)<0)
    {
        if(root->left==NULL)
        {
            return root;
        }
        return search(root->left,x);
    }
    else if(strcasecmp(x,root->data)>0)
    {
        if(root->right==NULL)
        {
            return root;
        }
        return search(root->right,x);
    }
}
int countNodes(Node*root)
{
    if(root==NULL)
        return 0;
    else
        return 1+countNodes(root->left)+countNodes(root->right);
}
int max(int a,int b)
{
    return a>b?a:b;
}
int height(Node *root)
{
    if ( root == NULL)
        return -1;
    else
        return 1 + max(height(root->left),
                       height(root->right));
}
int main()
{
    char pre[30],main[30],after[30],sentence[200];
    Node*head=NULL,*tempNode=NULL;
    FILE *f=fopen("EN-US-Dictionary.txt","r");
    while (!feof(f))
    {
        char *temp=malloc(100);
        fscanf(f,"%s",temp);
        head=insert(head,temp);
    }
    fclose(f);

    printf("FILE LOADED SUCCESSFULLY\n**************************\nNumber of nodes : %d\n**************************\nHeight : %d\n**************************\n",countNodes(head),height(head));
        printf("Enter your sentence : ");
        gets(sentence);
        char* token=strtok(sentence," ");
        while(token)
        {
            tempNode=search(head,token);
            if(strcasecmp(token,tempNode->data)==0)
            {
                printf("%s - CORRECT\n",token);
            }
            else
            {
                printf("%s - INCORRECT, Suggestions : ",token);
                printPreAfter(head,tempNode->data,pre,main,after);
            }
            token=strtok(NULL," ");
        }
    return 0;
}
