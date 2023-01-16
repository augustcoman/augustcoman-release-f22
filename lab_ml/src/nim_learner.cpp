/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"
#include <ctime>
#include <string>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    g_.insertVertex("p1-" + std::to_string(startingTokens));
    startingVertex_ = "p1-" + std::to_string(startingTokens);
    if(startingTokens == 0) {
      return;
    }
    for(unsigned i = startingTokens - 1; i > 0; i--) {
      g_.insertVertex("p2-" + std::to_string(i));
      g_.insertVertex("p1-" + std::to_string(i - 1));
    }
    g_.insertVertex("p2-0");
    for(unsigned i = startingTokens; i > 0; i--) {
      std::string p1v = "p1-" + std::to_string(i);
      std::string p2v = "p2-" + std::to_string(i);
      std::string p1take1 = "p1-" + std::to_string(i - 1);
      std::string p2take1 = "p2-" + std::to_string(i - 1);
      std::string p1take2 = "p1-" + std::to_string(i - 2);
      std::string p2take2 = "p2-" + std::to_string(i - 2);
     //Note: insertEdge creates non-existent verticies
      if(g_.vertexExists(p1v) && g_.vertexExists(p2take1)) {
        g_.insertEdge(p1v, p2take1);
        g_.setEdgeWeight(p1v, p2take1, 0);
      }
      if(g_.vertexExists(p1v) &&g_.vertexExists(p2take2)) {
        g_.insertEdge(p1v, p2take2);
        g_.setEdgeWeight(p1v, p2take2, 0);
      }
      if(g_.vertexExists(p2v) &&g_.vertexExists(p1take1)) {
        g_.insertEdge(p2v, p1take1);
        g_.setEdgeWeight(p2v, p1take1, 0);
      }
      if(g_.vertexExists(p2v) &&g_.vertexExists(p1take2)) {
        g_.insertEdge(p2v, p1take2);
        g_.setEdgeWeight(p2v, p1take2, 0);
      }
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  //if(g_.getAdjacent(startingVertex_).size() > 2) {
  //  throw;
  //}
  //if(g_.getEdge("p1-3", "p2-2").getWeight() == -1) {
  //  throw;
  //}
 /* Your code goes here! */
  std::string traveler = startingVertex_;
  while(!g_.getAdjacent(traveler).empty()) {
    //Gets a random adjacent vertex. All adjacent verticies are of directed nature.
    //Should be 1 or 2 adjacent verticies
    std::string next = g_.getAdjacent(traveler).at(rand() % g_.getAdjacent(traveler).size());
    path.push_back(g_.getEdge(traveler, next));
    traveler = next;
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 if(path.empty()) {
  return;
 }
 //If player 1 wins, add 1. Else add -1.
 int p1_wins_change = (path.back().dest.substr(0, 2) == "p2")?1:-1;
 for(unsigned i = 0; i < path.size(); i++) {
  if(path.at(i).source.substr(0, 2) == "p1") {
    int updated_weight = g_.getEdgeWeight(path.at(i).source, path.at(i).dest) + p1_wins_change;
    g_.setEdgeWeight(path.at(i).source, path.at(i).dest, updated_weight);
  } else {
    int updated_weight = g_.getEdgeWeight(path.at(i).source, path.at(i).dest) - p1_wins_change;
    g_.setEdgeWeight(path.at(i).source, path.at(i).dest, updated_weight);
  }
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
