#include <jni.h>
#include <UsageEnvironment.hh>
#include "testProgs/testRTSPClient.h"
#include "android/log.h"


extern "C" JNIEXPORT jlong JNICALL
Java_com_shuaijun_live_MainActivity_createNew(
        JNIEnv *jniEnv,
        jobject thiz, jstring rtspUrl, jstring progName) {
    TaskScheduler *scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment *env = BasicUsageEnvironment::createNew(*scheduler);
    const char *c_rtspUrl = jniEnv->GetStringUTFChars(rtspUrl, JNI_FALSE);
    const char *c_progName = jniEnv->GetStringUTFChars(progName, JNI_FALSE);
    ourRTSPClient *rtspClient = ourRTSPClient::createNew(*env, c_rtspUrl,
                                                         RTSP_CLIENT_VERBOSITY_LEVEL,
                                                         c_progName);
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "rtspUrl:%s", c_rtspUrl);
    jniEnv->ReleaseStringUTFChars(rtspUrl, c_rtspUrl);
    jniEnv->ReleaseStringUTFChars(progName, c_progName);

    if (rtspClient == NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "TAG", "RtspClient create failure");
    }
    return reinterpret_cast<jlong>(rtspClient);
}

extern "C" JNIEXPORT void JNICALL
Java_com_shuaijun_live_MainActivity_openURL(
        JNIEnv *jniEnv,
        jobject thiz, jlong client) {
    char eventLoopWatchVariable = 0;
    ourRTSPClient *rtspClient = reinterpret_cast<ourRTSPClient *>(client);
    openURL(rtspClient->envir(), rtspClient);
    rtspClient->envir().taskScheduler().doEventLoop(&eventLoopWatchVariable);
}


extern "C" JNIEXPORT void JNICALL
Java_com_shuaijun_live_MainActivity_close(
        JNIEnv *jniEnv,
        jobject thiz, jlong client) {
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "shutdownStream");
    ourRTSPClient *rtspClient = reinterpret_cast<ourRTSPClient *>(client);
    shutdownStream(rtspClient, 0);
}

