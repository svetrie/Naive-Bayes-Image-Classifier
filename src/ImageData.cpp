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
    //vector<vector<bool>> trainingImage (28, vector<bool>(28, false));
    //vector<vector<vector<bool>>> trainingImages;
    string line;

    //int i;
    for(int i = 0; getline(inFile, line); i = (i + 1) % 28) {
        //vector<bool> row;
        vector<bool> row(28, false);

        for (int j = 0; j < line.size(); ++j) {
            row[j] = (line[j] != ' ');
        }


        /*
        for (char c : line) {
            row.push_back(c != ' ');
        }*/

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
    ifstream myFile;
    myFile.open(file_name);

    char* feature_probabiltity;
    int line = 1;

    cout << "works fine 1" << endl;


    for (int i = 0; i < probabilities.size(); i++) {

        cout << "works 2" << endl;

        for (int j = 0; j < probabilities[0].size(); ++j) {

            cout << "works 3" << endl;

            for (int k = 0; k < probabilities[0][0].size(); ++k) {

                cout << "works 4" << endl;

                myFile.getline(feature_probabiltity, line);
                probabilities[i][j][k] = atof(feature_probabiltity);
                line++;
            }
        }
    }

    char* prior_value;

    cout << "works efore priors" << endl;

    for (int m = 0; m < priors.size(); ++m) {
        cout << "works 5#" << endl;

        myFile.getline(prior_value, line);

        cout << "works 6 " << endl;

        priors[m] = atof(prior_value);

        cout << "works 7 " << endl;

        line++;
    }

    cout << probabilities[0][0][2] << endl;
    cout << priors[5] << endl;
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
    //int class_frequency = 0;

    //cout << "err" << endl;


    for (Image image : training_images) {
        class_frequencies[image.getImageLabel()]++;
    }

    /*
    for (int i = 0; i < training_images.size(); ++i) {
        if (training_images[i].getImageLabel() == class_num) {
            class_frequency++;
        }
    }*/

    //return class_frequency;
}

int ImageData::getFeaturesSum(int class_num, int row, int col) {
    int feature_sum = 0;

    //cout << "possible err" << endl;

    for (Image image : training_images) {

        //cout << "passed for each loop" << endl;
        //cout << image.getImageLabel() << endl;

        if (image.getImageLabel() == class_num && image.getImage()[row][col]) {
            feature_sum += 1;
        }
    }

    return feature_sum;
}

void ImageData::findProbabilities() {
    //cout << "Working before loop" << endl;

    //cout << probabilities.size() << endl;

    for (int i = 0; i < probabilities.size(); i++) {

       // cout << "Class freq" << endl;
        // dl;

        //int class_frequency = getClassFrequency(i);
        //cout << "class frequency:" << class_frequency << endl;

        //cout << "Working after 1st loop" << endl;

        for (int j = 0; j < probabilities[0].size(); j++) {

          //  cout << "Working after 2nd loop" << endl;

            for (int k = 0; k < probabilities[0][0].size(); k++) {

            //    cout << "Working after 3rd loop" << endl;

                probabilities[i][j][k] = ((LAPLACE_VALUE + getFeaturesSum(i, j, k))
                                                          / (2 * LAPLACE_VALUE + class_frequencies[i]));
               // cout << probabilities[i][j][k] << endl;

              //  cout << "working after calculations" << endl;
            }
        }
    }
}

void ImageData::findPriors() {
    for (int i = 0; i < priors.size(); ++i) {
        priors[i] = double(class_frequencies[i] * 1.0) / training_images.size();
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
                    if (image.getImage()[j][k]) {
                        class_probabilities[i] += log(probabilities[i][j][k]);
                    }
                }
            }
        }

        cout << getMostProbableClass(class_probabilities) << endl;
        image.setPredictedLabel(getMostProbableClass(class_probabilities));
        class_probabilities = initial_probabilities;
    }
}

double ImageData::getAccuracyRate() {
    //int num_images = 0;
    int num_correct_predictions = 0;

    for (Image image : test_images) {
        //num_images++;

        if (image.getPredictedLabel() == image.getImageLabel()) {
            num_correct_predictions++;
        }
    }

    return ((double)(num_correct_predictions) / test_images.size());
}