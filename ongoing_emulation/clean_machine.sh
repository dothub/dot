#!/bin/bash
# This file is part of DOT.
#
#     DOT is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     DOT is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with DOT.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright 2011-2013 dothub.org
#

#
#  dot_access
#
#  Created on: 2014-02-18
#      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)


#This script will clear the VMs and VNs deployed by DOT

echo "This script will clear the VMs and VNs deployed by DOT"
    
echo "Deleting all the components...."

#Retrieving the virtual links created by DOT
interfaces=`ovs-vsctl show | grep 'Port "veth'|tr -d ' '| cut -f2 -d'"'`

#Retrieving the OVS instances created by DOT
bridges=`ovs-vsctl show | grep 'Bridge "'|tr -d ' '| cut -f2 -d'"'`

#Retrieving the networks created by DOT
networks=`virsh net-list | grep 'ovs_network_' | awk '{print $1}'`  

#Retrieving the names of the VMS
VMs=`virsh list | grep h| awk '{print $2}'`

#Deleting VMs
for VM in $VMs
do
    echo "Deleting $VM..."
    virsh destroy $VM
    virsh undefine $VM
done

#Deleting KVM networks
for network in $networks
do
    echo "Deleting $network..."
    virsh net-destroy $network
    virsh net-undefine $network
done

#Deleting the OVS instances
for bridge in $bridges
do
    echo "Deleting $bridge..."
    ovs-vsctl del-br $bridge
done

#Deleting the Interfaces
for interface in $interfaces
do
    interface_id=`echo ${interface:4}`
    
    #If the veth ID is even, then deleting it
    if [ $((interface_id%2)) == 0 ]; then
        echo "Deleting $interface..."
        ip link del $interface
    fi
done


