#include "main.h"
#include "jniutil.h"

uintptr_t g_libGTASA = 0;
const char* g_pAPKPackage;

jobject appContext;
JavaVM *mVm;
JNIEnv *mEnv;

uint8_t fps = 120;
void Main() 
{
	// .. RQ
	ARMHook::writeMem(GTA(0x463FE8), (uintptr_t)&fps, 1);
    ARMHook::writeMem(GTA(0x56C1F6), (uintptr_t)&fps, 1);
    ARMHook::writeMem(GTA(0x56C126), (uintptr_t)&fps, 1);
    ARMHook::writeMem(GTA(0x95B074), (uintptr_t)&fps, 1);
    ARMHook::writeMem(GTA(0x56C1A2), (uintptr_t)&fps, 1);

	// .. SAFix (Gun) (TODO: move to InstallPatches func)
	float fps_timeStep = (fps / 428.5714);
	float timeStep = ((int)((100 * fps_timeStep)) / 100.0);
	ARMHook::makeNOP(GTA(0x46C03C), 2);
	*(float*)(GTA(0x46C03C)) = timeStep;
}

void *InitialiseThread(void *p)
{
	Main();
	pthread_exit(0);
}          

JNIEnv *getEnv() 
{
	JNIEnv* env = nullptr;
    JavaVM* javaVM = mVm;
	int getEnvStat = javaVM->GetEnv((void**)& env, JNI_VERSION_1_6);

	if (getEnvStat == JNI_EDETACHED)
		if (javaVM->AttachCurrentThread(&env, NULL) != 0)
		  return nullptr;

	if (getEnvStat == JNI_EVERSION)
	    return nullptr;

	if (getEnvStat == JNI_ERR)
	   return nullptr;

	return env;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    mVm = vm;
    mEnv = getEnv();

	appContext = GetGlobalActivity(mEnv);
    if(appContext != NULL) 
	{ 
        g_pAPKPackage = mEnv->GetStringUTFChars(GetPackageName(mEnv, appContext), NULL);
		// toasty(OBFUSCATE("WNFPS"));

        char sea_of_feelings[100+1];
		sprintf(sea_of_feelings, OBFUSCATE("Package: %s / Plugin: Frame Rate"), g_pAPKPackage);

		__android_log_write(ANDROID_LOG_INFO, OBFUSCATE("WNPath"), OBFUSCATE("Powered by Weikton"));
		__android_log_write(ANDROID_LOG_INFO, OBFUSCATE("WNPath"), sea_of_feelings);
    }
    
	g_libGTASA = ARMHook::getLibraryAddress(OBFUSCATE("libGTASA.so"));
	if(g_libGTASA)
	{
		srand(time(0));

		uintptr_t memlib_start = (g_libGTASA + 0x174D4);
		uintptr_t size = 0x1234A;
		
		ARMHook::InitialiseTrampolines(memlib_start, size);

		pthread_t thread;
		pthread_create(&thread, 0, InitialiseThread, 0);
	}

	return JNI_VERSION_1_6;
}

uint32_t GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);

	return (tv.tv_sec*1000 + tv.tv_usec/1000);
}