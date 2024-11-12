#include "NativeOboeModule.h"
#include "oboe/Oboe.h"
#include <android/log.h>

namespace facebook::react {
    std::shared_ptr<oboe::AudioStream> mStream;

    oboe::DataCallbackResult
NativeOboeModule::onAudioReady(oboe::AudioStream* audioStream,
                                                 void* audioData,
                                                 int32_t numFrames) {
        // Fill the output buffer with random white noise.
        const int numChannels = oboe::DefaultStreamValues::ChannelCount;
        // This code assumes the format is AAUDIO_FORMAT_PCM_FLOAT.
        float *output = (float *)audioData;
        for (int frameIndex = 0; frameIndex < numFrames; frameIndex++) {
            for (int channelIndex = 0; channelIndex < numChannels; channelIndex++) {
                float noise = (float)(drand48() - 0.5);
                *output++ = noise;
            }
        }
        return oboe::DataCallbackResult::Continue;
    }

NativeOboeModule::NativeOboeModule(std::shared_ptr<CallInvoker> jsInvoker)
    : NativeOboeModuleCxxSpec(std::move(jsInvoker)) {}

void NativeOboeModule::initOboe(jsi::Runtime& rt) {
    oboe::AudioStreamBuilder builder;
        builder.setSharingMode(oboe::SharingMode::Exclusive)
                ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
                ->setFormat(oboe::AudioFormat::Float)
                ->setChannelCount(oboe::DefaultStreamValues::ChannelCount)
                ->setDataCallback(this);

    oboe::Result result = builder.openStream(mStream);
    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, "1234", "Failed to create stream. Error: %s", oboe::convertToText(result));
    }

    oboe::AudioFormat format = mStream->getFormat();
    __android_log_print(ANDROID_LOG_ERROR, "1234", "AudioStream format is %s", oboe::convertToText(format));

    mStream->requestStart();
}

} // namespace facebook::react