#pragma once

// clang-format off
#define TL_LABEL_ALPHA 0
#define TL_LABEL_BETA  1
#define TL_LABEL_NONE  255

#define TL_VERSION_MAJOR         0
#define TL_VERSION_MINOR         0
#define TL_VERSION_PATCH         1
// clang-format on

#define TARGET_BDS_PROTOCOL_VERSION 686

#define TL_VERSION_TO_STRING_INNER(ver) #ver
#define TL_VERSION_TO_STRING(ver)       TL_VERSION_TO_STRING_INNER(ver)

#define TL_FILE_VERSION_FLAG 0x00000000L
#define TL_FILE_VERSION_STRING                                                                                         \
    TL_VERSION_TO_STRING(TL_VERSION_MAJOR)                                                                             \
    "." TL_VERSION_TO_STRING(TL_VERSION_MINOR) "." TL_VERSION_TO_STRING(TL_VERSION_PATCH)
