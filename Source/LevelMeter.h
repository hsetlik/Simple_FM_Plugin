/*
  ==============================================================================

    LevelMeter.h
    Created: 16 Sep 2020 7:28:48pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class MeterSource
{
public:
    MeterSource(juce::AudioBuffer<float>* sourceBuffer)
    {
        lastBlockSum = 0.0f;
        buffer = sourceBuffer;
        blockSize = buffer->getNumSamples();
    }
    ~MeterSource() {}
    void updateSize()
    {
        blockSize = buffer->getNumSamples();
    }
    void addSampleToSum(float sampleToAdd)
    {
        lastBlockSum += 10 * (fabs(sampleToAdd));
        if(fabs(sampleToAdd) > 0)
            printf("Greater than Zero\n");
    }
    void addBlockAverage()
    {
        float avg = lastBlockSum / blockSize;
        if(avg > 0.1)
            printf("nonzero average\n");
        blockAverages.push_back(avg);
        lastBlockSum = 0.0f;
        printf("block# %lu: %f\n", blockAverages.size(), avg);
    }
    
    juce::AudioBuffer<float>* buffer;
    int blockSize;
    long double lastBlockSum;
    std::vector<float> blockAverages;
    
};

class HorizontalLevelMeter : public juce::Component, public juce::Timer
{
public:
    HorizontalLevelMeter(int x, int y, int w, int h)
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
        
        
        startTimerHz(24);
        printf("MB xPos: %d\n", meterBox.getX());
        printf("MB yPos: %d\n", meterBox.getY());
        printf("MB width: %d\n", meterBox.getWidth());
        printf("MB height: %d\n", meterBox.getHeight());
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
        sourceBlockAverages = &levelSource->blockAverages;
    }
    void adjustRectToLevel(float level)
    {
        meterContent.setBoundsRelative(0.0f, 0.0f,  1.5f * level, 1.0f);
    }
    float getAvgOfBlocks()
    {
        auto numBlocks = sourceBlockAverages->size();
        std::vector<float> blockCopy;
        long double blockSum = 0.0f;
        for(int i = 0; i < numBlocks; ++i)
        {
            blockCopy.push_back(sourceBlockAverages->at(i));
            blockSum += blockCopy.back();
        }
        float newAvg = (float)(blockSum / numBlocks);
        printf("Block Sum: %Lf\n", blockSum);
        return newAvg;
    }
    void timerCallback() override
    {
        adjustRectToLevel(getAvgOfBlocks());
        sourceBlockAverages->clear();
        //repaint();
    }
    int xPos, yPos, width, height;
    MeterSource* levelSource;
    juce::Component meterBox;
    juce::Component meterContent;
    std::vector<float>* sourceBlockAverages;
    juce::Colour meterBoxColor = juce::Colours::darkslategrey;
    juce::Colour meterContentColor = juce::Colours::orange;
};
