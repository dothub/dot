sudo ovs-ofctl del-flows gw2
sudo ovs-ofctl add-flow gw2 in_port=1,actions=set_tunnel:1,output:4
sudo ovs-ofctl add-flow gw2 in_port=4,tun_id=1,actions=output:1
sudo ovs-ofctl add-flow gw2 in_port=2,actions=set_tunnel:1,output:5
sudo ovs-ofctl add-flow gw2 in_port=5,tun_id=1,actions=output:2
sudo ovs-ofctl add-flow gw2 in_port=3,actions=set_tunnel:2,output:4
sudo ovs-ofctl add-flow gw2 in_port=4,tun_id=2,actions=output:3
