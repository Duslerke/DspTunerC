#include <stdio.h>
#include <portaudio.h>

int main()
{
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError)
    {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        return 1;
    }

    printf("PortAudio initialized successfully!\n");

    const PaDeviceIndex defaultInputIndex = Pa_GetDefaultInputDevice();

    if (defaultInputIndex == paNoDevice)
    {
        fprintf(stderr, "Error! No device.");
        Pa_Terminate();
        return 1;
    }

    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(defaultInputIndex);

    if (deviceInfo == NULL)
    {
        fprintf(stderr, "Error! Device Info Null Pointer");
        Pa_Terminate();
        return 1;
    }

    printf("Name: %s\n", deviceInfo->name);
    printf("Default Sample Rate: %f\n", deviceInfo->defaultSampleRate);

    Pa_Terminate();
    return 0;
}
