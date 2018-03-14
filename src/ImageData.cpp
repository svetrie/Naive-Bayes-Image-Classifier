//
// Created by Vet Senthil on 3/10/2018.
//

#include "ImageData.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <complex>
#include <math.h>


ImageData::ImageData() {
    probabilities = vector<vector<vector<double>>>(NUM_CLASSES,
                                                   vector<vector<double>>(Image::IMAGE_SIZE, vector<double>(Image::IMAGE_SIZE, 0)));
    priors = vector<double>(NUM_CLASSES);
    class_frequencies = vector<int>(NUM_CLASSES);
}

vector<Image>* ImageData::getTrainingImages() {
    vector<Image>* training_images_ptr = &training_images;
    return training_images_ptr;
}

vector<Image>* ImageData::getTestImages() {
    vector<Image>* testing_images_ptr = &test_images;
    return testing_images_ptr;
}

void ImageData::loadImages(const char* file_name, vector<Image>* images) {
    ifstream inFile;
    inFile.open(file_name);

    if (!inFile) {
         cout << "Unable to open file datafile.txt" << endl;
    }

    vector<vector<bool>> trainingImage;
    string line;

    for(int i = 0; getline(inFile, line); i = (i + 1) % 28) {
        vector<bool> row(28, false);

        for (int j = 0; j < line.size(); ++j) {
            row[j] = (line[j] != ' ');
        }

        trainingImage.push_back(row);

        if (i == 27) {
            Image image(trainingImage);
            images->push_back(image);

            trainingImage.clear();
        }
    }

    inFile.close();
}

void ImageData::loadLabels(const char* file_name, vector<Image>* images) {
    ifstream inFile;
    inFile.open(file_name);

    if (!inFile) {
        cout << "Unable to open file datafile.txt" << endl;
    }

    string image_label;
    int i = 0;

    while (getline(inFile, image_label)) {
        stringstream strstream(image_label);
        int label_num = 0;
        strstream >> label_num;

        (*images)[i++].setImageLabel(label_num);
    }

    inFile.close();
}

void ImageData::loadModel(const char* file_name) {
    ifstream myFile;
    myFile.open(file_name);

    char* feature_probabiltity;

    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); ++j) {
            for (int k = 0; k < probabilities[0][0].size(); ++k) {
                myFile.getline(feature_probabiltity, 10);
                probabilities[i][j][k] = atof(feature_probabiltity);
            }
        }
    }

    char* prior_value;

    for (int m = 0; m < priors.size() - 1; ++m) {

        if(!myFile.eof()) {
            myFile.getline(prior_value, 10);
            priors[m] = atof(prior_value);
        }
    }

    myFile.close();
}

void ImageData::saveModel(const char* file_name) {
    ofstream newFile;
    newFile.open(file_name);

    for (vector<vector<double>> class_features : probabilities) {
        for (vector<double> row_features : class_features) {
            for (double feature_value : row_features) {
                newFile << feature_value << endl;
            }
        }
    }

    for (double class_prior : priors) {
        newFile << class_prior << endl;
    }

}

void ImageData::findClassFrequencies() {
    for (Image image : training_images) {
        class_frequencies[image.getImageLabel()]++;
    }
}

int ImageData::getFeaturesSum(int class_num, int row, int col) {
    int feature_sum = 0;

    for (Image image : training_images) {
        if (image.getImageLabel() == class_num && image.getImage()[row][col]) {
            feature_sum += 1;
        }
    }

    return feature_sum;
}

void ImageData::findProbabilities() {
    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); j++) {
            for (int k = 0; k < probabilities[0][0].size(); k++) {
                probabilities[i][j][k] = ((LAPLACE_VALUE + getFeaturesSum(i, j, k))
                                          / 2 * LAPLACE_VALUE + class_frequencies[i]);
            }
        }
    }
}

void ImageData::findPriors() {
    for (int i = 0; i < priors.size(); ++i) {
        priors[i] = double(class_frequencies[i] * 1.0) / training_images.size();
    }
}

vector<double> ImageData::getLogPriors() {
    vector<double> log_priors(NUM_CLASSES);

    for (double class_probability : priors) {
        log(class_probability);
    }

    return log_priors;
}

int ImageData::getMostProbableClass(vector<double> class_probabilities) {
    int class_num = 0;

    for (int i = 1; i < NUM_CLASSES; i++) {
        if (class_probabilities[i] > class_probabilities[class_num]) {
            class_num = i;
        }
    }

    return class_num;
}

void ImageData::classifyImages() {
    vector<double> class_probabilities;
    vector<double> initial_probabilities = getLogPriors();
    class_probabilities = initial_probabilities;

    for (Image image : test_images) {
        for (int i = 0; i < NUM_CLASSES; ++i) {
            for (int j = 0; j < image.getImage().size(); ++j) {
                for (int k = 0; k < image.getImage()[0].size(); ++k) {
                    if (image.getImage()[j][k]) {
                        class_probabilities[i] += log(probabilities[i][j][k]);
                    }
                }
            }
        }

        image.setPredictedLabel(getMostProbableClass(class_probabilities));
        class_probabilities = initial_probabilities;
    }
}

double ImageData::getAccuracyRate() {
    int num_correct_predictions = 0;

    for (Image image : test_images) {
        if (image.getPredictedLabel() == image.getImageLabel()) {
            num_correct_predictions++;
        }
    }

    return ((double)(num_correct_predictions) / test_images.size());
}