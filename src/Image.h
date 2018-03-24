//
// Created by Vet Senthil on 3/10/2018.
//
#ifndef NAIVEBAYES_IMAGE_H
#define NAIVEBAYES_IMAGE_H

#endif //NAIVEBAYES_IMAGE_H

#include <vector>
using namespace std;

class Image {
private:
    vector<vector<bool>> image_pixels;
    int image_label;
    int predicted_label;

public:
    Image(vector<vector<bool>>);

    static const int IMAGE_SIZE = 28;
    vector<vector<bool>> getFeatures();

    int getImageLabel();
    void setImageLabel(int class_label);

    int getPredictedLabel();
    void setPredictedLabel(int class_label);
};