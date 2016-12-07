////////////////////////////////////////////////////////////////////////////////
#include "openaltools.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
void alFlushErrors()
{
    int i = 0;
    ALenum err = alGetError();
    while (err != AL_NO_ERROR)
    {
        if (i > 1000)
            break;
        err = alGetError();
        ++i;
    }
}
////////////////////////////////////////////////////////////////////////////////
const char* alGetErrorString(ALenum err)
{
    switch(err)
    {
    case AL_NO_ERROR:
        return "AL_NO_ERROR";
    case AL_INVALID_ENUM:
        return "AL_INVALID_ENUM";
    case AL_INVALID_VALUE:
        return "AL_INVALID_VALUE";
    case AL_INVALID_OPERATION:
        return "AL_INVALID_OPERATION";
    case AL_OUT_OF_MEMORY:
        return "AL_OUT_OF_MEMORY";
    }
    return "AL_UNKNOWN_ERROR";
}
////////////////////////////////////////////////////////////////////////////////
void alLogCurrentError()
{
    ALenum err = alGetError();
    if (err != AL_NO_ERROR)
        log().log() << alGetErrorString(err) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
void alcFlushErrors(ALCdevice *device)
{
    int i = 0;
    ALCenum err = alcGetError(device);
    while (err != ALC_NO_ERROR)
    {
        if (i > 1000)
            break;
        err = alcGetError(device);
        ++i;
    }
}
////////////////////////////////////////////////////////////////////////////////
const char* alcGetErrorString(ALCenum err)
{
    switch(err)
    {
    case ALC_NO_ERROR:
        return "ALC_NO_ERROR";
    case ALC_INVALID_ENUM:
        return "ALC_INVALID_ENUM";
    case ALC_INVALID_VALUE:
        return "ALC_INVALID_VALUE";
    case ALC_INVALID_CONTEXT:
        return "ALC_INVALID_CONTEXT";
    case ALC_INVALID_DEVICE:
        return "ALC_INVALID_DEVICE";
    case ALC_OUT_OF_MEMORY:
        return "ALC_OUT_OF_MEMORY";
    }
    return "ALC_UNKNOWN_ERROR";
}
////////////////////////////////////////////////////////////////////////////////
void alcLogCurrentError(ALCdevice *device)
{
    ALCenum err = alcGetError(device);
    if (err != ALC_NO_ERROR)
        log().log() << alcGetErrorString(err) << "\n";
}
////////////////////////////////////////////////////////////////////////////////
