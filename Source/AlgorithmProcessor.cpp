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
    
    procAlgIndex = 1;
}

void AlgorithmProcessor::newNote(double fund)
{
    fundamental = fund;
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->envelope.trigger = 1;
    }
}

void AlgorithmProcessor::assignLayersInOrder()
{
    layer0 = allOps[0];
    layer1 = allOps[1];
    layer2 = allOps[2];
    layer3 = allOps[3];
    layer4 = allOps[4];
    layer5 = allOps[5];
}

void AlgorithmProcessor::setModSourcesFromGrid()
{
    
}

void AlgorithmProcessor::setModValuesFromGrid()
{
    for(int i = 0; i < 6; ++i)
    {
        
        allOps[i]->modValue = 0.0f;
        
        {
            for(int n = 0; n < 6; ++n)
            {
                if(!modGridSettings[i][n])
                {
                    allOps[i]->modValue += allOps[n]->lastOutputSample;
                    //printf("op# %d taking from op# %d\n", i, n);
                }
            }
        }
    }
}

double AlgorithmProcessor::getAudibleSampleForGrid()
{
    double output = 0.0f;
    for(int i = 0; i < 6; ++i)
    {
        double thisSample = allOps[i]->getSample();
        if(allOps[i]->toOutput == false)
            output += thisSample;
    }
    return output;
}

void AlgorithmProcessor::setOutputsInLayerOrder()
{
    if(layer0 != nullptr)
    {
        layer0->lastOutputSample = layer0->getSample();
    }
    if(layer1 !=  nullptr)
    {
        layer1->lastOutputSample = layer1->getSample();
    }
    if(layer2 != nullptr)
    {
            layer2->lastOutputSample = layer2->getSample();
    }
    if(layer3 != nullptr)
    {
            layer3->lastOutputSample = layer3->getSample();
    }
    if(layer4 != nullptr)
    {
            layer4->lastOutputSample = layer4->getSample();
    }
    if(layer5 != nullptr)
    {
            layer5->lastOutputSample = layer5->getSample();
    }
}

void AlgorithmProcessor::endNote()
{
    for(int i = 0; i < 6; ++i)
    {
        allOps[i]->envelope.trigger = 0;
    }
}
