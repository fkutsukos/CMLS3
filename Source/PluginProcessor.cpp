/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Cmls_fmsynthAudioProcessor::Cmls_fmsynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    ds.bindToPort(57120);
    sender.connectToSocket(ds, "127.0.0.1", 57120);
}

Cmls_fmsynthAudioProcessor::~Cmls_fmsynthAudioProcessor()
{
    sender.disconnect();
}

//==============================================================================
const String Cmls_fmsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Cmls_fmsynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Cmls_fmsynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Cmls_fmsynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Cmls_fmsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Cmls_fmsynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int Cmls_fmsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Cmls_fmsynthAudioProcessor::setCurrentProgram (int index)
{
}

const String Cmls_fmsynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void Cmls_fmsynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Cmls_fmsynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Cmls_fmsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Cmls_fmsynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Cmls_fmsynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    MidiMessage m;
    int time;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);){
        if (m.isNoteOn()) {
            freq = (float) MidiMessage::getMidiNoteInHertz (m.getNoteNumber());
            sender.send("/FM/p5", freq);
                        
            data.amp = 0.5;
            data.car_freq = m.getMidiNoteInHertz(m.getNoteNumber());
        }
        else if (m.isNoteOff()) {
            data.amp = 0;
        }
        else if (m.isAftertouch()) {
            
        }
        else if (m.isPitchWheel()) {
            
        }
    }
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());
}

//==============================================================================
bool Cmls_fmsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Cmls_fmsynthAudioProcessor::createEditor()
{
    return new Cmls_fmsynthAudioProcessorEditor (*this);
}

//==============================================================================
void Cmls_fmsynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Cmls_fmsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void Cmls_fmsynthAudioProcessor::setModFreq(float val)
{
    data.mod_Freq = val;
}

void Cmls_fmsynthAudioProcessor::setCarrierFreq(float val)
{
    data.car_freq = val;
}
void Cmls_fmsynthAudioProcessor::setModIndex(float val)
{
    data.mod_Index = val;
}

void Cmls_fmsynthAudioProcessor::sendmodIndex(float modIndexValue)
{
    sender.send("/FM/p7",(modIndexValue));
}

void Cmls_fmsynthAudioProcessor::sendmodFreq(float modFreqValue)
{
    sender.send("/FM/p6",(modFreqValue));
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Cmls_fmsynthAudioProcessor();
}
