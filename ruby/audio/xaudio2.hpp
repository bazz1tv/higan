/*
  xaudio2.hpp (2010-08-14)
  author: OV2
  
  ruby-specific header to provide mingw-friendly xaudio2 interfaces
*/

#ifndef XAUDIO2_RUBY_H
#define XAUDIO2_RUBY_H

//64-bit GCC fix
#define GUID_EXT EXTERN_C
#define GUID_SECT

#include <BaseTyps.h>

#define DEFINE_GUID_X(n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) GUID_EXT const GUID n GUID_SECT = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
#define DEFINE_CLSID_X(className, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    DEFINE_GUID_X(CLSID_##className, 0x##l, 0x##w1, 0x##w2, 0x##b1, 0x##b2, 0x##b3, 0x##b4, 0x##b5, 0x##b6, 0x##b7, 0x##b8)
#define DEFINE_IID_X(interfaceName, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    DEFINE_GUID_X(IID_##interfaceName, 0x##l, 0x##w1, 0x##w2, 0x##b1, 0x##b2, 0x##b3, 0x##b4, 0x##b5, 0x##b6, 0x##b7, 0x##b8)
#define X2DEFAULT(x) =x

DEFINE_CLSID_X(XAudio2, e21a7345, eb21, 468e, be, 50, 80, 4d, b9, 7c, f7, 08);
DEFINE_CLSID_X(XAudio2_Debug, f7a76c21, 53d4, 46bb, ac, 53, 8b, 45, 9c, ae, 46, bd);
DEFINE_IID_X(IXAudio2, 8bcf1f58, 9fe7, 4583, 8a, c6, e2, ad, c4, 65, c8, bb);

DECLARE_INTERFACE(IXAudio2Voice);

#define XAUDIO2_COMMIT_NOW              0
#define XAUDIO2_DEFAULT_CHANNELS        0
#define XAUDIO2_DEFAULT_SAMPLERATE      0
#define XAUDIO2_DEFAULT_FREQ_RATIO      4.0f
#define XAUDIO2_DEBUG_ENGINE            0x0001
#define XAUDIO2_VOICE_NOSRC             0x0004

typedef struct
{
    WAVEFORMATEX Format;
    union
    {
        WORD wValidBitsPerSample;
        WORD wSamplesPerBlock;
        WORD wReserved;
    } Samples;
    DWORD dwChannelMask;
    GUID SubFormat;
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE, *LPPWAVEFORMATEXTENSIBLE;
typedef const WAVEFORMATEXTENSIBLE* LPCWAVEFORMATEXTENSIBLE;

typedef enum XAUDIO2_DEVICE_ROLE
{
    NotDefaultDevice            = 0x0,
    DefaultConsoleDevice        = 0x1,
    DefaultMultimediaDevice     = 0x2,
    DefaultCommunicationsDevice = 0x4,
    DefaultGameDevice           = 0x8,
    GlobalDefaultDevice         = 0xf,
    InvalidDeviceRole = ~GlobalDefaultDevice
} XAUDIO2_DEVICE_ROLE;

typedef struct XAUDIO2_DEVICE_DETAILS
{
    WCHAR DeviceID[256];
    WCHAR DisplayName[256];
    XAUDIO2_DEVICE_ROLE Role;
    WAVEFORMATEXTENSIBLE OutputFormat;
} XAUDIO2_DEVICE_DETAILS;

typedef struct XAUDIO2_VOICE_DETAILS
{
    bUINT32 CreationFlags;
    bUINT32 InputChannels;
    bUINT32 InputSampleRate;
} XAUDIO2_VOICE_DETAILS;

typedef enum XAUDIO2_WINDOWS_PROCESSOR_SPECIFIER
{
    Processor1  = 0x00000001,
    Processor2  = 0x00000002,
    Processor3  = 0x00000004,
    Processor4  = 0x00000008,
    Processor5  = 0x00000010,
    Processor6  = 0x00000020,
    Processor7  = 0x00000040,
    Processor8  = 0x00000080,
    Processor9  = 0x00000100,
    Processor10 = 0x00000200,
    Processor11 = 0x00000400,
    Processor12 = 0x00000800,
    Processor13 = 0x00001000,
    Processor14 = 0x00002000,
    Processor15 = 0x00004000,
    Processor16 = 0x00008000,
    Processor17 = 0x00010000,
    Processor18 = 0x00020000,
    Processor19 = 0x00040000,
    Processor20 = 0x00080000,
    Processor21 = 0x00100000,
    Processor22 = 0x00200000,
    Processor23 = 0x00400000,
    Processor24 = 0x00800000,
    Processor25 = 0x01000000,
    Processor26 = 0x02000000,
    Processor27 = 0x04000000,
    Processor28 = 0x08000000,
    Processor29 = 0x10000000,
    Processor30 = 0x20000000,
    Processor31 = 0x40000000,
    Processor32 = 0x80000000,
    XAUDIO2_ANY_PROCESSOR = 0xffffffff,
    XAUDIO2_DEFAULT_PROCESSOR = XAUDIO2_ANY_PROCESSOR
} XAUDIO2_WINDOWS_PROCESSOR_SPECIFIER, XAUDIO2_PROCESSOR;

typedef struct XAUDIO2_VOICE_SENDS
{
    bUINT32 OutputCount;
    IXAudio2Voice** pOutputVoices;
} XAUDIO2_VOICE_SENDS;

typedef struct XAUDIO2_EFFECT_DESCRIPTOR
{
    IUnknown* pEffect;
    BOOL InitialState;
    bUINT32 OutputChannels;
} XAUDIO2_EFFECT_DESCRIPTOR;

typedef struct XAUDIO2_EFFECT_CHAIN
{
    bUINT32 EffectCount;
    const XAUDIO2_EFFECT_DESCRIPTOR* pEffectDescriptors;
} XAUDIO2_EFFECT_CHAIN;

typedef enum XAUDIO2_FILTER_TYPE
{
    LowPassFilter,
    BandPassFilter,
    HighPassFilter
} XAUDIO2_FILTER_TYPE;

typedef struct XAUDIO2_FILTER_PARAMETERS
{
    XAUDIO2_FILTER_TYPE Type;
    float Frequency;
    float OneOverQ;

} XAUDIO2_FILTER_PARAMETERS;

typedef struct XAUDIO2_BUFFER
{
    bUINT32 Flags;
    bUINT32 AudioBytes;
    const BYTE* pAudioData;
    bUINT32 PlayBegin;
    bUINT32 PlayLength;
    bUINT32 LoopBegin;
    bUINT32 LoopLength;
    bUINT32 LoopCount;
    void* pContext;
} XAUDIO2_BUFFER;

typedef struct XAUDIO2_BUFFER_WMA
{
    const bUINT32* pDecodedPacketCumulativeBytes;
    bUINT32 PacketCount;
} XAUDIO2_BUFFER_WMA;

typedef struct XAUDIO2_VOICE_STATE
{
    void* pCurrentBufferContext;
    bUINT32 BuffersQueued;
    bUINT64 SamplesPlayed;
} XAUDIO2_VOICE_STATE;

typedef struct XAUDIO2_PERFORMANCE_DATA
{
    bUINT64 AudioCyclesSinceLastQuery;
    bUINT64 TotalCyclesSinceLastQuery;
    bUINT32 MinimumCyclesPerQuantum;
    bUINT32 MaximumCyclesPerQuantum;
    bUINT32 MemoryUsageInBytes;
    bUINT32 CurrentLatencyInSamples;
    bUINT32 GlitchesSinceEngineStarted;
    bUINT32 ActiveSourceVoiceCount;
    bUINT32 TotalSourceVoiceCount;
    bUINT32 ActiveSubmixVoiceCount;
    bUINT32 TotalSubmixVoiceCount;
    bUINT32 ActiveXmaSourceVoices;
    bUINT32 ActiveXmaStreams;
} XAUDIO2_PERFORMANCE_DATA;

typedef struct XAUDIO2_DEBUG_CONFIGURATION
{
    bUINT32 TraceMask;
    bUINT32 BreakMask;
    BOOL LogThreadID;
    BOOL LogFileline;
    BOOL LogFunctionName;
    BOOL LogTiming;
} XAUDIO2_DEBUG_CONFIGURATION;

DECLARE_INTERFACE(IXAudio2EngineCallback)
{
    STDMETHOD_(void, OnProcessingPassStart) (THIS) PURE;
    STDMETHOD_(void, OnProcessingPassEnd) (THIS) PURE;
    STDMETHOD_(void, OnCriticalError) (THIS_ HRESULT Error) PURE;
};

DECLARE_INTERFACE(IXAudio2VoiceCallback)
{
    STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ bUINT32 BytesRequired) PURE;
    STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) PURE;
    STDMETHOD_(void, OnStreamEnd) (THIS) PURE;
    STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) PURE;
    STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) PURE;
    STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) PURE;
    STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) PURE;
};

DECLARE_INTERFACE(IXAudio2Voice)
{
    #define Declare_IXAudio2Voice_Methods() \
    STDMETHOD_(void, GetVoiceDetails) (THIS_ XAUDIO2_VOICE_DETAILS* pVoiceDetails) PURE; \
    STDMETHOD(SetOutputVoices) (THIS_ const XAUDIO2_VOICE_SENDS* pSendList) PURE; \
    STDMETHOD(SetEffectChain) (THIS_ const XAUDIO2_EFFECT_CHAIN* pEffectChain) PURE; \
    STDMETHOD(EnableEffect) (THIS_ bUINT32 EffectIndex, \
                             bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD(DisableEffect) (THIS_ bUINT32 EffectIndex, \
                              bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD_(void, GetEffectState) (THIS_ bUINT32 EffectIndex, BOOL* pEnabled) PURE; \
    STDMETHOD(SetEffectParameters) (THIS_ bUINT32 EffectIndex, \
                                    const void* pParameters, \
                                    bUINT32 ParametersByteSize, \
                                    bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD(GetEffectParameters) (THIS_ bUINT32 EffectIndex, void* pParameters, \
                                    bUINT32 ParametersByteSize) PURE; \
    STDMETHOD(SetFilterParameters) (THIS_ const XAUDIO2_FILTER_PARAMETERS* pParameters, \
                                   bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD_(void, GetFilterParameters) (THIS_ XAUDIO2_FILTER_PARAMETERS* pParameters) PURE; \
    STDMETHOD(SetVolume) (THIS_ float Volume, \
                          bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD_(void, GetVolume) (THIS_ float* pVolume) PURE; \
    STDMETHOD(SetChannelVolumes) (THIS_ bUINT32 Channels, const float* pVolumes, \
                                  bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD_(void, GetChannelVolumes) (THIS_ bUINT32 Channels, float* pVolumes) PURE; \
    STDMETHOD(SetOutputMatrix) (THIS_ IXAudio2Voice* pDestinationVoice, \
                                bUINT32 SourceChannels, bUINT32 DestinationChannels, \
                                const float* pLevelMatrix, \
                                bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE; \
    STDMETHOD_(void, GetOutputMatrix) (THIS_ IXAudio2Voice* pDestinationVoice, \
                                       bUINT32 SourceChannels, bUINT32 DestinationChannels, \
                                       float* pLevelMatrix) PURE; \
    STDMETHOD_(void, DestroyVoice) (THIS) PURE

    Declare_IXAudio2Voice_Methods();
};


DECLARE_INTERFACE_(IXAudio2MasteringVoice, IXAudio2Voice)
{
    Declare_IXAudio2Voice_Methods();
};

DECLARE_INTERFACE_(IXAudio2SubmixVoice, IXAudio2Voice)
{
    Declare_IXAudio2Voice_Methods();
};

DECLARE_INTERFACE_(IXAudio2SourceVoice, IXAudio2Voice)
{
    Declare_IXAudio2Voice_Methods();
    STDMETHOD(Start) (THIS_ bUINT32 Flags, bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE;
    STDMETHOD(Stop) (THIS_ bUINT32 Flags, bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE;
    STDMETHOD(SubmitSourceBuffer) (THIS_ const XAUDIO2_BUFFER* pBuffer, const XAUDIO2_BUFFER_WMA* pBufferWMA X2DEFAULT(NULL)) PURE;
    STDMETHOD(FlushSourceBuffers) (THIS) PURE;
    STDMETHOD(Discontinuity) (THIS) PURE;
    STDMETHOD(ExitLoop) (THIS_ bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE;
    STDMETHOD_(void, GetState) (THIS_ XAUDIO2_VOICE_STATE* pVoiceState) PURE;
    STDMETHOD(SetFrequencyRatio) (THIS_ float Ratio,
                                  bUINT32 OperationSet X2DEFAULT(XAUDIO2_COMMIT_NOW)) PURE;
    STDMETHOD_(void, GetFrequencyRatio) (THIS_ float* pRatio) PURE;
};

DECLARE_INTERFACE_(IXAudio2, IUnknown)
{
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, void** ppvInterface) PURE;
    STDMETHOD_(ULONG, AddRef) (THIS) PURE;
    STDMETHOD_(ULONG, Release) (THIS) PURE;
    STDMETHOD(GetDeviceCount) (THIS_ bUINT32* pCount) PURE;
    STDMETHOD(GetDeviceDetails) (THIS_ bUINT32 Index, XAUDIO2_DEVICE_DETAILS* pDeviceDetails) PURE;
    STDMETHOD(Initialize) (THIS_ bUINT32 Flags X2DEFAULT(0),
                           XAUDIO2_PROCESSOR XAudio2Processor X2DEFAULT(XAUDIO2_DEFAULT_PROCESSOR)) PURE;
    STDMETHOD(RegisterForCallbacks) (IXAudio2EngineCallback* pCallback) PURE;
    STDMETHOD_(void, UnregisterForCallbacks) (IXAudio2EngineCallback* pCallback) PURE;
    STDMETHOD(CreateSourceVoice) (THIS_ IXAudio2SourceVoice** ppSourceVoice,
                                  const WAVEFORMATEX* pSourceFormat,
                                  bUINT32 Flags X2DEFAULT(0),
                                  float MaxFrequencyRatio X2DEFAULT(XAUDIO2_DEFAULT_FREQ_RATIO),
                                  IXAudio2VoiceCallback* pCallback X2DEFAULT(NULL),
                                  const XAUDIO2_VOICE_SENDS* pSendList X2DEFAULT(NULL),
                                  const XAUDIO2_EFFECT_CHAIN* pEffectChain X2DEFAULT(NULL)) PURE;
    STDMETHOD(CreateSubmixVoice) (THIS_ IXAudio2SubmixVoice** ppSubmixVoice,
                                  bUINT32 InputChannels, bUINT32 InputSampleRate,
                                  bUINT32 Flags X2DEFAULT(0), bUINT32 ProcessingStage X2DEFAULT(0),
                                  const XAUDIO2_VOICE_SENDS* pSendList X2DEFAULT(NULL),
                                  const XAUDIO2_EFFECT_CHAIN* pEffectChain X2DEFAULT(NULL)) PURE;
    STDMETHOD(CreateMasteringVoice) (THIS_ IXAudio2MasteringVoice** ppMasteringVoice,
                                     bUINT32 InputChannels X2DEFAULT(XAUDIO2_DEFAULT_CHANNELS),
                                     bUINT32 InputSampleRate X2DEFAULT(XAUDIO2_DEFAULT_SAMPLERATE),
                                     bUINT32 Flags X2DEFAULT(0), bUINT32 DeviceIndex X2DEFAULT(0),
                                     const XAUDIO2_EFFECT_CHAIN* pEffectChain X2DEFAULT(NULL)) PURE;
    STDMETHOD(StartEngine) (THIS) PURE;
    STDMETHOD_(void, StopEngine) (THIS) PURE;
    STDMETHOD(CommitChanges) (THIS_ bUINT32 OperationSet) PURE;
    STDMETHOD_(void, GetPerformanceData) (THIS_ XAUDIO2_PERFORMANCE_DATA* pPerfData) PURE;
    STDMETHOD_(void, SetDebugConfiguration) (THIS_ const XAUDIO2_DEBUG_CONFIGURATION* pDebugConfiguration,
                                             void* pReserved X2DEFAULT(NULL)) PURE;
};

__inline HRESULT XAudio2Create(IXAudio2** ppXAudio2, bUINT32 Flags X2DEFAULT(0),
                               XAUDIO2_PROCESSOR XAudio2Processor X2DEFAULT(XAUDIO2_DEFAULT_PROCESSOR))
{
    IXAudio2* pXAudio2;
        HRESULT hr = CoCreateInstance((Flags & XAUDIO2_DEBUG_ENGINE) ? CLSID_XAudio2_Debug : CLSID_XAudio2,
                                      NULL, CLSCTX_INPROC_SERVER, IID_IXAudio2, (void**)&pXAudio2);
        if (SUCCEEDED(hr))
        {
            hr = pXAudio2->Initialize(Flags, XAudio2Processor);
            if (SUCCEEDED(hr))
            {
                *ppXAudio2 = pXAudio2;
            }
            else
            {
                pXAudio2->Release();
            }
        }
    return hr;
}
#endif
