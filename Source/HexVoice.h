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
    void setVoiceRatio(int index, std::atomic<float>* nvalue, std::atomic<float>* dvalue)
    {
        auto num = fabs(*nvalue);
        auto den = fabs(*dvalue);
        proc.allOps[index]->ratio = (num / den);
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
        proc.procAlgIndex = setting;
        //proc.setLayersForCurrentAlg();
    }
    void setVoiceGrid(int i, int n, std::atomic<float>* value)
    {
        bool setting = (bool) *value;
        proc.modGridSettings[i][n] = !setting;
    }
    void setAudioToggle(int index, std::atomic<float>* value)
    {
        bool setting = (bool) *value;
        proc.allOps[index]->toOutput = !setting;
    }
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        proc.newNote(fundamental);
        proc.assignLayersInOrder();
        proc.setModSourcesFromGrid();
        
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
            
            proc.setModValuesFromGrid();
            float mixSample = proc.getAudibleSampleForGrid();
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
    
    juce::AudioBuffer<float> opBuffers[6] = {
        juce::AudioBuffer<float>(1, 512),
        juce::AudioBuffer<float>(1, 512),
        juce::AudioBuffer<float>(1, 512),
        juce::AudioBuffer<float>(1, 512),
        juce::AudioBuffer<float>(1, 512),
        juce::AudioBuffer<float>(1, 512)};
    

};
