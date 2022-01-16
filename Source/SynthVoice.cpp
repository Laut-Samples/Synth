/*
  ==============================================================================

    SynthVoice.cpp
    Created: 14 Jan 2022 8:24:57pm
    Author:  Kai

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)

{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound * sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
    
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (! allowTailOff || ! adsr.isActive())
        clearCurrentNote();
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)

{
    adsr.setSampleRate(sampleRate);
    
    
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepare (spec);
    gain.prepare (spec);
    osc.setFrequency(220.0f);
    gain.setGainLinear (0.01f);
    
    adsParams.attack = 0.8f;
    adsParams.decay = 0.8f;
    adsParams.sustain = 1.5f;
    adsParams.release = 1.5f;
    
    adsr.setParameters (adsParams);
    
    
    isPrepared = true;
    
    
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startsample, int numSamples)
{
    jassert (isPrepared);
    
    if (! isVoiceActive())
        return;
    // Buffer
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer } ;
    
    // OSC
    
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    // ADSR
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumChannels());
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startsample, synthBuffer, channel, 0, numSamples);
        
        if(! adsr.isActive())
            clearCurrentNote();
    }
    
}
