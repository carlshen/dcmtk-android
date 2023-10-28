#include <jni.h>
#include <string>
#include <android/log.h>
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

#define TAG "Dylan"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

extern "C" JNIEXPORT
jstring JNICALL Java_com_example_dcmtkdemo_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
    DcmFileFormat readFileFormat;
    OFCondition status = readFileFormat.loadFile("/sdcard/4dicom/test1.dcm");
    std::string hello = "Hello from C++";
    LOGI("open file result: %s", status.text());
    if (status.good()) {
        OFString patientName;
        status = readFileFormat.getDataset()->findAndGetOFString(DCM_PatientName, patientName);
        if (status.good()) {
            hello = patientName.c_str();
        }
    }

    return env->NewStringUTF(hello.c_str());
}
