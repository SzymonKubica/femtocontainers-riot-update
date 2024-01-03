if [ $# -lt 2 ]
  then
    echo "Usage: $0 <network-interface> <board-ip-address> <bpf-executable-slot>"
    exit 1
fi

network_interface=$1
ip_address=$2
slot=$3

aiocoap-client -m POST "coap://[$ip_address%$network_interface]/bpf/exec/$slot"
