#include<stdio.h>
struct node
{
	int data;
	struct node *left,*right;
	int ht;
};

struct node *insert(struct node *,int);
struct node *Delete(struct node *,int);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
int height( struct node *);
struct node *rotateright(struct node *);
struct node *rotateleft(struct node *);
struct node *RightRight(struct node *);
struct node *LeftLeft(struct node *);
struct node *LeftRight(struct node *);
struct node *RightLeft(struct node *);
int BF(struct node *);

int main()
{
	struct node *root=NULL;
	int x,n,i,op;
	do
	{
		printf("\n1.Create:");
		printf("\n2.Insert:");
		printf("\n3.Delete:");
		printf("\n4.Print:");
		printf("\n5.Quit:");
		printf("\n\nEnter Your Choice");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				printf("\nEnter no.of elements:");
				scanf("%d",&n);
				printf("\nEnter tree data:");
				root=NULL;
				for(i=0;i<n;i++)
				{
					scanf("%d",&x);
					root=insert(root,x);
				}
				break;
				case 2:
					printf("\nEnter a data:");
					scanf("%d",&x);
					root=insert(root,x);
					break;
					case 3:
						printf("\nEnter a data:");
						scanf("%d",&x);
						break;
						case 4:
							printf("\nPreorder sequence:\n");
							preorder(root);
							printf("\n\nInorder sequence:\n");
							inorder(root);
							printf("\n\nPostorder sequence:\n");
							postorder(root);
							printf("\n");
							break;
		}
	}
	while(op!=5);
	return 0;
}
struct node * insert(struct node *temp,int x)
{
	if(temp==NULL)
	{
		temp=(struct node*)malloc(sizeof(struct node));
		temp->data=x;
		temp->left=NULL;
		temp->right=NULL;
	}
	else
	if(x > temp->data)
	{
		temp->right=insert(temp->right,x);
		if(BF(temp)==-2)
		if(x>temp->right->data)
		temp=RightRight(temp);
		else
		temp=RightLeft(temp);
    }
	else
	if(x<temp->data)
	{
		temp->left=insert(temp->left,x);
		if(BF(temp)==2)
		if(x < temp->left->data)
		temp=LeftLeft(temp);
		else
		temp=LeftRight(temp);
	}
	temp->ht=height(temp);
	return(temp);
}

struct node * Delete(struct node *temp,int data)
{
	struct node *p;
	if(temp==NULL)
	{
		return NULL;
	}
	else
	if(data > temp->data)
	{
			temp->right=Delete(temp->right,data);
	        if(BF(temp)==2)
        	if(BF(temp->left)>=0)
        	temp=LeftLeft(temp);
	        else
	        temp=LeftRight(temp);	
	}
	else
	if(data<temp->data)
	{
			temp->left=Delete(temp->left,data);
	        if(BF(temp)==-2)
	        if(BF(temp->right)<=0)
	        temp=RightRight(temp);
	        else
	        temp=RightLeft(temp);
	}
	else
	{
		//data to be deleted is found
		if(temp->right!=NULL)
		{
			//delete its inorder succesor
			p=temp->right;
			while(p->left!=NULL)
			p=p->left;
			temp->data=p->data;
			temp->right=Delete(temp->right,temp->data);
			if(BF(temp)==2)
			if(BF(temp->left)>=0)
			temp=LeftLeft(temp);
			else
			temp=LeftRight(temp);
		}
		else
		return(temp->left);
	}
	temp->ht=height(temp);
	return(temp);
}

int height(struct node *temp)
{
	int lh,rh;
	if(temp==NULL)
	return(0);
	if(temp->left==NULL)
	lh=0;
	else
	lh=1+temp->left->ht;
	if(temp->right==NULL)
	rh=0;
	else
	rh=1+temp->right->ht;
	if(lh>rh)
	return(lh);
	return(rh);
}

struct node * rotateright(struct node *x)
{
	struct node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

struct node * rotateleft(struct node *x)
{
    struct node *y;
	y=x->right;
	x->right=y->left;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

struct node * RightRight(struct node *temp)
{
	temp=rotateleft(temp);
    return(temp);
}

struct node * LeftLeft(struct node *temp)
{
	temp=rotateright(temp);
    return(temp); 
}

struct node * LeftRight(struct node *temp)
{
	temp->left=rotateleft(temp->left);
    temp=rotateright(temp);
    return(temp);
}

struct node * RightLeft(struct node *temp)
{
	temp->right=rotateright(temp->right);
    temp=rotateleft(temp);
    return(temp);
}

int BF(struct node *temp)
{
	int lh,rh;
	if(temp==NULL)
	return(0);
	
	if(temp->left==NULL)
	lh=0;
	else
	lh=1+temp->left->ht;
	
	if(temp->right==NULL)
	rh=0;
	else
	lh=1+temp->right->ht;
	
	return(lh-rh);
}

void preorder(struct node *temp)
{
	if(temp!=NULL)
	{
		printf("%d(Bf=%d)",temp->data,BF(temp));
        preorder(temp->left);
        preorder(temp->right);
	}
}

void inorder(struct node *temp)
{
	if(temp!=NULL)
	{
		preorder(temp->left);
		printf("%d(Bf=%d)",temp->data,BF(temp));
        preorder(temp->right);
	}
}

void postorder(struct node *temp)
{
	if(temp!=NULL)
	{
		preorder(temp->left);
        preorder(temp->right);
		printf("%d(Bf=%d)",temp->data,BF(temp));
	}
}
