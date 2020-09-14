/*
  ==============================================================================

    AlgorithmSelectorComponent.h
    Created: 13 Sep 2020 9:48:03am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class AlgorithmDiagram : public juce::Component
{
public:
    enum algorithm
    {
      alg1,
      alg2
      
    };
    //functions
    AlgorithmDiagram(AlgorithmDiagram::algorithm algSetting)
    {
        currentAlg = algSetting;
    }
    ~AlgorithmDiagram() {}
    void paint(juce::Graphics& g) override;
    void resized() override;
    AlgorithmDiagram::algorithm currentAlg;
    juce::Rectangle<int> opBox[6];
};
class AlgorithmSelectorComponent : public juce::Component
{
public:
    //functions
    AlgorithmSelectorComponent();
    ~AlgorithmSelectorComponent() {}
    AlgorithmDiagram::algorithm currentAlg = AlgorithmDiagram::alg2;
    void setAlgorithm(AlgorithmDiagram::algorithm setting)
    {
        currentAlg = setting;
    }
    void resized() override;
    //child componenets
    juce::Slider selectorKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> selectorKnobAttach;
    AlgorithmDiagram diagram;
};
