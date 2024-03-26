#include <iostream>
#include <cmath>
#include "Image_Class.h"
using namespace std;

void grayScale(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg=0;
            for (int k = 0; k < image.channels; k++) {
                avg += image(i, j, k);
            }
            avg = avg/3;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avg;
            }
        }
    }
    if(image.saveImage("output.jpg"))
        cout << "Image saved successfully at the file \"output.jpg\"." << endl;

}


void merge(Image& image1,Image& image2){
    unsigned int width ,height;
    width = min(image1.width,image2.width);
    height = min(image1.height,image2.height);

    Image image3(width,height);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < 3; k++) {
                image3(i,j,k)=(image1(i,j,k)+image2(i,j,k))/2;
                if(image3(i,j,k) > 255){
                    image3(i,j,k) = 255;
                }
            }
        }
    }
    if(image3.saveImage("output.jpg"))
        cout << "Image saved successfully at the file \"output.jpg\"." << endl;
}


void Black_White(const string& filename) {
    // Load the image
    Image image(filename);

    // Convert image to black and white
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Calculate luminance of each pixel
            int luminance = 0;
            for (int k = 0; k < image.channels; ++k) {
                luminance += image(i, j, k);
            }
            luminance /= image.channels;

            // Set pixel to black or white based on luminance
            for (int k = 0; k < image.channels; ++k) {
                if (luminance <= 127) {
                    image(i, j, k) = 0;
                } else {
                    image(i, j, k) = 255;
                }
            }
        }

    }


    if(image.saveImage("output.jpg"))
        cout << "Image saved successfully at the file \"output.jpg\"." << endl;
}


void horizontal(const string& filename) {
    // Load the image
    Image image(filename);

    // Iterate over each row
    for (int j = 0; j < image.height; ++j) {
        // Iterate over the left half of the width
        for (int i = 0; i < image.width/2; ++i) {
            // Swap pixels from left to right
            for (int k = 0; k < image.channels; ++k) {
                swap(image(i, j, k), image(image.width - 1 - i, j, k));
            }
        }
    }

    // Save the modified image
    image.saveImage("output.jpg");
}



void vertical(const string& filename) {
    // Load the image
    Image image(filename);

    // Iterate over each column
    for (int i = 0; i < image.width; ++i) {
        // Iterate over the top half of the height
        for (int j = 0; j < image.height / 2; ++j) {
            // Swap pixels from top to bottom
            for (int k = 0; k < image.channels; ++k) {
                swap(image(i, j, k), image(i, image.height - 1 - j, k));
            }
        }
    }

    // Save the modified image
    image.saveImage("output.jpg");

}



int main() {
    Image image,image1, image2;
    string filename, filename2;
    cout << " ==Welcome to Baby Photoshop program== " << endl;
    while (true) {
        cout << "Please choose an option : " << endl;
        cout << "1) Load New Image" << endl;
        cout << "2) Save and exit" << endl;

        string option;
        cin >> option;
        if (option == "1") {
            cout << "Please enter the image filename you want to edit : " << endl;
            cin >> filename;
            try {
                if (image1.loadNewImage(filename)) {
                    cout << "Image loaded successfully." << endl;
                }
            }
            catch (...) {
                cout << "Error, this image file does not exist, please try again" << endl;
                continue;
            }

            while (true) {
                cout << "Choose the filter you want to apply :" << endl;
                cout << "1) Gray scale\n2) Merging images\n3) Black and White\n4) Flip Image" << endl;
                string option2;
                cin >> option2;

                if (option2 == "1") {
                    grayScale(image1);
                    break;
                } else if (option2 == "2") {
                    while (true) {
                        cout << "Enter the name of the second image you want to merge with :  " << endl;
                        cin >> filename2;
                        try {
                            if (image2.loadNewImage(filename2)) {
                                merge(image1, image2);
                                break;
                            }
                        }
                        catch (...) {
                            cout << "Error, this image file does not exist, please try again" << endl;
                            continue;
                        }
                    }
                    break;
                } else if (option2 == "3") {
                    Black_White(filename);
                    break;
                }
                else if(option2=="4") {
                    int choice;
                    do {
                        cout << "You need to flip: \n1) Horizontally\n2) Vertically\n";

                        cin >> choice;

                        if (choice == 1) {
                            horizontal(filename);
                            cout << "Image saved successfully at the file \"output.jpg\"." << "'\n";
                            break;
                        } else if (choice == 2) {
                            vertical(filename);
                            cout << "Image saved successfully at the file \"output.jpg\"." << "'\n";
                            break;
                        } else {
                            cout << "Enter a valid number (1 or 2)\n";
                            break;
                        }
                    } while (choice!=1 || choice!=2);
                }
                else {
                    cout << "Invalid choice." << endl;
                }
                break;
            }
        } else if (option == "2") {
            cout << "Exiting" << endl;
            break; // Exit the loop
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
