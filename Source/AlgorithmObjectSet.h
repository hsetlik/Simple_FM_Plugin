/*
  ==============================================================================

    AlgorithmObjectSet.h
    Created: 14 Sep 2020 8:13:24am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AlgorithmDisplay : public juce::Component //make overrides of this for each algorithm
{
public:
    AlgorithmDisplay();
    ~AlgorithmDisplay() {}
    int algIdIndex;
    void paint(juce::Graphics& g) override
    {
        
    }
    juce::Rectangle<int> opBox[6];
};

