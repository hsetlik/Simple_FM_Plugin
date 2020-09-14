/*
  ==============================================================================

    AlgorithmSelectorComponent.cpp
    Created: 13 Sep 2020 9:48:03am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "AlgorithmSelectorComponent.h"
void AlgorithmDiagram::paint(juce::Graphics &g)
{
    switch(curAlg)
    {
        case alg1:
            paintAlg1(g);
            break;
        case alg2:
            paintAlg2(g);
            break;
    }
}

void AlgorithmDiagram::paintAlg1(juce::Graphics &g)
{
    int n = getHeight() / 18;
    g.fillAll(juce::Colours::whitesmoke);
    for(int i = 0; i < 6; ++i)
    {
        opBox[i].setSize(3 * n, 3 * n);
    }
    g.setColour(juce::Colours::seagreen);
    
    opBox[0].setX(7 * n);
    opBox[0].setY(n);
    
    opBox[1].setX(7 * n);
    opBox[1].setY(5 * n);
    
    opBox[2].setX(7 * n);
    opBox[2].setY(9 * n);
    
    opBox[3].setX(3 * n);
    opBox[3].setY(5 * n);
    
    opBox[4].setX(3 * n);
    opBox[4].setY(9 * n);
    
    opBox[5].setX(11 * n);
    opBox[5].setY(9 * n);
    
    for(int i = 0; i < 6; ++i)
    {
        g.setColour(juce::Colours::seagreen);
        g.fillRect(opBox[i]);
        g.setColour(juce::Colours::white);
        g.drawFittedText(juce::String(i + 1),opBox[i], juce::Justification::centred, 1, 0.0f);
    }
    g.setColour(juce::Colours::seagreen);
    
    juce::Rectangle<int> line1 = {8 * n, 4 * n, n, n};
    juce::Rectangle<int> line2 = {6 * n, 6 * n, n, n};
    juce::Rectangle<int> line3 = {4 * n, 8 * n, n, n};
    juce::Rectangle<int> line4 = {6 * n, 10 * n, n, n};
    juce::Rectangle<int> line5 = {10 * n, 10 * n, n, n};
    juce::Rectangle<int> line6 = {8 * n, 8 * n, n, n};
    
    g.fillRect(line1);
    g.fillRect(line2);
    g.fillRect(line3);
    g.fillRect(line4);
    g.fillRect(line5);
    g.fillRect(line6);
    printf("painted alg1\n");
}

void AlgorithmDiagram::paintAlg2(juce::Graphics &g)
{
    int n = getHeight() / 18;
    g.fillAll(juce::Colours::whitesmoke);
    for(int i = 0; i < 6; ++i)
    {
        opBox[i].setSize(3 * n, 3 * n);
    }
    g.setColour(juce::Colours::seagreen);
    
    opBox[0].setX(3 * n);
    opBox[0].setY(3 * n);
    
    opBox[1].setX(8 * n);
    opBox[1].setY(3 * n);
    
    opBox[2].setX(13 * n);
    opBox[2].setY(3 * n);
    
    opBox[3].setX(3 * n);
    opBox[3].setY(10 * n);
    
    opBox[4].setX(8 * n);
    opBox[4].setY(10 * n);
    
    opBox[5].setX(13 * n);
    opBox[5].setY(10 * n);
    
    for(int i = 0; i < 6; ++i)
    {
        g.setColour(juce::Colours::seagreen);
        g.fillRect(opBox[i]);
        g.setColour(juce::Colours::white);
        g.drawFittedText(juce::String(i + 1),opBox[i], juce::Justification::centred, 1, 0.0f);
    }
    g.setColour(juce::Colours::seagreen);
    
    juce::Rectangle<int> line1 = {6 * n, 4 * n, 2 * n, n};
    juce::Rectangle<int> line2 = {11 * n, 4 * n, 2 * n, n};
    juce::Rectangle<int> line3 = {4 * n, 6 * n, n, 4 * n};
    juce::Rectangle<int> line4 = {9 * n, 6 * n, n, 4 * n};
    juce::Rectangle<int> line5 = {14 * n, 6 * n, n, 4 * n};
    
    g.fillRect(line1);
    g.fillRect(line2);
    g.fillRect(line3);
    g.fillRect(line4);
    g.fillRect(line5);
    printf("painted alg2\n");
}

void AlgorithmDiagram::resized()
{

}



AlgorithmSelectorComponent::AlgorithmSelectorComponent() : diagram(AlgorithmDiagram::alg1)
{
    selectorKnob.setSliderStyle(juce::Slider::IncDecButtons);
    //int initAlg = (int)selectorKnob.getValue();
    
    selectorKnob.setRange(1.0, 2.0, 1.0);
    selectorKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    selectorKnob.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&selectorKnob);
    addAndMakeVisible(&diagram);
}

void AlgorithmSelectorComponent::resized()
{
    int n = getWidth() / 12;
    diagram.setBounds(n, n, 10 * n, 10 * n);
    selectorKnob.setBounds(4 * n, 11 * n, 4 * n, 4 * n);
}

