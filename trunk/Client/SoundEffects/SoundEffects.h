#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H
#include <string>
#include <phonon/mediaobject.h>
#include <phonon/mediaobjectinterface.h>
#include <phonon/mediacontroller.h>
#include <phonon/mediasource.h>
enum SOUNDTYPE
{
    animation_efx = 0,
    shot = 1,
    startgame = 2,
    respawn = 3,
    warp = 4,
    endgame = 5
};

class SoundEffects
{
public:
    SoundEffects(const std::string, SOUNDTYPE); // constructor
    void SetSoundSource(const std::string);
    std::string GetSoundSource();
    void PlaySound(); // will play current sound.
private:
    std::string effectPath_; // will hold the path to the sound effect.
    std::string effectName_;
    SOUNDTYPE type_;
    Phonon::MediaObject* soundEffect_; // used to play sounds;

};
#endif // SOUNDEFFECTS_H
