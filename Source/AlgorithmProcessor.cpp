/*
  ==============================================================================

    AlgorithmProcessor.cpp
    Created: 13 Sep 2020 1:18:52pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "AlgorithmProcessor.h"
AlgorithmProcessor::AlgorithmProcessor() : op0(0, &fundamental), op1(1, &fundamental), op2(2, &fundamental), op3(3, &fundamental), op4(4, &fundamental), op5(5, &fundamental)
{
    allOps.push_back(&op0);
    allOps.push_back(&op1);
    allOps.push_back(&op2);
    allOps.push_back(&op3);
    allOps.push_back(&op4);
    allOps.push_back(&op5);
    
    currentAlg = AlgorithmDiagram::alg1;
}

void AlgorithmProcessor::newNote(int midiNum)
{
    fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNum);
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->envelope.trigger = 1;
    }
}

void AlgorithmProcessor::setLayersForCurrentAlg()
{
    switch(currentAlg)
    {
        case AlgorithmDiagram::alg1:
        {
            layer0.push_back(allOps[0]);
            layer1.push_back(allOps[1]);
            layer2.push_back(allOps[3]);
            layer3.push_back(allOps[4]);
            layer4.push_back(allOps[2]);
            layer5.push_back(allOps[5]);
        }
        case AlgorithmDiagram::alg2:
        {
            //dummy code copied from above
            layer0.push_back(allOps[0]);
            layer1.push_back(allOps[1]);
            layer2.push_back(allOps[3]);
            layer3.push_back(allOps[4]);
            layer4.push_back(allOps[2]);
            layer5.push_back(allOps[5]);
        }
    }
}

void AlgorithmProcessor::setOutputsInLayerOrder()
{
    if(layer0.size() != 0)
    {
        for(int i = 0; i < layer0.size(); ++i)
        {
            layer0[i]->lastOutputSample = layer0[i]->getSample();
        }
    }
    if(layer1.size() != 0)
    {
        for(int i = 0; i < layer1.size(); ++i)
        {
            layer1[i]->lastOutputSample = layer1[i]->getSample();
        }
    }
    if(layer2.size() != 0)
    {
        for(int i = 0; i < layer2.size(); ++i)
        {
            layer2[i]->lastOutputSample = layer2[i]->getSample();
        }
    }
    if(layer3.size() != 0)
    {
        for(int i = 0; i < layer3.size(); ++i)
        {
            layer3[i]->lastOutputSample = layer3[i]->getSample();
        }
    }
    if(layer4.size() != 0)
    {
        for(int i = 0; i < layer4.size(); ++i)
        {
            layer4[i]->lastOutputSample = layer4[i]->getSample();
        }
    }
    if(layer5.size() != 0)
    {
        for(int i = 0; i < layer5.size(); ++i)
        {
            layer5[i]->lastOutputSample = layer5[i]->getSample();
        }
    }
}

float AlgorithmProcessor::getAudibleSampleForAlg()
{
    switch(currentAlg)
    {
        case AlgorithmDiagram::alg1:
        {
            float outSample = 0.0f;
            outSample += allOps[4]->lastOutputSample;
            outSample += allOps[2]->lastOutputSample;
            outSample += allOps[5]->lastOutputSample;
            return outSample;
            
        }
        case AlgorithmDiagram::alg2:
        {
            float outSample = 0.0f;
            outSample += allOps[4]->lastOutputSample;
            outSample += allOps[2]->lastOutputSample;
            outSample += allOps[5]->lastOutputSample;
            return outSample;
        }
    }
}

void AlgorithmProcessor::endNote()
{
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->envelope.trigger = 0;
    }
}
