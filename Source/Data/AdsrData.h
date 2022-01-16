/*
  ==============================================================================

    AdsrData.h
    Created: 16 Jan 2022 5:42:28pm
    Author:  Kai

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
    

public:
    
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    

private:
    
    juce::ADSR::Parameters adsParams;

};
