sudo ovs-vsctl add-br topo3
sudo ovs-vsctl set-controller topo3 tcp:10.254.254.50:6633
sudo ovs-vsctl set-fail-mode topo3 secure
sudo ovs-vsctl set bridge topo3 other-config:datapath-id=0000000000000003
