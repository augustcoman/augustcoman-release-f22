/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* r = t->right;
    t->right = r->left;
    r->left = t;
    t = r;
    correctHeight(r->left);
    correctHeight(r);
    
}

template <class K, class V>
void AVLTree<K, V>::correctHeight(Node* & subtree) {
    if(!subtree) {
        return;
    }
    subtree->height = 0;
    if(subtree->left) {
        subtree->height = subtree->left->height + 1;
    }
    if(subtree->right && subtree->right->height >= subtree->height) {
        subtree->height = subtree->right->height + 1;
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* l = t->left;
    t->left = l->right;
    l->right = t;
    t = l;
    correctHeight(l->right);
    correctHeight(l);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(!subtree || (!subtree->left && !subtree->right)) {
        return;
    }
    rebalance(subtree->left);
    rebalance(subtree->right);
    int balance = getBalance(subtree);
    if(balance > 1) {
        //left guaranteed to have children
        if(getBalance(subtree->left) < 0) {
            rotateLeftRight(subtree);
        } else {
            rotateRight(subtree);
        }
    } else if(balance < -1) {
        if(getBalance(subtree->right) > 0) {
            rotateRightLeft(subtree);
        } else {
            rotateLeft(subtree);
        }
    }
    return;
}

//Left minus Right
template <class K, class V>
int AVLTree<K, V>::getBalance(Node* & subtree) {
    if(!subtree) {
        return 0;
    }
    int l_h = (!subtree->left)?-1:subtree->left->height;
    int r_h = (!subtree->right)?-1:subtree->right->height;
    return l_h - r_h;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    
    if(!subtree) {
        subtree = new Node(key, value);
        subtree->height = 0;
        return;
    }
    if(key > subtree->key) {
        insert(subtree->right, key, value);
        if(subtree->right->height == subtree->height) {
            subtree->height++;
        }
    }
    if(key < subtree->key) {
        insert(subtree->left, key, value);
        if(subtree->left->height == subtree->height) {
            subtree->height++;
        }
    }
    
    //Node*& insertion_loc = find_loc(root, key);
    //if(!insertion_loc) {
    //    insertion_loc = new Node(key, value);
    //}
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
    //Node*& target = find_loc(root, key);
    //if(target) {
    //    remove(target, key);
    //}
    rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if(!subtree) {
        return;
    }
    if(key > subtree->key) {
        remove(subtree->right, key);
        subtree->height = 0;
        if(subtree->left) {
            subtree->height = subtree->left->height + 1;
        }
        if(subtree->right && subtree->right->height >= subtree->height) {
            subtree->height = subtree->right->height + 1;
        }
        return;
    }
    if(key < subtree->key) {
        remove(subtree->left, key);
        subtree->height = 0;
        if(subtree->left) {
            subtree->height = subtree->left->height + 1;
        }
        if(subtree->right && subtree->right->height >= subtree->height) {
            subtree->height = subtree->right->height + 1;
        }
        return;
    }
    if(subtree->left && subtree->right) {
        Node* second = subtree->left;
        while(second->right) {
            second = second->right;
        }
        K second_key = second->key;
        V second_val = second->value;
        remove(second_key);  // Guaranteed to be 1 or 2 child case.
        subtree->key = second_key;
        subtree->value = second_val;
        return;
    }
    if(subtree->left) {
        Node* temp = subtree;
        subtree = subtree->left;
        delete temp;
    } else {
        Node* temp = subtree;
        subtree = subtree->right;
        delete temp;
    }
    /*
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
    } else if (key > subtree->key) {
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            / no-child remove /
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            / two-child remove /
            // your code here
        } else {
            / one-child remove /
            // your code here
        }
        // your code here
    }
    */
}


template <class K, class V>
struct AVLTree<K, V>::Node* & AVLTree<K, V>::find_loc(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if(subtree->key > key) {
        return find_loc(subtree->left, key);
    }
    return find_loc(subtree->right, key);
}
