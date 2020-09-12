/*
  ==============================================================================

    OperatorProcessor.cpp
    Created: 11 Sep 2020 9:38:49pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "OperatorProcessor.h"

OperatorProcessor::OperatorProcessor(int index, float* fund)
{
    opIndex = index;
    fundamental = fund;
}

void OperatorProcessor::setModValue()
{
    modValue = 0.0f;
    for(int i = 0; i < modSourceValues.size(); ++i)
    {
        int sourceIndex = modSourceValues[i];
        modValue += modSourceValues[sourceIndex];
    }
}

void OperatorProcessor::setFrequency()
{
    frequency = *fundamental * ratio;
    frequency += (modValue * modIndex);
}

void OperatorProcessor::setEnvelope()
{
    envelope.setAttack(fAttack);
    envelope.setDecay(fDecay);
    envelope.setSustain(fSustain);
    envelope.setRelease(fRelease);
}

float OperatorProcessor::getOutputSample()
{
    auto preEnv = oscillator.sinewave(frequency);
    auto postEnv = envelope.adsr(preEnv);
    return postEnv;
}
