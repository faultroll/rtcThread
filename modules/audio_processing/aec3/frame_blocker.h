/*
 *  Copyright (c) 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_MODULES_AUDIO_PROCESSING_AEC3_FRAME_BLOCKER_H_
#define WEBRTC_MODULES_AUDIO_PROCESSING_AEC3_FRAME_BLOCKER_H_

#include <stddef.h>
#include <vector>

#include "rtc_base/array_view.h"
#include "rtc_base/constructormagic.h"
#include "modules/audio_processing/aec3/aec3_common.h"

namespace webrtc {

// Class for producing 64 sample multiband blocks from frames consisting of 1 or
// 2 subframes of 80 samples.
class FrameBlocker {
 public:
  explicit FrameBlocker(size_t num_bands);
  ~FrameBlocker();
  // Inserts one 80 sample multiband subframe from the multiband frame and
  // extracts one 64 sample multiband block.
  void InsertSubFrameAndExtractBlock(
      const std::vector<rtc::ArrayView<float>>& sub_frame,
      std::vector<std::vector<float>>* block);
  // Reports whether a multiband block of 64 samples is available for
  // extraction.
  bool IsBlockAvailable() const;
  // Extracts a multiband block of 64 samples.
  void ExtractBlock(std::vector<std::vector<float>>* block);

 private:
  const size_t num_bands_;
  std::vector<std::vector<float>> buffer_;

  RTC_DISALLOW_IMPLICIT_CONSTRUCTORS(FrameBlocker);
};
}  // namespace webrtc

#endif  // WEBRTC_MODULES_AUDIO_PROCESSING_AEC3_FRAME_BLOCKER_H_