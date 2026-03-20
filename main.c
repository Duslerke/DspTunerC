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

    // unplugged device, CPU spike, driver crash, etc.
    if (f32Buffer == NULL)
    {
        printf("Casted frames buffer is missing! Skipping chunk.\n");
        return paAbort;
    }

    // printf is "line-buffered" - won't print until it sees \n.
    // this force-flushes the output buffer
    fflush(stdout);

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

    printf("Attempting to start the stream.\n");

    err = Pa_StartStream(stream);

    if (err != paNoError)
    {
        fprintf(stderr, "Failed to start the stream.");
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    printf("Stream started! Capturing audio for 2 seconds...\n");
    Pa_Sleep(5000);
    printf("Done capturing. Stopping stream...\n");

    err = Pa_StopStream(stream);
    if (err != paNoError)
    {
        fprintf(stderr, "Failed to stop the stream.\n");
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    printf("Closing the stream...\n");

    err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        fprintf(stderr, "Failed to close the stream.\n");
        Pa_Terminate();
        return 1;
    }

    printf("Stream closed safely.\n");

    Pa_Terminate();
    return 0;
}
