sudo ovs-vsctl add-br topo1
sudo ovs-vsctl set-controller topo1 tcp:10.254.254.50:6633
sudo ovs-vsctl set-fail-mode topo1 secure
sudo ovs-vsctl set bridge topo1 other-config:datapath-id=0000000000000001
