sudo ovs-ofctl del-flows gw1
sudo ovs-ofctl add-flow gw1 in_port=1,actions=set_tunnel:1,output:3
sudo ovs-ofctl add-flow gw1 in_port=3,tun_id=1,actions=output:1
sudo ovs-ofctl add-flow gw1 in_port=2,actions=set_tunnel:2,output:3
sudo ovs-ofctl add-flow gw1 in_port=3,tun_id=2,actions=output:2
