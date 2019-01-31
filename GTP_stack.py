from rubik import *
from protocols.TCP import *
from protocols.IP import *
from protocols.UDP import *
from protocols.GTP import *
from protocols.Ethernet import *

def build_GTP_stack():
    stacks = layer()

    eth = eth_layer()
    stacks['eth'] = eth

    ip, ip_temp = ip_layer()
    stacks['eth']['ip'] = ip

    udp = udp_layer()
    stacks['eth']['ip']['udp'] = \
        if_((stacks['eth']['ip'].psm['last_buffer'] or \
             stacks['eth']['ip'].psm['no_buffer']) and \
             stacks['eth']['ip'].header['protocol'] == 17) >> udp

    gtp = gtp_layer()
    stacks['eth']['ip']['udp']['gtp'] = gtp

    stacks['eth']['ip']['udp']['gtp']['ip'] = \
        if_(stacks['eth']['ip']['udp']['gtp'].header['MT'] == 255) >> ip
    
    stacks['eth']['ip']['udp']['gtp']['ip']['udp'] = \
        if_((stacks['eth']['ip']['udp']['gtp']['ip'].psm['last_buffer'] or \
             stacks['eth']['ip']['udp']['gtp']['ip'].psm['no_buffer']) and \
            stacks['eth']['ip']['udp']['gtp']['ip'].header['protocol'] == 17) >> udp

    tcp, tcp_temp = tcp_layer(stacks['eth']['ip']['udp']['gtp']['ip'])
    stacks['eth']['ip']['udp']['gtp']['ip']['tcp'] = \
        if_((stacks['eth']['ip']['udp']['gtp']['ip'].psm['last_buffer'] or \
             stacks['eth']['ip']['udp']['gtp']['ip'].psm['no_buffer']) and \
             stacks['eth']['ip']['udp']['gtp']['ip'].header['protocol'] == 6) >> tcp

    code_generator(stacks).generate(sys.argv[1])

if __name__ == '__main__':
    build_GTP_stack()