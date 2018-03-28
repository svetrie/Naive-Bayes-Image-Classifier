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
        //vector<vector<double>> confusion_matrix;

    public:
        NaiveBayesClassifier();
        static constexpr double LAPLACE_VALUE = 1.0;
        static constexpr int NUM_CLASSES = 10;

        vector<Image> getTrainingImages();
        vector<Image> getTestImages();
        vector<int> getClassFrequencies();
        vector<double> getPriors();
        vector<vector<vector<double>>> getProbabilities();

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
        vector<double> findLogPriors();
        int getFeaturesSum(int class_num, int row, int col);
        void findProbabilities();

        double findImageClassProbability(Image test_img, int class_num);
        int getMostProbableClass(vector<double> class_probabilities);
        void classifyImages();
        double getAccuracyRate();
        void printConfusionMatrix();

        void saveModel(const char* file_name);
        void loadModel(const char* file_name);
};