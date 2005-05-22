/***************************************************************************
                          playerportaudio.h  -  description
                             -------------------
    begin                : Wed Feb 20 2002
    copyright            : (C) 2002 by Tue and Ken Haste Andersen
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PLAYERPORTAUDIO_H
#define PLAYERPORTAUDIO_H

#include "player.h"
#include <portaudio.h>

/**
  *@author Tue and Ken Haste Andersen
  */

/** Maximum frame size used with PortAudio. Used to determine no of buffers
  * when setting latency */
const int kiMaxFrameSize = 1024;

class PlayerPortAudio : public Player  {
public:
    PlayerPortAudio(ConfigObject<ConfigValue> *config);
    ~PlayerPortAudio();
    bool initialize();
    bool open();
    void close();
    void setDefaults();
    QStringList getInterfaces();
    QStringList getSampleRates();
    static QString getSoundApi();
    QString getSoundApiName() { return getSoundApi(); };
    /** Satisfy virtual declaration in EngineObject */
    void process(const CSAMPLE *, const CSAMPLE *, const int) {};
    /** Process samples. Called from PortAudio callback */
    int callbackProcess(int iBufferSize, float *out);

protected:
    /** Get id of device with a given name. Returns -1 if device is not found */
    PaDeviceID getDeviceID(QString name);
    /** Get channel number of device with a given name. Returns -1 if device is no found */
    int getChannelNo(QString name);

    /** PortAudio stream */
    PortAudioStream *m_pStream;
    /** Id of currently open device. -1 if no device is open */
    PaDeviceID m_devId;
    /** Channels used for each output from Mixxx. Set to -1 when not in use */
    int m_iMasterLeftCh, m_iMasterRigthCh, m_iHeadLeftCh, m_iHeadRightCh;
    /** True if PortAudio was sucessfully initialized */
    bool m_bInit;
    /** Number of buffers */
    int m_iNumberOfBuffers;
};


int paCallback(void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      PaTimestamp outTime, void *_player);
#endif
