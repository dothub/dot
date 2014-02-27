sudo ovs-vsctl add-br topo4
sudo ovs-vsctl set-controller topo4 tcp:10.254.254.50:6633
sudo ovs-vsctl set-fail-mode topo4 secure
sudo ovs-vsctl set bridge topo4 other-config:datapath-id=0000000000000004
