/*
  ==============================================================================

    LevelMeter.h
    Created: 16 Sep 2020 7:28:48pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"

class MeterSource
{
public:
    MeterSource(float* source)
    {
        sourceLevel = source;
    }
    ~MeterSource() {}
    float getCurrentSample()
    {
        return *sourceLevel;
    }
    float* sourceLevel;
 
};
class HorizontalLevelMeter : public juce::Component, public juce::Timer
{
public:
    HorizontalLevelMeter()
    {
        juce::Rectangle<int> localBounds = getBounds();
        xPos = localBounds.getX();
        yPos = localBounds.getY();
        width = localBounds.getWidth();
        height = localBounds.getHeight();
        
        addAndMakeVisible(&meterBox);
        addAndMakeVisible(&meterContent);
        
        meterBox.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
        meterContent.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
        
        printf("MB xPos: %d\n", meterBox.getX());
        printf("MB yPos: %d\n", meterBox.getY());
        printf("MB width: %d\n", meterBox.getWidth());
        printf("MB height: %d\n", meterBox.getHeight());
        
        startTimerHz(24);
    }
    ~HorizontalLevelMeter() {}
    void resized() override
    {
      meterBox.setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    }
    void paint(juce::Graphics& g) override
    {
        g.setColour(meterBoxColor);
        g.fillRect(meterBox.getBounds());
        g.setColour(meterContentColor);
        g.fillRect(meterContent.getBounds());
    }
    void attach(MeterSource* source)
    {
        levelSource = source;
        //sourceBlockAverages = &levelSource->blockAverages;
    }
    void timerCallback() override
    {
        
    }
    void adjustRectToLevel(float level)
    {
        meterContent.setBoundsRelative(0.0f, 0.0f,  1.5f * level, 1.0f);
    }
    int xPos, yPos, width, height;
    MeterSource* levelSource;
    juce::Component meterBox;
    juce::Component meterContent;
    juce::Colour meterBoxColor = juce::Colours::darkslategrey;
    juce::Colour meterContentColor = juce::Colours::orange;
};
