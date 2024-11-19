#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG // Give us better error messages in stbi_failure_reason()
#define STBI_WINDOWS_UTF8    // Don't fail to open files containing unicode characters
#include "stb_image.h"