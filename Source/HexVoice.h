/*
  ==============================================================================

    HexVoice.h
    Created: 11 Sep 2020 6:45:11pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OperatorProcessor.h"

class HexSound : public juce::SynthesiserSound
{
    public:
    bool appliesToNote(int /*midiNoteNumber*/) //just plays this sound for any midi note
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/) //plays the sound on both channels
    {
        return true;
    }
};

class HexVoice : public juce::SynthesiserVoice
{
    public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<HexSound*>(sound) != nullptr;
    }
    //==============================================
    void attackSet(int index, std::atomic<float>* value)
    {
        
    }
    void decaySet(int index, std::atomic<float>* value)
    {
        
    }
    void sustainSet(int index, std::atomic<float>* value)
    {
        
    }
    void releaseSet(int index, std::atomic<float>* value)
    {
        
    }
    void levelSet(int index, std::atomic<float>* value)
    {
        
    }
    void ratioSet(int index, std::atomic<float>* value)
    {
        
    }
    void modIndexSet(int index, std::atomic<float>* value)
    {
        
    }
    void outputSwitchSet(int index, std::atomic<float>* value)
    {
        bool isOn;
        if(*value > 0.5f)
            isOn = true;
        else
            isOn = false;
        proc.allOps[index]->isAudible = isOn;
    }
    void modInputSet(int iIndex, int nIndex, std::atomic<float>* value)
    {
        bool isOn;
        if(*value > 0.5f)
        {
            isOn = true;
        }
        else
            isOn = false;
        proc.allOps[iIndex]->takesInputFrom[nIndex] = isOn;
    }
    
    //========================================
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        
    }
    //===========================================
    void pitchWheelMoved(int newPitchWheelVal)
    {
        
    }
    //=============================================
    void controllerMoved(int controllerNumber, int controllerValue)
    {
        
    }
    //===============================================
    void aftertouchChanged (int newAftertouchValue)
    {

    }
    //==============================================
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    }
    //===============================================
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    //===============================================
    
    SetProcessor proc;
};
