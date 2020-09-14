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
    OperatorProcessor(int index, float* fund)
    {
        opIndex = index;
        fundamental = fund;
    }
    ~OperatorProcessor() {}
    //data
    maxiEnv envelope;
    maxiOsc oscillator;
    int opIndex;
    float* fundamental;
    double modValue;
    float ratio;
    float modIndex;
    float level;
    double frequency;
    double lastOutputSample;
    float getSample()
    {
        float baseFreq = *fundamental * ratio;
        float modOffset = modValue * modIndex;
        frequency = baseFreq + modOffset;
        double preEnv = oscillator.sinewave(frequency);
        double postEnv =  envelope.adsr(preEnv, envelope.trigger);
        lastOutputSample = postEnv * level;
        return lastOutputSample;
    }
};
