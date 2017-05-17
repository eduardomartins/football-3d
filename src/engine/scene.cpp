/*
 * MIT License
 *
 * Copyright (c) 2017 Eduardo Sant'Anna Martins <eduardo@eduardomartins.site>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "scene.h"

Scene::Scene(QObject *parent) : QObject(parent)
{

}


Room::Room(QObject *parent) : QObject(parent)
  , cube
{
        // Piso
{ { -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 } },

        // Teto
{ { -1, +1, -1 }, { +1, +1, -1 }, { +1, +1, +1 }, { -1, +1, +1 } },

        // Paredes
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } },
//{ { -2.5f, -2.5f, +2.5f }, { +2.5, -2.5f, +2.5f }, { +2.5f, -2.5f, -2.5f }, { -2.5f, -2.5f, -2.5f } },
{ { -1, -1, -1 }, { +1, -1, -1 }, { +1, +1, -1 }, { -1, +1, -1 } },
{ { +1, +1, +1 }, { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 } },
{ { -1, +1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { -1, +1, -1 } },
        }
{
    image = loadBMP("../../media/wood_texture_mini.bmp");
    texture = loadTexture(image);
}


Room::~Room()
{
    delete image;
    vbo.destroy();
}


void Room::draw() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(NORM_HEX(192), NORM_HEX(192), NORM_HEX(192));

    float tex[4][2] = {
        {0.0f, 0.0f},
        {2.5f, 0.0f},
        {2.5f, 2.5f},
        {0.0f, 2.5f},
    };

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0f, 0.0f);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            glTexCoord2f(tex[j][0], tex[j][1]);
            glVertex3f(cube[i][j][0], cube[i][j][1], cube[i][j][2]);
        }
    }
    glEnd();
}


void Room::drawTextures()
{

    QVector<GLfloat> vertData;

    for(int i = 0; i < 1; i++) {
        for (int j = 0; j < 4; ++j) {
            // vertex position
            vertData.append(0.2 * cube[i][j][0]);
            vertData.append(0.2 * cube[i][j][1]);
            vertData.append(0.2 * cube[i][j][2]);
            // texture coordinate
            vertData.append(j == 0 || j == 3);
            vertData.append(j == 0 || j == 1);
        }
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

}

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {

}

Image::~Image() {
    delete[] pixels;
}

namespace {
//Converts a four-character array to an integer, using little-endian form
int toInt(const char* bytes) {
    return (int)(((unsigned char)bytes[3] << 24) |
            ((unsigned char)bytes[2] << 16) |
            ((unsigned char)bytes[1] << 8) |
            (unsigned char)bytes[0]);
}

//Converts a two-character array to a short, using little-endian form
short toShort(const char* bytes) {
    return (short)(((unsigned char)bytes[1] << 8) |
            (unsigned char)bytes[0]);
}

//Reads the next four bytes as an integer, using little-endian form
int readInt(ifstream &input) {
    char buffer[4];
    input.read(buffer, 4);
    return toInt(buffer);
}

//Reads the next two bytes as a short, using little-endian form
short readShort(ifstream &input) {
    char buffer[2];
    input.read(buffer, 2);
    return toShort(buffer);
}

//Just like auto_ptr, but for arrays
template<class T>
class auto_array {
private:
    T* array;
    mutable bool isReleased;
public:
    explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false) {
    }

    auto_array(const auto_array<T> &aarray) {
        array = aarray.array;
        isReleased = aarray.isReleased;
        aarray.isReleased = true;
    }

    ~auto_array() {
        if (!isReleased && array != NULL) {
            delete[] array;
        }
    }

    T* get() const {
        return array;
    }

    T &operator*() const {
        return *array;
    }

    void operator=(const auto_array<T> &aarray) {
        if (!isReleased && array != NULL) {
            delete[] array;
        }
        array = aarray.array;
        isReleased = aarray.isReleased;
        aarray.isReleased = true;
    }

    T* operator->() const {
        return array;
    }

    T* release() {
        isReleased = true;
        return array;
    }

    void reset(T* array_ = NULL) {
        if (!isReleased && array != NULL) {
            delete[] array;
        }
        array = array_;
    }

    T* operator+(int i) {
        return array + i;
    }

    T &operator[](int i) {
        return array[i];
    }
};
}

Image* loadBMP(const char* filename) {
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch(headerSize) {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            for(int c = 0; c < 3; c++) {
                pixels2[3 * (width * y + x) + c] =
                        pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}
