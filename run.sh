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

if [ ! "$#" -eq 1 ] && [ ! "$#" -eq 2 ]; then
    echo "To run the script: ./run.sh configuration_file [-d]"
    exit 1
fi

executable="dot_manager"
if [ ! -x dot_manager ]; then
    echo "dot_manager is not found"
    echo -n "Enter the name of your DOT Manager executable file: "
    read executable
fi

if [ ! -f "$1" ]; then
    echo "The configuration file $1 does not exist"
    exit 1
fi

if [ ! "$2" = "-d" ]; then
    echo "Invalid second parameter $2"
    echo "To turn the debug mode on use -d as second parameter"
    exit 1
fi
 
echo "Start reading the configuration file"

create_conf/conf_util -c $1 &>/dev/null
line_number=`grep -n "\[EmulationName\]" $1 | cut -f1 -d':'`
line_number=$(($line_number+1))
emulation_name=`awk 'NR=='"$line_number"'' $1`

echo "End Reading the configuration file"

echo "Running DOT Manager...."

./$executable -g emulations/$emulation_name/DefaultConfiguration_$emulation_name $2
