/*
  ==============================================================================

    SynthVoice.h
    Created: 14 Jan 2022 8:24:57pm
    Author:  Kai

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound * sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startsample, int numSamples) override;
    

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsParams;

    //    juce::dsp::Oscillator<float> osc { [](float x) {return std::sin (x); }};
    juce::dsp::Oscillator<float> osc { [](float x) {return x / juce::MathConstants<float>::pi; }};
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
    

};
