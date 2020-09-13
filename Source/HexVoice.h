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
        proc.allOps[index]->fAttack = *value;
        
    }
    void decaySet(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->fDecay = *value;
    }
    void sustainSet(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->fSustain = *value;
    }
    void releaseSet(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->fRelease = *value;
    }
    void levelSet(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->level = *value;
    }
    void ratioSet(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->ratio = *value;
    }
    void modIndexSet(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->modIndex = *value;
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
        proc.newNote(midiNoteNumber);
        proc.calculateLayers();
        
    }
    //=============================================
    void stopNote (float velocity, bool allowTailOff)
    {
        proc.endNote();
        allowTailOff = true;
        if(velocity == 0)
            clearCurrentNote();
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
        for(int sample = 0; sample < numSamples; ++sample) //calculate all the samples for this block
        {
            proc.setModValsByLayer();
            proc.setAllFrequencies();
            proc.applyEnvelopesAndLevels();
            float outSample = proc.mixSample();
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, outSample);
            }
            ++startSample;
        }
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    //===============================================
    
    SetProcessor proc;
};
