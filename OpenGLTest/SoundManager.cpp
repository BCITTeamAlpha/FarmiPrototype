#include "SoundManager.h"
#include <iostream>
#include <mutex>
//defines for track filenames
#define MAIN_BGM "../Music/bgm1.wav" 
#define MENU_BGM "../Music/bgm2.wav"
#define WELCOME_BGM "../Music/bgm3.wav"

//defines for SoundEffect Names
#define JUMP "../Sounds/jumpSE.wav"
#define DAMAGE "../Sounds/damageSE.wav"
#define GOAT_DEATH "../Sounds/goatDeath.wav"

//private mutex variable
std::mutex SoundMtx;
//our currently selected sound effect buffer to play sound effects from.
int currentSoundBuffer;

//Constructor. Creates our Sound Engine object, loads all our audio files into memory, and instantiates our Audio sources/buffers. Also subscribes us to events.
SoundManager::SoundManager() {
    //make engine object
    soundObject = new Sound();
    //make BGM objects
    soundObject->makeBuffer(&bgmBuffer);
    soundObject->makeSource(&bgmSource);
    //make Sound effect Objects
    for (int i = 0; i < MAX_SOUND_BUFFERS; i++) {
        soundObject->makeSource(&seSource[i]);
        soundObject->makeBuffer(&seBuffer[i]);
    }
    //set our Sound effect buffer to the first one
    currentSoundBuffer = 0;
    //load in audio files to memory
    loadAudioData();
    //subscribe to events
	EventManager::subscribe(PLAY_SONG, this);
	EventManager::subscribe(PLAY_SOUND, this);
	EventManager::subscribe(GAME_START, this);
}

//method that loads Audio Files into memory to minimize repeated file I/O
void SoundManager::loadAudioData() {
    //Load Music Section
    
    //load main BGM and store it
    AudioData temp; //temp storage
    temp = soundObject->getAudioData(MAIN_BGM); //attempt to read file
    if (temp.data == NULL) {
        std::cout << "Main BGM failed to store correctly." << std::endl; //handle failed file read
    }
    Music.insert(std::pair<TrackList,AudioData>(MainBGM, temp)); //store in track memory with handle
    
    //load menu BGM, steps are identical to above but with different file and Handle
    temp = soundObject->getAudioData(MENU_BGM);
    if (temp.data == NULL) {
        std::cout << "Menu BGM failed to store correctly." << std::endl;
    }
    Music.insert(std::pair<TrackList, AudioData>(MenuBGM, temp));

    //load welcome message BGM, steps are identical to above but with different file and Handle
    temp = soundObject->getAudioData(WELCOME_BGM);
    if (temp.data == NULL) {
        std::cout << "Welcome BGM failed to store correctly." << std::endl;
    }
    Music.insert(std::pair<TrackList, AudioData>(WelcomeBGM, temp));

    //Load Sounds Section
    //Jump Sound
    temp = soundObject->getAudioData(JUMP); //attempt to read file
    if (temp.data == NULL) {
        std::cout << "Jump SE failed to store correctly." << std::endl; //handle failed file read
    }
    SoundEffects.insert(std::pair<SoundsList, AudioData>(Jump, temp)); //store in Sounds Memory with handle

    //Explosion Sound, steps are identical to above but with different file and Handle
    temp = soundObject->getAudioData(DAMAGE);
    if (temp.data == NULL) {
        std::cout << "Explosion SE failed to store correctly." << std::endl;
    }
    SoundEffects.insert(std::pair<SoundsList, AudioData>(Damage, temp));

    //death Sound 1, steps are identical to above but with different file and Handle
    temp = soundObject->getAudioData(GOAT_DEATH);
    if (temp.data == NULL) {
        std::cout << "Death SE failed to store correctly." << std::endl;
    }
    SoundEffects.insert(std::pair<SoundsList, AudioData>(GoatDeath, temp));
}

//destructor. Cleans up the engine object/ local memory and unsubscribes
SoundManager::~SoundManager() {
    cleanUp();
	EventManager::unsubscribe(PLAY_SONG, this);
	EventManager::unsubscribe(PLAY_SOUND, this);
	EventManager::unsubscribe(GAME_START, this);
}

//Method that plays the given song at the given position
void SoundManager::playSong(TrackList track, float x, float y, float z) {
    //ensure buffer is cleared
    soundObject->PauseAudio(bgmSource); //prevent accessing active memory
    soundObject->clearBuffer(bgmBuffer,bgmSource); //empty buffer to load new data

    //switch statement that handles each song. Format is the same for each.
        // Song Label
            // load song data into the BGM buffer from memory and attach it to the source
            // set if we want this track to loop. We usually do, but not always
            // set the location from which the song should play.
            // actually play music from the source
    switch (track){
        case MainBGM:
            soundObject->bufferData(bgmBuffer, bgmSource, Music.find(MainBGM)->second);
            soundObject->toggleLooping(bgmSource, true);
            soundObject->placeSource(bgmSource, x, y, z);
            soundObject->PlayAudio(bgmSource);
            break;
        case MenuBGM:
            soundObject->bufferData(bgmBuffer, bgmSource, Music.find(MenuBGM)->second);
            soundObject->toggleLooping(bgmSource, true);
            soundObject->placeSource(bgmSource, x, y, z);
            soundObject->PlayAudio(bgmSource);
            break;
        case WelcomeBGM:
            soundObject->bufferData(bgmBuffer, bgmSource, Music.find(WelcomeBGM)->second);
            soundObject->toggleLooping(bgmSource, false);
            soundObject->placeSource(bgmSource, x, y, z);
            soundObject->PlayAudio(bgmSource);
            break;
        default:
            break;
    }
}

//method that plays the given sound effect at the given location
void SoundManager::playSound(SoundsList soundEffect, float x, float y, float z) {
    
    //mutex check to ensure we don't commit access violations by accessing dead buffers while they're being remade.
    SoundMtx.lock();
    int selectedBuffer = currentSoundBuffer; //selct the current buffer
    currentSoundBuffer++; //increment the buffer to the next buffer
    if (currentSoundBuffer >= MAX_SOUND_BUFFERS) { //if we have gone past the number of buffers we have
        currentSoundBuffer = 0; //wrap back around to oldest buffer
    }
    SoundMtx.unlock(); //unlock the mutex
    
    //ensure that our selected buffer is cleared
    soundObject->PauseAudio(seSource[selectedBuffer]); //prevent access to active memory
    soundObject->clearBuffer(seBuffer[selectedBuffer], seSource[selectedBuffer]); //empty out any existing data from the buffer

    //switch statement that handles each sound. Format is the same for each.
        // Sound Label
            // load sound data into the selected sound buffer from memory and attach it to the source
            // set if we want this track to loop. We usually don't, but not always
            // set the location from which the sound should play.
            // actually play sound from the source
    switch (soundEffect) {
    case Jump:
        soundObject->bufferData(seBuffer[selectedBuffer], seSource[selectedBuffer], SoundEffects.find(Jump)->second);
        soundObject->toggleLooping(seSource[selectedBuffer], false);
        soundObject->placeSource(seSource[selectedBuffer], x, y, z);
        soundObject->PlayAudio(seSource[selectedBuffer]);
        break;
    case Damage:
        soundObject->bufferData(seBuffer[selectedBuffer], seSource[selectedBuffer], SoundEffects.find(Damage)->second);
        soundObject->toggleLooping(seSource[selectedBuffer], false);
        soundObject->placeSource(seSource[selectedBuffer], x, y, z);
        soundObject->PlayAudio(seSource[selectedBuffer]);
        break;
    case GoatDeath:
        soundObject->bufferData(seBuffer[selectedBuffer], seSource[selectedBuffer], SoundEffects.find(GoatDeath)->second);
        soundObject->toggleLooping(seSource[selectedBuffer], false);
        soundObject->placeSource(seSource[selectedBuffer], x, y, z);
        soundObject->PlayAudio(seSource[selectedBuffer]);
        break;
    default:
        break;
    }
}

//helper for the destructor that deletes all of our stored memory
void SoundManager::cleanUp() {
    //clean up step

    //bgm cleanup
    alDeleteSources(1, &bgmSource);
    alDeleteBuffers(1, &bgmBuffer);

    //sound effect cleanup
    for (int i = 0; i < MAX_SOUND_BUFFERS; i++) {
        alDeleteSources(1, &seSource[i]);
        alDeleteBuffers(1, &seBuffer[i]);
    }

    //sound object cleanup
    soundObject->~Sound();
}

//notify method for the event system
void SoundManager::notify(EventName eventName, Param* param) {

    //switch based on event name to handle properly
    switch (eventName) {
        case PLAY_SONG: { //play a piece of BGM
            TrackParams* TrackInfo;
            // Safetly cast generic param pointer to a specific type
            TypeParam<TrackParams *> *p = dynamic_cast<TypeParam<TrackParams*> *>(param);
            if (p != nullptr) {
                // Successful type cast
                //extract out the Track Params object
                TrackInfo = p->Param;
                //call the play song method with the Track Param data
                playSong(TrackInfo->track, TrackInfo->x, TrackInfo->y, TrackInfo->z);
            }
            break;
        }
        case PLAY_SOUND:{ //play a specific sound
            SoundParams* SoundInfo;
            // Safetly cast generic param pointer to a specific type
            TypeParam<SoundParams*> *sound = dynamic_cast<TypeParam<SoundParams*> *>(param);
            if (sound != nullptr) {
                // Successful type cast
                //extract out the Sound Params object
                SoundInfo = sound->Param;
                //call the play sound method with the Sound Param data
                playSound(SoundInfo->sound, SoundInfo->x, SoundInfo->y, SoundInfo->z);
                //delete pointers so they don't stay in the heap
                delete SoundInfo;
                delete param;
            }
            break;
        }
        case GAME_START: { //transition between main menu and main scene
            //play welcome
            playSong(WelcomeBGM, 0, 0, 0);
            //wait for welcome to finish
            while (soundObject->isPlaying(bgmSource)){}
            //play main music
            playSong(MainBGM,0,0,0);
        }
        default:
            break;
    }

}