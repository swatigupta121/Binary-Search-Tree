#include<stdio.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node* search(struct node *root,int ele);
struct node* find_successor(struct node *root,struct node * found);
struct node* find_parent(struct node *root, struct node * ptr);
void inorder_traversal(struct node* root);
struct node* insert(struct node *root,int ele);
int main()
{
    int choice,ele;
    struct node *succ=NULL,*parent=NULL,*root=NULL,*found=NULL;
    do
    {
        printf("\nPRESS 1.INSERTION 2.DELETION 3.INORDER TRAVERSAL 4.SEARCH 5.FIND PARENT 6.EXIT: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("ENTER DATA FOR NODE: ");
                scanf("%d",&ele);
                root=insert(root,ele);
                //printf("%d",root->data);
                break;
            case 2:
                printf("ENTER THE NODE WHICH YOU WANT TO DELETE: ");
                scanf("%d",&ele);
                found=search(root,ele);
                parent=find_parent(root,found);
                if(found->left==NULL && found->right==NULL)
                {
                    if(parent->left == found)
                    {
                        parent->left=NULL;
                    }
                    else if(parent->right==found)
                    {
                        parent->right=NULL;
                    }
                    free(found);
                }
                else if(found->left==NULL && found->right!=NULL)
                {
                    if(parent->left==found)
                    {
                        parent->left=found->right;
                    }
                    else if(parent->right==found)
                    {
                        parent->right=found->right;
                    }
                    free(found);
                }
                else if(found->left!=NULL && found->right==NULL)
                {
                    if(parent->left==found)
                    {
                        parent->left=found->left;
                    }
                    else if(parent->right==found)
                    {
                        parent->right=found->left;
                    }
                    free(found);
                }
                else if(found->left!=NULL && found->right!=NULL)
                {
                    succ=find_successor(root,found);
                    printf("SUCCESSOR OF %d IS %d.",found->data,succ->data);
                    if(succ->right==NULL)
                    {
                        parent=find_parent(root,succ);
                        if(parent!=found)
                        {
                            found->data=succ->data;
                            parent->left=NULL;
                        }
                        else
                        {
                            found->data=succ->data;
                            found->right=NULL;
                        }
                    }
                    else if(succ->right!=NULL)
                    {
                        parent=find_parent(root,succ);
                        parent->left=succ->right;
                        found->data=succ->data;
                    }
                }
                //printf("%d",root->data);
                break;
            case 3:
                inorder_traversal(root) ;
                break;
            case 4:
                printf("ENTER ELEMENT YOU WANT TO SEARCH: ");
                scanf("%d",&ele);
                found=search(root,ele);
                if(found==NULL)
                {
                    printf("ELEMENT NOT FOUND.");
                }
                else
                {
                    printf("%d ELEMENT FOUND.",found->data);
                }
                break;
            case 5:
                printf("ENTER ELEMENT FOR WHICH YOU HAVE TO FIND PARENT: ");
                scanf("%d",&ele);
                found=search(root,ele);
                if(found==NULL)
                {
                    printf("ELEMENT NOT FOUND.");
                }
                else
                {
                    printf("%d ELEMENT FOUND.",found->data);
                }
                parent=find_parent(root,found);
                if(parent==NULL)
                {
                    printf("THERE IS NO SUCH PARENT PRESENT.");
                }
                else
                {
                    printf("PARENT FOR %d NODE IS %d.",ele,parent->data);
                }
                break;
            case 6:
                exit(0);
        }
    }while(1);
    return 0;
}
struct node* find_successor(struct node *root,struct node * found)
{
    struct node *successor;
    successor=found->right;
    while(successor->left!=NULL)
    {
        successor=successor->left;
    }
    return successor;
}
struct node* find_parent(struct node *root, struct node * ptr)
{
	if(root == NULL)
		return root;
	else
	{
		if(root->left == ptr || root->right == ptr)
		{
			return root;
		}
		else if(root->data > ptr->data)
		{
			root= find_parent(root->left, ptr);
		}
		else if(root->data < ptr->data)
		{
			root=find_parent(root->right, ptr);
		}
	}
	return root;
}
struct node* search(struct node *root,int ele)
{
    struct node *ptr=NULL;
    if(root==NULL)
    {
        return ptr;
    }
    else
    {
        if(root->data==ele)
        {
            ptr=root;
            return ptr;
        }
        else if(root->data > ele)
        {
            ptr=search(root->left,ele);
        }
        else if(root->data < ele)
        {
            ptr=search(root->right,ele);
        }
        return ptr;
    }
}
struct node* insert(struct node *root,int ele)
{
    if(root==NULL)
    {
        struct node *nn;
        nn=(struct node *)malloc(sizeof(struct node));
        nn->data=ele;
        nn->left=NULL;
        nn->right=NULL;
        return nn;
    }
    else if(root->data > ele)
    {
        root->left=insert(root->left,ele);
        return root;
    }
    else if(root->data<ele)
    {
        root->right=insert(root->right,ele);
        return root;
    }
}
void inorder_traversal(struct node* root)
{
  if(root==NULL)
  {
      return 0;
  }
  else
  {
      inorder_traversal(root->left);
      printf("%d ",root->data);
      inorder_traversal(root->right);
  }
}
