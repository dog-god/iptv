/*
 * add by armite@126.com
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "advanced.h"
#include <sys/prctl.h>

extern "C" {
#include "portlibs/ansi_c/java.h"
#include "javavm/export/jni.h"

static void* runCdcThread(void *url)
{
    int argc = 9;
    const char *argv[9] = {
        "CVM",
        "-Dsun.midp.home.path=/data/data/com.armite.webkit/cvm",
        "-Dcom.sun.midp.mainClass.name=com.sun.midp.main.CdcMIDletSuiteLoader",
        "-Djava.home=/data/data/com.armite.webkit/cvm",
        "sun.misc.MIDPLauncher",
        "-suitepath",
        "suite.jar",
        "-1",
        "internal"
    };

    MYLOGI("runCdcThread start %d %d %s\n", getpid(), gettid(), (const char *)url);
    pthread_setname_np(pthread_self(), "runCdcThread");
    prctl(PR_SET_NAME, "runCdcThread");
    argv[6] = (const char *)url;
    int ret = ansiJavaMain(argc, argv, JNI_CreateJavaVM);
    MYLOGI("runCdcThread retsult %d %d %d\n", ret, getpid(), gettid());
}

static pthread_t cdcThread;
void startCVM(char *url)
{
    MYLOGI("startCVM %s %d %d", url, getpid(), gettid());
    if (access(url, R_OK)) {
        MYLOGI("startCVM %s fail to read", url);
        return;
    }

    pthread_create(&cdcThread, 0, runCdcThread, (void *)url);
}

}


