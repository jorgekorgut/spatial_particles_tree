#pragma once
#include <vector>
#include "Node.h"

class ParticlesTree
{
public:
    ParticlesTree(int maxWidth, int maxHeight, int minWidth, int minHeight, int leafsNumber);
    
    /*
    *  spatialData is a vector of coordinate points [int x, int y, int z]
    */
    void generateTreeFromVector3(std::vector<int *> & spatialData);

    /*
    *  x, y : Determine the top-left border of the searched area rectangle
    *  width, height : Search area rectangle dimensions
    *  resolution : Represents the width and height of each cell returned by this function
    */
    int * getParticlesCountByFarm(int x, int y, int width, int height, int resolution);

private:
    void generateNode(Node * node);
    Node * root;
};
