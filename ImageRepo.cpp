#include "ImageRepo.h"
#include <fstream>
#include <iostream>
#include <cstdlib>


ImageRepo::ImageRepo(CommandExecutor* commandExec)
{
  
    this->commandExec = commandExec;
}
 
void ImageRepo::prepareImage(string type, string cloneName,   
                unsigned long vmId)
{
    if(type.compare("tc") == 0)
    {
        //do nothing
    }
    else if(type.compare("ubuntu") == 0)
    {


    }
}
 

Image* ImageRepo::getImage(unsigned short image_id)
{
    return imageStore.find(image_id)->second;
}


void ImageRepo::populateImages(string fileName)
{
    ifstream fin(fileName.c_str());

    if(fin.is_open())
    {
        fin >> this->numberOfImages;


        for(unsigned short i = 0; i < this->numberOfImages; i++)
        {
            string name, type, location;

            fin >> name >> type >> location;
            
            unsigned short image_id =  (short)atoi(name.substr(1).c_str())-1;

            Image* newImage = new Image(image_id, type, location); 
                    
            this->imageStore.insert(make_pair(image_id, newImage));
        }


        fin.close();
    }
    else
        cout << "Unable to open physical machine file: " << fileName << endl;

}   
ImageRepo::~ImageRepo()
{

}

