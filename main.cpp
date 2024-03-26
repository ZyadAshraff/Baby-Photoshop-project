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



int main() {
    Image image1, image2;
    string filename,filename2;
    cout << " ==Welcome to Baby Photoshop program== " << endl;
    while (true) {
        cout << "Please choose an option : " << endl;
        cout << "1) Load New Image" << endl;
        cout << "2) Save and exit" << endl;

        string option,option2,option3;
        cin >> option;
        if ( option != "1" && option != "2"){
            cout << "Invalid choice." << endl;
            continue;
        }

        while (true) {
            if (option == "1") {
                cout << "Please enter the image filename you want to edit : " << endl;
                cin >> filename;
                try {
                    if (image1.loadNewImage(filename)) {
                        cout << "Image loaded successfully." << endl;
                    }
                }
                catch (...) {
                    cout << "Error, this image file is not exist, please try again" << endl;
                    continue;
                }
                while (true) {
                    cout << "Choose the filter you want to apply :" << endl;
                    cout << "1) Gray scale\n2) Merging images" << endl;
                    cin >> option2;


                    if (option2 == "1") {
                        grayScale(image1);
                        break;
                    } else if (option2 == "2") {
                        while (true) {
                            cout << "Enter the name of the second image you want to merge with :  " << endl;
                            cin >> filename2;
                            try {
                                image2.loadNewImage(filename2);
                                merge(image1, image2);
                                break;
                            }
                            catch (...) {
                                cout << "Error, this image file is not exist, please try again" << endl;
                                continue;
                            }
                        }
                        break;
                    }
                }
                if (option == "2") {
                    cout << "Exiting" << endl;
                    return 0;
                } else {
                    cout << "Invalid choice." << endl;
                    continue;
                }
            }
        }
    }
}