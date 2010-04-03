#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <string.h>

#include <phonon/mediaobject.h>
#include <phonon/mediaobjectinterface.h>
#include <phonon/mediacontroller.h>
#include <phonon/mediasource.h>

enum SOUNDTYPE
{
    explosion = 0,
    shot = 1,
    startgame = 2,
    respawn = 3,
    warp = 4,
    endgame = 5,
    exhaust = 6
};

class SoundEffects
{
private:
    /*std::string effectPath_; // will hold the path to the sound effect.
    std::string effectName_;
    SOUNDTYPE type_;
    Phonon::MediaObject* soundEffect_; // used to play sounds;
	*/
public:
	std::string effectPath_; // will hold the path to the sound effect.
	std::string effectName_;
	SOUNDTYPE type_;
	Phonon::MediaObject* soundEffect_; // used to play sounds;

	SoundEffects();

    SoundEffects(const std::string, SOUNDTYPE); // constructor
    SoundEffects(const SoundEffects& efx);
    void SetSoundSource(const std::string);
    std::string GetSoundName(){return effectName_;}
    std::string GetSoundSource();
    Phonon::MediaObject* GetSoundEffectObject(){return soundEffect_;}
    SOUNDTYPE GetType(){return type_;}
    void PlaySound(); // will play current sound.


};
#endif // SOUNDEFFECTS_H
