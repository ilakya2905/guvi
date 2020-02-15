#include<stdio.h>
#include<stdlib.h>
#define MAX 30
#define full 7
int store[full], i=0;
struct node
{
    int data; //node will store an integer
    struct node *right_child; // right child
    struct node *left_child; // left child
};
struct node* new_node(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}
struct node* insert(struct node *root, int x)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,x);
    return root;
}
typedef struct edge
{
	int u,v,w;
}edge;
 
typedef struct edgelist
{
	edge data[MAX];
	int n;
}edgelist;
 
edgelist elist;
 
int G[MAX][MAX],n,e;
edgelist spanlist;
void adj(int e1,int e2,int c){
    G[e1][e2]=c;
    G[e2][e1]=c;
}
void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        store[i]=root->data;
        i++;
        //printf(" %d ", root->data); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}
 
void minimumCost();
int find(int belongs[],int vertexno);
void union1(int belongs[],int c1,int c2);
void sort();
void print();
int main(){
    struct node *root;
    int i,j,a[30][3],e1,e2,c,s,search,fr, fruits[100];
    printf("\n Number of fruits:");
    scanf("%d", &fr);
    if(fr<0){
            printf("Invalid Input");
            return 0;
    }
    for(i=0;i<fr;i++){
    
        scanf("%d",&fruits[i]);
        if(fruits[i]<0)
            printf("Invalid Input");
    }
    

    printf("\n Number of cities:");
    scanf("%d",&n);
    if(fr<0 || n<0 || fr>100 || n>100){
        printf("\n Invalid input");
        return 0;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            G[i][j]=0;
        }
    }
    printf("\n Number of routes:");
    scanf("%d",&e);
    if(e<0){
            printf("Invalid Input");
            return 0;
    }
    printf("\n Travelling Cost from source to destination city:\n");
    for(i=0;i<e;i++){
        scanf("%d",&a[i][0]);
        scanf("%d",&a[i][1]);
        scanf("%d",&a[i][2]);
        if(a[i][0]<0 || a[i][1]<0 || a[i][2]<0){
            printf("Invalid Input");
            return 0;
        }
        e1=a[i][0];
        e2=a[i][1];
        c=a[i][2];
        adj(e1,e2,c);
        e1=0;
        e2=0;
        c=0;
    }
    printf("\n Enter the city position:");
    scanf("%d",&search);
    if(search<0 || search>n){
            printf("Invalid Input, Given city exceeds the number of cities in Coding Land");
            return 0;
    }
    s= search;
    minimumCost();
    print();
    
    root = new_node(fruits[0]);
    for(i=1;i<fr;i++){
        insert(root,fruits[i]);
    }
    inorder(root);
    printf("\n");
    
    if(search>fr){
        search=search%fr;
    }
    printf("Cost of the fruit sold in %dth city:%d ", s, store[search-1]);
}
void minimumCost()
{
	int belongs[MAX],i,j,cno1,cno2;
	elist.n=0;
 
	for(i=1;i<n;i++)
		for(j=0;j<i;j++)
		{
			if(G[i][j]!=0)
			{
				elist.data[elist.n].u=i;
				elist.data[elist.n].v=j;
				elist.data[elist.n].w=G[i][j];
				elist.n++;
			}
		}
 
	sort();
	
	for(i=0;i<n;i++)
		belongs[i]=i;
	
	spanlist.n=0;
	
	for(i=0;i<elist.n;i++)
	{
		cno1=find(belongs,elist.data[i].u);
		cno2=find(belongs,elist.data[i].v);
		
		if(cno1!=cno2)
		{
			spanlist.data[spanlist.n]=elist.data[i];
			spanlist.n=spanlist.n+1;
			union1(belongs,cno1,cno2);
		}
	}
}
 
int find(int belongs[],int vertexno)
{
	return(belongs[vertexno]);
}
 
void union1(int belongs[],int c1,int c2)
{
	int i;
	
	for(i=0;i<n;i++)
		if(belongs[i]==c2)
			belongs[i]=c1;
}
 
void sort()
{
	int i,j;
	edge temp;
	
	for(i=1;i<elist.n;i++)
		for(j=0;j<elist.n-1;j++)
			if(elist.data[j].w>elist.data[j+1].w)
			{
				temp=elist.data[j];
				elist.data[j]=elist.data[j+1];
				elist.data[j+1]=temp;
			}
}
 
void print()
{
	int i,cost=0;
	printf("\n Path \n");
	for(i=0;i<spanlist.n;i++)
	{
		printf("\n%d<--->\t%d",spanlist.data[i].u,spanlist.data[i].v);
		cost=cost+spanlist.data[i].w;
	}
 
	printf("\n\nEfficient Travelling Cost =%d",cost);
}
