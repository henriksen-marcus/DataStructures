#include "PathfindingBoard.h"

void PathfindingBoard::init()
{
    int loops = 0;
    // Generate the board based on the template
    for (int y{}; y < grid.size(); y++)
    {
        for (int x{}; x < grid[y].size(); x++)
        {
            // If the node is a blocking node we don't give it a specific name
            std::string name = grid[y][x] ? generate_name(loops++) : "BK";
            auto* node = new PNode(name, x, y, !grid[y][x]);
            nodes.push_back(node);
        std::cout << "Created node with name: " << node->name << std::endl;
        }
    }

    // We can only start adding connection references once
    // all nodes have been created.
    for (auto node : nodes)
    {
        setup_connections(node);
    }
    
    // Start node is top left, end is bottom right
    origin = nodes.front();
    destination = nodes.back();
}

void PathfindingBoard::setup_connections(PNode* node)
{
    /*
    A node can have a total of 8 connections.
    
    N.W   N   N.E
       \  |  /
        \ | /
   W --- node --- E
        / | \
       /  |  \
    S.W   S   S.E

    We connect to all adjacent nodes.
    */

    std::cout << "Setting connections for node: " << node->name<< "\n";

    // North west
    PNode* other_node = find(node->x-1, node->y-1);
    /* We don't add blocking nodes to the connection list,
     * makes evaluating paths during pathfinding easier */
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);

    // North
    other_node = find(node->x, node->y-1);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);
    
    // North east
    other_node = find(node->x+1, node->y-1);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);

    // East
    other_node = find(node->x+1, node->y);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);
    

    // South east
    other_node = find(node->x+1, node->y+1);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);

    // South
    other_node = find(node->x, node->y+1);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);

    // South west
    other_node = find(node->x-1, node->y+1);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);

    // West
    other_node = find(node->x-1, node->y);
    if (other_node and !other_node->blockingNode)
        node->conn.add(other_node);

    for(int i{};i<node->conn.size();i++)
    {
        std::cout << "  "<<node->conn[i]->name<< "\n";
    }
}

PNode* PathfindingBoard::find(int x, int y)
{
    // Check if we are outside the board
    if (x < 0 or x >= grid.size() or y < 0 or y >= grid.size())
        return nullptr;
    
    for (PNode* node : nodes)
    {
        if (node->x == x and node->y == y)
            return node;
    }
    return nullptr;
}

void PathfindingBoard::update_priority(PNode* node)
{
    priority_queue.remove(node);
    for(int i{}; i < priority_queue.size(); i++)
    {
        // Find the right position based on the node's cost
        if (node->cost < priority_queue[i]->cost)
        {
            printf("		update_priority(): Moved %s before %s in the priority_queue.", node->name.c_str(), priority_queue[i]->name.c_str());
            priority_queue.insert(node, i);
            return;
        }
    }
    // If the node had a higher cost than all other nodes
    printf("		update_priority(): Added %s to the end of the priority_queue.", node->name.c_str());
    priority_queue.add(node);
}

std::string PathfindingBoard::generate_name(int i)
{
    const int Number = i / Alphabet.size();
    return Number > 0 ? Alphabet[i - Alphabet.size() * Number] + std::to_string(Number) : Alphabet[i];
}

float PathfindingBoard::get_heuristic(PNode* n1, PNode* p2)
{
    
}

void PathfindingBoard::print()
{
    int loops{};
    for (int y{}; y < grid.size(); y++)
    {
        for (int x{}; x < grid[y].size(); x++)
        {
            std::cout << nodes[loops++]->name << " ";
        }
        std::cout << "\n";
    }
}
