#include "core/sound/Track.h"
#include "core/sound/SoundManager.h"

void Track::Play()
{
    SoundManager::Instance()->PlayTrack(GetName());
}

void Track::Stop()
{
    SoundManager::Instance()->StopTrack();
}

void Track::Cleanup()
{
    Stop();
}

int Track::SetVolume(int volume)
{
    return SoundManager::Instance()->SetTrackVolume(volume);
}