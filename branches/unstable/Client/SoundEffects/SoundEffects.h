#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <string.h>

#include <phonon/mediaobject.h>
#include <phonon/mediaobjectinterface.h>
#include <phonon/mediacontroller.h>
#include <phonon/mediasource.h>

class SoundEffects
{
private:
    /*std::string effectPath_; // will hold the path to the sound effect.
    std::string effectName_;
    SOUNDTYPE type_;
    Phonon::MediaObject* soundEffect_; // used to play sounds;
	*/
public:
	enum SOUNDTYPE
	{
	    EXPLOSION = 0,
	    EXHAUST = 1,
	    SHOT = 2,
	    STARTGAME = 3,
	    RESPAWN = 4,
	    WARP = 5,
	    ENDGAME = 6
	};
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
