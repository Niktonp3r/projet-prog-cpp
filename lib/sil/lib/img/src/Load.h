#pragma once

#include <filesystem>
#include "Image.h"

namespace img {

/// Loads an Image from a file
/// Throws a std::runtime_error if the file doesn't exist or isn't a valid image file
/// @param file_path The path to the image: something like "icons/myImage.png"
/// @param desired_channels_count The number of channels that you want the image to have. For example if your file contains only RGB but you want RGBA, this will add a 4th component of 255 to each pixel
/// @param flip_vertically By default we use the OpenGL convention: the first row will be the bottom of the image. You can set flip_vertically to false if you want the first row to be the top of the image
Image load(std::filesystem::path file_path, int desired_channels_count = 4, bool flip_vertically = true);

} // namespace img
