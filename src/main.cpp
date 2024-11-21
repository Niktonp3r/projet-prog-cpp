#include <sil/sil.hpp>
#include "random.hpp"
#include<cmath>
#include<iostream>
#include<complex>

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

void RGB(sil::Image& image){

    sil::Image new_image{image.width(), image.height()};


    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            if(x-20>0){
                new_image.pixel(x,y).b=image.pixel(x-20,y).b;
            }
            if(x+20<image.width()){
                new_image.pixel(x,y).r=image.pixel(x+20,y).r;
            }
            new_image.pixel(x,y).g=image.pixel(x,y).g;
        }
    }

    image = new_image;
}

void disco(sil::Image& image){
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            image.pixel(x,y)=glm::vec3{0.f};
            if (pow(x-image.width()/2,2)+pow(y-image.height()/2,2)<3000){
                image.pixel(x,y)=glm::vec3{1.f};
            }
        }   
    }
}

void circle(sil::Image& image, float r, float thickness){
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            image.pixel(x,y)=glm::vec3{0.f};
            if (pow(x-image.width()/2,2)+pow(y-image.height()/2,2)<3000){
                image.pixel(x,y)=glm::vec3{1.f};
            }
            if (pow(x-image.width()/2,2)+pow(y-image.height()/2,2)<900){
                image.pixel(x,y)=glm::vec3{0.f};
            }   
        }
    }
}

void circle2(sil::Image& image, float r, float thickness, float xposition,float yposition){
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
          //  image.pixel(x,y)=glm::vec3{0.f};
            if (r-thickness<sqrt(pow(x-xposition,2)+pow(y-yposition,2)) && sqrt((pow(x-xposition,2)+pow(y-yposition,2)))<r){
                image.pixel(x,y)=glm::vec3{1.f};
            }   
        }
    }
}

void rosace2(sil::Image& image, float r, float thickness){
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            image.pixel(x,y)=glm::vec3{0.f};
        }
    }

    for (int i= 0; i<6;i++){
        float xposition= image.width()/2+r*cos(i*M_PI/3);
        float yposition= image.height()/2+r*sin(i*M_PI/3);
        circle2(image, r,  thickness,  xposition, yposition);
    }
}

void mosaique(sil::Image& image, float box){
    sil::Image original{image};
    for (int x = 0; x < image.width()/box; x++) {
        for (int y = 0; y < image.height()/box; y++) {
            for(int i=0; i<box;i++){
                for (int j=0; j<box;j++){
                    image.pixel(x+i*image.width()/box,y+j*image.height()/box)=original.pixel(x*box,y*box);
                }
            }
        }
    }
}

void mosaique_mirror(sil::Image& image, float box){
    sil::Image original{image};
    for (int x = 0; x < image.width()/box; x++) {
        for (int y = 0; y < image.height()/box; y++) {
            for(int i=0; i<box;i++){
                for (int j=0; j<box;j++){
                    if(j%2==1 && i%2==1){     
                        image.pixel(x+i*image.width()/box,y+j*image.height()/box)=original.pixel(image.width()-x*box-1,image.height()-y*box-1);
                    }
                    else 
                    if(j%2==0 && i%2==1){   
                        image.pixel(x+i*image.width()/box,y+j*image.height()/box)=original.pixel(image.width()-x*box-1,y*box);

                    }
                    else if(j%2==1 && i%2==0){
                        image.pixel(x+i*image.width()/box,y+j*image.height()/box)=original.pixel(x*box,image.height()-y*box-1);

                    }
                    else{
                        image.pixel(x+i*image.width()/box,y+j*image.height()/box)=original.pixel(x*box,y*box);
                        
                    }
                }
            }
        }
    }
}

void glitch(sil::Image& image, int number){
    
    for(int a=0; a<number;a++){
       
        int largeur{random_int(0,50)};
        int hauteur{random_int(0,10)};

        int randomx{random_int(0, image.width()-largeur)};
        int randomy{random_int(0, image.height()-hauteur)};

        int randomw{random_int(0, image.width()-largeur)};
        int randomz{random_int(0, image.height()-hauteur)};

        // for (int x = randomx; x < randomx+largeur; x++) {
    
        //     for (int y = randomy; y < randomy+hauteur; y++) {
        //      z++;
        //         std::swap(image.pixel(x,y),image.pixel(w,z));
        //     }
        //     z = zz;
        // }

        for (int offset_x = 0; offset_x < 0+largeur; offset_x++) {
            int x = offset_x + randomx;
            int w = offset_x + randomw;
            for (int offset_y = 0; offset_y< 0+hauteur; offset_y++) {
                int y = offset_y + randomy;
                int z = offset_y + randomz;
                std::swap(image.pixel(x,y),image.pixel(w,z));
            }
        }
    }
}

void fractale(sil::Image& image){
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            std::complex<float> c{static_cast<float>(x), static_cast<float>(y)}; // Définis le nombre z = x + y*i
        
    
        std::complex<float> z{0, 0};
        for (int i=0; i<image.width();i++){
            z = z * z + c;
            if (std::abs(z)>2){
                image.pixel(x,y)=glm::vec3{0.f};
            }
            else{
                image.pixel(x,y)=glm::vec3{1.f};
            }
        }
        }
    }
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

    // {
    // sil::Image image{"images/logo.png"};
    // bruit(image);
    // image.save("output/pouet.png");
    // }

    {
    sil::Image image{"images/logo.png"};
    rotation(image);
    image.save("output/pouet.png");
    }

    {
        sil::Image image{"images/logo.png"};
        RGB(image);
        image.save("output/pouet.png");
    }

    {
    sil::Image image{500, 500};
    disco(image);
    image.save("output/pouet.png");
    }

    {
    sil::Image image{500, 500};
    circle2(image, 500,100, image.width()/2, image.height()/2);
    image.save("output/pouet.png");
    }

    {
    sil::Image image{500, 500};
    rosace2(image, 100,10);
    image.save("output/pouet.png");
    }

   {
    sil::Image image{"images/logo.png"};
    mosaique(image,5);
    image.save("output/pouet.png");
    }

    {
    sil::Image image{"images/logo.png"};
    mosaique_mirror(image,5);
    image.save("output/pouet.png");
    }

    {
    sil::Image image{"images/logo.png"};
    glitch(image,80);
    image.save("output/pouet.png");
    }

    {
    sil::Image image{500, 500};
    fractale(image);
    image.save("output/pouet.png");
    }


}
