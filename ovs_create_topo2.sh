sudo ovs-vsctl add-br topo2
sudo ovs-vsctl set-controller topo2 tcp:10.254.254.50:6633
sudo ovs-vsctl set-fail-mode topo2 secure
sudo ovs-vsctl set bridge topo2 other-config:datapath-id=0000000000000002
