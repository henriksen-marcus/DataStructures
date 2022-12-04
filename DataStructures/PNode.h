#pragma once

#include <string>
#include "LinkedList.h"

/**
 * \brief Pathfinding node. Used in Dijkstra/A* algorithm.
 */
struct PNode
{
    PNode(std::string& name, int x, int y, bool isBlocking) : name(name), x(x), y(y)
    {
        blockingNode = isBlocking;
        visited = false;
        cost = heuristic = std::numeric_limits<float>::infinity();
        prev = nullptr;
    }
    std::string name;
    bool visited, blockingNode;
    float cost; // Including the cost of prev. nodes
    float heuristic; // Distance cost from this to dest.
    int x, y;
    PNode* prev; // The previous node
    LinkedList<PNode*> conn; // Connections
};
