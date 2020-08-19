#pragma once

#include "../Geometry/point.h"
#include "../Trees/binaryTree.h"

class Graph {
    private:
        int noVertices;
        Point* vertices;
    public:
        Graph(){}
        Graph(int noVertices, Point* vertices): noVertices(noVertices), vertices(vertices){}
        BinaryTree convertToBinaryTree();
        Point* findClosestVertex(Point targetVertex);
        Point* fastestPathAllVs(Point startingVertex);
};