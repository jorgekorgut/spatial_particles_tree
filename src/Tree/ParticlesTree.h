#pragma once
#include <vector>
#include "Node.h"

class Vector4
{
public:
    double x;
    double y;
    double z;
    int farm;
};
class ParticlesTree
{
public:
    ParticlesTree(double maxWidth, double maxHeight, double minResolution, int leavesNumberX, int leavesNumberY, int nFarms);

    ~ParticlesTree();

    /*
     *  spatialData is a vector of coordinate points [int x, int y, int z]
     */
    void generateTreeFromVector3(std::vector<Vector4> &spatialData);

    /*
     *  x, y : Determine the top-left border of the searched area rectangle
     *  width, height : Search area rectangle dimensions
     *  resolution : Represents the width and height of each cell returned by this function
     */
    int *getParticlesCountByFarm(int x, int y, int width, int height, int resolution);

    int getTreeDepth();

private:
    void addNode(const Vector4 & spatialData, int numberOfLeaves);
    //inline int findTreeDepth(int maxDimension, int minResolution, int leafsNumber);
    Node *root = nullptr;
    double width;
    double height;
    double resolution;
    int leavesX;
    int leavesY;
    int treeDepth;

    int numberOfFarms;
};
