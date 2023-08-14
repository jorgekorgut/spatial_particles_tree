#include "Tree/ParticlesTree.h"

int main(){
    int width = 1000;
    int height = 600;
    int minResolution = 10;

    int leavesNumberX = 10;
    int leavesNumberY = 6;

    int numberOfFarms = 3;

    ParticlesTree tree(width, height, minResolution, leavesNumberX, leavesNumberY, numberOfFarms);


    return 0;
}