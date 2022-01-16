/*
  ==============================================================================

    AdsrData.cpp
    Created: 16 Jan 2022 5:42:28pm
    Author:  Kai

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR (const float attack, const float decay, const float sustain, const float release)
{
    
    adsParams.attack = attack;
    adsParams.decay = decay;
    adsParams.sustain = sustain;
    adsParams.release = release;
    
    setParameters (adsParams);
    
}
