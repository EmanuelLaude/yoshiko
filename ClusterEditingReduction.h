//
//  ClusterEditingReduction.h
//  weighted-cluster-editing
//
//  Created by Emanuel Laude on 18.11.12.
//  Copyright (c) 2012 Emanuel Laude. All rights reserved.
//

#ifndef CLUSTEREDITINGREDUCTION_H
#define CLUSTEREDITINGREDUCTION_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include <lemon/connectivity.h>

#include "ClusterEditingInstance.h"
#include "ClusterReductionInstance.h"

using namespace std;

class ClusterEditingReduction {
public:
    ClusterEditingReduction(bitset<NUMBER_OF_REDUCTION_RULES> active, double multiplicativeFactor, bool conserveMultipleSolutions) : _totalCost(0.0), _active(active), _multiplicativeFactor(multiplicativeFactor), _conserveMultipleSolutions(conserveMultipleSolutions) {
    }
    void perform(ClusterEditingInstance& orig);
    virtual ~ClusterEditingReduction();
    vector<ClusterReductionInstance*>& getInstances();
    double getTotalCost() const;
private:
    vector<ClusterReductionInstance*> _instances;
    double _totalCost;
    bitset<NUMBER_OF_REDUCTION_RULES> _active;
    double _multiplicativeFactor;
    bool _conserveMultipleSolutions;
};

#endif /* CLUSTEREDITINGREDUCTION_H */
