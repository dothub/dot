from image import Image
from controller import Controller
from vswitch import VSwitch
from host import Host
from link import Link
from collections import defaultdict

import re
import subprocess

class Dot(object):
    
    
    def __init__(self):
        self.root = ""        
        self.images = []
        self.hosts = []
        self.switches = []
        self.controllers = []
        self.dotUser = ""
        self.links = defaultdict(dict) 
        self.of_version = ""


    def load_hosts(self, fileName):
        """Populating the hosts"""
        
        with open(fileName) as f:
            for line in f:
                words = line.split()
                if words[0][0] == 'h':
                    host  = Host(words[0][1:], words[2])
                    self.hosts.append(host)
                else:
                    self.dotUser=words[0]
    
    def load_ctrls(self, fileName):
        """Populating the ctrl"""
        
        with open(fileName) as f:
            for line in f:
                words = line.split()
                if words[0][0] == 'c':
                    host_subnet=re.escape('10.254.')
                    in_band=0 if re.match(host_subnet, words[1]) == None else 1                    
                    controller = Controller(words[0][1:], words[1], words[2], in_band)
                    self.controllers.append(controller)
                else:
                    self.of_version=words[0]
    
    
    def load_images(self, fileName):
        """Populating the images"""
        
        with open(fileName) as f:
            for line in f:
                words = line.split()
                image = Image(words[0], words[1])
                self.images.append(image)
    
    
    def load_switches(self, fileName):
        '''Populating vswitches'''
        with open(fileName) as f:
            for line in f:
                words = line.split()
                vswitch = VSwitch(words[0][1:], words[1])
                self.switches.append(vswitch)
    

    def load_links(self, fileName):
        '''Populating links'''
        with open(fileName) as f:
            for line in f:
                words = line.split()
                link = Link(words[0][1:], words[1], words[2][1:], words[3])
                self.links[words[0][1:]][words[2][1:]] = link
                revLink = Link(words[2][1:], words[3], words[0][1:], words[1])
                self.links[words[2][1:]][words[0][1:]] = revLink
    


    def load(self):
        '''Loads information from the mapping'''
        
        self.load_images("../image_username")
        self.load_ctrls("../ctrl_mapping") 
        self.load_switches("../switch_mapping")
        self.load_hosts("../mapping")           
        self.load_links("../link_mapping")

    def execute(self, cmd, wait='true'):
        '''Method to execute command'''
        p = subprocess.Popen([cmd], shell=True, stdout=subprocess.PIPE)
        
        if wait == 'true':
            p.wait()
            return p.stdout.read()
    
 
    def ping(self, host1, host2):
        '''Method to invoke ping'''
        
        host1_id = host1[1:]
        host2_id = host2[1:]
        image_id = self.hosts[int(host1_id)-1].image_id
        uname = self.images[int(image_id)-1].user_name
        cmd = './scripts/ping h' + host1_id + ' h' + host2_id + ' ' + uname

        return self.execute(cmd)

         
    def linkAttachDetachParameter(self, switch1, switch2):
        '''Method to generate the link attach/detach parameter'''
        
        switch1_id = switch1[1:]
        switch2_id = switch2[1:]
        
        switch1_DN = self.switches[int(switch1_id)-1].dot_node
        switch2_DN = self.switches[int(switch2_id)-1].dot_node
        
        switch1_port = self.links[switch1_id][switch2_id].switch1_port
        switch2_port = self.links[switch1_id][switch2_id].switch2_port

        param = switch1_id + ' ' + switch1_DN + ' ' + switch1_port 
        param = param + ' ' + switch2_id + ' ' + switch2_DN + ' ' + switch2_port + ' ' + self.dotUser
        
        return param

    def attach(self, switch1, switch2):
        '''Method to attach the previously detached link'''
        
        param = self.linkAttachDetachParameter(switch1, switch2)

        cmd = './scripts/attach_link ' + param     
        
        return self.execute(cmd)
    
    def detach(self, switch1, switch2):
        '''Method to detach the previously detached link'''
        
        param = self.linkAttachDetachParameter(switch1, switch2)

        cmd = './scripts/detach_link ' + param     
        
        return self.execute(cmd)
                 
    def run(self, host, inCmd):
        ''' Method to run an arbitrary command in the background'''
        host_id = host[1:]
        image_id = self.hosts[int(host_id)-1].image_id
        uname = self.images[int(image_id)-1].user_name

        cmd = './scripts/cmd ' + host + ' ' + uname + ' \'' + inCmd + '\''

        self.execute(cmd, 'false')
