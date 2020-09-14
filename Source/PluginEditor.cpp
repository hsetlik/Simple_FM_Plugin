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
    
    addAndMakeVisible(&algSelector);
    algSelector.selectorKnob.addListener(this);
    
    algSelector.selectorKnobAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "algorithmParam", algSelector.selectorKnob));
    
    for(int i = 0; i < 6; ++i)
    {
        juce::String iStr = juce::String(i);
        OpComps[i]->aSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attackParam" + iStr,
        OpComps[i]->aSlider));
        
        OpComps[i]->dSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "decayParam" + iStr,
        OpComps[i]->dSlider));
        
        OpComps[i]->sSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "sustainParam" + iStr,
        OpComps[i]->sSlider));
        
        OpComps[i]->rSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "releaseParam" + iStr,
        OpComps[i]->rSlider));
        
        OpComps[i]->modIndexSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "modIndexParam" + iStr,
        OpComps[i]->modIndexSlider));
        
        OpComps[i]->ratioSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "ratioParam" + iStr,
        OpComps[i]->ratioSlider));
        
        OpComps[i]->levelSliderAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "levelParam" + iStr,
        OpComps[i]->levelSlider));
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
    int quarterW = getWidth() / 4;
    int halfH = getHeight() / 2;
    
    op0.setBounds(0, 0, quarterW, halfH);
    op1.setBounds(quarterW, 0, quarterW, halfH);
    op2.setBounds(2 * quarterW, 0, quarterW, halfH);
    algSelector.setBounds(3 * quarterW, 0, quarterW, halfH);
    op3.setBounds(0, halfH, quarterW, halfH);
    op4.setBounds(quarterW, halfH, quarterW, halfH);
    op5.setBounds(2 * quarterW, halfH, quarterW, halfH);
    
}

void HexFmAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &algSelector.selectorKnob)
    {
        algSelector.selectorKnob.setRange(1.0, 2.0, 1.0);
        auto aStr = algSelector.selectorKnob.getTextFromValue(algSelector.selectorKnob.getValue());
        float fValue = algSelector.selectorKnob.getValue();
        algSelector.selectorKnob.setNumDecimalPlacesToDisplay(0);
        //algSelector.selectorKnob.setRange(1.0f, 2.0f, 1.0f);
        int iValue = (int)fValue;
        if(iValue == 1)
        {
            audioProcessor.thisVoice->proc.procAlgIndex = 1;
            algSelector.selectorKnob.setValue(1);
        }
        else if(iValue > 1)
        {
            audioProcessor.thisVoice->proc.procAlgIndex = 2;
            algSelector.selectorKnob.setValue(2);
        }
        algSelector.diagram.repaint();
        
    }
    for(int i = 0; i < 6; ++i)
    {
        if(slider == &OpComps[i]->aSlider)
        {
            auto aFlt = OpComps[i]->aSlider.getValue();
            int strLen;
            if(aFlt < 10)
                strLen = 2;
            else if(aFlt < 100)
                strLen = 2;
            else if(aFlt < 1000)
                strLen = 3;
            else
                strLen = 4;
            auto aStr = OpComps[i]->aSlider.getTextFromValue(OpComps[i]->aSlider.getValue()).substring(0, strLen);
            OpComps[i]->aSliderLabel.setText("A: "+ aStr, juce::dontSendNotification);
        }
        else if(slider == &OpComps[i]->dSlider)
        {
            auto aFlt = OpComps[i]->dSlider.getValue();
            int strLen;
            if(aFlt < 10)
                strLen = 2;
            else if(aFlt < 100)
                strLen = 2;
            else if(aFlt < 1000)
                strLen = 3;
            else
                strLen = 4;
            auto aStr = OpComps[i]->dSlider.getTextFromValue(OpComps[i]->dSlider.getValue()).substring(0, strLen);
            OpComps[i]->dSliderLabel.setText("D: "+ aStr, juce::dontSendNotification);
        }
        else if(slider == &OpComps[i]->sSlider)
        {
            printf("sustain slider moved\n");
            auto aFlt = OpComps[i]->sSlider.getValue();
            int strLen;
            if(aFlt < 10)
                strLen = 3;
            else if(aFlt < 100)
                strLen = 2;
            else if(aFlt < 1000)
                strLen = 3;
            else
                strLen = 4;
            auto aStr = OpComps[i]->sSlider.getTextFromValue(OpComps[i]->sSlider.getValue()).substring(0, strLen);
            OpComps[i]->sSliderLabel.setText("S: "+ aStr, juce::dontSendNotification);
            
        }
        else if(slider == &OpComps[i]->rSlider)
        {
            auto aFlt = OpComps[i]->rSlider.getValue();
            int strLen;
            if(aFlt < 10)
                strLen = 2;
            else if(aFlt < 100)
                strLen = 2;
            else if(aFlt < 1000)
                strLen = 3;
            else
                strLen = 4;
            auto aStr = OpComps[i]->rSlider.getTextFromValue(OpComps[i]->rSlider.getValue()).substring(0, strLen);
            OpComps[i]->rSliderLabel.setText("R: "+ aStr, juce::dontSendNotification);
            
        }
        else if(slider == &OpComps[i]->ratioSlider)
        {
            printf("ratio slider moved\n");
            auto aFlt = OpComps[i]->ratioSlider.getValue();
            int strLen;
            if(aFlt < 1)
                strLen = 4;
            else if(aFlt < 10)
                strLen = 3;
            else if(aFlt < 100)
                strLen = 4;
            else if(aFlt < 1000)
                strLen = 4;
            else
                strLen = 5;
            auto aStr = OpComps[i]->ratioSlider.getTextFromValue(OpComps[i]->ratioSlider.getValue()).substring(0, strLen);
            OpComps[i]->ratioLabel.setText("Ratio: " + aStr, juce::dontSendNotification);
        }
        else if(slider == &OpComps[i]->modIndexSlider)
        {
            auto aFlt = OpComps[i]->modIndexSlider.getValue();
            int strLen;
            if(aFlt < 10)
                strLen = 3;
            else if(aFlt < 100)
                strLen = 3;
            else if(aFlt < 1000)
                strLen = 4;
            else
                strLen = 5;
            auto aStr = OpComps[i]->modIndexSlider.getTextFromValue(aFlt).substring(0, aFlt);
            OpComps[i]->indexLabel.setText("Mod Index: " + aStr, juce::dontSendNotification);
            
        }
        else if(slider == &OpComps[i]->levelSlider)
        {
            auto aFlt = OpComps[i]->levelSlider.getValue();
            int strLen = 0;
            if(aFlt < 10)
                strLen = 3;
            auto aStr = OpComps[i]->levelSlider.getTextFromValue(aFlt).substring(0, strLen);
            OpComps[i]->levelLabel.setText("Level: " + aStr, juce::dontSendNotification);
            
        }
    }
    
        
}

void HexFmAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    printf("button clicked\n");
}
