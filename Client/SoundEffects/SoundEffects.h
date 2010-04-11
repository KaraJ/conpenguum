#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <QObject>
#include <QBuffer>
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <Phonon/Global>
#include <Phonon/Path>
#include <string.h>

class SoundEffects: public QObject
{
	Q_OBJECT
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
	SoundEffects(QObject *parent = 0);

	SoundEffects(const SoundEffects& efx);
	SoundEffects(const std::string, SOUNDTYPE); // constructor

	void SetSoundSource(const std::string);
	std::string GetSoundName(){return effectName_;}
	std::string GetSoundSource(){return effectPath_;};
	Phonon::MediaObject* GetSoundEffectObject(){return soundEffect_;}
	SOUNDTYPE GetType(){return type_;}
	void PlaySound(); // will play current sound.


	std::string effectPath_; // will hold the path to the sound effect.
	std::string effectName_;
	SOUNDTYPE type_;
	Phonon::MediaObject* soundEffect_; // used to play sounds;

};
#endif // SOUNDEFFECTS_H
