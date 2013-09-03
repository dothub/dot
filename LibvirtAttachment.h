/*
 * LibvirtAttachment.h
 *
 *  Created on: 2013-08-12
 *      Author: ar3roy
 */

#ifndef LIBVIRTATTACHMENT_H_
#define LIBVIRTATTACHMENT_H_

#include "InstantitiateHost.h"

class LibvirtAttachment: public InstantitiateHost {

	string virt_type;
	string networkFile;

	void loadConfiguration(string fileName);
	string createNewImage(unsigned long host_id);
public:
	LibvirtAttachment(Configurations* globalConf, Hosts* hosts, CommandExecutor* commandExec, InputTopology *topology, Mapping* mapping);
	void createHost2SwitchAttachmentConf();
	void startHost(unsigned long host_id);
	void prepare();
	string tapInterfacePrefix();

	virtual ~LibvirtAttachment();
};

#endif /* LIBVIRTATTACHMENT_H_ */
