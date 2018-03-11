//
// Created by Vet Senthil on 3/10/2018.
//

#ifndef NAIVEBAYES_IMAGEDATA_H
#define NAIVEBAYES_IMAGEDATA_H

#endif //NAIVEBAYES_IMAGEDATA_H

#include "Image.h"
#include <vector>
#include <string>

class ImageData {
private:
    //vector<Image> training_images;
    //vector<Image> testing_images;

public:
    vector<Image> training_images;
    vector<Image> testing_images;
    vector<Image> getTrainingImages();
    vector<Image> getTestingImages();
    void loadImages();
    void saveToFile(string file_name);
    void loadFromFile(string file_name);
};