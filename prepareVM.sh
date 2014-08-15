mkdir -p /home/ar3roy/DOT/dot_v1/temp/h5/
cp /home/ar3roy/DOT/dot_v1/resources/provisioning/ubuntu/* /home/ar3roy/DOT/dot_v1/temp/h5/
sed -i 's/$host_name/h5/g' /home/ar3roy/DOT/dot_v1/temp/h5/hostname
sed -i 's/$ip_address/10.254.0.5/g' /home/ar3roy/DOT/dot_v1/temp/h5/interfaces
virt-copy-in -a /home/ar3roy/DOT/dot_v1/resources/images/clone_h5.qcow2 /home/ar3roy/DOT/dot_v1/temp/h5/70-persistent-net.rules /etc/udev/rules.d
virt-copy-in -a /home/ar3roy/DOT/dot_v1/resources/images/clone_h5.qcow2 /home/ar3roy/DOT/dot_v1/temp/h5/hostname /etc
virt-copy-in -a /home/ar3roy/DOT/dot_v1/resources/images/clone_h5.qcow2 /home/ar3roy/DOT/dot_v1/temp/h5/interfaces /etc/network
rm -r /home/ar3roy/DOT/dot_v1/temp/h5/