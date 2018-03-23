//
// Created by Vet Senthil on 3/10/2018.
//

#ifndef NAIVEBAYES_IMAGEDATA_H
#define NAIVEBAYES_IMAGEDATA_H

#endif //NAIVEBAYES_IMAGEDATA_H

#include "Image.h"
#include <vector>
#include <string>

class NaiveBayesClassifier {
    private:
        vector<Image> training_images;
        vector<Image> test_images;
        vector<vector<vector<double>>> probabilities;
        vector<double> priors;
        vector<int> class_frequencies;

    public:
        NaiveBayesClassifier();
        static constexpr double LAPLACE_VALUE = 1.0;
        static constexpr int NUM_CLASSES = 10;

        vector<Image> getTrainingImages();
        vector<Image> getTestImages();

        void setTrainingImages(vector<Image>);
        void setTestImages(vector<Image>);

        //vector<Image>* getTrainingImages();
        //vector<Image>* getTestImages();

        vector<Image> loadImages(const char* img_file_name, const char* labels_file_name);
        vector<Image> loadImageFeatures(const char *file_name);
        vector<int> loadImageLabels(const char *file_name);
        //void loadImageFeatures(const char *file_name, vector<Image> *images);
        //void loadImageLabels(const char *file_name, vector<Image> *images);

        void findClassFrequencies();
        void findPriors();
        vector<double> getLogPriors();
        int getFeaturesSum(int class_num, int row, int col);
        void findProbabilities();

        int getMostProbableClass(vector<double> class_probabilities);
        void classifyImages();
        double getAccuracyRate();


        void saveModel(const char* file_name);
        void loadModel(const char* file_name);
};