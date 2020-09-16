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
        int sixth = getParentWidth() / 6;
        setBounds(x * sixth, y * sixth, sixth, sixth);
        buttonBounds = (getBounds().reduced(3));
        auto bX = buttonBounds.getX();
        auto bY = buttonBounds.getY();
        auto bWidth = buttonBounds.getWidth();
        auto bHeight = buttonBounds.getHeight();
        printf("button Bounds: %d, %d, %d, %d\n", bX, bY, bWidth, bHeight);
        setOnColours(onColor, onColor, onColor);
        shouldUseOnColours(true);
         printf("button Bounds 2: %d, %d, %d, %d\n", bX, bY, bWidth, bHeight);
        
        xPos = x;
        yPos = y;
    }
    ~ModButton() {}
    void resized() override
    {
    }
    void paintButton(juce::Graphics& g, bool mouseOver, bool isMouseDown) override
    {
        juce::Colour buttonColor;
        if(getToggleState())
            buttonColor = juce::Colours::lightseagreen;
        else
            buttonColor = juce::Colours::lightslategrey;
        g.setColour(buttonColor);
        juce::Rectangle<int> buttonArea = getBounds().reduced(5);
        g.fillRect(buttonArea);
    }
    
    int xPos;
    int yPos;
    juce::Path buttonShapePath;
    juce::Rectangle<int> buttonBounds;
    juce::Colour onColor = juce::Colours::lightseagreen;
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
                addAndMakeVisible(newButton);
                newInnerArray->add(newButton);
            }
            outerButtons.add(newInnerArray);
        }
        //setBoundsRelative(0.0f, 0.0f, 0.1f, 0.1f);
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
                button->setClickingTogglesState(true);
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
                button->paintButton(g, false, false);
            }
        }
    }
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> buttonAttachments[6][6];
    juce::OwnedArray<juce::OwnedArray<ModButton>> outerButtons;
};


