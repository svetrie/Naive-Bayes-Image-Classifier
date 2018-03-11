//
// Created by Vet Senthil on 3/10/2018.
//

#include "Image.h"

vector<vector<bool>> Image::getImage() {
    return image_pixels;
    //vector<vector<bool>>* image_ptr = &image_pixels;
    //return image_ptr;
}

/*int* Image::getImageLabel() {
    //return image_label;
    int* image_label_ptr = &image_label;
    return image_label_ptr;
}*/

int Image::getImageLabel() {
    return image_label;
}

void Image::setImageLabel(int class_label) {
    image_label = class_label;
}

int Image::getPredictedLabel() {
    return predicted_label;
}

void Image::setPredictedLabel(int class_label) {
    predicted_label = class_label;
}

Image::Image(vector<vector<bool>> pixelated_image) {
    image_pixels = pixelated_image;
}
