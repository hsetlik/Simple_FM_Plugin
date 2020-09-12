/*
  ==============================================================================

    OperatorProcessor.h
    Created: 11 Sep 2020 9:38:49pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"


class OperatorProcessor
{
public:
    //functions
    OperatorProcessor(int index, float* fund);
    OperatorProcessor() {}
    void setFrequency();
    void setEnvelope();
    void setModValue();
    float getOutputSample();
    //data
    int opIndex;
    maxiEnv envelope;
    maxiOsc oscillator;
    float fAttack, fDecay, fSustain, fRelease;
    int modlayer;
    float modIndex;
    float ratio;
    float lastOutputSample;
    bool takesInputFrom[6];
    std::vector<float> modSourceValues;
    float modValue;
    float frequency;
    float* fundamental;
    
};

class SetProcessor
{
public:
    //functions
    SetProcessor();
    ~SetProcessor(){}
    void newNote();
    void calculateLayers();
    void setAllEnvelopes();
    void setModValsByLayer();
    //data
    OperatorProcessor op0;
    OperatorProcessor op1;
    OperatorProcessor op2;
    OperatorProcessor op3;
    OperatorProcessor op4;
    OperatorProcessor op5;
    //all data for operator objects
    //should be accessed and assigned via these pointers
    OperatorProcessor* allOps[6] = {&op0, &op1, &op2, &op3, &op4, &op5};
    float fundamental;
    std::vector<OperatorProcessor*> layer0;
    std::vector<OperatorProcessor*> layer1;
    std::vector<OperatorProcessor*> layer2;
    std::vector<OperatorProcessor*> layer3;
    std::vector<OperatorProcessor*> layer4;
    std::vector<OperatorProcessor*> layer5;
    
    
    
    
};
