#pragma once
#include "NativeOboeJSI.h"
#include "oboe/Oboe.h"

namespace facebook::react {

class NativeOboeModule :  public NativeOboeModuleCxxSpec<NativeOboeModule>,
                          public oboe::AudioStreamDataCallback
 {
 public:
  NativeOboeModule (std::shared_ptr<CallInvoker> jsInvoker);
  oboe::DataCallbackResult onAudioReady(oboe::AudioStream* audioStream,
                                        void* audioData,
                                        int32_t framesCount) override;

  std::shared_ptr<oboe::AudioStream> mStream;
  void initOboe(jsi::Runtime& rt);
};

} // namespace facebook::react