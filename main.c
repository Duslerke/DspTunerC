#include <stdio.h>
#include <portaudio.h>

int main()
{
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError)
    {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return 1;
    }

    printf("PortAudio initialized successfully!\n");

    const PaDeviceIndex defaultInputIndex = Pa_GetDefaultInputDevice();

    if (defaultInputIndex == paNoDevice)
    {
        printf("Error! No device.");
        return 1;
    }

    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(defaultInputIndex);

    if (deviceInfo == NULL)
    {
        printf("Error! Device Info Null Pointer");
        return 1;
    }

    printf("Name: %s\n", deviceInfo->name);
    printf("Default Sample Rate: %f\n", deviceInfo->defaultSampleRate);

    Pa_Terminate();
    return 0;
}
