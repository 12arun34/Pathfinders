#include <iostream>
using namespace std;

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

Node *left_rotation(Node *current)
{

    if (current->parent->parent != NULL)
    {

        if (current->parent->parent->left == current->parent)
        {
            current->parent->parent->left = current;
        }
        else
        {
            current->parent->parent->right = current;
        }
    }

    Node *temp = new Node();
    temp = current->parent;
    current->parent->right = current->left;
    if (current->parent->parent != NULL)
    {

        current->parent = current->parent->parent;
    }
    else
    {
        current->parent = NULL;
    }
    current->left = temp;

    return current;
}

Node *right_rotation(Node *current)
{

    if (current->parent->parent != NULL)
    {

        if (current->parent->parent->left == current->parent)
        {
            current->parent->parent->left = current;
        }
        else
        {
            current->parent->parent->right = current;
        }
    }

    Node *temp = new Node();
    temp = current->parent;
    current->parent->left = current->right;
    if (current->parent->parent != NULL)
    {

        current->parent = current->parent->parent;
    }
    else
    {
        current->parent = NULL;
    }
    current->right = temp;

    return current;
}

Node *search_insert(Node *root, int target_key)
{

    if (root->key == target_key)
    {
        return root;
    }
    if (root->key > target_key)
    {
        if (root->left == NULL)
        {
            Node *temp = new Node();
            temp->key = target_key;
            temp->parent = root;
            root->left = temp;
            return temp;
        }
        return search_insert(root->left, target_key);
    }
    else if (root->right == NULL)
    {
        Node *temp = new Node();
        temp->key = target_key;
        temp->parent = root;
        root->right = temp;
        return temp;
    }
    return search_insert(root->right, target_key);
}

Node *splay(Node *current)
{
    // cout<<"help"<<endl;
    while (current->parent != NULL)
    {
        if (current->parent->parent != NULL)
        {
            if (current->parent->left == current)
            {
                if (current->parent->parent->left == current->parent)
                {
                    // cout<<"help"  <<endl;     //zig-zig
                    current->parent = right_rotation(current->parent);
                    current = right_rotation(current);
                }
                else
                { // zig-zag
                    current = right_rotation(current);
                    current = left_rotation(current);
                }
            }
            else
            {
                if (current->parent->parent->right == current->parent)
                {                                                             // zag-zag
                    current->parent = left_rotation(current->parent);
                    current = left_rotation(current);
                }
                else
                {                                                             // zag-zig
                    current = left_rotation(current);
                    current = right_rotation(current);
                }
            }
        }
        else
        {

            if (current->parent->left == current)
            {                                                                  // zig
               
                current = right_rotation(current);
            }
            else
            {                                                                   // zag
                
                current = left_rotation(current);
            }
        }
    }
    
    return current;
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main()
{

    Node *Root = new Node();
    Root->key = 8;

    Node *f = new Node();
    f->key = 6;

    Node *i = new Node();
    i->key = 9;

    Node *g = new Node();
    g->key = 7;

    Node *b = new Node();
    b->key = 2;

    Node *e = new Node();
    e->key = 5;

    Node *a = new Node();
    a->key = 1;

    Node *d = new Node();
    d->key = 4;

    Node *c = new Node();
    c->key = 3;

    Root->left = f;
    Root->right = i;

    f->left = b;
    f->right = g;
    f->parent = Root;

    g->parent = f;

    b->left = a;
    b->right = e;
    b->parent = f;

    i->parent = Root;
    a->parent = b;

    e->left = d;
    e->parent = b;

    d->left = c;
    d->parent = e;

    c->parent = d;

    cout << "preorder of current tree : ";
    preorder(Root);
    cout << endl;

    cout << "enter key to splay : ";
    int target_key;
    cin >> target_key;
    Node *target_node = new Node();
    target_node = search_insert(Root, target_key);

    Root = splay(target_node);

    cout << "preorder after splay : ";
    preorder(Root);
    cout << endl;

    cout << "inorder after splay : ";
    inorder(Root);
    cout << endl;

    return 0;
}