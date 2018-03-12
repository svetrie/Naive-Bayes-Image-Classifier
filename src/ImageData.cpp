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
    probabilities = vector<vector<vector<double>>>(Image::IMAGE_SIZE, vector<vector<double>>(Image::IMAGE_SIZE, vector<double>(NUM_CLASSES, 0)));
    priors = vector<double>(NUM_CLASSES);
}

// Returning a reference for now
vector<Image>* ImageData::getTrainingImages() {
    //return training_images;
    vector<Image>* training_images_ptr = &training_images;
    return training_images_ptr;
}

vector<Image>* ImageData::getTestImages() {
    //return  vector<Image>();
    vector<Image>* testing_images_ptr = &test_images;
    return testing_images_ptr;
}

void ImageData::loadImages(const char* file_name, vector<Image>* images) {
    ifstream inFile;
    //inFile.open("../data/trainingimages");
    inFile.open(file_name);

    if (!inFile) {
         cout << "Unable to open file datafile.txt" << endl;
    }

    vector<vector<bool>> trainingImage;
    //vector<vector<vector<bool>>> trainingImages;
    string line;

    //int i;
    for(int i = 0; getline(inFile, line); i = (i + 1) % 28) {
        vector<bool> row;

        for (char c : line) {
            row.push_back(c != ' ');
        }

        trainingImage.push_back(row);

        if (i == 27) {
            Image image(trainingImage);
            //training_images.push_back(image);
            images->push_back(image);

            //delete image;
      //      trainingImages.push_back(trainingImage);
            trainingImage.clear();
        }
    }

    for (auto row : (*images)[0].getImage()){
        for (bool t : row){
            cout << t;
        }
        cout << endl;
    }

    /*  for (auto row : training_images[0].getImage()){
        for (bool t : row){
            cout << t;
        }
        cout << endl;
    }
*/
    inFile.close();
}

void ImageData::loadLabels(const char* file_name, vector<Image>* images) {
    ifstream inFile;
    //inFile.open("../data/traininglabels");
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

        //(*(*images)[i++].getImageLabel()) = label_num;
        (*images)[i++].setImageLabel(label_num);
    }

    inFile.close();
}

void ImageData::loadModel(const char* file_name) {

}

void ImageData::saveModel(const char* file_name) {
    ofstream newFile;
    //newFile.open(file_name);
}

int ImageData::getClassFrequency(int class_num) {
    int class_frequency = 0;

    for (Image image : training_images) {
        if (image.getImageLabel() == class_num) {
            class_frequency += 1;
        }
    }

    return class_frequency;
}

int ImageData::getFeaturesSum(int class_num, int row, int col) {
    int feature_sum = 0;

    for (Image image : training_images) {
        if (image.getImageLabel() == class_num && image.getImage()[row][col] == true) {
            feature_sum += 1;
        }
    }

    return feature_sum;
}

void ImageData::findProbabilities() {
    cout << "Working before loop" << endl;

    for (int i = 0; i < probabilities.size(); i++) {

        int class_frequency = getClassFrequency(i);

        cout << "Working after 1st loop" << endl;

        for (int j = 0; j < probabilities[0].size(); j++) {

            cout << "Working after 2nd loop" << endl;

            for (int k = 0; k < probabilities[0][0].size(); k++) {

                cout << "Working after 3rd loop" << endl;

                probabilities[i][j][k] = (LAPLACE_VALUE + getFeaturesSum(i, j, k)
                                                          / (2 * LAPLACE_VALUE + class_frequency));

                cout << "working after calculations" << endl;
            }
        }
    }
}

void ImageData::findPriors() {
    for (int i = 0; i < priors.size(); ++i) {
        priors[i] = getClassFrequency(i) / training_images.size();
    }
}

vector<double>* ImageData::getPriors() {
    vector<double>* priors_ptr = &priors;
    return priors_ptr;
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
                    class_probabilities[i] += log(probabilities[i][j][k]);
                }
            }
        }

        image.setPredictedLabel(getMostProbableClass(class_probabilities));
        class_probabilities = initial_probabilities;
    }
}

double ImageData::getAccuracyRate() {
    int num_images = 0;
    int num_correct_predictions = 0;

    for (Image image : test_images) {
        num_images++;

        if (image.getPredictedLabel() == image.getImageLabel()) {
            num_correct_predictions++;
        }
    }

    return ((double)(num_correct_predictions) / num_images);
}