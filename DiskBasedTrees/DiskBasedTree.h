/*
 * File Name: DiskBasedTree.h
 * Name: Michael Gerdes
 * Date: 4/19/2016
 * Class: Linear Data Structures
 *
 * This file is the interface for the Disk Based Tree
 * The AVLTree and BTree both implement this.
 */

#ifndef DISK_BASED_TREE
#define DISK_BASED_TREE

#include <string>

class DiskBasedTree {
    public:
        // Function to insert a key.
        virtual void insert(std::string data) = 0;

        // Function to get the count of a key.
        virtual int count(std::string data) = 0;

        // Function to list the keys.
        virtual void list() = 0;

        // Function to get the height.
        virtual int height() = 0;

        // Function to print the results of the tree.
        virtual void printResults () = 0;
};

#endif
