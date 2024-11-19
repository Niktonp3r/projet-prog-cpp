#include <sil/sil.hpp>
#include "random.hpp"

void green_filter(sil::Image& image){
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

void canal_change(sil::Image& image){
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y).r,image.pixel(x,y).b);

        }
    }
}

void noir_blanc(sil::Image& image){
    for (glm::vec3& color : image.pixels())
    {
        glm::vec3 grey{0.299f*color.r+0.587f*color.g+0.114f*color.b};
        color=grey;
    }
}

void negatif(sil::Image& image){
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 1-image.pixel(x, y).r;
            image.pixel(x, y).b = 1-image.pixel(x, y).b;
            image.pixel(x, y).g = 1-image.pixel(x, y).g;
        }
    }
}


void degrade(sil::Image& image){

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            float value = static_cast<float>(x) / (image.width() - 1); // Normalise x entre 0 et 1
            glm::vec3 color{value}; 
            image.pixel(x, y) = color;
        }
    }
}

void mirror(sil::Image& image){
    for (int x = 0; x < image.width()/2; x++) {
        for (int y = 0; y < image.height(); y++) {
            std::swap(image.pixel(x,y),image.pixel(image.width()-(x+1),y));
        }
    }
}

void bruit(sil::Image& image){
   for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            if (true_with_probability(0.25)){
                glm::vec3 rand_color;
                rand_color.r = random_float(0,1);
                rand_color.b = random_float(0,1);
                rand_color.g = random_float(0,1);
                image.pixel(x,y)=rand_color;
            }
        }
    }
}

void rotation(sil::Image& image){
    sil::Image new_image{image.height(), image.width()};
   for (int x = 0; x < new_image.width(); x++) {
        for (int y = 0; y < new_image.height(); y++) {

          new_image.pixel(x, y) = image.pixel(  y  ,image.height()-(x+1));
       // std::swap(image.pixel(x,y),);
       // new_width
        }
    }
    image = new_image;
}
int main()
{
    // {
    // sil::Image image{"images/logo.png"};
    // green_filter(image);
    // image.save("output/pouet.png");
    // }

    // {
    // sil::Image image{"images/logo.png"};
    // canal_change(image);
    // image.save("output/pouet.png");
    // }

    // {
    // sil::Image image{"images/logo.png"};
    // noir_blanc(image);
    // image.save("output/pouet.png");
    // }

    // {
    // sil::Image image{"images/logo.png"};
    // negatif(image);
    // image.save("output/pouet.png");
    // }
    
    // {
    // sil::Image image{300, 200};
    // degrade(image);
    // image.save("output/pouet.png");
    // }

    // {
    // sil::Image image{"images/logo.png"};
    // mirror(image);
    // image.save("output/pouet.png");
    // }

    {
    sil::Image image{"images/logo.png"};
    bruit(image);
    image.save("output/pouet.png");
    }

    {
    sil::Image image{"images/logo.png"};
    rotation(image);
    image.save("output/pouet.png");
    }
}