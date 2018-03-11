//
// Created by Vet Senthil on 3/10/2018.
//

#include "Image.h"

vector<vector<bool>> Image::getImage() {
    return image_pixels;
    //vector<vector<bool>>* image_ptr = &image_pixels;
    //return image_ptr;
}

int* Image::getImageLabel() {
    //return image_label;
    int* image_label_ptr = &image_label;
    return image_label_ptr;
}

Image::Image(vector<vector<bool>> pixelated_image) {
    image_pixels = pixelated_image;
}
