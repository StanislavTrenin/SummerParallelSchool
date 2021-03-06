#include "Server.h"
#include <dlfcn.h>
#include <string.h>

JNIEXPORT void JNICALL Java_Server_cLaunchMethod (JNIEnv* env, jobject obj, jstring string1, jstring string2, jint num)
{
    const char* dll = (*env)->GetStringUTFChars(env, string1, 0);
    char dll_location[200];
    strcpy(dll_location, "/home/ruslan/Kraken/SummerParallelSchool/src/");
    strcat(dll_location, dll);
    void* handle = dlopen(dll_location, RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return;
    }
    
    void (*the_function)(int);
    const char* codeName = (*env)->GetStringUTFChars(env, string2, 0);
    *(void**)(&the_function) = dlsym(handle, codeName);
    if (!the_function)
    {
        // no such symbol
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        dlclose(handle);
        return;
    }

    int call_id = (int) num;
    the_function(call_id);
    dlclose(handle);
}

void main()
{
    
}
