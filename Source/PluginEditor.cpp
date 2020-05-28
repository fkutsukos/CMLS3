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
    modFreq.setSliderStyle(Slider::RotaryVerticalDrag);
    modFreq.setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    modFreq.setTextValueSuffix(" Hz");
    modFreq.setLookAndFeel(&otherLookAndFeel);
    modFreq.addListener(this);
    
    modFreqLabel.setText("Mod Frequency",dontSendNotification);
    
    modIndex.setRange(0,10,0.5);
    modIndex.setSliderStyle(Slider::RotaryVerticalDrag);
    modIndex.setTextBoxStyle (Slider::TextBoxBelow, false, 50, 20);
    modIndex.setLookAndFeel(&otherLookAndFeel);
    modIndex.addListener(this);

    modIndexLabel.setText("Mod Index", dontSendNotification);

    level.setSliderStyle(Slider::LinearVertical);
    level.setRange(0, 1, 100);
    level.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    level.setValue(50);
    level.addListener(this);

    addAndMakeVisible(modFreq);
    addAndMakeVisible(modFreqLabel);
    addAndMakeVisible(modIndex);
    addAndMakeVisible(modIndexLabel);
    addAndMakeVisible(level);
    addAndMakeVisible(textLabel);

    textLabel.setFont(textFont);

    // add items to the combo-box
    addAndMakeVisible(styleMenu);
    styleMenu.addItem("Plain", 1);
    styleMenu.addItem("Bold", 2);
    styleMenu.addItem("Italic", 3);

    styleMenu.onChange = [this] { styleMenuChanged(); };
    styleMenu.setSelectedId(1);

    setSize(550, 350);
}

Cmls_fmsynthAudioProcessorEditor::~Cmls_fmsynthAudioProcessorEditor()
{
}

//==============================================================================
void Cmls_fmsynthAudioProcessorEditor::paint (Graphics& g)
{

    Image background = ImageCache::getFromMemory(BinaryData::_3950b7d79751e82ab42ee90443941577_jpg, BinaryData::_3950b7d79751e82ab42ee90443941577_jpgSize);
    g.drawImageAt(background, 0, 0);

    Rectangle<int> box(425, 15, 110, 320);
    g.setColour(Colours::darkgrey);
    ColourGradient myGradient4(Colours::black, 535, 335, Colours::darkgrey, 425, -5, false);
    g.setGradientFill(myGradient4);
    g.fillRect(box);

    Rectangle<int> lev(430, 20, 100, 310);
    g.setColour(Colours::darkgrey);
    ColourGradient myGradient3(Colours::black, 430, -20, Colours::darkgrey, 430, 310, false);
    g.setGradientFill(myGradient3);
    g.fillRect(lev);

    g.setColour(Colours::whitesmoke);
    g.drawText("Level", 430, 30, 100, 50, Justification::centredTop);



    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("FM Synth", getLocalBounds(), Justification::centred, 1);
}

void Cmls_fmsynthAudioProcessorEditor::resized()
{
    modFreqLabel.setBounds(15,50,130,20);
    modFreq.setBounds(15,80,100,100);

    modIndexLabel.setBounds(30,200,130,20);
    modIndex.setBounds(15,230,100,100);

    level.setBounds(430, 50, 100, 260);

    textLabel.setBounds(10, 10, getWidth() - 20, 20);
    styleMenu.setBounds(80, 10, 150, 20);
}

void Cmls_fmsynthAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
   processor.volume = level.getValue();

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
