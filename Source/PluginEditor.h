/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OperatorComponent.h"

//==============================================================================
/**
*/
class HexFmAudioProcessorEditor  :
public juce::AudioProcessorEditor,
public juce::Slider::Listener,
public juce::Button::Listener
{
public:
    HexFmAudioProcessorEditor (HexFmAudioProcessor&);
    ~HexFmAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HexFmAudioProcessor& audioProcessor;
    std::vector<OperatorComponent*> OpComps;
    OperatorComponent op0;
    OperatorComponent op1;
    OperatorComponent op2;
    OperatorComponent op3;
    OperatorComponent op4;
    OperatorComponent op5;
    
    AlgorithmSelectorComponent algSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HexFmAudioProcessorEditor)
};
