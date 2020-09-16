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
    audioTogggleButton.setButtonText("Output");
    audioTogggleButton.setClickingTogglesState(true);
    audioTogggleButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkslategrey);
    audioTogggleButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::lightseagreen);
    addAndMakeVisible(&audioTogggleButton);
    
    aSlider.setSliderStyle(juce::Slider::Rotary);
    aSlider.setRange(1.0f, 5000.0);
    aSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    aSlider.setValue(15.0);
    aSlider.addListener(sliderLstnr);
    addAndMakeVisible(&aSlider);
    aSlider.setNumDecimalPlacesToDisplay(1);
    aSlider.setSkewFactorFromMidPoint(25.0);
    
    addAndMakeVisible(aSliderLabel);
    aSliderLabel.attachToComponent(&aSlider, true);
    aSliderLabel.setText("A: " + aSlider.getTextFromValue(aSlider.getValue()), juce::dontSendNotification);
    
    dSlider.setSliderStyle(juce::Slider::Rotary);
    dSlider.setRange(1.0f, 5000.0);
    dSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    dSlider.setValue(20.0);
    dSlider.addListener(sliderLstnr);
    addAndMakeVisible(&dSlider);
    dSlider.setNumDecimalPlacesToDisplay(1);
    dSlider.setSkewFactorFromMidPoint(60.0);
    addAndMakeVisible(dSliderLabel);
    dSliderLabel.attachToComponent(&dSlider, true);
    dSliderLabel.setText("D: " + dSlider.getTextFromValue(dSlider.getValue()), juce::dontSendNotification);
    
    sSlider.setSliderStyle(juce::Slider::Rotary);
    sSlider.setRange(0.0f, 1.0f);
    sSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    sSlider.setValue(0.6);
    sSlider.addListener(sliderLstnr);
    addAndMakeVisible(&sSlider);
    sSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(sSliderLabel);
    sSliderLabel.attachToComponent(&sSlider, true);
    sSliderLabel.setText("S: " + sSlider.getTextFromValue(sSlider.getValue()), juce::dontSendNotification);
    
    rSlider.setSliderStyle(juce::Slider::Rotary);
    rSlider.setRange(1.0f, 5000.0);
    rSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    rSlider.setValue(100.0);
    rSlider.addListener(sliderLstnr);
    rSlider.setSkewFactorFromMidPoint(200.0);
    addAndMakeVisible(&rSlider);
    rSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(rSliderLabel);
    rSliderLabel.attachToComponent(&rSlider, true);
    rSliderLabel.setText("R: " + rSlider.getTextFromValue(rSlider.getValue()), juce::dontSendNotification);
    //setting up ratio slider
    ratioSlider.setSliderStyle(juce::Slider::Rotary);
    
    juce::Range<double> rRange( -10.0f, 10.0f);
    ratioSlider.setRange(rRange, 1.0f);
    ratioSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    ratioSlider.setValue(1.0);
    ratioSlider.addListener(sliderLstnr);
    //addAndMakeVisible(&ratioSlider);
    ratioSlider.setNumDecimalPlacesToDisplay(1);
    //addAndMakeVisible(ratioLabel);
    auto rLabelStr1 = ratioSlider.getTextFromValue(ratioSlider.getValue());
    auto rLabelStr2 = rLabelStr1.substring(0, 4);
    ratioLabel.setText("Ratio: " + rLabelStr2, juce::dontSendNotification);
    ratioLabel.setColour(ratioLabel.textColourId, juce::Colours::lightslategrey);
    ratioLabel.setJustificationType(juce::Justification::centred);
    
    //setting up level slider
    levelSlider.setSliderStyle(juce::Slider::Rotary);
    levelSlider.setRange(0.0f, 1.0f);
    levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    levelSlider.setValue(1.0);
    levelSlider.addListener(sliderLstnr);
    addAndMakeVisible(&levelSlider);
    levelSlider.setNumDecimalPlacesToDisplay(1);
    
    addAndMakeVisible(levelLabel);
    auto lLabelStr1 = levelSlider.getTextFromValue(levelSlider.getValue());
    auto lLabelStr2 = lLabelStr1.substring(0, 4);
    levelLabel.setText("Level: " + lLabelStr2, juce::dontSendNotification);
    levelLabel.setColour(levelLabel.textColourId, juce::Colours::lightslategrey);
    levelLabel.setJustificationType(juce::Justification::centred);
    //setting up index slider
    modIndexSlider.setSliderStyle(juce::Slider::Rotary);
    modIndexSlider.setRange(1.0f, 500.0f);
    modIndexSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    modIndexSlider.setSkewFactorFromMidPoint(150.0f);
    modIndexSlider.setValue(1.0);
    modIndexSlider.addListener(sliderLstnr);
    
    addAndMakeVisible(indexLabel);
    auto iLabelStr1 = modIndexSlider.getTextFromValue(modIndexSlider.getValue());
    auto iLabelStr2 = iLabelStr1.substring(0, 4);
    indexLabel.setText("Mod Index: " + iLabelStr2, juce::dontSendNotification);
    indexLabel.setColour(indexLabel.textColourId, juce::Colours::lightslategrey);
    indexLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(&modIndexSlider);
    modIndexSlider.setNumDecimalPlacesToDisplay(1);
    
    addAndMakeVisible(ratioNumSlider);
    ratioNumSlider.setSliderStyle(juce::Slider::IncDecButtons);
    ratioNumSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    ratioNumSlider.setRange(1, 15, 1);
    
    addAndMakeVisible(ratioDenSlider);
    ratioDenSlider.setSliderStyle(juce::Slider::IncDecButtons);
    ratioDenSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    ratioDenSlider.setRange(1, 15, 1);
}

void OperatorComponent::paint(juce::Graphics &g)
{
    int n = getWidth() / 12;
    juce::Rectangle<int> numberLabel;
    numberLabel.setBounds(5.5 * n, 14 * n, 4 * n, 6 * n);
    g.setColour(juce::Colours::whitesmoke);
    auto newFont = juce::Font("Futura", 2.6 * n, juce::Font::bold | juce::Font::italic);
    g.setFont(newFont);
    g.setColour(juce::Colours::lightseagreen);
    auto labelString = juce::String(OpComponentIndex + 1);
    g.drawText(labelString, numberLabel, juce::Justification::centred, false);
    
    /*
    juce::Rectangle<int> levelBar;
    auto currentScale = *barLevel;
    levelBar.setBounds(n / 2, 16 * n, 6 * n * currentScale, n);
    g.fillRect(levelBar);
     */
}

void OperatorComponent::resized()
{
    int n = getWidth() / 12;
    
    audioTogggleButton.setBounds(5.2 * n, (int)0.95 * n, (int)3.5 * n, (int)1.75 * n);
    
    aSlider.setBounds(8 * n, n, 4 * n, 4 * n);
    dSlider.setBounds(8 * n, 5 * n, 4 * n, 4 * n);
    sSlider.setBounds(8 * n, 9 * n, 4 * n, 4 * n);
    rSlider.setBounds(8 * n, 13 * n, 4 * n, 4 * n);
    
    ratioLabel.setBounds(n / 3, n / 10, 5 * n,  n);
    ratioSlider.setBounds(n, n, 4 * n, 4 * n);
    ratioNumSlider.setBounds(n, n / 3, 4 * n, 2.5 * n);
    ratioDenSlider.setBounds(n, 3 * n, 4 * n, 2.5 * n);
    
    indexLabel.setBounds(n / 3, 5.5 * n, 5 * n, 2 * n);
    modIndexSlider.setBounds(n, 7 * n, 4 * n, 4 * n);
    
    levelLabel.setBounds(n / 3, 11 * n, 5 * n, n);
    levelSlider.setBounds(n, 12 * n, 4 * n, 4 * n);
}
