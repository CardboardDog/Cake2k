#include <pspkernel.h>
#include <pspdisplay.h>
static int exited = 0;
int running(){
    return !exited; 
}
int exitCallback(int arg1, int arg2, void *common){
    exited = 1;
    return 0;
}
int callbackThread(SceSize args, void *argp){
    int id;
    id = sceKernelCreateCallback("Exited",exitCallback,NULL);
    sceKernelRegisterExitCallback(id);
    sceKernelSleepThreadCB();
    return 0;
}
int setupCallbacks(void){
    int id = 0;
    id = sceKernelCreateThread("update_thread",callbackThread,0x11,0xFA0,0,0);
    if(id >= 0)sceKernelStartThread(id,0,0);
    return id;
}