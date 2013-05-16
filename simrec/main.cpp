#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) 
    {
        cout << "need arguments: file_name x_size y_size" << endl;
        return 1;
    }
    
    const char* filename = argv[1];
    int x_size = atoi(argv[2]);
    int y_size = atoi(argv[3]);

    ifstream image(filename, ios::in | ios::binary | ios::ate);
    
    if (image.is_open())
    {   
        ifstream::pos_type size = image.tellg();
        char* image_data = new char[size];
        
        image.seekg(0, ios::beg);
        image.read(image_data, size);
        image.close();

        cout << "Image reading ready!" << endl;
        
        if (size == x_size*y_size)
            cout << "Image is of correct size!" << endl;
        else
        {
            cout << "Image size doesn't match the arguments!" << endl;
            cout << "Should have been: " << x_size*y_size
                 << " but was " << size << endl;
        }
        delete[] image_data;
    }
    else
    {
        cout << "Unable to open file" << endl;
    }

    return 0;
}
