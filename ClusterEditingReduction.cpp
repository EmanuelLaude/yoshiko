//
//  ClusterEditingReduction.cpp
//  weighted-cluster-editing
//
//  Created by Emanuel Laude on 18.11.12.
//  Copyright (c) 2012 Emanuel Laude. All rights reserved.
//

#include "ClusterEditingReduction.h"

ClusterEditingReduction::~ClusterEditingReduction() {
    for(vector<ClusterReductionInstance*>::iterator it = _instances.begin(); it != _instances.end(); it++) {
        delete *it;
    }
}

vector<ClusterReductionInstance*>& ClusterEditingReduction::getInstances() {
    return _instances;
}

void ClusterEditingReduction::perform(ClusterEditingInstance& orig) {
    vector<ClusterReductionInstance*> instances;
    ClusterReductionInstance i(&orig, _active, _multiplicativeFactor, _conserveMultipleSolutions);
    i.computeChildInstances(instances);
    
    while(instances.size() != 0) {
        vector<ClusterReductionInstance*> tmp;
        
        for(vector<ClusterReductionInstance*>::iterator it = instances.begin(); it != instances.end(); it++) {
            int i = (*it)->applyReductionRules();
            
            if(i != -1) {
                double cost = (*it)->getInstance()->computeCost();
                _totalCost += cost;
                if(verbosity > 0)
                    cout << "cost:\t"<<cost<<endl;
                
                vector<ClusterReductionInstance*> childInstances;
                (*it)->computeChildInstances(childInstances);
                tmp.insert(tmp.end(), childInstances.begin(), childInstances.end());
                delete (*it)->getInstance();
                delete *it;
            } else {
                _instances.push_back(*it);
            }
        }
        instances = tmp;
    }
}

double ClusterEditingReduction::getTotalCost() const {
    return _totalCost;
}
