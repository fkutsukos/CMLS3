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
class OtherLookAndFeel : public LookAndFeel_V4
{
public:

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin(width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        ColourGradient myGradient2(Colours::darkgrey, x, y, Colours::black, x+radius, y+2*radius, false);
        g.setGradientFill(myGradient2);
        //g.setColour(Colours::darkgrey);
        g.fillEllipse(rx, ry, rw, rw);
        
        // outline
        g.setColour(Colours::grey);
        g.drawEllipse(rx, ry, rw, rw, 1.0f);

        Path p;
        auto pointerLength = radius * 0.4f;
        auto pointerThickness = 2.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

        ColourGradient myGradient(Colours::black, centreX, ry, Colours::darkgrey, centreX, 1.5* centreY, false);
        g.setGradientFill(myGradient);
        g.fillEllipse(rx + pointerLength, ry + pointerLength, rw - 2 * pointerLength, rw - 2 * pointerLength);

        g.setColour(Colours::lightslategrey);
        g.drawEllipse(rx + pointerLength, ry + pointerLength, rw - 2*pointerLength, rw - 2*pointerLength, 1.0f);

        // pointer
        g.setColour(Colours::white);
        g.fillPath(p);
    }

};

/**
*/
class Cmls_fmsynthAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    Cmls_fmsynthAudioProcessorEditor (Cmls_fmsynthAudioProcessor&);
    ~Cmls_fmsynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    OtherLookAndFeel otherLookAndFeel;

    Slider level;

    Slider modFreq;
    Label modFreqLabel;
    
    Slider modIndex;
    Label modIndexLabel;

    Label textLabel{ {}, "Presets:" };
    Font textFont{ 18.0f };
    ComboBox styleMenu;

    void sliderValueChanged( Slider * slider) override;

    void styleMenuChanged()
    {
        switch (styleMenu.getSelectedId())
        {
        case 1: textFont.setStyleFlags(Font::plain);  break;
        case 2: modFreq.setValue(550), modIndex.setValue(2.5);   break;
        case 3: modFreq.setValue(100), modIndex.setValue(6); break;
        default: break;
        }

        textLabel.setFont(textFont);
    }
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Cmls_fmsynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cmls_fmsynthAudioProcessorEditor)
};

