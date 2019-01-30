from rubik import layer, code_generator, if_, set_
from protocols.TCP import *
from protocols.IP import *
from protocols.Ethernet import *
def build_IP_TCP_layer():
    stacks = layer()

    eth = eth_layer()
    stacks['eth'] = eth

    ip, ip_temp = ip_layer()
    stacks['eth']['ip'] = ip

    tcp, tcp_temp = tcp_layer(stacks['eth']['ip'])
    stacks['eth']['ip']['tcp'] = \
        if_(( \
            stacks['eth']['ip'].psm['last_buffer'] or \
            stacks['eth']['ip'].psm['no_buffer'] \
        ) and stacks['eth']['ip'].header['protocol'] == 6) >> tcp

    code_generator(stacks).generate(sys.argv[1])

if __name__ == '__main__':
    build_IP_TCP_layer()