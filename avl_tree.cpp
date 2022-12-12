#include<bits/stdc++.h>
using namespace std;
class NODE{
public:
    int info;
    NODE * rlink;
    NODE * llink;
};
NODE* minValue(NODE* root)
{
    NODE* cur = root;
    while(cur->llink!=NULL)
    {
        cur = cur->llink;
    }
    return cur;
}
int height(NODE* root)
{
    if(root == NULL)
    {
        return -1;
    }
    else{
      int lh = height(root->llink);//-1
      int rh = height(root->rlink);//
      if(lh > rh)
      {
          return lh+1;
      }
      else
        return rh+1;
    }
}
int getbalancefactor(NODE* root)
{
    if(root == NULL)
    {
        return -1;
    }
    else{
        return(height(root->llink)-height(root->rlink));
    }
}

NODE* right_rotate(NODE* root)
{
    NODE* X = root->llink;
    NODE* Y = X->rlink;

    X -> rlink = root;
    root->llink = Y;

    return X;
}
NODE* left_rotate(NODE* root)
{
    NODE * X = root->rlink;
    NODE * Y = X ->llink;
    X ->llink = root;
    root->rlink = Y;
    return X;
}
NODE * insert(NODE * r, NODE * new_node) {
    if (r == NULL) {
      r = new_node;
      //cout << "Value inserted successfully" << endl;
      return r;
    }

    if (new_node -> info < r -> info) {
      r -> llink = insert(r -> llink, new_node);
    } else if (new_node -> info > r -> info) {
      r -> rlink = insert(r -> rlink, new_node);
    } else {
      cout << "No duplicate values allowed!" << endl;
      return r;
    }

    int bf = getbalancefactor(r);

    if (bf > 1 && new_node -> info < r -> llink -> info)
      return right_rotate(r);


    if (bf < -1 && new_node -> info > r -> rlink -> info)
      return left_rotate(r);


    if (bf > 1 && new_node -> info > r -> llink -> info) {
      r -> llink = left_rotate(r -> llink);
      return right_rotate(r);
    }


    if (bf < -1 && new_node -> info < r -> rlink-> info) {
      r -> rlink = right_rotate(r -> rlink);
      return left_rotate(r);
    }


    return r;

  }
 NODE* delete_node(NODE * r, int v) {

    if (r == NULL) {

      return NULL;
    }

    else if (v < r -> info) {
      r -> llink = delete_node(r -> llink, v);
    }

    else if (v > r -> info) {
      r -> rlink = delete_node(r -> rlink, v);
    }

    else {

      if (r -> llink == NULL) {
       NODE* temp = r -> rlink;
        delete r;
        return temp;
      } else if (r -> rlink == NULL) {
        NODE * temp = r -> llink;
        delete r;
        return temp;
      } else {

        NODE * temp = minValue(r -> rlink);

        r -> info = temp -> info;

        r -> rlink = delete_node(r -> rlink, temp -> info);

      }
    }

    int bf = getbalancefactor(r);

    if (bf == 2 && getbalancefactor(r -> llink) >= 0)
      return right_rotate(r);

    else if (bf == 2 && getbalancefactor(r -> llink) == -1) {
      r -> llink = left_rotate(r -> llink);
      return right_rotate(r);
    }
    else if (bf == -2 && getbalancefactor(r -> rlink) <= -0)
      return left_rotate(r);

    else if (bf == -2 && getbalancefactor(r -> rlink) == 1) {
      r -> rlink = right_rotate(r -> rlink);
      return left_rotate(r);
    }

    return r;

  }
  void display(NODE* root,int i) {
    if(root == NULL)
        return;
    display(root->llink, i-1);
    cout << root->info << " ";
    display(root->rlink, i-1);
  }
void search_node(NODE* root ,int item)
{
    NODE * cur;
    if(root == NULL)
    {
        cout<<"THE AVL TREE IS EMPTY!!"<<endl;
        return;
    }
    cur = root;
    while(cur!=NULL)
    {
        if(item == cur->info) break;
        if(item< cur->info){
            cur = cur->llink;
        }
        else{
            cur = cur->rlink;
        }
    }
    if(cur == NULL)
    {
        cout<<"ELEMENT NOT FOUND !!"<<endl;
        return;
    }
    cout<<"ELEMENT FOUND "<<cur->info<<endl;
}
int main()
{
    NODE* root = NULL;
    int choice,item;
    for(;;)
    {
        cout<<"Operations on AVL tree"<<endl;
        cout<<"1.Insert\n 2.Search\n 3.Delete\n 4.Display\n "<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1: {
            cout<<"Enter the value to be inserted: ";
            cin>>item;
            NODE * new_node = new NODE();
            new_node->info = item;
            root = insert(root,new_node);
            cout<<"New node has been inserted"<<endl;
            break;
            }
            case 2:{
            cout<<"Enter the element to be searched:\n";
            cin >> item;
            search_node(root,item);
            break;
            }
            case 3:{
                 cout<<"Enter the item to be deleted:\n";
            cin>>item;
            root = delete_node(root,item);
            cout << "Item " << item << " has been deleted" << endl;
            break;
            }
            case 4:{
                int i =0;
                if(!root)
                    cout << "The tree is empty\n";
                display(root,i);

            }break;

            default: exit(0);
        }
    }
    return 0;
}