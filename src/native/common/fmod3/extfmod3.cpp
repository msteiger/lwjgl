/* 
 * Copyright (c) 2002 Light Weight Java Game Library Project
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 * * Redistributions of source code must retain the above copyright 
 *	 notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'Light Weight Java Game Library' nor the names of 
 *	 its contributors may be used to endorse or promote products derived 
 *	 from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <stdio.h>
#include "extfmod3.h"

/** Instance of fmod  */
FMOD_INSTANCE * fmod_instance = NULL;

// jnienvs
JNIEnv *mixer_jnienv;
JNIEnv *stream_jnienv;

// FMusic cached fields
jmethodID music_instcallback;
jmethodID music_ordercallback;
jmethodID music_rowcallback;
jmethodID music_zxxcallback;
jclass fmusic;

#ifdef _WIN32
/**
 * DLL entry point for Windows. Called when Java loads the .dll
 */
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	return true;
}
#endif

/**
 * Creates and loads the FMOD instance
 *
 * @param path path to try to load dll
 */
void fmod_create(JNIEnv *env, char* path) {
  fmod_instance = FMOD_CreateInstance(path);
  
  if (fmod_instance != NULL) {
    fmusic = env->FindClass("org/lwjgl/fmod3/FMusic");
    music_instcallback = env->GetStaticMethodID(fmusic, "music_instcallback", "(JI)V");
    music_ordercallback = env->GetStaticMethodID(fmusic, "music_ordercallback", "(JI)V");
    music_rowcallback = env->GetStaticMethodID(fmusic, "music_rowcallback", "(JI)V");
    music_zxxcallback = env->GetStaticMethodID(fmusic, "music_zxxcallback", "(JI)V");
  }
}

/**
 * Destroys the fmod instance
 */
void fmod_destroy() {
  if (fmod_instance != NULL) {
    FMOD_FreeInstance(fmod_instance);
  }
}