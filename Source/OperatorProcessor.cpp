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
    if(modSources.size() != 0)
    {
        for(int i = 0; i < modSources.size(); ++i)
        {
            modValue += modSources[i]->lastOutputSample;
        }
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

SetProcessor::SetProcessor() : op0(0, &fundamental), op1(1, &fundamental), op2(2, &fundamental), op3(3, &fundamental), op4(4, &fundamental), op5(5, &fundamental)
{
    
}

void SetProcessor::newNote(int midiNumber)
{
    fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNumber);
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->setEnvelope();
        allOps[i]->envelope.trigger = 1;
        allOps[i]->lastOutputSample = 0.0f;
    }
}

void SetProcessor::calculateLayers()
{
    layer0.clear();
    layer1.clear();
    layer2.clear();
    layer3.clear();
    layer4.clear();
    layer5.clear();
    //finding the number of modulators and assigning the sources for each operator
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->modSources.clear();
        allOps[i]->totalDependencies = 0;
        int modCount = 0;
        for(int n = 0; n < 6; ++n)
        {
            if(allOps[i]->takesInputFrom[n])
            {
                modCount++;
                allOps[i]->modSources.push_back(allOps[n]);
                allOps[i]->totalDependencies += 1;
            }
        }
        allOps[i]->numModulators = modCount;
    }
    //==========calculating the total dependencies for each operator
    for(int i = 0; i < 6; ++i)
    {
       if(allOps[i]->numModulators != 0)
       {
           for(int n = 0; n < allOps[i]->numModulators; ++n)
           {
               if(allOps[i]->modSources[n]->numModulators != 0)
                   allOps[i]->totalDependencies += allOps[i]->modSources[n]->numModulators;
           }
       }
    }
    //adding each operator to the appropriate layer based on its dependencies
    for(int i = 0; i < 6; ++i)
    {
        int depCount = allOps[i]->totalDependencies;
        if(depCount == 0)
        {
            layer0.push_back(allOps[i]);
            allOps[i]->modLayer = 0;
        }
        else if(depCount == 1)
        {
            layer1.push_back(allOps[i]);
            allOps[i]->modLayer = 1;
        }
        else if(depCount == 2)
        {
            layer2.push_back(allOps[i]);
            allOps[i]->modLayer = 2;
        }
        else if(depCount == 3)
        {
            layer3.push_back(allOps[i]);
            allOps[i]->modLayer = 3;
        }
        else if(depCount == 4)
        {
            layer4.push_back(allOps[i]);
            allOps[i]->modLayer = 4;
        }
        else
        {
            layer5.push_back(allOps[i]);
            allOps[i]->modLayer = 5;
        }
    }
}
//=====================================================
void SetProcessor::setModValsByLayer()
{
    if(layer0.size() != 0)
    {
        for(int i = 0; i < layer0.size(); ++i)
        {
            layer0[i]->setModValue();
        }
    }
    //=======
    if(layer1.size() != 0)
    {
        for(int i = 0; i < layer1.size(); ++i)
        {
            layer1[i]->setModValue();
        }
    }
    //=====
    if(layer2.size() != 0)
    {
        for(int i = 0; i < layer2.size(); ++i)
        {
            layer2[i]->setModValue();
        }
    }
    //=======
    if(layer3.size() != 0)
    {
        for(int i = 0; i < layer3.size(); ++i)
        {
            layer3[i]->setModValue();
        }
    }
    //=======
    if(layer4.size() != 0)
    {
        for(int i = 0; i < layer4.size(); ++i)
        {
            layer4[i]->setModValue();
        }
    }
    //========
    if(layer5.size() != 0)
    {
        for(int i = 0; i < layer5.size(); ++i)
        {
            layer5[i]->setModValue();
        }
    }
}
//============================
void SetProcessor::setAllFrequencies()
{
    for(int i = 0; i < 6; ++i)
        allOps[i]->setFrequency();
}
//============================

void SetProcessor::applyEnvelopesAndLevels()
{
    for(int i = 0; i < 6; ++i)
    {
        float oscSample = allOps[i]->oscillator.sinewave(allOps[i]->frequency);
        float tempSample = allOps[i]->envelope.adsr(oscSample);
        allOps[i]->lastOutputSample = tempSample * allOps[i]->level;
    }
}

//=====================

float SetProcessor::mixSample()
{
    float sample = 0.0f;
    for(int i = 0; i < 6; ++i)
    {
        if(allOps[i]->isAudible)
            sample += allOps[i]->lastOutputSample;
    }
    return sample;
}

//=========================
void SetProcessor::endNote()
{
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->envelope.trigger = 0;
    }
    
}
