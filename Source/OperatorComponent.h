/*
  ==============================================================================

    OperatorComponent.h
    Created: 11 Sep 2020 9:39:17pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AlgorithmSelectorComponent.h"

 class OperatorComponent : public juce::Component
{
public:
    //functions
    OperatorComponent(int index, juce::Slider::Listener* sLstnr, juce::Button::Listener* bLstnr);
    ~OperatorComponent() {}
    void resized() override;
    void paint(juce::Graphics& g) override;
    //non-component data
    int OpComponentIndex;
    juce::Rectangle<int> levelBarContainer;
    juce::Rectangle<int> levelBarContent;
    void setContentWidth(float portion);
    int contentWidth;
    
    juce::Button::Listener* buttonLstnr;
    juce::Slider::Listener* sliderLstnr;
    //child components & attachments
    juce::TextButton audioTogggleButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> aToggleAttach;
    
    juce::Slider aSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> aSliderAttach;
    juce::Label aSliderLabel;
    
    juce::Slider dSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dSliderAttach;
    juce::Label dSliderLabel;
    
    juce::Slider sSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sSliderAttach;
    juce::Label sSliderLabel;
    
    juce::Slider rSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rSliderAttach;
    juce::Label rSliderLabel;
    
    juce::Slider levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelSliderAttach;
    juce::Label levelLabel;
    
    juce::Slider modIndexSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> modIndexSliderAttach;
    juce::Label indexLabel;
    
    juce::Slider ratioSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioSliderAttach;
    juce::Label ratioLabel;
    
    juce::Slider ratioNumSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioNumSliderAttach;
    
    juce::Slider ratioDenSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioDenSliderAttach;
};
