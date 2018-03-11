//
// Created by Vet Senthil on 3/10/2018.
//

#include "ImageData.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


ImageData::ImageData() {
    probabilities = vector<vector<vector<double>>>(28, vector<vector<double>>(28, vector<double>(10, 0)));
}

// Returning a reference for now
vector<Image>* ImageData::getTrainingImages() {
    //return training_images;
    vector<Image>* training_images_ptr = &training_images;
    return training_images_ptr;
}

vector<Image>* ImageData::getTestingImages() {
    //return  vector<Image>();
    vector<Image>* testing_images_ptr = &testing_images;
    return testing_images_ptr;
}

void ImageData::loadImages(vector<Image>* images) {
    ifstream inFile;
    inFile.open("../data/trainingimages");

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
}

void ImageData::loadLabels(vector<Image>* images) {
    ifstream inFile;
    inFile.open("../data/traininglabels");

    if (!inFile) {
        cout << "Unable to open file datafile.txt" << endl;
    }

    string image_label;
    int i = 0;

    while (getline(inFile, image_label)) {
        stringstream strstream(image_label);
        int label_num = 0;
        strstream >> label_num;

        (*(*images)[i++].getImageLabel()) = label_num;
    }
}

void ImageData::loadFromFile(string file_name) {

}

void ImageData::saveToFile(string file_name) {
    ofstream newFile;
    newFile.open(file_name);
}

int ImageData::getClassFrequency(int class_num) {
    int class_frequency = 0;

    for (Image image : training_images) {
        if ((*image.getImageLabel()) == class_num) {
            class_frequency += 1;
        }
    }

    return class_frequency;
}

int ImageData::getFeaturesSum(int class_num, int row, int col) {
    int feature_sum = 0;

    for (Image image : training_images) {
        if ((*image.getImageLabel()) == class_num && image.getImage()[row][col] == true) {
            feature_sum += 1;
        }
    }

    return feature_sum;
}

void ImageData::findProbabilities() {
    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); j++) {
            for (int k = 0; k < probabilities[0][0].size(); k++) {
                probabilities[i][j][k] = (LAPLACE_VALUE + getFeaturesSum(i, j, k)
                                                          / (2 * LAPLACE_VALUE + getClassFrequency(i)));
            }
        }
    }
}




