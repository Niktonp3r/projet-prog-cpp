#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>

namespace img {

/// Represents the width and height of an axis-aligned rectangle.
/// width and height are guaranteed to be >= 1
/// The template parameter T is the type of width and height
template<typename T>
class SizeT {
public:
    /// The type of width and height
    using DataType = T;

    SizeT() = default;
    SizeT(DataType w, DataType h)
        : _width{make_valid_size(w)}
        , _height{make_valid_size(h)}
    {
    }
    friend auto operator==(const SizeT& lhs, const SizeT& rhs) -> bool { return lhs.width() == rhs.width() && lhs.height() == rhs.height(); }
    friend auto operator!=(const SizeT& lhs, const SizeT& rhs) -> bool { return !(lhs == rhs); }
    template<typename U>
    explicit operator SizeT<U>() const
    {
        return SizeT<U>{static_cast<U>(_width), static_cast<U>(_height)};
    }

    auto width() const -> DataType { return _width; }
    auto height() const -> DataType { return _height; }

    /// Sets the width. If w < 1, it will be set to 1.
    void set_width(DataType w)
    {
        _width = make_valid_size(w);
    }

    /// Sets the height. If h < 1, it will be set to 1.
    void set_height(DataType h)
    {
        _height = make_valid_size(h);
    }

private:
    auto make_valid_size(DataType x) const -> DataType
    {
        return std::max(x, static_cast<DataType>(1));
    }

private:
    DataType _width  = 1;
    DataType _height = 1;
};

using Size = SizeT<uint32_t>;

} // namespace img