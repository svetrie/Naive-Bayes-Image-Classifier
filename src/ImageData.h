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
    vector<Image> training_images;
    vector<Image> testing_images;
    //std::vector<std::vector<std::vector<int> > > vec3D(9, std::vector<std::vector<int> > (9, std::vector<int>(9,0)));
    vector<vector<vector<double>>> probabilities;
    vector<double> priors;
            //(28, vector<vector<double>>(28, vector<double>(10, 0)));
public:
    ImageData();
    //vector<Image> training_images;
    //vector<Image> testing_images;
    static constexpr double LAPLACE_VALUE = 6.0;
    vector<double>* getPriors();
    void setPriors();
    vector<Image>* getTrainingImages();
    vector<Image>* getTestingImages();
    void loadImages(vector<Image>* images);
    void loadLabels(vector<Image>* images);
    int getClassFrequency(int class_num);
    int getFeaturesSum(int class_num, int row, int col);
    void findProbabilities();
    void saveToFile(string file_name);
    void loadFromFile(string file_name);
};