/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node* location = find(root, key);
    if(location) {
        return location->value;
    }
    return V();
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if(subtree->key > key) {
        return find(subtree->left, key);
    }
    return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    Node*& insertion_loc = find(root, key);
    if(!insertion_loc) {
        insertion_loc = new Node(key, value);
    }
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K first_key = first->key;
    V first_val = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = first_key;
    second->value = first_val;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    Node*& target = find(root, key);
    if(target) {
        remove(target, key);
    }
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if(subtree->left && subtree->right) {
        Node* second = subtree->left;
        while(second->right) {
            second = second->right;
        }
        //swap(subtree, second);
        K second_key = second->key;
        V second_val = second->value;
        remove(second_key);  // Guaranteed to be 1 or 2 child case.
        //subtree = second;   //problem here! Pointer reference modification!
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
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> output;
    for(unsigned i = 0; i < inList.size(); i++) {
        output.insert(inList[i].first, inList[i].second);
    }
    return output;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::sort(inList.begin(), inList.end());
    std::vector<int> histogram(inList.size(), 0);
    do {
        BST<K, V> permutation = listBuild(inList);
        histogram.at(permutation.height())++;
    } while(std::next_permutation(inList.begin(), inList.end()));
    return histogram;
}