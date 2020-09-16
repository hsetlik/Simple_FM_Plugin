/*
  ==============================================================================

    AlgorithmProcessor.h
    Created: 13 Sep 2020 1:18:52pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OperatorProcessor.h"
#include "AlgorithmSelectorComponent.h"

class AlgorithmProcessor
{
public:
    //functions
    AlgorithmProcessor();
    ~AlgorithmProcessor() {}
    void newNote(double fundamental);
    void setModSourcesFromGrid();
    void setLayersForCurrentAlg();
    void assignLayersInOrder();
    void setModValues();
    void setModValuesFromGrid();
    void setOutputsInLayerOrder();
    float getAudibleSampleForAlg();
    double getAudibleSampleForGrid();
    void endNote();
    
    //data
    OperatorProcessor op0;
    OperatorProcessor op1;
    OperatorProcessor op2;
    OperatorProcessor op3;
    OperatorProcessor op4;
    OperatorProcessor op5;
    std::vector<OperatorProcessor*> allOps;
    int procAlgIndex;
    float fundamental;
    bool modGridSettings[6][6];
    OperatorProcessor* layer0;
    OperatorProcessor* layer1;
    OperatorProcessor* layer2;
    OperatorProcessor* layer3;
    OperatorProcessor* layer4;
    OperatorProcessor* layer5;
    
};
