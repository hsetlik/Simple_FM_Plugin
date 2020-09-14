/*
  ==============================================================================

    HexVoice.h
    Created: 11 Sep 2020 6:45:11pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AlgorithmProcessor.h"

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
    void setVoiceAttack(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->envelope.setAttack(*value);
    }
    void setVoiceDecay(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->envelope.setDecay(*value);
    }
    void setVoiceSustain(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->envelope.setSustain(*value);
    }
    void setVoiceRelease(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->envelope.setRelease(*value);
    }
    void setVoiceRatio(int index, std::atomic<float>* value)
    {
        float outValue;
        if(*value > 0)
            outValue = *value;
        else
            outValue = 1.0 / fabs(*value);
        proc.allOps[index]->ratio = outValue;
    }
    void setVoiceIndex(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->modIndex = *value;
    }
    void setVoiceLevel(int index, std::atomic<float>* value)
    {
        proc.allOps[index]->level = *value;
    }
    
    void setVoiceAlgorithm(std::atomic<float>* value)
    {
        float fValue = (float)*value;
        //printf("setting voice algorithm: %f\n", fValue);
        int setting = (int)fValue;
        if(setting == 1)
            proc.procAlgIndex = 1;
        else if(setting == 2)
            proc.procAlgIndex = 2;
        else if(setting == 3)
            proc.procAlgIndex = 3;
        proc.setLayersForCurrentAlg();
        
    }
    
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        proc.newNote(fundamental);
        proc.setLayersForCurrentAlg();
        proc.setOutputsInLayerOrder();
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
            proc.setModValues();
            float mixSample = proc.getAudibleSampleForAlg();
            
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, mixSample);
            }
            ++startSample;
        }
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    //===============================================
    AlgorithmProcessor proc;
    double fundamental;
    
    SetProcessor proc;
};
