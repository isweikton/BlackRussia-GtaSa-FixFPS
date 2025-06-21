#pragma once 

#include <jni.h>
#include <android/log.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "ARMHook.h"
#include "str_obfuscate.hpp"

extern uintptr_t g_libGTASA;
#define GTA(addr) (g_libGTASA + (addr))

extern const char* g_pAPKPackage;
extern JavaVM *mVm;
extern JNIEnv *mEnv;

uint32_t GetTickCount();
void SetFunc(uintptr_t addr, uintptr_t *orig);