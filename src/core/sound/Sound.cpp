#include "core/sound/Sound.h"
#include "core/sound/SoundManager.h"

void Sound::Play(int loops)
{
    channel = SoundManager::Instance()->PlaySound(GetName(), loops);
}

void Sound::Stop()
{
    if (channel != -1)
    {
        SoundManager::Instance()->StopSound(channel);
        channel = -1;
    }
}

void Sound::Cleanup()
{
    Stop();
}