/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HexFmAudioProcessorEditor::HexFmAudioProcessorEditor (HexFmAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
op0(0, this, this),
op1(1, this, this),
op2(2, this, this),
op3(3, this, this),
op4(4, this, this),
op5(5, this, this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    addAndMakeVisible(&op0);
    addAndMakeVisible(&op1);
    addAndMakeVisible(&op2);
    addAndMakeVisible(&op3);
    addAndMakeVisible(&op4);
    addAndMakeVisible(&op5);
    
    OpComps.push_back(&op0);
    OpComps.push_back(&op1);
    OpComps.push_back(&op2);
    OpComps.push_back(&op3);
    OpComps.push_back(&op4);
    OpComps.push_back(&op5);
}

HexFmAudioProcessorEditor::~HexFmAudioProcessorEditor()
{
}

//==============================================================================
void HexFmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void HexFmAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int thirdW = getWidth() / 3;
    int halfH = getHeight() / 2;
    
    op0.setBounds(0, 0, thirdW, halfH);
    op1.setBounds(thirdW, 0, thirdW, halfH);
    op2.setBounds(2 * thirdW, 0, thirdW, halfH);
    op3.setBounds(0, halfH, thirdW, halfH);
    op4.setBounds(thirdW, halfH, thirdW, halfH);
    op5.setBounds(2 * thirdW, halfH, thirdW, halfH);
    
}

void HexFmAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    printf("slider changed\n");
}

void HexFmAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    printf("button clicked\n");
}
