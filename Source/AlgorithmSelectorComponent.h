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
        curAlg = algSetting;
    }
    ~AlgorithmDiagram() {}
    void paint(juce::Graphics& g) override;
    void paintAlg1(juce::Graphics& g);
    void paintAlg2(juce::Graphics& g);
    void resized() override;
    AlgorithmDiagram::algorithm curAlg = alg2; //setting the default algorithm to 1
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
    AlgorithmDiagram diagram;
};
