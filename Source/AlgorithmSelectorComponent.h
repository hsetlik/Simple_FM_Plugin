/*
  ==============================================================================

    AlgorithmSelectorComponent.h
    Created: 13 Sep 2020 9:48:03am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AlgorithmObjectSet.h"


class AlgorithmDiagramSet : public juce::Component
{
public:
    //functions
    AlgorithmDiagramSet()
    {
      
    }
    ~AlgorithmDiagramSet() {}
    void paint(juce::Graphics& g) override;
    void paintAlg1(juce::Graphics& g);
    void paintAlg2(juce::Graphics& g);
    void resized() override;
    int currentAlgIndex = 1; //setting the default algorithm to 1
    juce::Rectangle<int> opBox[6];
};
class AlgorithmSelectorComponent : public juce::Component
{
public:
    //functions
    AlgorithmSelectorComponent();
    ~AlgorithmSelectorComponent() {}
    void resized() override;
    //child componenets
    juce::Slider selectorKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> selectorKnobAttach;
    AlgorithmDiagramSet diagram;
};
