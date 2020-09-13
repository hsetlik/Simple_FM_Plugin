/*
  ==============================================================================

    OperatorComponent.cpp
    Created: 11 Sep 2020 9:39:17pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "OperatorComponent.h"


OperatorComponent::OperatorComponent(int index, juce::Slider::Listener* sLstnr, juce::Button::Listener* bLstnr)
{
    OpComponentIndex = index;
    sliderLstnr = sLstnr;
    buttonLstnr = bLstnr;
    //setting up envelope knobs
    aSlider.setSliderStyle(juce::Slider::Rotary);
    aSlider.setRange(1.0f, 5000.0);
    aSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    aSlider.setValue(1.0);
    aSlider.addListener(sliderLstnr);
    addAndMakeVisible(&aSlider);
    aSlider.setNumDecimalPlacesToDisplay(1);
    
    dSlider.setSliderStyle(juce::Slider::Rotary);
    dSlider.setRange(1.0f, 5000.0);
    dSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    dSlider.setValue(1.0);
    dSlider.addListener(sliderLstnr);
    addAndMakeVisible(&dSlider);
    dSlider.setNumDecimalPlacesToDisplay(1);
    
    sSlider.setSliderStyle(juce::Slider::Rotary);
    sSlider.setRange(0.0f, 1.0f);
    sSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    sSlider.setValue(1.0);
    sSlider.addListener(sliderLstnr);
    addAndMakeVisible(&sSlider);
    sSlider.setNumDecimalPlacesToDisplay(1);
    
    rSlider.setSliderStyle(juce::Slider::Rotary);
    rSlider.setRange(1.0f, 5000.0);
    rSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    rSlider.setValue(1.0);
    rSlider.addListener(sliderLstnr);
    addAndMakeVisible(&rSlider);
    rSlider.setNumDecimalPlacesToDisplay(1);
    
    //setting up ratio slider
    ratioSlider.setSliderStyle(juce::Slider::Rotary);
    ratioSlider.setRange(-10.0f, 10.0f);
    ratioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    ratioSlider.setValue(1.0);
    ratioSlider.addListener(sliderLstnr);
    addAndMakeVisible(&ratioSlider);
    ratioSlider.setNumDecimalPlacesToDisplay(1);
    //setting up level slider
    levelSlider.setSliderStyle(juce::Slider::Rotary);
    levelSlider.setRange(0.0f, 1.0f);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    levelSlider.setValue(1.0);
    levelSlider.addListener(sliderLstnr);
    addAndMakeVisible(&levelSlider);
    levelSlider.setNumDecimalPlacesToDisplay(1);
    //setting up index slider
    modIndexSlider.setSliderStyle(juce::Slider::Rotary);
    modIndexSlider.setRange(1.0f, 500.0f);
    modIndexSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    modIndexSlider.setValue(1.0);
    modIndexSlider.addListener(sliderLstnr);
    addAndMakeVisible(&modIndexSlider);
    modIndexSlider.setNumDecimalPlacesToDisplay(1);
}

void OperatorComponent::resized()
{
    int n = getWidth() / 12;
    
    aSlider.setBounds(8 * n, n, 4 * n, 4 * n);
    dSlider.setBounds(8 * n, 5 * n, 4 * n, 4 * n);
    sSlider.setBounds(8 * n, 9 * n, 4 * n, 4 * n);
    rSlider.setBounds(8 * n, 13 * n, 4 * n, 4 * n);
    
    ratioSlider.setBounds(n, n, 5 * n, 5 * n);
    modIndexSlider.setBounds(n, 7 * n, 5 * n, 5 * n);
    levelSlider.setBounds(n, 12 * n, 5 * n, 5 * n);
}
