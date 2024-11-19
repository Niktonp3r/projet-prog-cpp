#pragma once

#include <memory>
#include "Size.h"

namespace img {

/// An Image is an array of pixel channels
/// The pixels are stored sequentially, something like [255, 200, 100, 255, 120, 30, 80, 255, ...] where (255, 200, 100, 255) would be the first pixel and (120, 30, 80, 255) the second pixel
/// The order in which the pixels are stored is up to the user to decide
struct Image {
public:
    /// NB: The Image takes ownership of the data pointer
    /// It is your responsibility to make sure that size and channels_count properly match what is in data
    /// Alternatively you can use img::load() to create an Image
    Image(Size size, int channels_count, uint8_t* data)
        : _size{size}, _channels_count{channels_count}, _data{data}
    {
    }

    /// Returns the size of the image (in pixels)
    Size size() const { return _size; }

    /// Returns the width of the image (in pixels)
    Size::DataType width() const { return size().width(); }

    /// Returns the height of the image (in pixels)
    Size::DataType height() const { return size().height(); }

    /// Returns the number of channels per pixel (e.g. 4 if the format is RGBA)
    int channels_count() const { return _channels_count; }

    /// Returns a pointer to the beginning of the data array
    uint8_t* data() { return _data.get(); }

    /// Returns a pointer to the beginning of the data array
    const uint8_t* data() const { return _data.get(); }

    /// Returns the number of elements in the data array
    size_t data_size() const { return width() * height() * static_cast<size_t>(channels_count()); }

private:
    Size                       _size;
    int                        _channels_count;
    std::unique_ptr<uint8_t[]> _data;
};

} // namespace img