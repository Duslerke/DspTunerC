#include <stdio.h>
#include <portaudio.h>

const double SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;

int captureMicInput(
    const void *paInputBuffer,
    void *paOutputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    const float *f32Buffer = (const float *)paInputBuffer;

    printf("First sample within the buffer %f\n", f32Buffer[0]);

    return paContinue;
}

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

    printf("Opening Default device stream.\n");

    PaStream *stream;
    err = Pa_OpenDefaultStream(
        &stream,
        1,         // mono mic
        0,         // no output channels
        paFloat32, // practically infinite dynamic range
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        captureMicInput,
        NULL);

    if (err != paNoError)
    {
        fprintf(stderr, "Failed to open the default device stream.");
        Pa_Terminate();
        return 1;
    }


    Pa_Terminate();
    return 0;
}
