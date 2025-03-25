#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <cstdio>
#include <string>
#include <easyx.h>//包含easyx图形库
#include<mmsystem.h>
//Windows多媒体API的头文件，包含了播放音频、视频等多媒体功能的函数和结构体的声明。
#pragma comment(lib,"Winmm.lib")
//这是一个编译器指令，告诉链接器在链接时将Winmm.lib库文件包含进来。Winmm.lib是Windows多媒体API的库文件，包含了实现多媒体功能的函数。
using namespace std;
void PlayMusic(const char* music,bool repeat=false,int volume=-1)//第一个参数是要打开音乐的文件名，第二个参数是是否开启循环，默认是不开启的，第三个参数是设置音量，默认是-1，也就是使用默认的音量
{
    static int i=0;
    char cmd[100]={0};
    sprintf(cmd,"open %s alias bgm%d",music,i);
    MCIERROR ret=mciSendString(cmd, NULL, 0, NULL);//打开音乐
    if(ret!=0)//如果失败，返回非0值，成功返回0
    {
        //获取错误消息,并存储在字符串中
        char error[100];
        mciGetErrorString(ret,error,sizeof(error));
        /*
        函数作用
            mciGetErrorString 将 MCI（媒体控制接口）函数返回的错误代码 ret 转换为人类可读的错误描述，并存储在缓冲区 error 中。
            参数解析
                ret：MCI 函数（如 mciSendCommand）返回的错误代码。
                error：用于存储错误信息的字符数组（如 char error[256];）。
                sizeof(error)：缓冲区的总字节大小，确保写入时不会溢出。
        */
        printf("[open] error: %s",error);//输出错误信息
    }
    sprintf(cmd,"play bgm%d %s",i,repeat?"repeat":"");
    ret=mciSendString(cmd, NULL, 0, NULL);//打开音乐
    if(ret!=0)//如果失败，返回非0值，成功返回0
    {
        //获取错误消息,并存储在字符串中
        char error[100];
        mciGetErrorString(ret,error,sizeof(error));
        /*
        函数作用
            mciGetErrorString 将 MCI（媒体控制接口）函数返回的错误代码 ret 转换为人类可读的错误描述，并存储在缓冲区 error 中。
            参数解析
                ret：MCI 函数（如 mciSendCommand）返回的错误代码。
                error：用于存储错误信息的字符数组（如 char error[256];）。
                sizeof(error)：缓冲区的总字节大小，确保写入时不会溢出。
        */
        printf("[play] error: %s",error);//输出错误信息
    }
    if(volume!=-1)
    {
        sprintf(cmd,"setaudio bgm%d volume to %d",i,volume);
        ret=mciSendString(cmd, NULL, 0, NULL);//设置音乐音量
        if(ret!=0)//如果失败，返回非0值，成功返回0
        {
            //获取错误消息,并存储在字符串中
            char error[100];
            mciGetErrorString(ret,error,sizeof(error));
            /*
            函数作用
               mciGetErrorString 将 MCI（媒体控制接口）函数返回的错误代码 ret 转换为人类可读的错误描述，并存储在缓冲区 error 中。
               参数解析
                   ret：MCI 函数（如 mciSendCommand）返回的错误代码。
                  error：用于存储错误信息的字符数组（如 char error[256];）。
                  sizeof(error)：缓冲区的总字节大小，确保写入时不会溢出。
            */
            printf("[volume] error: %s",error);//输出错误信息
        }
    }
    i++;
}
int main()
{
    PlayMusic("Music/j57gx-hru1n.mp3",true,1000);
    // mciSendString("open Music/j57gx-hru1n.mp3 alias bgm", NULL, 0, NULL);//打开音乐
    // mciSendString("play bgm", NULL, 0, NULL); // 播放音乐
    // MCIERROR ret=mciSendString("setaudio bgm volume 1000", NULL, 0, NULL); //设置播放别名为 myaudio的设备的音量，音量的范围在：0~1000
    //MCIERROR使用这个类型来判断mciSendString()是否错误，如果失败，返回非0值，成功返回0
    /*
        第一个参数是
            lpszCommand: 要发送的 MCI 命令字符串
            类型: LPCTSTR（指向常量字符串的指针）
            作用: 这是一个字符串参数，用于指定要发送给 MCI 设备的命令。
            内容: 命令字符串由命令和参数组成，格式为 "命令 参数1 参数2 ..."
            例如：
                "open mysong.mp3 alias myaudio"：打开文件 mysong.mp3 并为其分配别名 myaudio。
                "play myaudio"：播放别名为 myaudio 的设备。
                "status myaudio mode"：查询别名为 myaudio 的设备的状态。
                "setaudio myaudio volume to 100"设置播放别名为 myaudio的设备的音量，音量的范围在：0~1000
            注意事项:
            命令字符串中的文件名路径需要使用双反斜杠 \\ 或单斜杠 /，以避免转义字符问题。
            命令字符串是区分大小写的。
        第二个参数是
            lpszReturnString: 用于接收返回信息的缓冲区
            类型: LPTSTR（指向字符串缓冲区的指针）
            作用: 这是一个输出参数，用于接收 MCI 命令执行后的返回信息。
            使用场景:
                当你发送的命令需要返回信息时（例如查询设备状态），可以将返回信息存储在这个缓冲区中。
                如果不需要返回信息，可以设置为 NULL
        第三个参数
            3. cchReturn: 返回信息缓冲区的大小
            类型: UINT（无符号整数）
            作用: 指定 lpszReturnString 缓冲区的大小（以字符为位）。
            使用场景:
                当 lpszReturnString 不为 NULL 时，需要指定缓冲区的大小，以防止缓冲区溢出。
                如果 lpszReturnString 为 NULL，则此参数应设为
            注意事项:
                缓冲区大小应足够大，以容纳返回的信息。
                如果缓冲区太小，可能会导致信息截断或缓冲区溢出。
        第四个参数
            hwndCallback: 回调窗口的句柄
            类型: HANDLE（窗口句柄）
            作用: 指定一个窗口句柄，用于接收 MCI 设备的通知消息（例如播放完成的通知）。
                使用场景:
                当你希望 MCI 设备在特定事件（如播放完成）发生时通知你的程序时，可以指定一个窗口句柄。
                如果不需要回调通知，可以设置为 NULL。
    */
    // if(ret!=0)//如果失败，返回非0值，成功返回0
    // {
    //     //获取错误消息,并存储在字符串中
    //     char error[100];
    //     mciGetErrorString(ret,error,sizeof(error));
    //     /*
    //     函数作用
    //         mciGetErrorString 将 MCI（媒体控制接口）函数返回的错误代码 ret 转换为人类可读的错误描述，并存储在缓冲区 error 中。
    //         参数解析
    //             ret：MCI 函数（如 mciSendCommand）返回的错误代码。
    //             error：用于存储错误信息的字符数组（如 char error[256];）。
    //             sizeof(error)：缓冲区的总字节大小，确保写入时不会溢出。
    //     */
    //     puts(error);//输出错误信息
    // }
    //专门用来播放音效的函数
    /*
        PlaySound 是 Windows API 中的一个函数，用于播放音频文件或系统声音。它支持以下功能：
        播放 .wav 文件。
        播放系统预定义的声音（如提示音）。
        从程序资源中加载并播放音频。
        从内存中直接播放音频数据。
        函数原型
            BOOL PlaySound(
                LPCSTR pszSound,  // 声音来源（文件路径、资源名、内存地址等）
                HMODULE hmod,     // 包含资源的模块句柄（若从资源加载）
                DWORD  fdwSound   // 播放标志（控制播放行为）
                参数详解
                3.1 pszSound
                    作用：指定要播放的声音来源。
                    常见值：
                        文件路径：例如 "C:\\sound.wav"（注意路径中的反斜杠需要转义）。
                        资源名：例如 MAKEINTRESOURCE(IDR_WAVE1)（需在资源文件中定义声音资源）。
                        内存地址：直接指向音频数据的指针（需配合 SND_MEMORY 标志）。
                        系统声音：例如 "SystemAsterisk"（需配合 SND_ALIAS 标志）。
                3.2 hmod
                    作用：指定包含声音资源的模块句柄（仅当从资源加载时使用）。
                    常用值：
                        NULL：默认值，表示不使用资源。
                        GetModuleHandle(NULL)：当前程序的模块句柄。
                3.3 fdwSound
                    作用：控制播放行为的标志位，可以组合使用。
                    常用标志：
                        SND_SYNC：同步播放，函数会阻塞直到播放完成。
                        SND_ASYNC：异步播放，函数立即返回，声音在后台播放。
                        SND_LOOP：循环播放（需与 SND_ASYNC 组合使用）。
                        SND_NODEFAULT：如果指定的声音不存在，不播放默认声音。
                        SND_MEMORY：从内存加载声音数据（pszSound 为内存指针）。
                        SND_ALIAS：播放系统预定义声音（如 "SystemAsterisk"）。
                        SND_FILENAME：指定 pszSound 为文件路径。
    */
    system("pause");//防止窗口一闪而过,闪退
    return 0;
}