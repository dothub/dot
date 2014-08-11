#include "ImageRepo.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Util.h"

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
        ofstream fout("prepareVM.sh");

        if(fout.is_open())
        {
            
            string tempDir = Global::dotRoot + "/temp/h";
            
            tempDir += Util::longToString(vmId +1);
            tempDir += "/";

            fout << "mkdir -p " << tempDir << endl;
            
            fout << "cp " <<  Global::dotRoot << "/resources/provisioning/ubuntu/* "
                 << tempDir << endl;

            
            fout << "sed -i 's/$host_name/h"<< (vmId + 1) << "/g' " << tempDir << "hostname" << endl; 
            
            fout << "sed -i 's/$ip_address/" << Global::vms->getIPAddress(vmId)
                << "/g' " << tempDir << "interfaces" << endl; 
            
            fout << "virt-copy-in -a " << cloneName << " " << tempDir 
                << "70-persistent-net.rules /etc/udev/rules.d" << endl;
            
            fout << "virt-copy-in -a " << cloneName << " " << tempDir 
                << "hostname /etc" << endl;
            
            fout << "virt-copy-in -a " << cloneName << " " << tempDir 
                << "interfaces /etc/network" << endl;
            
            fout << "rm -r " << tempDir;

            fout.close();      
            
            this->commandExec->executeLocal("chmod +x prepareVM.sh");
            this->commandExec->executeScriptLocal("", "prepareVM.sh");
           // this->commandExec->executeLocal("rm prepareVM.sh");
           
        }
        else
            cout << "Unbale to open the script file" << endl;
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

