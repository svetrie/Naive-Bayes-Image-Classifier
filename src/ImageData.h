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
    vector<vector<vector<double>>> probabilities;
    vector<double> priors;
    vector<int> class_frequencies;

public:
    ImageData();
    static constexpr double LAPLACE_VALUE = 10.0;
    static constexpr int NUM_CLASSES = 10;

    vector<double>* getPriors();
    void findPriors();
    vector<double> getLogPriors();

    vector<Image>* getTrainingImages();
    vector<Image>* getTestImages();

    void loadImages(const char* file_name, vector<Image>* images);
    void loadLabels(const char* file_name, vector<Image>* images);

    void findClassFrequencies();
    int getFeaturesSum(int class_num, int row, int col);
    void findProbabilities();

    void classifyImages();
    double getAccuracyRate();
    int getMostProbableClass(vector<double> class_probabilities);

    void saveModel(const char* file_name);
    void loadModel(const char* file_name);
};