#pragma once

#include "PathfindingBoard.h"

namespace AStar
{
    /**
     * \brief Run the algorithm.
     * \param board The board to create a path on.
     * \param SPT The linked list to put the shortest path in.
     * \return If the algorithm was successful. 
     */
    bool run(PathfindingBoard* board, LinkedList<PNode*>& SPT);

    void printq(PathfindingBoard* board);

    bool generate_tree(PathfindingBoard* board,LinkedList<PNode*>& SPT);

    bool handle_finish(PathfindingBoard* board, LinkedList<PNode*>& SPT);
}