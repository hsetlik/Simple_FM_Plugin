/*
  ==============================================================================

    OperatorComponent.h
    Created: 11 Sep 2020 9:39:17pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

 class OperatorComponent : public juce::Component
{
public:
    //functions
    OperatorComponent(int index, juce::Slider::Listener* sLstnr, juce::Button::Listener* bLstnr);
    ~OperatorComponent() {}
    void resized() override;
    //non-component data
    int OpComponentIndex;
    juce::Slider::Listener* sliderLstnr;
    juce::Button::Listener* buttonLstnr;
    //child components & attachments
    juce::Slider aSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> aSliderAttach;
    juce::Slider dSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dSliderAttach;
    juce::Slider sSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sSliderAttach;
    juce::Slider rSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rSliderAttach;
    juce::Slider levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelSliderAttach;
    juce::Slider modIndexSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> modIndexSliderAttach;
    juce::Slider ratioSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioSliderAttach;
};
