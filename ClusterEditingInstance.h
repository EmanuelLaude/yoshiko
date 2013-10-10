/*
 * File:   ClusterEditingInstance.h
 * Author: emanuellaude
 *
 * Created on 25. August 2012, 14:50
 */

#ifndef CLUSTEREDITINGINSTANCE_H
#define	CLUSTEREDITINGINSTANCE_H

#include <lemon/adaptors.h>
#include <lemon/lgf_writer.h>
#include <lemon/full_graph.h>

#include <vector>
#include <cmath>
#include <string>
#include <limits>
#include <map>

#include "WorkingCopyInstance.h"
#include "Helpers.h"

using namespace lemon;
using namespace std;

class WorkingCopyInstance;

class ClusterEditingInstance {
public:
    
    ClusterEditingInstance() : _unweighted(true), _dualWeighted(true), _realValued(false), _costInsertion(0.0), _costDeletion(0.0), _initializedCostInsertion(false), _initializedCostDeletion(false), _nodeNames(_orig), _weight(_orig), _permanent(_orig), _forbidden(_orig), _clusters(_orig) {
    }
    
    virtual ~ClusterEditingInstance();
    
    void init(int size);
    
    void initNode(FullGraph::Node node, string name, vector<int>& cluster);
    
    void initEdge(FullGraph::Edge edge, double weight, bool permanent, bool forbidden);
    
    WorkingCopyInstance& getWorkingCopyInstance();
    
    const FullGraph& getOrig() const;
    
    double computeCost() const;
    
    double getWeight(const FullGraph::Edge& e) const;
    
    bool isUnweighted() const;
    
    bool isDualWeighted() const;
    
    bool isRealValued() const;
    
    string getEdgeName(const FullGraph::Edge e) const;
    
    string getNodeName(const FullGraph::Node node) const;
    
    bool isPermanent(const FullGraph::Edge& e) const;
    
    bool isForbidden(const FullGraph::Edge& e) const;
    
    bool isDirty() const;
    
    void parseJenaFormat(std::istream &is);
    
    void parseCleverFormat(std::istream &is);
    
    void parseSIFFormat(std::istream &is);
    
    vector<int>* getCluster(FullGraph::Node u) const;
    
    friend ostream& operator <<(ostream &os, ClusterEditingInstance &inst);
private:
    bool _unweighted;
    bool _dualWeighted;
    bool _realValued;
    
    double _costInsertion;
    double _costDeletion;
    bool _initializedCostInsertion;
    bool _initializedCostDeletion;
    
    FullGraph _orig;
    FullGraph::NodeMap<string> _nodeNames;
    FullGraph::EdgeMap<double> _weight;
    FullGraph::EdgeMap<bool> _permanent;
    FullGraph::EdgeMap<bool> _forbidden;
    FullGraph::NodeMap<vector<int>* > _clusters;
    
    WorkingCopyInstance* _workingCopyInstance;
};

#endif	/* CLUSTEREDITINGINSTANCE_H */
