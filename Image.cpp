#include "Image.h"



Image::Image(unsigned short image_id, string& type, 
    string& baseImage)
{
  
    this->id = image_id;
    this->type = type;
    this->baseImage = baseImage;
}
 
 

short Image::getId()
{
    return id;
}

string Image::getType()
{
    return type;
}

string Image::getBaseImage()
{
    return baseImage;
}

   
Image::~Image()
{

}

