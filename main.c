#include <stdio.h>
#include <portaudio.h> // the "Interface" for PortAudio

int main()
{
    PaError err;

    // 1. Initialize the library
    err = Pa_Initialize();
    if (err != paNoError)
    {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return 1;
    }

    printf("PortAudio initialized successfully!\n");

    // 2. Clean up before exiting
    Pa_Terminate();
    return 0;
}
