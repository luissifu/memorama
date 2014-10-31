#include "Card.h"
#include "Imageloader.h"

#include <assert.h>
#include <fstream>


using namespace std;
static GLuint texName[36];
const int TEXTURE_COUNT=6;
int angulo=0;

Card::Card() {
	value = 0;
	show = selected = false;
}

Card::Card(int value) {
	this->value = value;
	show = selected = false;
}

void Card::flip() {
	show = !show;
}

bool Card::shouldShow() {
	return show;
}

void Card::setShow(bool show) {
	this->show = show;
}

int Card::getValue() {
	return value;
}

void Card::setValue(int value) {
	this->value = value;
}
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

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

}

void initRendering()
{
    int i=0;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); ///Users/mariaroque/Imagenes
    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(5, texName); //Make room for our texture
    Image* image = loadBMP("c:/ciervo.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/mariaroque/Imagenes/LOBO.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/mariaroque/Imagenes/SOL.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/mariaroque/Imagenes/LEON.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/mariaroque/Imagenes/TEC.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/mariaroque/Imagenes/earth.bmp");
    loadTexture(image,i++);
    // image = loadBMP("/Users/mariaroque/Imagenes/ojo.bmp");
    delete image;
}
Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}
Image* loadBMP(const char* filename)
{
    std::ifstream input;
    input.open(filename, std::ifstream::binary);
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
    switch (headerSize)
    {
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
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}

void Card::draw(float ang) {
     glEnable(GL_TEXTURE_2D);
 //   glScalef(1.0*(30angulo+1)/1.5,1.0*(angulo+1)/1.5,1.0*(angulo+1)/10);


	if (selected)
	{
		glColor3ub(255, 255, 200);
	}
	else
	{    glBindTexture(GL_TEXTURE_2D, texName[0]);
		//glColor3ub(255, 255, 255);
	}

	glPushMatrix();
	glColor3f(0,0,1);

		glTranslatef(x, y, 0.0);
		glScalef(0.5,1.0,0.02);
		if (selected)
		{
			glRotatef(ang, 0.0, 1.0, 0.0);
			glColor3ub(255, 255, 200);
		}
		else if (!show)
		{
		glBindTexture(GL_TEXTURE_2D, texName[angulo]);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-5.0f, -5.0f, 0);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(-4.0f, -5.0f, 0);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(-4.0f, -6.0f, 0);

                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-5.0f, -6.0f, 0);
                glEnd();
			//glColor3ub(255, 0, 0);
		}
		else
		{
			glRotatef(ang, 0.0, 1.0, 0.0);
			glColor3ub(255, 255, 255);}



        if(value == 3 && selected){
            glEnable (GL_POLYGON_STIPPLE);
			glColor3f (1.0, 1.0, 0.0);
			glPolygonStipple (tres);
			glutSolidCube(2);
			glDisable(GL_POLYGON_STIPPLE);
        }
        else if(value == 6 && selected){
			glEnable (GL_POLYGON_STIPPLE);
			glColor3f (1.0, 1.0, 0.0);
			glPolygonStipple (seis);
			glutSolidCube(2);
			glDisable(GL_POLYGON_STIPPLE);
        }
        else {

            glutSolidCube(2);
        }
		glColor3f(0,0,0);
		glutWireCube(2);
	glPopMatrix();

}

bool Card::inside(float px, float py) {
	if (px < x || px > x + 1.1)
		return false;
	else if (py < y || py > y + 1.95)
		return false;

	return true;
}


bool Card::isSelected() {
	return selected;
}

void Card::setSelected(bool select) {
	selected = select;
}
