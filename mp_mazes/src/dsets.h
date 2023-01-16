/* Your code here! */
#pragma once
#include <vector>

class DisjointSets {
    public:
    /** Adds unjoined elements to end of set
     *  @param num the number of unjoined elements to add
    */
    void addelements(int num);
    /** Finds the index of the root element, performing path compression in the process.
     *  @param elem the index of the element to find the root at
     *  @returns the root of the element
    */
    int find(int elem);
    /** Joins two disjoint sets from their roots, union by size
     *  @param a the element in the first set
     *  @param b the element in the second set
    */
    void setunion(int a, int b);
    /** Returns the size of the set elem is part of
     * @param elem the index of the element to find its set size
     * @returns the size of the disjoint set in elem.
    */
    int size(int elem);
    private:
    std::vector<int> elements_;
};
