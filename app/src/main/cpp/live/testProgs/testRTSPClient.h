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
private:

    static void continueAfterDESCRIBE(RTSPClient *rtspClient, int resultCode, char *resultString);

    static void continueAfterSETUP(RTSPClient *rtspClient, int resultCode, char *resultString);

    static void continueAfterPLAY(RTSPClient *rtspClient, int resultCode, char *resultString);

    static void subsessionAfterPlaying(
            void *clientData);

    static void subsessionByeHandler(void *clientData, char const *reason);

    static void streamTimerHandler(void *clientData);

    static void setupNextSubsession(RTSPClient *rtspClient);

public:
    static ourRTSPClient *createNew(UsageEnvironment &env, const char *rtspURL,
                                    char const *outFilePath,
                                    int verbosityLevel = 0,
                                    char const *applicationName = NULL,
                                    portNumBits tunnelOverHTTPPortNum = 0);

    char outPath[512];
protected:
    ourRTSPClient(UsageEnvironment &env, char const *rtspURL,
                  char const *outFilePath,
                  int verbosityLevel, char const *applicationName,
                  portNumBits tunnelOverHTTPPortNum);

    // called only by createNew();
    virtual ~ourRTSPClient();

public:
    StreamClientState scs;
    void openURL(UsageEnvironment &env, ourRTSPClient *rtspClient);
    static void shutdownStream(RTSPClient *rtspClient, int exitCode = 0);
};



#endif //LIVE_TESTRTSPCLIENT_H
