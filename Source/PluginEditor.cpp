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
    //placing operator components
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
    //setting up attachments
    for(int i = 0; i < 6; ++i)
    {
        //string to append to each parameter name
        juce::String iStr = juce::String(i);
        //loop to attach mod toggle buttons
        for(int n = 0; n < 6; ++n)
        {
            juce::String nStr = juce::String(n);
            OpComps[i]->modToggleAttachments[n].reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.tree, "mod" + nStr + "op" + iStr + "Param", OpComps[i]->modToggleButtons[i]));
        }
        //attaching audio toggle
        OpComps[i]->audioToggleAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(audioProcessor.tree, "audioToggleParam" + iStr, OpComps[i]->audioToggleButton));
        //attaching envelope parameters
        OpComps[i]->aSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "aParam" + iStr, OpComps[i]->aSlider));
        OpComps[i]->dSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "dParam" + iStr, OpComps[i]->dSlider));
        OpComps[i]->sSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "sParam" + iStr, OpComps[i]->sSlider));
        OpComps[i]->rSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "rParam" + iStr, OpComps[i]->rSlider));
        //attach index slider
        OpComps[i]->modIndexSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "modIndexParam" + iStr, OpComps[i]->modIndexSlider));
        //attach ratio slider
        OpComps[i]->ratioSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "ratioParam" + iStr, OpComps[i]->ratioSlider));
        //attach level slider
        OpComps[i]->levelSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "levelParam" + iStr, OpComps[i]->levelSlider));
    }
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
