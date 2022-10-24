/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]) {
      return true;
    }
    if(first[curDim] > second[curDim]) {
      return false;
    }
    return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int dist1 = squareDistance(currentBest, target);
    int dist2 = squareDistance(potential, target);
    if(dist1 == dist2) {
      return potential < currentBest;
    }
    return dist1 > dist2;
}

template <int Dim>
int KDTree<Dim>::squareDistance(const Point<Dim>& first, const Point<Dim>& second) const {
  int distance = 0;
  for(int i = 0; i < Dim; i++) {
    distance += (first[i] - second[i]) * (first[i] - second[i]);
  }
  return distance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    root = NULL;
    size = 0;
    if(!newPoints.empty()) {
      vector<Point<Dim>> copyPoints(newPoints);
      root = TreeConstructHelper(copyPoints, ConstructArgs(0, copyPoints.size() - 1, 0));
      size = newPoints.size();
    }
}

/*
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::TreeConstructHelper(vector<Point<Dim>>& newPoints, size_t left, size_t right) {
  //empty case
  if(newPoints.empty()) {
    return NULL;
  }
  //one node case
  if(left == right) {
    return new KDTreeNode(newPoints.at(left));
  }
  size_t median_idx = (left + right) / 2;
  quickSelect(newPoints, left, right, median_idx);
  KDTreeNode* output = new KDTreeNode(newPoints.at(median_idx));
  return NULL;
}
*/
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::TreeConstructHelper(vector<Point<Dim>>& newPoints, ConstructArgs args) {
  //empty case
  if(newPoints.empty()) {
    return NULL;
  }
  //one node case
  if(args.left == args.right) {
    return new KDTreeNode(newPoints.at(args.left));
  }
  args.pivot = (args.left + args.right) / 2;
  quickSelect(newPoints, args);
  KDTreeNode* output = new KDTreeNode(newPoints.at(args.pivot));
  if(args.left != args.pivot) {
    output->left = TreeConstructHelper(newPoints, args.left_args());
  }
  output->right = TreeConstructHelper(newPoints, args.right_args());
  return output;
}

template <int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>>& points, ConstructArgs args) {
  while(true) {
    if(args.left == args.right) {
      return;
    }
    size_t pivot_index = partition(points, args);
    if(args.pivot == pivot_index) {
      return;
    }
    if(args.pivot < pivot_index) {
      args.right = pivot_index - 1;
    } else {
      args.left = pivot_index + 1;
    }
    //Note: for smaller cases, there may be an error with two element partitions
  }
}

template <int Dim>
size_t KDTree<Dim>::partition(vector<Point<Dim>>& points, ConstructArgs args) {
  Point<Dim> _right = points.at(args.right);
  points.at(args.right) = points.at(args.pivot);
  points.at(args.pivot) = _right;
  size_t storeIndex = args.left;
  for(size_t i = args.left; i < args.right; i++) {
    if(smallerDimVal(points.at(i), points.at(args.right), args.curDim)) {
      Point<Dim> store = points.at(storeIndex);
      points.at(storeIndex) = points.at(i);
      points.at(i) = store;
      storeIndex++;
    }
  }
  Point<Dim> store = points.at(storeIndex);
  points.at(storeIndex) = points.at(args.right);
  points.at(args.right) = store;
  return storeIndex;
}

// Bug that caused prior problems: i < args.right - 1

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = TreeConstructHelper(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != &rhs) {
    //delete helper when I implement it.
    deleteTreeHelper(root);
    this->root = TreeConstructHelper(rhs.root);
    this->size = rhs.size;
  }
  return *this;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::TreeConstructHelper(const KDTreeNode* other) {
  if(other == NULL) {
    return NULL;
  }
  KDTreeNode* copy_ = new KDTreeNode(other->point);
  copy_->left = TreeConstructHelper(other->left);
  copy_->right = TreeConstructHelper(other->right);
  return copy_;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  deleteTreeHelper(root);
  size = 0;
  root = NULL;
}

template <int Dim>
void KDTree<Dim>::deleteTreeHelper(KDTreeNode* target) {
  if(target) {
    KDTreeNode* left_ = target->left;
    KDTreeNode* right_ = target->right;
    delete target;
    deleteTreeHelper(left_);
    deleteTreeHelper(right_);
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if(root) {
      return findNearestNeighbor(query, 0, root)->point;
    }
    return Point<Dim>();
}

template <int Dim>
const typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int curDim, const KDTreeNode* node) const {
  if(!node->left && !node->right) {
    return node;
  }
  const KDTreeNode* nearest = NULL;
  bool recursedLeft = false;
  bool recursedRight = false;
  if(node->left && smallerDimVal(query, node->point, curDim)) {
    nearest = findNearestNeighbor(query, (curDim + 1) % Dim, node->left);
    recursedLeft = true;
  } else if (node->right) {
    nearest = findNearestNeighbor(query, (curDim + 1) % Dim, node->right);
    recursedRight = true;
  }

  if(!nearest || shouldReplace(query, nearest->point, node->point)) {
    nearest = node;
  }
  int dist = squareDistance(query, nearest->point);
  int splitDist = (node->point[curDim] - query[curDim]);
  splitDist *= splitDist;
  if(dist >= splitDist) {
    const KDTreeNode* temp = NULL;
    if(!recursedRight && node->right) {
      temp = findNearestNeighbor(query, (curDim + 1) % Dim, node->right);
    } else if(!recursedLeft && node->left) {
      temp = findNearestNeighbor(query, (curDim + 1) % Dim, node->left);
    }
    if(temp && shouldReplace(query, nearest->point, temp->point)) {
      nearest = temp;
    }
  }
  return nearest;
}

//query[curDim] < node->point[curDim]

/*
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int curDim, const KDTreeNode* node) const {
  const KDTreeNode* nearest = NULL;
  bool recursedLeft = false;
  if(node->left && smallerDimVal(query, node->point, curDim)) {
    nearest = findNearestNeighbor(query, (curDim + 1) % Dim, node->left);
    recursedLeft = true;
  } else if (node->right) {
    nearest = findNearestNeighbor(query, (curDim + 1) % Dim, node->right);
  }

  if(!nearest) {
    return node;
  }
  if(shouldReplace(query, nearest->point, node->point)) {
    nearest = node;
  }
  int dist = squareDistance(query, nearest->point);
  int splitDist = (node->point[curDim] - query[curDim]);
  splitDist *= splitDist;
  if(dist >= splitDist) {
    const KDTreeNode* temp = NULL;
    if(recursedLeft && node->right) {
      temp = findNearestNeighbor(query, (curDim + 1) % Dim, node->right);
    } else if(node->left)
  }
}
*/