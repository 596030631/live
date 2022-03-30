#include <jni.h>
#include <string>
#include <UsageEnvironment.hh>
#include <BasicUsageEnvironment.hh>
#include "testProgs/testRTSPClient.h"
#include "android/log.h"

extern "C" JNIEXPORT void JNICALL
Java_com_shuaijun_live_MainActivity_stringFromJNI(
        JNIEnv *jniEnv,
        jobject /* this */) {
    char eventLoopWatchVariable = 0;
    TaskScheduler *scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment *env = BasicUsageEnvironment::createNew(*scheduler);
    const char *rtspUrl = "rtsp://admin:123456@192.168.1.11:554/stream0";
    const char *progName = "progName";
    openURL(*env, progName, rtspUrl);
    env->taskScheduler().doEventLoop(&eventLoopWatchVariable);
}

