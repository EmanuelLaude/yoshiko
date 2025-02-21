//
//  CliqueRule.cpp
//  weighted-cluster-editing
//
//  Created by Emanuel Laude on 20.11.12.
//  Copyright (c) 2012 Emanuel Laude. All rights reserved.
//

#include "CliqueRule.h"

void CliqueRule::apply() {
    bool clique = true;
    
    for(WorkingCopyGraph::NodeIt u(_instance.getGraph()); u != INVALID; ++u) {
        WorkingCopyGraph::NodeIt v(_instance.getGraph(), u);
        ++v;
        for(; v != INVALID; ++v) {
            WorkingCopyGraph::Edge uv = _instance.edge(u, v);
            if(_instance.getWeight(uv)<=0) {
                clique = false;
                break;
            }
        }
        
    }
    
    if(clique) {
        vector<WorkingCopyGraph::Node> nodes;
        for(WorkingCopyGraph::NodeIt u(_instance.getGraph()); u != INVALID; ++u) {
            nodes.push_back(u);
        }
        _success = true;
        _instance.merge(nodes);
    }
}
