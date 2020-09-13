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
    OperatorProcessor(int index)
    {
        opIndex = index;
    }
    ~OperatorProcessor() {}
    //data
    maxiEnv envelope;
    maxiOsc oscillator;
    int opIndex;
    float fundamental;
    float modValue;
    float ratio;
    float modIndex;
    float level;
    float lastOutputSample;
    float getSample()
    {
        float baseFreq = fundamental * ratio;
        float modOffset = modValue * modIndex;
        double preEnv = oscillator.sinewave(baseFreq + modOffset);
        double postEnv =  envelope.adsr(preEnv);
        return postEnv * level;
    }
};
