#include "SoundEffects.h"
/*-----------------------------------------------------------------------------
 --
 -- FUNCION NAME: SoundEffects
 --
 -- FUNCTION PURPOSE: ctor
 --
 -- FUNCTION INTERFACE: SoundEffects::SoundEffects(const std::string name, SOUNDTYPE type)
 --
 -- FUNCTION PARAM: const std::string name: name of effect
 --                 SOUNDTYPE type: type of effect
 --
 -- PROGRAMMER: Jordan Lewis
 --
 -- DATE: March. 28th/2010
 --
 ----------------------------------------------------------------------------*/
SoundEffects::SoundEffects(QObject *parent) : QObject(parent)
{

	// do nothing right now.
}


SoundEffects::SoundEffects(const std::string path, SOUNDTYPE type)
{
    effectPath_= path;
    type_ = type;
    soundEffect_ = NULL;
}

/*-----------------------------------------------------------------------------
 --
 -- FUNCION NAME: SetSoundSource
 --
 -- FUNCTION PURPOSE: sets the source of the sound file. Confirm that we need to give document name????
 --
 -- FUNCTION INTERFACE: void SoundEffects::SetSoundSource(const std::string path)
 --
 -- FUNCTION PARAM: const std::string path: path to sound file.
 --
 -- PROGRAMMER: Jordan Lewis
 --
 -- DATE: March. 28th/2010
 --
 ----------------------------------------------------------------------------*/
void SoundEffects::SetSoundSource(const std::string path)
{
    effectPath_ = path;

    // should try catch internally to handle incorrect path specs. Must confirm try catch allowed in project.
    soundEffect_ = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(path.c_str())); // set up media source for playing when needed.
}


SoundEffects::SoundEffects(const SoundEffects& efx) : QObject()
{
	effectPath_ = efx.effectPath_;
	effectName_ = efx.effectName_;
	type_ = efx.type_;
	soundEffect_ = efx.soundEffect_;
}

/*-----------------------------------------------------------------------------
 --
 -- FUNCION NAME: PlaySound
 --
 -- FUNCTION PURPOSE: plays the audio sound file.
 --
 -- FUNCTION INTERFACE: void SoundEffects::PlaySound()
 --
 -- PROGRAMMER: Jordan Lewis
 --
 -- DATE: March. 28th/2010
 --
 ----------------------------------------------------------------------------*/
void SoundEffects::PlaySound()
{

	Phonon::MediaObject *mediaObject;
	Phonon::AudioOutput *audioOutput;

	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	mediaObject = new Phonon::MediaObject(this);

	Phonon::MediaSource source(Phonon::MediaSource("./1.wav"));
	Phonon::createPath(mediaObject, audioOutput);

    if(soundEffect_ !=  NULL)
    {
        soundEffect_->play(); // will play sound effect.
    }
}
