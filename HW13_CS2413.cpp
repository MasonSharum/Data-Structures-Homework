//
// ========================================
// HW13: Implement a Binary Search Tree 
//       which can be converted to AVL Tree 
// ========================================
// 
// In this assignment, we will implement 
// an AVL tree which can also do standard 
// Binary Search Tree adding and removal.  
// 
// The Node class and AVL class are both 
// partly defined for you. 
// 
// ***************************************
// You can add new variables and functions 
// in both classes. However, you should 
// implement the following given functions 
// because they will be called in the main 
// function to test part of your implementation. 
// (Check "main" function for more details.)
// 1. PreTraverse()
// 2. GetRoot()
// 3. Add()
// 4. Remove()
// 5. Add_AVL()
// 6. Remove_AVL()
// 7. Height()
// Other given functions are only recommended. 
// ***************************************
// 

#include <iostream>
using namespace std;

class Node {
private:
	int key;
	Node* left; 
	Node* right;
	Node* parent;
public:
	void Set_key(int x);
	int Get_key();
	void Set_left(Node *p);
	void Set_right(Node* p);
	void Set_parent(Node* p);
	Node* Get_left();
	Node* Get_right();
	Node* Get_parent();
	Node();
};

Node::Node()
{
	key = 0;
	left = NULL;
	right = NULL;
	parent = NULL;
}

void Node::Set_key(int x)
{
	key = x;
}

int Node::Get_key()
{
	return key;
}

void Node::Set_left(Node* p)
{
	left = p;
}

void Node::Set_right(Node* p)
{
	right = p;
}

void Node::Set_parent(Node* p)
{
	parent = p;
}

Node* Node::Get_left()
{
	return left;
}

Node* Node::Get_right()
{
	return right;
}

Node* Node::Get_parent()
{
	return parent;
}

class AVL {
private:
	
	// This is root of the AVL
	Node* root;

public:

	// This function implements pre-order 
	// traverse, starting from the root, 
	// and prints the traverse sequence 
	// (with no space between nodes). 
	// You can use the function you implemented 
	// in HW10 (by slightly modifying it). 
	// This function is only used to test 
	// if your updated AVL/BST is correct. 
	void PreTraverse(Node* p);

	// This function returns the root node. 
	// Normally we don't need it. Here we 
	// just need it to evaluate your Height function.
	// See main function test case 5 for details.
	Node* GetRoot();

	// This function performs search 
	// on the current AVL with "key".
	// It returns address of a matching 
	// node, or returns NULL if no 
	// matching node is found. 
	Node* Search(int key);

	// This function adds a new node at 
	// "p" to AVL without considering 
	// any violation of AVL property. 
	// (So just standard BST adding.)
	// It can return a proper address.
	Node* Add(Node* p);

	// This function removes a node with 
	// "key" from AVL without considering 
	// any violation of AVL property. 
	// (So just standard BST removal.) 
	// For simplicty, to fill holes, let 
	// us only use the recursive algorithm 
	// that looks for the max/min node in 
	// the left/right subtress of the hole. 
	// It can return a proper address.
	Node* Remove(int key);

	// This function adds a new node 
	// stored at "p" to AVL and performs 
	// necessary rotations to restore 
	// the AVL property.
	void Add_AVL(Node* p);

	// This function removes a node 
	// with "key" from AVL and performs 
	// necessary rotations to restore 
	// the AVL property.
	void Remove_AVL(int key);

	// This function returns height 
	// of a subtree rooted at "p". 
	int Height(Node* p);

	// This function performs clock-wise
	// rotation at node "p". It only does
	// rotation and does not consider 
	// the type of violation scenario.
	// It can return a proper address.
	Node* Rotate_cw(Node* A);

	// This function performs counter 
	// clock-wise rotation at node "p". 
	// It only does rotation and does 
	// not consider the type of violation 
	// scenario. It can return a proper address.
	Node* Rotate_cc(Node* A);

	// This function checks if there 
	// is a violation at a node p, and 
	// return the violation scenario. 
	// It returns a string of 
	// - "NO" if no violation 
	// - "LL" if it is left-left violation 
	// - "RR" if it is right-right violation
	// - "LR" if it is left-right violation
	// - "RL" if it is right-left violation
	string CheckViolation(Node* p);

	// This function intiailizes root = NULL
	AVL();
};

AVL::AVL() {
    root = NULL;
}

// Preorder traversal to print the tree nodes
void AVL::PreTraverse(Node* p) {
    if (p == NULL)
        return;
    cout << p->Get_key();

    PreTraverse(p->Get_left());
    PreTraverse(p->Get_right());
}

Node* AVL::GetRoot() {
    return root;
}

// Search for a node with a given key
Node* AVL::Search(int key) {
    Node* current = root;
    while (current != NULL) {
        if (current->Get_key() == key)
            return current;
        else if (key > current->Get_key())
            current = current->Get_right();
        else if (key < current->Get_key())
            current = current->Get_left();
    }
    return NULL;
}

// Add a node to the tree without AVL property
Node* AVL::Add(Node* p) {
    if (root == NULL) {
        root = p;  // If the tree is empty, make the new node the root
        return root;  // Return the root node
    }
    int key = p->Get_key();
    Node* previous = root;
    Node* current = root;

    while (current != NULL) {
        previous = current;
        if (key > current->Get_key())
            current = current->Get_right();  // Move to the right subtree
        else if (key < current->Get_key())
            current = current->Get_left();  // Move to the left subtree
    }

    if (key < previous->Get_key()) {
        p->Set_parent(previous);
        previous->Set_left(p);  // Make the new node the left child of its parent
    }
    else {
        p->Set_parent(previous);
        previous->Set_right(p);  // Make the new node the right child of its parent
    }
    return p;  // Return a pointer to the added node
}

// Remove a node from the tree without AVL property
Node* AVL::Remove(int key) {
    Node* removed = Search(key);  // Find the node to be removed by its key

    if (removed == NULL)
        return NULL;  // If the node with the key is not found, return NULL

    Node* parent = removed->Get_parent();  // Get the parent of the removed node

    if (removed->Get_left() == NULL) {  // Case 1: Node has no left child
        if (removed->Get_right() != NULL) {
            if (parent) {
                if (parent->Get_left() == removed)
                    parent->Set_left(removed->Get_right());
                else
                    parent->Set_right(removed->Get_right());
            }
            else {
                root = removed->Get_right();
                root->Set_parent(NULL);
            }
        }
        else {
            if (parent) {
                if (parent->Get_left() == removed)
                    parent->Set_left(NULL);
                else
                    parent->Set_right(NULL);
            }
            else
                root = NULL;
        }
        delete removed;  // Delete the removed node
    }
    else if (removed->Get_right() == NULL) {  // Case 2: Node has no right child
        if (parent) {
            if (parent->Get_left() == removed)
                parent->Set_left(removed->Get_left());
            else
                parent->Set_right(removed->Get_left());
            removed->Get_left()->Set_parent(parent);
        }
        else {
            root = removed->Get_left();
            root->Set_parent(NULL);
        }
        delete removed;  // Delete the removed node
    }
    else {  // Case 3: Node has both left and right children
        Node* next = removed->Get_right();
        while (next->Get_left() != NULL)
            next = next->Get_left();
        removed->Set_key(next->Get_key());  // Replace the key of the removed node with the key of the next node
        Remove(next->Get_key());  // Recursively remove the next node, which has now replaced the removed node
    }
    return removed;  // Return a pointer to the removed node
}


// Add a node to the tree with AVL property and perform necessary rotations to restore AVL property
void AVL::Add_AVL(Node* p) {
    Node* temp = Add(p);
    while (temp != NULL) {
        string violation = CheckViolation(temp);
        if (violation == "NO") {
            temp = temp->Get_parent();
        }
        else if (violation == "RR") {
            temp = Rotate_cc(temp);
            temp = temp->Get_parent(); // Update temp to its parent
        }
        else if (violation == "LR") {
            temp = Rotate_cc(temp->Get_left());
            temp = Rotate_cw(temp->Get_parent());
        }
        else if (violation == "RL") {
            temp = Rotate_cw(temp->Get_right());
            temp = Rotate_cc(temp->Get_parent());
        }
        else if (violation == "LL") {
            temp = Rotate_cw(temp);
            temp = temp->Get_parent(); // Update temp to its parent
        }
    }
}

// Remove a node from the tree with AVL property and perform necessary rotations to restore AVL property
void AVL::Remove_AVL(int key) {
    // Step 1: Remove the node with the given key and get a pointer to the removed node
    Node* removed = Remove(key);

    if (removed == NULL)
        return; // Node with the key does not exist

    // Step 2: Traverse back up the tree and check for AVL violations
    Node* parent = removed->Get_parent();

    while (parent != NULL) {
        // Step 3: Check for the type of violation at the parent node
        string violation = CheckViolation(parent);

        if (violation == "NO") {
            parent = parent->Get_parent(); // No violation, move up to the parent
        }
        else if (violation == "RR") {
            // Right-Right violation, perform a counter-clockwise rotation
            if (key > parent->Get_key()) {
                parent = Rotate_cc(parent);
            }
            else {
                // Right-Left violation, perform a clockwise rotation on the right child
                parent->Set_right(Rotate_cc(parent->Get_right()));
                parent = Rotate_cw(parent);
            }
        }
        else if (violation == "LL") {
            // Left-Left violation, perform a clockwise rotation
            if (key < parent->Get_key()) {
                parent = Rotate_cw(parent);
            }
            else {
                // Left-Right violation, perform a counter-clockwise rotation on the left child
                parent->Set_left(Rotate_cw(parent->Get_left()));
                parent = Rotate_cc(parent);
            }
        }
        else if (violation == "RL") {
            // Right-Left violation, perform a counter-clockwise rotation on the right child
            parent->Set_right(Rotate_cw(parent->Get_right()));
            parent = Rotate_cc(parent);
        }
        else if (violation == "LR") {
            // Left-Right violation, perform a clockwise rotation on the left child
            parent->Set_left(Rotate_cc(parent->Get_left()));
            parent = Rotate_cw(parent);
        }
    }
}







// Calculate the height of a subtree rooted at node p
int AVL::Height(Node* p) {
    if (p == nullptr) {
        return -1;
    }
    else {
        int left = Height(p->Get_left());
        int right = Height(p->Get_right());
        return max(left, right) + 1;
    }
}

// Perform a clockwise rotation at node A
Node* AVL::Rotate_cw(Node* A) {
    // Step 1: Get nodes A, B, P, and right subtree of B
    Node* B = A->Get_left();
    Node* P = A->Get_parent();
    Node* B_right = B->Get_right();

    // Step 2: Perform the rotation
    B->Set_right(A);
    A->Set_left(B_right);
    B->Set_parent(P);
    A->Set_parent(B);

    // Update parent's child pointer
    if (P != nullptr) {
        if (P->Get_left() == A) {
            P->Set_left(B);
        }
        else {
            P->Set_right(B);
        }
    }
    else {
        root = B; // B becomes the new root if A was the root
    }

    return B; // Return the new root of the rotated subtree
}

// Perform a counterclockwise rotation at node A
Node* AVL::Rotate_cc(Node* A) {
    // Step 1: Get nodes A, B, P, and left subtree of B
    Node* B = A->Get_right();
    Node* P = A->Get_parent();
    Node* B_left = B->Get_left();

    // Step 2: Perform the rotation
    B->Set_left(A);
    A->Set_right(B_left);
    B->Set_parent(P);
    A->Set_parent(B);

    // Update parent's child pointer
    if (P != nullptr) {
        if (P->Get_left() == A) {
            P->Set_left(B);
        }
        else {
            P->Set_right(B);
        }
    }
    else {
        root = B; // B becomes the new root if A was the root
    }

    return B; // Return the new root of the rotated subtree
}

// Check for AVL violation at node p and return the violation scenario
string AVL::CheckViolation(Node* p) {
    if (Height(p->Get_left()) - Height(p->Get_right()) > 1) {
        Node* left = p->Get_left();
        if (Height(left->Get_left()) > Height(left->Get_right()))
            return "LL";
        else
            return "LR";
    }
    else if (Height(p->Get_right()) - Height(p->Get_left()) > 1) {
        Node* right = p->Get_right();
        if (Height(right->Get_left()) > Height(right->Get_right()))
            return "RL";
        else
            return "RR";
    }
    else
        return "NO";
}


// --------------
// Main Function 
// --------------
int main()
{
	// mode_test: indicate which function to test 
	// model_avl: if 1, we do adding with AVL property
	//            if 0, we do adding without AVL property 
	//            (so just standard bst adding)
	// key_temp:  keys of nodes to add to AVL initially
	// key_search:key of node for search/remove
	int mode_test, mode_avl, key_temp, key_search;
	
	Node* temp;

	// This is our AVL tree object.
	AVL tree;

	cin >> mode_test >> mode_avl >> key_search;

	while (cin >> key_temp) {

		temp = new Node;
		temp->Set_key(key_temp);

		if (mode_avl == 0)
		{
			tree.Add(temp);
		}
		else if (mode_avl == 1) {
			tree.Add_AVL(temp);
		}
	}

	// Mode 0: test "Add" function.
	if (mode_test == 0) {
		tree.PreTraverse(tree.GetRoot());
	}
	// Mode 1: test "Add_AVL" function
	else if (mode_test == 1) {
		tree.PreTraverse(tree.GetRoot());
	}
	// Mode 2: test "Search" function 
	else if (mode_test == 2) {
		temp = tree.Search(key_search);
		if (temp == NULL) {
			cout << -1;
		}
		else {
			cout << temp->Get_key();
		}		
	}
	// Mode 3: test "Remove" function 
	else if (mode_test == 3) {
		tree.Remove(key_search);
		tree.PreTraverse(tree.GetRoot());
	}
	// Mode 4: test "Remove_AVL" function 
	else if (mode_test == 4) {
		tree.Remove_AVL(key_search);
		tree.PreTraverse(tree.GetRoot());
	}
	// Mode 5: test "Height" function 
	else if (mode_test == 5) {
		cout << tree.Height(tree.GetRoot());
	}


	return 0;
}

