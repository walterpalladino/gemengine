#include "core/sound/Sound.h"
#include "core/sound/SoundManager.h"

void Sound::Play(int loops)
{
    channel = SoundManager::Instance()->PlaySound(sound, loops);
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

int Sound::SetVolume(int volume)
{
    return SoundManager::Instance()->SetSoundChannelVolume(channel, volume);
}
