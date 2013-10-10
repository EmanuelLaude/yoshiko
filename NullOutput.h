//
//  NullOutput.h
//  weighted-cluster-editing
//
//  Created by Emanuel Laude on 21.03.13.
//  Copyright (c) 2013 Emanuel Laude. All rights reserved.
//

#ifndef NULLOUTPUT_H
#define NULLOUTPUT_H

#include <iostream>
#include <string>

#include "ClusterEditingOutput.h"

using namespace std;

class NullOutput : public ClusterEditingOutput {
public:
    NullOutput(ClusterEditingInstance& inst, ClusterEditingSolutions& solutions, string filename, string suffix, string label) : ClusterEditingOutput(inst, solutions, filename, suffix, label) {
    }
    void openStream(size_t solution);
    void closeStream();
    void writeHeader(string label, size_t solution, size_t numberOfNodes, size_t numberOfClusters);
    void writeBeginNodes(size_t numberOfNodes);
    void writeEndNodes();
    void writeNode(int nodeId, string name, size_t cluster);
    void writeBeginEdges();
    void writeEdge(int sourceId, int targetId, string name, double weight, bool modified);
    void writeEndEdges();
    void writeBeginCluster(size_t cluster);
    void writeEndCluster();
    void writeFooter();
};

#endif /* NULLOUTPUT_H */
