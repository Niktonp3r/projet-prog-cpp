#pragma once
#include <filesystem>
#include <string>
#include "Image.h"

namespace img {

/// Saves an image as PNG.
/// Throws a std::runtime_error if writing to the file fails.
/// @param file_path The destination path for the image: something like "out/myImage.png". The folders in the path must exist.
/// @param flip_vertically By default we use the OpenGL convention: the first row should be the bottom of the image. You can set flip_vertically to false if your first row is at the top of the image.
void save_png(std::filesystem::path const& file_path, Image const& image, bool flip_vertically = true);

/// Saves an image as PNG.
/// Throws a std::runtime_error if writing to the file fails.
/// @param file_path The destination path for the image: something like "out/myImage.png". The folders in the path must exist.
/// @param width The width in pixels of the image represented by data.
/// @param height The height in pixels of the image represented by data.
/// @param data An array of uint8_t representing the image. The pixels should be written sequentially, row after row. Something like [255, 200, 100, 255, 120, 30, 80, 255, ...] where (255, 200, 100, 255) would be the first pixel and (120, 30, 80, 255) the second pixel and so on.
/// @param channels_count The number of channels per pixel, e.g. 4 if the format is RGBA.
/// @param flip_vertically By default we use the OpenGL convention: the first row should be the bottom of the image. You can set flip_vertically to false if your first row is at the top of the image.
void save_png(std::filesystem::path const& file_path, Size::DataType width, Size::DataType height, void const* data, int channels_count, bool flip_vertically = true);

/// Returns a string containing the image data in PNG format.
/// @param flip_vertically By default we use the OpenGL convention: the first row should be the bottom of the image. You can set flip_vertically to false if your first row is at the top of the image.
auto save_png_to_string(Image const& image, bool flip_vertically = true) -> std::string;

/// Returns a string containing the image data in PNG format.
/// @param data An array of uint8_t representing the image. The pixels should be written sequentially, row after row. Something like [255, 200, 100, 255, 120, 30, 80, 255, ...] where (255, 200, 100, 255) would be the first pixel and (120, 30, 80, 255) the second pixel and so on.
/// @param channels_count The number of channels per pixel, e.g. 4 if the format is RGBA.
/// @param flip_vertically By default we use the OpenGL convention: the first row should be the bottom of the image. You can set flip_vertically to false if your first row is at the top of the image.
auto save_png_to_string(Size::DataType width, Size::DataType height, void const* data, int channels_count, bool flip_vertically = true) -> std::string;

/// Saves an image as JPEG.
/// Throws a std::runtime_error if writing to the file fails.
/// @param file_path The destination path for the image: something like "out/myImage.jpeg". The folders in the path must exist.
/// @param flip_vertically By default we use the OpenGL convention: the first row should be the bottom of the image. You can set flip_vertically to false if your first row is at the top of the image.
void save_jpeg(std::filesystem::path const& file_path, Image const& image, bool flip_vertically = true);

/// Saves an image as JPEG.
/// Throws a std::runtime_error if writing to the file fails.
/// @param file_path The destination path for the image: something like "out/myImage.jpeg". The folders in the path must exist.
/// @param width The width in pixels of the image represented by data.
/// @param height The height in pixels of the image represented by data.
/// @param data An array of uint8_t representing the image. The pixels should be written sequentially, row after row. Something like [255, 200, 100, 255, 120, 30, 80, 255, ...] where (255, 200, 100, 255) would be the first pixel and (120, 30, 80, 255) the second pixel and so on.
/// @param channels_count The number of channels per pixel in data, e.g. 3 if the format is RGB and 4 if it is RGBA.
/// @param flip_vertically By default we use the OpenGL convention: the first row should be the bottom of the image. You can set flip_vertically to false if your first row is at the top of the image.
void save_jpeg(std::filesystem::path const& file_path, Size::DataType width, Size::DataType height, void const* data, int channels_count, bool flip_vertically = true);

} // namespace img