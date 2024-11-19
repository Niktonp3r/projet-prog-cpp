#include "Save.h"
#include <stb_image/stb_image_write.h>

namespace img {

void save_png(std::filesystem::path const& file_path, Image const& image, bool flip_vertically)
{
    save_png(file_path, image.width(), image.height(), image.data(), image.channels_count(), flip_vertically);
}

void save_png(
    std::filesystem::path const& file_path,
    Size::DataType               width,
    Size::DataType               height,
    const void*                  data,
    int                          channels_count,
    bool                         flip_vertically
)
{
    stbi_flip_vertically_on_write(flip_vertically ? 1 : 0);
    stbi_write_png(file_path.string().c_str(), static_cast<int>(width), static_cast<int>(height), channels_count, data, 0);
}

auto save_png_to_string(Image const& image, bool flip_vertically) -> std::string
{
    return save_png_to_string(image.width(), image.height(), image.data(), image.channels_count(), flip_vertically);
}

static void write_to_string(void* context, void* data, int size)
{
    auto& str = *reinterpret_cast<std::string*>(context);
    str += std::string{reinterpret_cast<char*>(data), static_cast<size_t>(size)};
}

auto save_png_to_string(
    Size::DataType width,
    Size::DataType height,
    const void*    data,
    int            channels_count,
    bool           flip_vertically
) -> std::string
{
    stbi_flip_vertically_on_write(flip_vertically ? 1 : 0);

    std::string res{};
    stbi_write_png_to_func(&write_to_string, &res, static_cast<int>(width), static_cast<int>(height), channels_count, data, 0);
    return res;
}

void save_jpeg(std::filesystem::path const& file_path, Image const& image, bool flip_vertically)
{
    save_jpeg(file_path.string().c_str(), image.width(), image.height(), image.data(), image.channels_count(), flip_vertically);
}

void save_jpeg(
    std::filesystem::path const& file_path,
    Size::DataType               width,
    Size::DataType               height,
    void const*                  data,
    int                          channels_count,
    bool                         flip_vertically
)
{
    stbi_flip_vertically_on_write(flip_vertically ? 1 : 0);
    stbi_write_jpg(file_path.string().c_str(), static_cast<int>(width), static_cast<int>(height), channels_count, data, 100);
}

} // namespace img