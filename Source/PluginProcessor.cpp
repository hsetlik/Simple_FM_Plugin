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
    auto algId = "algorithmParam";
    auto algName = "Algorithm";
    layout.add(std::make_unique<juce::AudioParameterFloat>
               (algId, algName, 1, TotalAlgorithms, 1));
    for(int i = 0; i < 6; ++i)
    {
        juce::String iStr = juce::String(i);
        auto asId = "attackParam" + iStr;
        auto asName = "Operator " + iStr + " Attack";
        auto dsId = "decayParam" + iStr;
        auto dsName = "Operator " + iStr + " Decay";
        auto ssId = "sustainParam" + iStr;
        auto ssName = "Operator " + iStr + " Sustain";
        auto rsId = "releaseParam" + iStr;
        auto rsName = "Operator " + iStr + " Release";
        
        auto indexId = "modIndexParam" + iStr;
        auto indexName = "Operator " + iStr + " Index";
        auto ratioId = "ratioParam" + iStr;
        auto ratioName = "Operator " + iStr + " frequency ratio";
        auto levelId = "levelParam" + iStr;
        auto levelName = "Operator " + iStr + " Level";
        
        auto rNumId = "ratioNumParam" + iStr;
        auto rNumName = "Freq ratio " + iStr + " numerator";
        
        auto rDenId = "ratioDenParam" + iStr;
        auto rDenName = "Freq ratio " + iStr + " denominator";
        
        
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(rNumId, rNumName, 1, 15, 1));
        layout.add(std::make_unique<juce::AudioParameterFloat>(rDenId, rDenName, 1, 15, 1));
        
        auto aRange = juce::NormalisableRange<float>(1.0, 4000.0, 1.0, 0.28, false);
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (asId, asName, aRange, 15.0));
        auto dRange = juce::NormalisableRange<float>(1.0, 4000.0, 0.5, 0.28, false);
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (dsId, dsName, dRange, 8.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>
        (ssId, ssName, 0.0f, 1.0f, 0.6f));
        auto rRange = juce::NormalisableRange<float>(1.0, 5000.0, 0.5, 0.28, false);
        layout.add(std::make_unique<juce::AudioParameterFloat>
                   (rsId, rsName, rRange, 100.0));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(indexId, indexName, 1.0f, 500.0f, 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(ratioId, ratioName, -10.0f, 10.0f, 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(levelId, levelName, 0.0f, 1.0f, 0.6f));
        
        for(int n = 0; n < 6; ++n)
        {
            juce::String modBoolId = "modSetParam" + iStr + juce::String(n);
            juce::String modBoolName = "Operator " + iStr + " > Operator " + juce::String(n);
           layout.add(std::make_unique<juce::AudioParameterBool>(modBoolId, modBoolName, false));
        }
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
                       ), tree(*this, nullptr, "ALLPARAMETERS", createLayout())
#endif
{
    for(int i = 0; i < 6; ++i)
    {
        HexSynth.addVoice(new HexVoice());
    }
    HexSynth.clearSounds();
    HexSynth.addSound(new HexSound());
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
    HexSynth.setCurrentPlaybackSampleRate(lastSampleRate);
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
    for(int i = 0; i < HexSynth.getNumVoices(); ++i)
       {
           //yes that is supposed to be a single '='
           if((thisVoice =  dynamic_cast<HexVoice*>(HexSynth.getVoice(i))))
           {
               thisVoice->setVoiceAlgorithm(tree.getRawParameterValue("algorithmParam"));
               for(int n = 0; n < 6; ++n)
               {
                   juce::String iStr = juce::String(n);
                   //thisVoice->
                   thisVoice->setVoiceAttack(n, tree.getRawParameterValue("attackParam" + iStr));
                   thisVoice->setVoiceDecay(n, tree.getRawParameterValue("decayParam" + iStr));
                   thisVoice->setVoiceSustain(n, tree.getRawParameterValue("sustainParam" + iStr));
                   thisVoice->setVoiceRelease(n, tree.getRawParameterValue("releaseParam" + iStr));
                   thisVoice->setVoiceIndex(n, tree.getRawParameterValue("modIndexParam" + iStr));
                   thisVoice->setVoiceRatio(n, tree.getRawParameterValue("ratioNumParam" + iStr),
                                            tree.getRawParameterValue("ratioDenParam" + iStr));
                   thisVoice->setVoiceLevel(n, tree.getRawParameterValue("levelParam" + iStr));
               }
           }
       }
       buffer.clear();
       HexSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
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
