#pragma once

#include <vector>
#include <array>
#include <queue>
#include <string>
#include "PNode.h"

/**
 * \brief Information class to be used by
 * a pathfinding algorithm.
 */
class PathfindingBoard
{
public:
    PNode* origin;
    PNode* destination;

    // This is just a layout template for the board.
    // This is not the actual board.
    /*std::array<std::array<int, 10>, 9> grid {
                    { { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
                      { { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 } },
                      { { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 } },
                      { { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 } },
                      { { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 } },
                      { { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 } },
                      { { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 } },
                      { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
                      { { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } } }
    };*/

    std::array<std::array<int, 4>, 4> grid {
            {{ { 1, 0, 1, 1 } },
              { { 1, 0, 1, 0 } },
              { { 1, 0, 1, 0 } },
              { { 1, 1, 1, 1 } } }
    };

    // This is the board. Relations and connections
    // are handled in the PNode struct.
    std::vector<PNode*> nodes;

    LinkedList<PNode*> priority_queue;
    
    std::vector<std::string> Alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};


    /**
     * \brief Create the nodes based on the template
     * layout of "grid"..
     */
    void init();

    /**
     * \brief Check the surroundings of the node
     * and create connections to all adjacent nodes,
     * not including blocking nodes.
     * \param node The node to add connections to.
     */
    void setup_connections(PNode* node);

    /**
     * \brief Get a ptr to the node at the given
     * coordinates, if it exists.
     * \param x x coordinate.
     * \param y y coordinate.
     * \return Ptr to the node, nullptr if it doesn't
     * exist or the coordinates are out of range.
     */
    PNode* find(int x, int y);

    void update_priority(PNode* node);
 
    std::string generate_name(int i);
 
    void print_board();
};
