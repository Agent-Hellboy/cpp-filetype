// Copyright 2025 Prince Roshan <princekrroshan01@gmail.com>

#ifndef INCLUDE_FILETYPE_TYPES_AUDIO_HPP_
#define INCLUDE_FILETYPE_TYPES_AUDIO_HPP_

#include <array>
#include <cstdint>

#include "filetype/type.hpp"
namespace filetype {
namespace audio {

using Type = ::filetype::Type;

//------------------------------------------------------------------------------
// Audio file type definitions
//------------------------------------------------------------------------------

// MP3 audio format
// Magic: FF FB or ID3 tags: 49 44 33 ("ID3")
inline const std::array<uint8_t, 2> MP3_MAGIC = {0xFF, 0xFB};
inline const std::array<uint8_t, 3> MP3_ID3_MAGIC = {0x49, 0x44, 0x33};
inline const Type TYPE_MP3{"audio/mpeg", "mp3"};

// WAV audio format
// Magic: 52 49 46 46 XX XX XX XX 57 41 56 45 ("RIFF....WAVE")
inline const std::array<uint8_t, 12> WAV_MAGIC = {
    0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45};
inline const Type TYPE_WAV{"audio/wav", "wav"};

// MIDI audio format
// Magic: 4D 54 68 64 ("MThd")
inline const std::array<uint8_t, 4> MIDI_MAGIC = {0x4D, 0x54, 0x68, 0x64};
inline const Type TYPE_MIDI{"audio/midi", "mid"};

// FLAC audio format
// Magic: 66 4C 61 43 ("fLaC")
inline const std::array<uint8_t, 4> FLAC_MAGIC = {0x66, 0x4C, 0x61, 0x43};
inline const Type TYPE_FLAC{"audio/flac", "flac"};

// AAC audio format
// Magic: FF F1 (ADTS) or FF F9 (we use FF F1 here)
inline const std::array<uint8_t, 2> AAC_MAGIC = {0xFF, 0xF1};
inline const Type TYPE_AAC{"audio/aac", "aac"};

// OGG audio format
// Magic: 4F 67 67 53 ("OggS")
inline const std::array<uint8_t, 4> OGG_MAGIC = {0x4F, 0x67, 0x67, 0x53};
inline const Type TYPE_OGG{"audio/ogg", "ogg"};

// WMA audio format
// Magic: 30 26 B2 75 8E 66 CF 11
inline const std::array<uint8_t, 8> WMA_MAGIC = {0x30, 0x26, 0xB2, 0x75,
                                                 0x8E, 0x66, 0xCF, 0x11};
inline const Type TYPE_WMA{"audio/x-ms-wma", "wma"};

// AIFF audio format
// Magic: 46 4F 52 4D XX XX XX XX 41 49 46 46 ("FORM....AIFF")
inline const std::array<uint8_t, 12> AIFF_MAGIC = {
    0x46, 0x4F, 0x52, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x41, 0x49, 0x46, 0x46};
inline const Type TYPE_AIFF{"audio/aiff", "aiff"};

// M4A audio format
// Magic: 00 00 00 XX 66 74 79 70 4D 34 41 20 ("....ftypM4A ")
inline const std::array<uint8_t, 12> M4A_MAGIC = {
    0x00, 0x00, 0x00, 0x20, 0x66, 0x74, 0x79, 0x70, 0x4D, 0x34, 0x41, 0x20};
inline const Type TYPE_M4A{"audio/mp4", "m4a"};

}  // namespace audio
}  // namespace filetype

#endif  // INCLUDE_FILETYPE_TYPES_AUDIO_HPP_
