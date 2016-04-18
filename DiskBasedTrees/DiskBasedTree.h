#ifndef DISK_BASED_TREE
#define DISK_BASED_TREE

#include <string>

class DiskBasedTree {
    public:
        virtual void insert(std::string data) = 0;

        virtual int count(std::string data) = 0;

        virtual void list() = 0;

        virtual int height() = 0;

        virtual void printResults () = 0;
};

#endif
