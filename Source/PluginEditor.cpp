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
    levelSlider.setRange(0, 100, 1);
    levelSlider.setSliderStyle(Slider::LinearVertical);
    levelSlider.setColour(Slider::thumbColourId, Colours::lightgrey);
    levelSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    levelSlider.setValue(50);
    levelSlider.addListener(this);

    durationSlider.setRange(0, 5, 0.1);
    durationSlider.setSliderStyle(Slider::LinearVertical);
    durationSlider.setColour(Slider::thumbColourId, Colours::lightgrey);
    durationSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    durationSlider.setTextValueSuffix(" sec");
    durationSlider.addListener(this);

    modFreq.setRange(0.20, 10, 0.01);
    modFreq.setSliderStyle(Slider::RotaryVerticalDrag);
    modFreq.setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    modFreq.setLookAndFeel(&otherLookAndFeel);
    modFreq.addListener(this);
    
    modIndex.setRange(0,10,0.5);
    modIndex.setSliderStyle(Slider::RotaryVerticalDrag);
    modIndex.setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    modIndex.setLookAndFeel(&otherLookAndFeel);
    modIndex.addListener(this);


    modIndex2.setRange(0, 10, 0.5);
    modIndex2.setSliderStyle(Slider::RotaryVerticalDrag);
    modIndex2.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    modIndex2.setLookAndFeel(&otherLookAndFeel);
    modIndex2.addListener(this);


    addAndMakeVisible(modFreq);
    addAndMakeVisible(modFreqLabel);
    addAndMakeVisible(modIndex);
    addAndMakeVisible(modIndexLabel);
    addAndMakeVisible(modIndex2);
    addAndMakeVisible(modIndexLabel2);
    addAndMakeVisible(textLabel);
    addAndMakeVisible(levelSlider);
    addAndMakeVisible(durationSlider);

    textLabel.setFont(textFont);

    // add items to the combo-box
    addAndMakeVisible(styleMenu);
    styleMenu.addItem("Brass", 1);
    styleMenu.addItem("Percussive", 2);
    styleMenu.addItem("Woodwind", 3);

    styleMenu.onChange = [this] { styleMenuChanged(); };
    styleMenu.setSelectedId(1);

    ///////////////
    enum RadioButtonIds
    {
        EnvButtons = 1001
    };

    envLabel.setFont(textFont);
    envLabel.setJustificationType(Justification::centred);

    addAndMakeVisible(envLabel);

    addAndMakeVisible(adsrButton);
    addAndMakeVisible(asrButton);
    addAndMakeVisible(percButton);
    adsrButton.onClick = [this] { updateToggleState(&adsrButton, "ADSR");   };
    asrButton.onClick = [this] { updateToggleState(&asrButton, "ASR"); };
    percButton.onClick = [this] { updateToggleState(&percButton, "Percussive"); };

    adsrButton.setRadioGroupId(EnvButtons);
    asrButton.setRadioGroupId(EnvButtons);
    percButton.setRadioGroupId(EnvButtons);

    setSize(550, 350);

    adsrButton.setClickingTogglesState(true);
    asrButton.setClickingTogglesState(true);
    percButton.setClickingTogglesState(true);
}

Cmls_fmsynthAudioProcessorEditor::~Cmls_fmsynthAudioProcessorEditor()
{
}

//==============================================================================
void Cmls_fmsynthAudioProcessorEditor::paint (Graphics& g)
{

    Image background = ImageCache::getFromMemory(BinaryData::_3950b7d79751e82ab42ee90443941577_jpg, BinaryData::_3950b7d79751e82ab42ee90443941577_jpgSize);
    g.drawImageAt(background, 0, 0);

    //BUTTONS BOX

    Rectangle<int> buttonsbox(20, 201, 305, 134);
    g.setColour(Colours::grey);
    g.fillRect(buttonsbox);

    Rectangle<int> buttons(22, 203, 301, 130);
    g.setColour(Colours::darkgrey);
    ColourGradient myGradient8(Colours::black, 430, -20, Colours::darkgrey, 430, 310, false);
    g.setGradientFill(myGradient8);
    g.fillRect(buttons);

    //KNOBS BOX

    Rectangle<int> cmbox(20, 55, 185, 130);
    g.setColour(Colours::grey);
    g.fillRect(cmbox);

    Rectangle<int> cm(22, 57, 181, 126);
    g.setColour(Colours::darkgrey);
    ColourGradient myGradient7(Colours::black, 430, -20, Colours::darkgrey, 430, 310, false);
    g.setGradientFill(myGradient7);
    g.fillRect(cm);

    Rectangle<int> idxsbox(140, 55, 185, 130);
    g.setColour(Colours::grey);
    g.fillRect(idxsbox);

    Rectangle<int> idxs(142, 57, 181, 126);
    g.setColour(Colours::darkgrey);
    ColourGradient myGradient6(Colours::black, 430, -20, Colours::darkgrey, 430, 310, false);
    g.setGradientFill(myGradient6);
    g.fillRect(idxs);

    //SLIDERS BOX

    Rectangle<int> box(345, 15, 190, 320);
    g.setColour(Colours::darkgrey);
    g.setColour(Colours::grey);
    g.fillRect(box);

    Rectangle<int> lev(347, 17, 186, 316);
    g.setColour(Colours::darkgrey);
    ColourGradient myGradient3(Colours::black, 430, -20, Colours::darkgrey, 430, 310, false);
    g.setGradientFill(myGradient3);
    g.fillRect(lev);

    g.setColour(Colours::whitesmoke);
    g.drawText("Level", 430, 30, 100, 50, Justification::centredTop);
    g.drawText("Duration", 350, 30, 100, 50, Justification::centredTop);
    g.drawText("C/M", 30, 60, 100, 50, Justification::centredTop);
    g.drawText("I1", 150, 70, 80, 50, Justification::centredTop);
    g.drawText("I2", 235, 70, 80, 50, Justification::centredTop);

}

void Cmls_fmsynthAudioProcessorEditor::resized()
{
    modFreq.setBounds(30, 80, 100, 100);

    modIndex.setBounds(150, 90, 80, 80);

    modIndex2.setBounds(235, 90, 80, 80);

    levelSlider.setBounds(430, 50, 100, 260);
    durationSlider.setBounds(350, 50, 100, 260);

    textLabel.setBounds(20, 20, getWidth() - 20, 20);
    styleMenu.setBounds(90, 21, 150, 20);

    envLabel.setBounds(30, 210, 285, 20);
    adsrButton.setBounds(30, 241, 285, 20);
    asrButton.setBounds(30, 272, 285, 20);
    percButton.setBounds(30, 303, 285, 20);
}

void Cmls_fmsynthAudioProcessorEditor::sliderValueChanged(Slider *slider)
{

   if (slider == &modFreq)
    {
        processor.sendmodFreq(modFreq.getValue());   
    }

    else if (slider == &modIndex)
    {
        processor.sendmodIndex(modIndex.getValue());
    }

    else if (slider == &modIndex2)
    {
       processor.sendmodIndex2(modIndex2.getValue());
    }

    else if (slider == &levelSlider)
    {
       processor.sendVolume(levelSlider.getValue());
    }

    else if (slider == &durationSlider)
    {
       processor.sendDuration(durationSlider.getValue());
    }
}
