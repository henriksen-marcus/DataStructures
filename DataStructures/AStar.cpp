
#include "AStar.h"
#include "PNode.h"
#include "LinkedList.h"

namespace AStar
{
    bool run(PathfindingBoard* board, LinkedList<PNode*>& SPT)
    {
    	
    printf("Start()\n");
    	
	// Safety check
	if (!board->nodes.size() || !board->origin || !board->destination) return false;

	board->priority_queue.empty();
	auto current_node = board->origin;
	current_node->visited = true;
	current_node->cost = 0;
    PNode* previous_node = nullptr;

	// add each node to the priority queue
	// Each node comes pre-init with max distance cost
	for (const auto Node : board->nodes)
	{
		// Don't add the destination node as we don't want
		// to check any path going FROM the destination
		if (Node != board->destination)
		{
			board->priority_queue.add(Node);
			printf("added %s to Priority Queue\n", Node->name.c_str());
		}
	}
	printq(board);

	// Algorithm runs as long as there are items left in the priority queue.
	// This means that we will check all nodes before concluding the shortest path.
	int loops = 0;
	while (loops++ < 500)
	{
		// Step 1: Update estimates
		// Go through each connected node and update the nodes cost and PreviousNode
		
		printf("current_node: %s\n", current_node->name.c_str());
		for (int i{}; i < current_node->conn.size(); i++)
		{
			PNode* NextNode = current_node->conn[i];

			// Avoid infinite loop of checking visited nodes
			if (NextNode == previous_node || NextNode == current_node->prev || NextNode == current_node) continue;
			
			float TotalCost = 1 /* + heuristic */ + current_node->cost;
			
			printf("		Checking connection to %s\n", NextNode->name.c_str());
			printf("		Cost to node:\n");
			printf("			Distance: %d\n", 1);
			printf("			Previous Nodes: %f\n", current_node->cost);
			printf("			Total: %f\n", TotalCost);
			printf("		Node visited: %s\n", NextNode->visited ? "true" : "false");
		
			// Skip check if node already has a shorter path!
			if (NextNode->visited && NextNode->cost <= TotalCost)
			{
				printf("		Skipped updating %s, shorter path already exists\n", NextNode->name.c_str());
				continue;
			}
			
			// We don't want to update this if there is already a shorter path to this node
			NextNode->cost = TotalCost;
			NextNode->prev = current_node; // Just like in linked list
			NextNode->visited = true;

			// Exit algorithm
			if (NextNode == board->destination) return handle_finish(board, SPT);

			// Update the node's position in the priority queue, unless it's the destination node
			if (NextNode != board->destination) board->update_priority(NextNode);
		}
		
		// Now that we've checked all the connections from this node, we remove it
		// from the priority queue so we don't get an infinite loop
		board->priority_queue.remove(current_node);
		printq(board);

		// Checked everything but no path
		if (board->priority_queue.is_empty()) break;
		
		// Step 2: Choose next node
		// We always choose the node at the top of the priority queue,
		// meaning that we can jump across the map between nodes depending
		// on what is the current shortest, unexplored path we can check
		
		previous_node = current_node;
		current_node = board->priority_queue[0];
	}
	printf("Not possible to get to destination!\n");
	return false;
    }

    void printq(PathfindingBoard* board)
    {
    	for (int i{}; i < board->priority_queue.size(); i++)
    	{
    		printf("%s", board->priority_queue[i]->name.c_str());	
    	}
    }

	bool generate_tree(PathfindingBoard* board, LinkedList<PNode*>& SPT)
    {
    	printf("GenerateTree()\n");
    	SPT.empty();
    	SPT.add(board->destination);
    	PNode* Previous = board->destination->prev;
    	while (Previous)
    	{
    		SPT.add(Previous);
    		Previous = Previous->prev;
    	}
    	// Check if we actually found a complete path
    	if (!SPT.find(board->origin)) return false;

    	//Algo::Reverse(ShortestPathTree);

    	printf("			Shortest path:\n");
	
    	std::string STP = "";
    	for (int i{}; i < SPT.size(); i++)
    	{
    		STP += SPT[i]->name + " ";
    	}
    	printf("			%s\n", STP.c_str());
	
	
    	return true;
    }
	
	bool handle_finish(PathfindingBoard* board, LinkedList<PNode*>& SPT)
    {
    	if (generate_tree(board, SPT))
    	{
    		printf("Dijkstra succeeded.\n");
		
    		int NodesVisited = 0;
    		for (const auto Node : board->nodes) { if (Node->visited) NodesVisited++; }
		
    		printf("Number of nodes visited: %d\n", NodesVisited);
    		return true;
    	}
    	return false;
    }
}
