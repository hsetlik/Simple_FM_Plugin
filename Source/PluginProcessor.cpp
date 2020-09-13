/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
juce::AudioProcessorValueTreeState::ParameterLayout createLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for(int i = 0; i < 6; ++i)
    {
        juce::String iStr = juce::String(i);
        for(int n = 0; n < 6; ++n)
        {
            juce::String nStr = juce::String(n);
            juce::String tempID = "mod" + nStr + "op" + iStr + "Param";
            juce::String tempName = "Operator " + nStr + " modulating operator " + iStr;
            layout.add(std::make_unique<juce::AudioParameterFloat>(tempID, tempName, 0.0, 1.0, 0.0));
        }
        juce::String aID = "aParam" + iStr;
        juce::String aName = "Operator " + iStr + " attack";
        layout.add(std::make_unique<juce::AudioParameterFloat>(aID, aName, 0.1f, 5000.0f, 3.0f));
        
        juce::String dID = "dParam" + iStr;
        juce::String dName = "Operator " + iStr + " decay";
        layout.add(std::make_unique<juce::AudioParameterFloat>(dID, dName, 0.1f, 5000.0f, 55.0f));
        
        juce::String sID = "sParam" + iStr;
        juce::String sName = "Operator " + iStr + " sustain";
        layout.add(std::make_unique<juce::AudioParameterFloat>(sID, sName, 0.0f, 1.0f, 0.6f));
        
        juce::String rID = "rParam" + iStr;
        juce::String rName = "Operator " + iStr + " release";
        layout.add(std::make_unique<juce::AudioParameterFloat>(rID, rName, 0.1f, 5000.0f, 3.0f));
        
        juce::String indexID = "modIndexParam" + iStr;
        juce::String indexName = "Operator " + iStr + " modulation index";
        layout.add(std::make_unique<juce::AudioParameterFloat>(indexID, indexName, 1.0f, 500.0f, 1.0f));
        
        juce::String ratioID = "ratioParam" + iStr;
        juce::String ratioName = "Operator " + iStr + " frequency ratio";
        layout.add(std::make_unique<juce::AudioParameterFloat>(ratioID, ratioName, -10.0f, 10.0f, 1.0f));
        
        juce::String levelID = "levelParam" + iStr;
        juce::String levelName = "Operator " + iStr + " level";
        layout.add(std::make_unique<juce::AudioParameterFloat>(levelID, levelName, 0.0f, 1.0f, 1.0f));
        
        juce::String audioOutID = "audioToggleParam" + iStr;
        juce::String audioOutName = "Operator " + iStr + " audio Output";
        layout.add(std::make_unique<juce::AudioParameterFloat>(audioOutID, audioOutName, 0.0f, 1.0f, 0.0f));
    }
    return layout;
}

//==============================================================================
HexFmAudioProcessor::HexFmAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "ALLPARAMATERS", createLayout())
#endif
{
    for(int i = 0; i < 6; ++i)
    {
        thisSynth.addVoice(new HexVoice());
    }
    thisSynth.clearSounds();
    thisSynth.addSound(new HexSound());
}

HexFmAudioProcessor::~HexFmAudioProcessor()
{
}

//==============================================================================
const juce::String HexFmAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HexFmAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HexFmAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HexFmAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HexFmAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HexFmAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HexFmAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HexFmAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HexFmAudioProcessor::getProgramName (int index)
{
    return {};
}

void HexFmAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HexFmAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    thisSynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void HexFmAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HexFmAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HexFmAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for(int i = 0; i < thisSynth.getNumVoices(); ++i)
        {
            //yes that is supposed to be a single '='
            if((thisVoice =  dynamic_cast<HexVoice*>(thisSynth.getVoice(i))))
            {
                for(int n = 0; n < 6; ++n)
                {
                    juce::String iStr = juce::String(n);
                    for(int k = 0; k < 6; ++n)
                    {
                        juce::String kStr = juce::String(k);
                        thisVoice->modInputSet(n, k, tree.getRawParameterValue("mod" + kStr + "op" + iStr + "Param"));
                    }
                    
                }
            }
        }
        buffer.clear();
        thisSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool HexFmAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HexFmAudioProcessor::createEditor()
{
    return new HexFmAudioProcessorEditor (*this);
}

//==============================================================================
void HexFmAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HexFmAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HexFmAudioProcessor();
}
