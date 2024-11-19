# Simple-Image-Lib

*sil* is a minimalistic library that allows you to load an image, edit its pixels, and save it back.

- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
  - [Removing the red channel](#removing-the-red-channel)
  - [Drawing a gradient from left to right](#drawing-a-gradient-from-left-to-right)

## Installation

Simply add these lines to your *CMakeLists.txt*:

```cmake
# Download the library
include(FetchContent)
FetchContent_Declare(
    sil
    GIT_REPOSITORY https://github.com/JulesFouchy/Simple-Image-Lib
    GIT_TAG 89bd175cd55fb6daa9e99b218e869c3d516043f4
)
FetchContent_MakeAvailable(sil)

# Link the library into your project
target_link_libraries(${PROJECT_NAME} PRIVATE sil::sil)
```

## Usage

⚠️ All the image paths must be relative to the directory containing your *CMakeLists.txt*. So for example if your "hello.png" image is in the same folder as your *CMakeLists.txt*, the path to use would simply be "hello.png".

## Examples

### Removing the red channel

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/input.png"};
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y).r = 0.f;
        }
    }
    image.save("output/output.png");
}
```


| ![input](./tests/images/test.png)  | ![output](./tests/output/UseCase_RemoveRedChannel.png)  |
|---|----|
| input.png | output.png |

And if you don't care about the x and y positions, you can simply iterate over all the pixels:

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{"images/input.png"};
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
    }
    image.save("output/output.png");
}
```

### Drawing a gradient from left to right

```cpp
#include <sil/sil.hpp>

int main()
{
    sil::Image image{300 /*width*/, 200 /*height*/}; // Creates a black image with the given size.
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
    image.save("output/output.png");
}
```

<figure>
  <img src="./tests/output/UseCase_DrawGradientLeftToRight.png" alt="output" />
  <figcaption>output.png</figcaption>
</figure>