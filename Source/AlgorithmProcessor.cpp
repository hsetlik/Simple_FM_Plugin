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

void AlgorithmProcessor::newNote(double fund)
{
    fundamental = fund;
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
           layer0 = allOps[0];
           layer1 = allOps[1];
           layer2 = allOps[3];
           layer3 = allOps[4];
           layer4 = allOps[2];
           layer5 = allOps[5];
       }
       case AlgorithmDiagram::alg2:
       {
         layer0 = allOps[0];
         layer1 = allOps[1];
         layer2 = allOps[3];
         layer3 = allOps[4];
         layer4 = allOps[2];
         layer5 = allOps[5];
       }
   }
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

float AlgorithmProcessor::getAudibleSampleForAlg()
{
    setOutputsInLayerOrder();
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