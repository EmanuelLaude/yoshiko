/*
 * File:   WorkingCopyInstance.h
 * Author: emanuellaude
 *
 * Created on 28. August 2012, 16:54
 */

#ifndef WORKINGCOPYINSTANCE_H
#define	WORKINGCOPYINSTANCE_H

#include <lemon/full_graph.h>
#include <lemon/adaptors.h>
#include <lemon/connectivity.h>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>

#include "ClusterEditingInstance.h"
#include "Globals.h"


using namespace lemon;
using namespace std;

typedef SubGraph<const FullGraph> WorkingCopyGraph;

class ClusterEditingInstance;

class WorkingCopyInstance {
public:
    WorkingCopyInstance(ClusterEditingInstance* inst) : _instance(inst), _dirty(false) {
        
    }
    
    virtual ~WorkingCopyInstance();
    
    void init();
    
    void initNode(FullGraph::Node node, string name);
    
    void initEdge(FullGraph::Edge edge, double weight, bool permanent, bool forbidden);
    
    const WorkingCopyGraph& getGraph() const;
    
    const FullGraph& getOrig() const;
    
    WorkingCopyGraph::Edge edge(const WorkingCopyGraph::Node& u, const WorkingCopyGraph::Node& v) const;
    
    double getWeight(const WorkingCopyGraph::Edge& e) const;
    
    string getNodeName(const WorkingCopyGraph::Node& u) const;
    
    string getEdgeName(const WorkingCopyGraph::Edge& uv) const;
    
    const WorkingCopyGraph::EdgeMap<double>& getWeight() const;
    
    const WorkingCopyGraph::NodeMap<string>& getNodeNames() const;
    
    const WorkingCopyGraph::NodeMap<vector<int>*>& getClusters() const;
    
    void setForbidden(const WorkingCopyGraph::Edge& uv);
    
    //first node in vector nodes serves as proxy
    WorkingCopyGraph::Node merge(const vector<WorkingCopyGraph::Node>& nodes);
    
    WorkingCopyGraph::Node setPermanent(const WorkingCopyGraph::Edge& uv);
    
    void setPermanent(const WorkingCopyGraph::Edge& uv, const WorkingCopyGraph::Node& proxy);
    
    bool isPermanent(const WorkingCopyGraph::Edge& e) const;
    
    bool isForbidden(const WorkingCopyGraph::Edge& e) const;
    
    const WorkingCopyGraph::EdgeMap<bool>& getPermanent() const;
    
    const WorkingCopyGraph::EdgeMap<bool>& getForbidden() const;
    
    bool isDirty() const;
    
    friend ostream& operator <<(ostream &os, WorkingCopyInstance &inst);
private:
    ClusterEditingInstance* _instance;
    
    bool _dirty;
    
    WorkingCopyGraph* _graph;
    FullGraph::NodeMap<bool>* _nodes;
    FullGraph::EdgeMap<bool>* _edges;
    
    WorkingCopyGraph::NodeMap<string>* _nodeNames;
    WorkingCopyGraph::EdgeMap<double>* _weight;
    WorkingCopyGraph::EdgeMap<bool>* _permanent;
    WorkingCopyGraph::EdgeMap<bool>* _forbidden;
    WorkingCopyGraph::NodeMap<vector<int>*>* _clusters;
};

#endif	/* WORKINGCOPYINSTANCE_H */
