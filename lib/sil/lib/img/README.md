# img

Simple utilities to work with images.

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/img)
target_link_libraries(${PROJECT_NAME} PRIVATE img::img)
```

Then include it as:
```cpp
#include <img/img.hpp>
```


## Size

This is a simple type that holds a width and a height, with one important invariant: ```width >= 1 && height >= 1```. Indeed them beeing negative would make no sense, and them beeing 0 would be problematic too, mostly because for graphics APIs like OpenGL an image with 0 pixels is an error resulting in a crash. Also, this is perfectly fine because if someone wants to be able to represent an empty image, then ```std::optional<img::Size>``` is the perfect fit for it.

Having this invariant removes the need for many checks: when computing the aspect ratio (no risk of dividing by 0) or when resizing a texture for example.

We have a templated version ```img::SizeT``` which allows you to choose the type used to store ```width``` and ```height```, and we have a default ```using Size = SizeT<uint32_t>```. You can ask for the type used to store ```width``` and ```height``` with ```img::SizeT::DataType```.

```img::SizeU::fit_into``` returns specifically an ```img::SizeT<float>``` instead of matching the ```DataType``` of the input (```img::SizeT<T>```) because this is what the computation gives us (since we multiply by the aspect ratio), and because ImGui expects the width and height to be floats and this function is mainly used to fit a texture in an ImGui window. Therefore we avoid extra conversions, and users can do them if they actually need them.
