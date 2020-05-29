/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
typedef struct
{
    float mod_phase;
    float mod_Freq;
    int mod_Index;
    float phase;
    float amp;
    float car_freq;
}
FMData;

//==============================================================================
/**
*/
class Cmls_fmsynthAudioProcessor  : public AudioProcessor
{
public:

    //==============================================================================
    Cmls_fmsynthAudioProcessor();
    ~Cmls_fmsynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void setCarrierFreq(float val);
    void setModFreq(float val);
    void setModIndex(float val);
    float freq;
    void sendmodIndex(float modIndexValue);
    void sendmodFreq(float modFreqValue);


private:
    FMData data;
    DatagramSocket ds;
    OSCSender sender; // Declaration of the // OSC sender
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cmls_fmsynthAudioProcessor)
};
