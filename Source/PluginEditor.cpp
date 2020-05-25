/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Cmls_fmsynthAudioProcessorEditor::Cmls_fmsynthAudioProcessorEditor (Cmls_fmsynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    modFreq.setRange(0,1000,1);
    modFreq.setSliderStyle(Slider::Rotary);
    modFreq.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 20);
    modFreq.addListener(this);
    
    modFreqLabel.setText("Modulation Frequency",dontSendNotification);
    modIndexLabel.setText("Modulation Index", dontSendNotification);
    
    modIndex.setRange(0,10,0.5);
    modIndex.setSliderStyle(Slider::Rotary);
    modIndex.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 20);
    modIndex.addListener(this);
    
    addAndMakeVisible(modFreq);
    addAndMakeVisible(modFreqLabel);
    addAndMakeVisible(modIndex);
    addAndMakeVisible(modIndexLabel);
    setSize (600, 250);
}

Cmls_fmsynthAudioProcessorEditor::~Cmls_fmsynthAudioProcessorEditor()
{
}

//==============================================================================
void Cmls_fmsynthAudioProcessorEditor::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("FM Synth", getLocalBounds(), Justification::centred, 1);
}

void Cmls_fmsynthAudioProcessorEditor::resized()
{
    modFreqLabel.setBounds(10,50,130,20);
    modFreq.setBounds(10,80,100,100);
    modIndexLabel.setBounds(200,50,130,20);
    modIndex.setBounds(200,80,100,100);
}

void Cmls_fmsynthAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
   if (slider == &modFreq)
    {
        processor.setModFreq(modFreq.getValue());
        processor.sendmodFreq(modFreq.getValue());
        
    }
    else if (slider == &modIndex)
    {
        processor.setModIndex(modIndex.getValue());
        processor.sendmodIndex(modIndex.getValue());
    }
}
