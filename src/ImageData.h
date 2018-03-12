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
    vector<Image> test_images;
    //std::vector<std::vector<std::vector<int> > > vec3D(9, std::vector<std::vector<int> > (9, std::vector<int>(9,0)));
    vector<vector<vector<double>>> probabilities;
    vector<double> priors;
            //(28, vector<vector<double>>(28, vector<double>(10, 0)));
public:
    ImageData();
    //vector<Image> training_images;
    //vector<Image> test_images;
    static constexpr double LAPLACE_VALUE = 6.0;
    static constexpr int NUM_CLASSES = 10;

    vector<double>* getPriors();
    void findPriors();
    vector<double> getLogPriors();

    vector<Image>* getTrainingImages();
    vector<Image>* getTestImages();

    void loadImages(const char* file_name, vector<Image>* images);
    void loadLabels(const char* file_name, vector<Image>* images);

    int getClassFrequency(int class_num);
    int getFeaturesSum(int class_num, int row, int col);
    void findProbabilities();

    void classifyImages();
    double getAccuracyRate();
    int getMostProbableClass(vector<double> class_probabilities);

    void saveModel(const char* file_name);
    void loadModel(const char* file_name);


};