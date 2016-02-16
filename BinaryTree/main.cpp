#include <iostream>
#include <string>
#include <assert.h>

#include "binary_tree.h"

void randomizeArray(int* a, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        int r1 = rand() % size; 
        int r2 = rand() % size;
        int temp = a[r1];
        a[r1] = a[r2];
        a[r2] = temp;
    }
}

void test()
{
    int *a = new int[89];

    for (int i = 10; i < 99; i++)
    {
        a[i - 10] = i;
    }
    randomizeArray(a, 89);
    
    BinaryTree tree;
    for (int i = 0; i < 89; i++)
    {
        tree.insert(std::to_string(a[i]));
    }

    for (int i = 11; i < 98; i++)
    {
        assert(tree.next(std::to_string(i)) == std::to_string(i + 1)); 
        assert(tree.prev(std::to_string(i)) == std::to_string(i - 1)); 
    }

    delete a;
}

int main() 
{
    BinaryTree tree;
    std::string command;
    std::string tempString;

    test();

    while (true) 
    {
        std::cin >> command;

        if (command == "insert")
        {
            std::cin >> tempString;
            tree.insert(tempString);
        }
        else if (command == "delete")
        {
            std::cin >> tempString;
            tree.remove(tempString);
        }
        else if (command == "search")
        {
            std::cin >> tempString;
            std::cout << tree.search(tempString) << "\n"; 
        }
        else if (command == "min")
        {
            std::cout << tree.min() << "\n"; 
        }
        else if (command == "max")
        {
            std::cout << tree.max() << "\n"; 
        }
        else if (command == "next")
        {
            std::cin >> tempString;
            std::cout << tree.next(tempString) << "\n"; 
        }
        else if (command == "prev")
        {
            std::cin >> tempString;
            std::cout << tree.prev(tempString) << "\n"; 
        }
        else if (command == "list")
        {
            tree.list();
        }
        else if (command == "help")
        {
            std::cout << "insert <string>:" << std::endl 
                << "If <string> is already IN the set, increment the count (stored in the node "
                << "containing <string>). If <string> is NOT already in the set, add it to the set "
                << "(and set the count to 1). "
                << "In either case, send <string> <count> to cout." 
                << std::endl << std::endl
                << "delete <string>:" << std::endl

                << "If <string> is NOT in the set, output <string> <-1>." << std::endl
                << "If <string> IS in the set, and has a count of more than 1, decrement "
                << "the count corresponding to the string, and output <string> <nnn>, "
                << "where nnn is the new count. If <string> IS in the set, and has a count"
                << " of exactly 1, delete it from the set, and output <string> <0>." 
                << std::endl << std::endl

                << "search <string>:" << std::endl;
        }
        else if (command == "exit")
        {
            break;
        }
        else 
        {
            std::cout << "Unknown command: " << command << "\n";
        }
    }
}
