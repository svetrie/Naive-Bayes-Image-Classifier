//
// Created by Vet Senthil on 3/10/2018.
//

#include "Image.h"

vector<vector<bool>> Image::getImage() {
    return image_pixels;
}

int Image::getImageLabel() {
    return image_label;
}

Image::Image(vector<vector<bool>> pixelated_image) {
    image_pixels = pixelated_image;
}
