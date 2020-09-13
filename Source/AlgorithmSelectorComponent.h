/*
  ==============================================================================

    AlgorithmSelectorComponent.h
    Created: 13 Sep 2020 9:48:03am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
enum algorithm
{
  alg1,
  alg2
  
};

class AlgorithmDiagram : public juce::Component
{
public:
    //functions
    AlgorithmDiagram(algorithm algSetting)
    {
        currentAlg = algSetting;
    }
    ~AlgorithmDiagram() {}
    void paint(juce::Graphics& g) override;
    void resized() override;
    algorithm currentAlg;
    juce::Rectangle<int> opBox[6];
};
class AlgorithmSelectorComponent : public juce::Component
{
public:
    //functions
    AlgorithmSelectorComponent();
    ~AlgorithmSelectorComponent() {}
    algorithm currentAlg = alg1;
    void resized() override;
    //child componenets
    juce::Slider selectorKnob;
    AlgorithmDiagram diagram;
    
};
