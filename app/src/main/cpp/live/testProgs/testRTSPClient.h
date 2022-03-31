//
// Created by sjh on 2022/3/19.
//

#ifndef LIVE_TESTRTSPCLIENT_H
#define LIVE_TESTRTSPCLIENT_H

#include "BasicUsageEnvironment.hh"
#include "liveMedia.hh"
#include "android/log.h"
#include "H264VideoFileSink.hh"

#define RTSP_CLIENT_VERBOSITY_LEVEL 1 // by default, print verbose output from each "RTSPClient"

class StreamClientState {
public:
    StreamClientState();

    virtual ~StreamClientState();

public:
    MediaSubsessionIterator *iter;
    MediaSession *session;
    MediaSubsession *subsession;
    TaskToken streamTimerTask;
    double duration;
};

class ourRTSPClient : public RTSPClient {
public:
    static ourRTSPClient *createNew(UsageEnvironment &env, char const *rtspURL,
                                    int verbosityLevel = 0,
                                    char const *applicationName = NULL,
                                    portNumBits tunnelOverHTTPPortNum = 0);

protected:
    ourRTSPClient(UsageEnvironment &env, char const *rtspURL,
                  int verbosityLevel, char const *applicationName,
                  portNumBits tunnelOverHTTPPortNum);

    // called only by createNew();
    virtual ~ourRTSPClient();

public:
    StreamClientState scs;
};


void openURL(UsageEnvironment &env, ourRTSPClient *rtspClient);
void shutdownStream(RTSPClient *rtspClient, int exitCode);


#endif //LIVE_TESTRTSPCLIENT_H
