#include "SoundEffects.h"
// SoundEffects cpp
SoundEffects::SoundEffects(const std::string name, SOUNDTYPE type)
{
    effectName_ = name;
    type_ = type;
    soundEffect_ = NULL;
}
void SoundEffects::SetSoundSource(const std::string path)
{
    effectPath_ = path;
    soundEffect_ = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(path.c_str())); // set up media source for playing when needed.
}
std::string SoundEffects::GetSoundSource()
{
    return effectPath_;
}
void SoundEffects::PlaySound()
{
    if(soundEffect_ !=  NULL)
    {
        soundEffect_->play(); // will play sound effect.
    }
}
