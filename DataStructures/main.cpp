#include <fstream>
#include <iostream>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "AStar.h"
#include "PathfindingBoard.h"
#include "heapsort.h"

using namespace std;

int main(int argc, char* argv[])
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int N = sizeof(arr) / sizeof(arr[0]);

    // Function call
    heapSort(arr, N);

    cout << "Sorted array is \n";
    printArray(arr, N);

    return 0;
    
    PathfindingBoard board;
    board.init();
    LinkedList<PNode*> list;
    AStar::run(&board, list);
    cout << list.size() << endl;
    board.print();
    
    return 0;
}
