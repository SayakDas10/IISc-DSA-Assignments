#include <iostream>
using namespace std;

struct Node {
    int key;
    bool colour;  // true : Black, false : Red
    Node *left, *right, *parent;

    // Node Constructor
    Node(int key) {
        this->key = key;
        colour = false;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class RedBlackTree {
   private:
    Node *root;                             // root of the tree
    Node *NIL;                              // sentinel node T.nil
    void __initNIL();                       // initializing the sentinal
    void __leftRotate(Node *x);             // left rotate (insert sub-routine)
    void __rightRotate(Node *y);            // right rotate (insert sub-routine)
    void __RBInsertFixUp(Node *z);          // insert fix (insert sub-routine)
    void __RBTransplant(Node *u, Node *v);  // transplant (delete sub-routine)
    void __RBDeleteFixUp(Node *x);          // delete fix  (delete subroutine)
    void __RBDelete(Node *root, int key);   // delete
    Node *__TreeMinimum(Node *root);        // minimum value of the tree
    void preOrder(Node *root);              // pre-order traversal
    void inOrder(Node *root);               // in-order traversal

   public:
    RedBlackTree();            // tree constructor
    void insert(int key);      // insert
    void deleteNode(int key);  // delete
    void printTree();          // print tree
};

// T.nil initializer

void RedBlackTree ::__initNIL() {
    NIL = new Node(0);
    NIL->colour = true;
    NIL->left = nullptr;
    NIL->right = nullptr;
}

void RedBlackTree ::__leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)  // DO NOT CHANGE  nullptr TO NIL!!
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlackTree ::__rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)  // DO NOT CHANGE  nullptr TO NIL!!
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void RedBlackTree ::__RBInsertFixUp(Node *z) {
    // uncle == y (trying to follow clrs notation)
    Node *y;
    while (z->parent->colour == false) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->colour == false) {
                // Case 1: y is red
                z->parent->colour = true;
                y->colour = true;
                z->parent->parent->colour = false;
                z = z->parent->parent;
            } else {
                // Case 2: y is black
                if (z == z->parent->right) {
                    z = z->parent;
                    __leftRotate(z);
                }
                // Case 3: colour and rotate
                z->parent->colour = true;
                z->parent->parent->colour = false;
                __rightRotate(z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->colour == false) {
                // Case 1: y is red
                z->parent->colour = true;
                y->colour = true;
                z->parent->parent->colour = false;
                z = z->parent->parent;
            } else {
                // Case 2: y is black
                if (z == z->parent->left) {
                    z = z->parent;
                    __rightRotate(z);
                }
                // Case 3: colour and rotate
                z->parent->colour = true;
                z->parent->parent->colour = false;
                __leftRotate(z->parent->parent);
            }
        }
        if (z == root) break;  //!! DO NOT REMOVE!!
    }
    root->colour = true;
}

void RedBlackTree ::__RBTransplant(Node *u, Node *v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void RedBlackTree ::__RBDeleteFixUp(Node *x) {
    while (x != root && x->colour == true) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->colour == false) {
                // Case 1: sibling is red
                w->colour = true;
                x->parent->colour = false;
                __leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->colour == true && w->right->colour == true) {
                // Case 2: both of siblings child are black
                w->colour = false;
                x = x->parent;
            } else {
                if (w->right->colour == true) {
                    // Case 3: siblings left child is red and right child is black
                    w->left->colour = true;
                    w->colour = false;
                    __rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4: siblings right child is red
                w->colour = x->parent->colour;
                x->parent->colour = true;
                w->right->colour = true;
                __leftRotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->colour == false) {
                // Case 1: sibling is red
                w->colour = true;
                x->parent->colour = false;
                __rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->colour == true && w->left->colour == true) {
                // Case 2: sibling has two black children
                w->colour = false;
                x = x->parent;
            } else {
                if (w->left->colour == true) {
                    // Case 3: siblings right child is red and left child is black
                    w->right->colour = true;
                    w->colour = false;
                    __leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4: siblings left child is red
                w->colour = x->parent->colour;
                x->parent->colour = true;
                w->left->colour = true;
                __rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->colour = true;
}

void RedBlackTree ::__RBDelete(Node *root, int key) {
    Node *z = NIL;
    Node *x, *y;
    // creating a node inside the function (to make debugging easier)
    // search for the node to be deleted
    while (root != NIL) {
        if (root->key == key)
            z = root;

        if (root->key <= key)
            root = root->right;
        else
            root = root->left;
    }

    if (z == NIL) {
        cout << "Node doesn't exist in tree\n";
        return;
    }

    // clrs algorithm
    y = z;
    bool yOriginalcolour = y->colour;
    if (z->left == NIL) {
        x = z->right;
        __RBTransplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        __RBTransplant(z, z->left);
    } else {
        y = __TreeMinimum(z->right);
        yOriginalcolour = y->colour;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            __RBTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        __RBTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->colour = z->colour;
    }
    delete z;
    if (yOriginalcolour == true)
        __RBDeleteFixUp(x);
}

Node *RedBlackTree ::__TreeMinimum(Node *root) {
    // left most child is minimum in any tree satisfying binary search tree property
    while (root->left != NIL)
        root = root->left;
    return root;
}

RedBlackTree ::RedBlackTree() {
    __initNIL();
    root = NIL;
}

void RedBlackTree::insert(int key) {
    // creating a node inside the function (to make debugging easier)
    Node *z = new Node(key);
    z->parent = nullptr;
    z->key = key;

    // last 3 lines of clrs are done here because of continutiy. If we want, we can move them to the end.
    z->left = NIL;
    z->right = NIL;
    z->colour = false;

    // clrs algorithm starts here

    Node *y = nullptr;
    Node *x = this->root;

    while (x != NIL) {
        y = x;
        x = (z->key < x->key) ? x->left : x->right;
    }

    z->parent = y;

    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    //!! DO NOT REMOVE!! deals with the case when z is root
    if (z->parent == nullptr) {
        z->colour = true;
        return;
    }

    //!! DO NOT REMOVE!! deals with the case when z's parent is root
    if (z->parent->parent == nullptr) {
        return;
    }

    __RBInsertFixUp(z);
}

void RedBlackTree ::deleteNode(int key) {
    // need this as we need to access root. Which must stay private.
    __RBDelete(this->root, key);
}

void RedBlackTree ::printTree() {
    // With both preorder and inorder we can determine a binary tree uniquely. That is why both is implemented.
    cout << "PreOrder: \n";
    preOrder(this->root);
    cout << "\nInOrder: \n";
    inOrder(this->root);
}

void RedBlackTree ::preOrder(Node *root) {
    if (root != NIL) {
        cout << root->key << "(";
        if (root->colour == true)
            cout << "B) ";
        else
            cout << "R) ";

        preOrder(root->left);
        preOrder(root->right);
    }
}

void RedBlackTree ::inOrder(Node *root) {
    if (root != NIL) {
        inOrder(root->left);

        cout << root->key << "(";
        if (root->colour == true)
            cout << "B) ";
        else
            cout << "R) ";

        inOrder(root->right);
    }
}

int main() {
    RedBlackTree tree;

    // Insertion Example : http://www.rnlkwc.ac.in/pdf/study-material/comsc/Design.pdf

    for (int i = 1; i < 10; i++) {
        tree.insert(i);
    }
    tree.insert(5);
    tree.insert(4);

    // tree.insert(8);
    // tree.insert(18);
    // tree.insert(5);
    // tree.insert(15);
    // tree.insert(17);
    // tree.insert(25);
    // tree.insert(40);
    // tree.insert(80);

    // Deletion Example : https://www.programiz.com/dsa/deletion-from-a-red-black-tree
    // tree.insert(55);
    // tree.insert(40);
    // tree.insert(65);
    // tree.insert(60);
    // tree.insert(75);
    // tree.insert(57);

    // tree.printTree();

    // tree.deleteNode(40);

    tree.printTree();

    return 0;
}