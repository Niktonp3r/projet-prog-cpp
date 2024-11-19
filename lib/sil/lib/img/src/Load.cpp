#include "Load.h"
#include <stb_image/stb_image.h>
#include <stdexcept>
#include <string>

namespace img {

Image load(std::filesystem::path file_path, int desired_channels_count, bool flip_vertically)
{
    stbi_set_flip_vertically_on_load(flip_vertically ? 1 : 0);
    int      w, h; // NOLINT
    uint8_t* data = stbi_load(file_path.string().c_str(), &w, &h, nullptr, desired_channels_count);
    if (!data)
    {
        throw std::runtime_error{"[img::load] Couldn't load image from \"" + file_path.string() + "\":\n" + stbi_failure_reason()};
    }
    return Image{{
                     static_cast<Size::DataType>(w),
                     static_cast<Size::DataType>(h),
                 },
                 desired_channels_count,
                 data};
}

} // namespace img