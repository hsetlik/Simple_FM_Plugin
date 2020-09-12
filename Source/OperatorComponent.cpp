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
    //setting up modulator source toggles
    for(int i = 0; i < 6; ++i)
    {
        modToggleButtons[i].setClickingTogglesState(true);
        modToggleButtons[i].setButtonText(juce::String(i + 1));
        modToggleButtons[i].changeWidthToFitText();
        modToggleButtons[i].setColour(modToggleButtons[i].buttonColourId, juce::Colours::lightgrey);
        modToggleButtons[i].setColour(modToggleButtons[i].buttonOnColourId, juce::Colours::lightgreen);
        modToggleButtons[i].addListener(buttonLstnr);
        addAndMakeVisible(&modToggleButtons[i]);
    }
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
    //setting up audio toggle button
    audioToggleButton.setClickingTogglesState(true);
    audioToggleButton.setButtonText("Audio");
    audioToggleButton.changeWidthToFitText();
    audioToggleButton.setColour(audioToggleButton.buttonColourId, juce::Colours::lightgrey);
    audioToggleButton.setColour(audioToggleButton.buttonOnColourId, juce::Colours::lightgreen);
    audioToggleButton.addListener(buttonLstnr);
    addAndMakeVisible(&audioToggleButton);
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
    modIndexSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    modIndexSlider.setRange(1.0f, 500.0f);
    modIndexSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    modIndexSlider.setValue(1.0);
    modIndexSlider.addListener(sliderLstnr);
    addAndMakeVisible(&modIndexSlider);
    modIndexSlider.setNumDecimalPlacesToDisplay(1);
}

void OperatorComponent::resized()
{
    int n = getHeight() / 18;
    modToggleButtons[0].setBounds(n, n, 2 * n, 2 * n);
    modToggleButtons[1].setBounds(n, 3 * n, 2 * n, 2 * n);
    modToggleButtons[2].setBounds(n, 5 * n, 2 * n, 2 * n);
    modToggleButtons[3].setBounds(n, 7 * n, 2 * n, 2 * n);
    modToggleButtons[4].setBounds(n, 9 * n, 2 * n, 2 * n);
    modToggleButtons[5].setBounds(n, 11 * n, 2 * n, 2 * n);
    
    aSlider.setBounds(4 * n, n, 4.5 * n, 4.5 * n);
    dSlider.setBounds(7 * n, n, 4.5 * n, 4.5 * n);
    sSlider.setBounds(10 * n, n, 4.5 * n, 4.5 * n);
    rSlider.setBounds(13 * n, n, 4.5 * n, 4.5 * n);
    
    audioToggleButton.setBounds(9 * n, 8 * n, 3 * n, 1.5 * n);
    
    ratioSlider.setBounds(4 * n, 6 * n, 5 * n, 5 * n);
    levelSlider.setBounds(12 * n, 6 * n, 5 * n, 5 * n);
    
    modIndexSlider.setBounds(2 * n, 14 * n, 13 * n, 2.5 * n);
}
