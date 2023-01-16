/* Your code here! */

#include <vector>

#include "dsets.h"

void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        elements_.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    //Note: error of oversize not handled here.
    if(elements_.at(elem) < 0) {
        return elem;
    }
    elements_.at(elem) = find(elements_.at(elem));
    return elements_.at(elem);
}

void DisjointSets::setunion(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if(root_a == root_b) {
        return;
    }
    if(size(root_a) >= size(root_b)) {
        elements_.at(root_a) += elements_.at(root_b);
        elements_.at(root_b) = root_a;
    } else {
        elements_.at(root_b) += elements_.at(root_a);
        elements_.at(root_a) = root_b;
    }
}

int DisjointSets::size(int elem) {
    //Note: is guaranteed to be negative when found
    return -1 * elements_.at(find(elem));
}