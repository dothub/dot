sudo ovs-ofctl del-flows gw3
sudo ovs-ofctl add-flow gw3 in_port=1,actions=set_tunnel:1,output:3
sudo ovs-ofctl add-flow gw3 in_port=3,tun_id=1,actions=output:1
