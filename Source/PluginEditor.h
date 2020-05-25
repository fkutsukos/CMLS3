/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Cmls_fmsynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Cmls_fmsynthAudioProcessorEditor (Cmls_fmsynthAudioProcessor&);
    ~Cmls_fmsynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Cmls_fmsynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cmls_fmsynthAudioProcessorEditor)
};
