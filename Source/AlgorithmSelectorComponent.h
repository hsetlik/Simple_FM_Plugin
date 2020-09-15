/*
  ==============================================================================

    AlgorithmSelectorComponent.h
    Created: 13 Sep 2020 9:48:03am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#define TotalAlgorithms 6



class AlgorithmDiagramSet : public juce::Component
{
public:
    //functions
    AlgorithmDiagramSet()
    {
      
    }
    ~AlgorithmDiagramSet() {}
    void paint(juce::Graphics& g) override;
    void paintAlg1(juce::Graphics& g);
    void paintAlg2(juce::Graphics& g);
    void paintAlg3(juce::Graphics& g);
    void paintAlg4(juce::Graphics& g);
    void paintAlg5(juce::Graphics& g);
    void paintAlg6(juce::Graphics& g);
    void resized() override;
    int currentAlgIndex = 1; //setting the default algorithm to 1
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
    AlgorithmDiagramSet diagram;
};

class ModButton : public juce::ShapeButton
{
public:
    ModButton(int x, int y) : juce::ShapeButton("Button" + juce::String(x) + juce::String(y), juce::Colours::lightslategrey, juce::Colours::lightslategrey, juce::Colours::lightslategrey)
    {
        buttonShapePath.startNewSubPath(0.0f, 0.0f);
        buttonShapePath.addEllipse(0.0f, 0.0f, (float)getWidth(), (float)getHeight());
        buttonShapePath.closeSubPath();
        auto onColor = juce::Colours::lightseagreen;
        setOnColours(onColor, onColor, onColor);
        shouldUseOnColours(true);
        setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
        
        xPos = x;
        yPos = y;
    }
    ~ModButton() {}
    void resized() override
    {
     setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    }
    void paintButton(juce::Graphics& g, bool mouseOver, bool isMouseDown) override
    {
        juce::Colour buttonColor;
        if(getToggleState())
            buttonColor = juce::Colours::lightslategrey;
        else
            buttonColor = juce::Colours::lightseagreen;
        g.setColour(buttonColor);
        g.fillPath(buttonShapePath);
        g.fillAll();
    }
    
    int xPos;
    int yPos;
    juce::Path buttonShapePath;
};

class ModulationGrid : public juce::Component
{
public:
    ModulationGrid()
    {
        //creating the ModButton objects
        for(int i = 0; i < 6; ++i)
        {
            juce::OwnedArray<ModButton> * newInnerArray = new juce::OwnedArray<ModButton>;
            for(int n = 0; n < 6; ++n)
            {
                ModButton* newButton = new ModButton(i, n);
                newInnerArray->add(newButton);
            }
            outerButtons.add(newInnerArray);
        }
        
    }
    ~ModulationGrid() {}
    void resized() override
    {
        int sixth = getWidth() / 6;
        for(int i = 0; i < 6; ++i)
        {
            juce::OwnedArray<ModButton> * thisInnerArray = outerButtons.getUnchecked(i);
            for(int n = 0; n < 6; ++n)
            {
                ModButton* button = thisInnerArray->getUnchecked(n);
                button->setBounds(i * sixth, n * sixth, sixth, sixth);
            }
        }
    }
    void paint(juce::Graphics&g) override
    {
        for(int i = 0; i < 6; ++i)
        {
           juce::OwnedArray<ModButton> * thisInnerArray = outerButtons.getUnchecked(i);
            for(int n = 0; n < 6; ++n)
            {
                ModButton* button = thisInnerArray->getUnchecked(n);
                button->paintButton(g, true, true);
            }
        }
    }
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachments[6][6];
    juce::OwnedArray<juce::OwnedArray<ModButton>> outerButtons;
};


