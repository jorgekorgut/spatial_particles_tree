#pragma once
#include <vector>
#include "Node.h"

class Vector4
{
public:
    Vector4() : x(0), y(0), z(0), farm(1)
    {
    }

    Vector4(double x, double y, double z, int farm) : x(x), y(y), z(z), farm(1)
    {
    }

    double x;
    double y;
    double z;
    int farm;
};

class ReturnParticleCountByFarm
{
public:
    ReturnParticleCountByFarm(int sx, int sy, int nFarms, std::vector<int *> *countMatrix, double resX, double resY)
    {
        sizeX = sx;
        sizeY = sy;
        numberOfFarms= nFarms;
        countParticlesMatrix = countMatrix;
        resolutionX = resX;
        resolutionY = resY;
    }
    int sizeX;
    int sizeY;
    std::vector<int *> *countParticlesMatrix;
    int numberOfFarms;
    double resolutionX;
    double resolutionY;
};

class ParticlesTree
{
public:
    ParticlesTree(double maxWidth, double maxHeight, double minResolution, int leavesNumberX, int leavesNumberY, int nFarms);

    ~ParticlesTree();

    /*
     *  spatialData is a vector of coordinate points [int x, int y, int z, farmNode]
     */
    void generateTreeFromVector3(std::vector<Vector4> &spatialData);

    /*
     *  x, y : Determine the top-left border of the searched area rectangle
     *  width, height : Search area rectangle dimensions
     */
    ReturnParticleCountByFarm *getParticlesCountByFarm(double x, double y, double width, double height, double wantedResolution);

    /*
     *  add a node into the tree
     *  spatialData is a vector of coordinate points [int x, int y, int z, farmNode]
     */
    void addNode(const Vector4 &spatialData);

    int getLeavesCountX()
    {
        return leavesX;
    }

    int getLeavesCountY()
    {
        return leavesY;
    }

    int getLeavesCount()
    {
        return numberOfLeaves;
    }

    Node *getRoot()
    {
        return root;
    }

    double getWidth()
    {
        return width;
    }

    double getHeight()
    {
        return height;
    }

    int getTreeDepth();

private:
    void searchRecursivelyParticlesCount(Node *currentNode,
                                         double currentX,
                                         double currentY,
                                         double currentWidth,
                                         double currentHeight,
                                         double realX,
                                         double realY,
                                         double realWidth,
                                         double realHeight,
                                         double realResolutionX,
                                         double realResolutionY,
                                         double realSizeX,
                                         double realSizeY);

    Node *root = nullptr;
    double width;
    double height;
    double minResolution;
    int leavesX;
    int leavesY;
    int numberOfLeaves;
    // int treeDepth;
    std::vector<int *> *countMatrix = nullptr;

    int numberOfFarms;
};
