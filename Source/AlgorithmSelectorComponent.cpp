/*
  ==============================================================================

    AlgorithmSelectorComponent.cpp
    Created: 13 Sep 2020 9:48:03am
    Author:  Hayden Setlik

  ==============================================================================
*/


#include "AlgorithmSelectorComponent.h"
void AlgorithmDiagramSet::paint(juce::Graphics &g)
{
    if(currentAlgIndex == 1)
        paintAlg1(g);
    else if(currentAlgIndex == 2)
        paintAlg2(g);
    else if(currentAlgIndex == 3)
        paintAlg3(g);
    else if(currentAlgIndex == 4)
        paintAlg4(g);
    else if(currentAlgIndex == 5)
        paintAlg5(g);
    else if(currentAlgIndex == 6)
        paintAlg6(g);
}

void AlgorithmDiagramSet::paintAlg1(juce::Graphics &g)
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

void AlgorithmDiagramSet::paintAlg2(juce::Graphics &g)
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

void AlgorithmDiagramSet::paintAlg3(juce::Graphics &g)
{
    int n = getHeight() / 18;
    g.fillAll(juce::Colours::whitesmoke);
    for(int i = 0; i < 6; ++i)
    {
        opBox[i].setSize(3 * n, 3 * n);
    }
    g.setColour(juce::Colours::seagreen);
    
    opBox[0].setX(3 * n);
    opBox[0].setY(n);
    
    opBox[1].setX(3 * n);
    opBox[1].setY(5 * n);
    
    opBox[2].setX(3 * n);
    opBox[2].setY(9 * n);
    
    opBox[3].setX(3 * n);
    opBox[3].setY(13 * n);
    
    opBox[4].setX(7 * n);
    opBox[4].setY(13 * n);
    
    opBox[5].setX(11 * n);
    opBox[5].setY(13 * n);
    
    for(int i = 0; i < 6; ++i)
    {
        g.setColour(juce::Colours::seagreen);
        g.fillRect(opBox[i]);
        g.setColour(juce::Colours::white);
        g.drawFittedText(juce::String(i + 1),opBox[i], juce::Justification::centred, 1, 0.0f);
    }
    g.setColour(juce::Colours::seagreen);
    
    juce::Rectangle<int> line1 = {4 * n, 4 * n, n, n};
    juce::Rectangle<int> line2 = {4 * n, 8 * n, n, n};
    juce::Rectangle<int> line3 = {4 * n, 12 * n, n, n};
    juce::Rectangle<int> line4 = {6 * n, 14 * n, n, n};
    juce::Rectangle<int> line5 = {10 * n, 14 * n, n, n};
    
    g.fillRect(line1);
    g.fillRect(line2);
    g.fillRect(line3);
    g.fillRect(line4);
    g.fillRect(line5);
    printf("painted alg2\n");
}

void AlgorithmDiagramSet::paintAlg4(juce::Graphics &g)
{
    int n = getHeight() / 18;
    g.fillAll(juce::Colours::whitesmoke);
    for(int i = 0; i < 6; ++i)
    {
        opBox[i].setSize(3 * n, 3 * n);
    }
    g.setColour(juce::Colours::seagreen);
    
    opBox[0].setX(5 * n);
    opBox[0].setY(3 * n);
    
    opBox[1].setX(10 * n);
    opBox[1].setY(3 * n);
    
    opBox[2].setX(5 * n);
    opBox[2].setY(7 * n);
    
    opBox[3].setX(10 * n);
    opBox[3].setY(7 * n);
    
    opBox[4].setX(5 * n);
    opBox[4].setY(11 * n);
    
    opBox[5].setX(10 * n);
    opBox[5].setY(11 * n);
    
    for(int i = 0; i < 6; ++i)
    {
        g.setColour(juce::Colours::seagreen);
        g.fillRect(opBox[i]);
        g.setColour(juce::Colours::white);
        g.drawFittedText(juce::String(i + 1),opBox[i], juce::Justification::centred, 1, 0.0f);
    }
    g.setColour(juce::Colours::seagreen);
    
    juce::Rectangle<int> line1 = {6 * n, 6 * n, n, n};
    juce::Rectangle<int> line2 = {11 * n, 6 * n, n, n};
    juce::Rectangle<int> line3 = {8 * n, 8 * n, 2 * n, n};
    juce::Rectangle<int> line4 = {6 * n, 10 * n, n, n};
    juce::Rectangle<int> line5 = {11 * n, 10 * n, n, n};
    
    g.fillRect(line1);
    g.fillRect(line2);
    g.fillRect(line3);
    g.fillRect(line4);
    g.fillRect(line5);
    printf("painted alg2\n");
}

void AlgorithmDiagramSet::paintAlg5(juce::Graphics &g)
{
    int n = getHeight() / 18;
    g.fillAll(juce::Colours::whitesmoke);
    for(int i = 0; i < TotalAlgorithms; ++i)
    {
        opBox[i].setSize(3 * n, 3 * n);
    }
    g.setColour(juce::Colours::seagreen);
    
    opBox[0].setX(8 * n);
    opBox[0].setY(2 * n);
    
    opBox[1].setX(8 * n);
    opBox[1].setY(6 * n);
    
    opBox[2].setX(8 * n);
    opBox[2].setY(10 * n);
    
    opBox[3].setX(8 * n);
    opBox[3].setY(14 * n);
    
    opBox[4].setX(3 * n);
    opBox[4].setY(14 * n);
    
    opBox[5].setX(13 * n);
    opBox[5].setY(14 * n);
    
    for(int i = 0; i < 6; ++i)
    {
        g.setColour(juce::Colours::seagreen);
        g.fillRect(opBox[i]);
        g.setColour(juce::Colours::white);
        g.drawFittedText(juce::String(i + 1),opBox[i], juce::Justification::centred, 1, 0.0f);
    }
    g.setColour(juce::Colours::seagreen);
    
    juce::Rectangle<int> line1 = {9 * n, 5 * n, n, n};
    juce::Rectangle<int> line2 = {9 * n, 9 * n, n, n};
    juce::Rectangle<int> line3 = {9 * n, 13 * n, n, n};
    juce::Rectangle<int> line4 = {6 * n, 15 * n, 2 * n, n};
    juce::Rectangle<int> line5 = {11 * n, 15 * n, 2 * n, n};
    
    juce::Rectangle<int> self1 = {(int)(9.5 * n),(int) (0.5 * n), n / 2, (int)(1.5 * n)};
    juce::Rectangle<int> self2 = {7 * n, n / 2, 3 * n, n / 2};
    juce::Rectangle<int> self3 = {7 * n, n, n / 2, 3 * n};
    juce::Rectangle<int> self4 = {7 * n, (int)(3.5 * n), n, n / 2};
    
    g.fillRect(line1);
    g.fillRect(line2);
    g.fillRect(line3);
    g.fillRect(line4);
    g.fillRect(line5);
    
    g.fillRect(self1);
    g.fillRect(self2);
    g.fillRect(self3);
    g.fillRect(self4);
    printf("painted alg2\n");
}

void AlgorithmDiagramSet::paintAlg6(juce::Graphics &g)
{
    int n = getHeight() / 18;
    g.fillAll(juce::Colours::whitesmoke);
    for(int i = 0; i < TotalAlgorithms; ++i)
    {
        opBox[i].setSize(3 * n, 3 * n);
    }
    g.setColour(juce::Colours::seagreen);
    
    opBox[0].setX(3 * n);
    opBox[0].setY(9 * n);
    
    opBox[1].setX(3 * n);
    opBox[1].setY(13 * n);
    
    opBox[2].setX(13 * n);
    opBox[2].setY(3 * n);
    
    opBox[3].setX(13 * n);
    opBox[3].setY(9 * n);
    
    opBox[4].setX(7 * n);
    opBox[4].setY(9 * n);
    
    opBox[5].setX(7 * n);
    opBox[5].setY(13 * n);
    
    juce::Rectangle<int> selfModOuter;
    selfModOuter.setSize(3 * n, 3 * n);
    selfModOuter.setCentre((int)(7.8 * n), (int)(9.5 * n));
    g.setColour(juce::Colours::seagreen);
    g.fillRect(selfModOuter);
    
    g.setColour(juce::Colours::white);
    juce::Rectangle<int> selfModInner;
    selfModInner.setSize((int)(2.35 * n), (int)(2.35 * n));
    selfModInner.setCentre((int)(7.8 * n), (int)(9.5 * n));
    g.fillRect(selfModInner);
    
    for(int i = 0; i < 6; ++i)
    {
        g.setColour(juce::Colours::seagreen);
        g.fillRect(opBox[i]);
        g.setColour(juce::Colours::white);
        g.drawFittedText(juce::String(i + 1),opBox[i], juce::Justification::centred, 1, 0.0f);
    }
    g.setColour(juce::Colours::seagreen);
    
    juce::Rectangle<int> line1 = {4 * n, 12 * n, n, n};
    juce::Rectangle<int> line2 = {6 * n, 14 * n, n, n};
    juce::Rectangle<int> line3 = {8 * n, 12 * n, n, n};
    juce::Rectangle<int> line4 = {10 * n, 10 * n, 3 * n, n};
    juce::Rectangle<int> line5 = {14 * n, 6 * n, n, 3 * n};
    
    g.fillRect(line1);
    g.fillRect(line2);
    g.fillRect(line3);
    g.fillRect(line4);
    g.fillRect(line5);
}

void AlgorithmDiagramSet::resized()
{

}



AlgorithmSelectorComponent::AlgorithmSelectorComponent()
{
    selectorKnob.setSliderStyle(juce::Slider::IncDecButtons);
    //int initAlg = (int)selectorKnob.getValue();
    
    selectorKnob.setRange(1, 6, 1);
    selectorKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    selectorKnob.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&selectorKnob);
    addAndMakeVisible(&diagram);
}

void AlgorithmSelectorComponent::resized()
{
    int n = getWidth() / 12;
    diagram.setBounds(n, n, 10 * n, 10 * n);
    selectorKnob.setBounds(4 * n, 11 * n, 4 * n, 4 * n);
}

