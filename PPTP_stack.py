import sys, os
sys.path.append(os.getcwd() + "/../../")
from rubik import *
from protocols.TCP import *
from protocols.IP import *
from protocols.UDP import *
from protocols.GRE import *
from protocols.PPP import *
from protocols.PPTP import *
from protocols.Ethernet import *

def build_PPTP_stack():
    stacks = layer()

    eth = eth_layer()
    stacks['eth'] = eth

    ip, ip_temp = ip_layer()
    stacks['eth']['ip'] = ip

    tcp, tcp_temp = tcp_layer(stacks['eth']['ip'])
    tcp = tcp_layer_modify(tcp)
    stacks['eth']['ip']['tcp'] = \
        if_((stacks['eth']['ip'].psm['last_buffer'] or \
            stacks['eth']['ip'].psm['no_buffer'])\
            and stacks['eth']['ip'].header['protocol'] == 6) >> \
        tcp

    pptp = pptp_layer(stacks["eth"]["ip"])
    stacks['eth']['ip']['tcp']['pptp'] = \
        if_(stacks['eth']['ip']['tcp'].header["psh"]) >> pptp

    gre = gre_layer(stacks["eth"]["ip"])
    stacks['eth']['ip']['gre'] = \
        if_((stacks['eth']['ip'].psm['last_buffer'] or \
             stacks['eth']['ip'].psm['no_buffer']) \
             and stacks['eth']['ip'].header['protocol'] == 47) >> \
        gre

    ppp, ppp_temp = ppp_layer(stacks["eth"]["ip"], stacks['eth']['ip']['gre'])
    stacks['eth']['ip']['gre']['ppp'] = \
        if_(stacks['eth']['ip']['gre'].header['protocol'] == 0x880b and \
           (stacks['eth']['ip']['gre'].psm['tunneling_a'] or \
              stacks['eth']['ip']['gre'].psm['tunneling_p'])) >> \
        ppp

    stacks['eth']['ip']['gre']['ppp']['ip'] = \
        if_(ppp_temp['protocol'] == 0x0021) >> ip

    tcp, tcp_temp = tcp_layer(stacks['eth']['ip']['gre']['ppp']['ip'])
    stacks['eth']['ip']['gre']['ppp']['ip']['tcp'] = \
        if_((stacks['eth']['ip']['gre']['ppp']['ip'].psm['last_buffer'] or \
             stacks['eth']['ip']['gre']['ppp']['ip'].psm['no_buffer']) and \
             stacks['eth']['ip']['gre']['ppp']['ip'].header['protocol'] == 6) >> tcp

    udp = udp_layer()
    stacks['eth']['ip']['gre']['ppp']['ip']['udp'] = \
        if_((stacks['eth']['ip']['gre']['ppp']['ip'].psm['last_buffer'] or \
             stacks['eth']['ip']['gre']['ppp']['ip'].psm['no_buffer']) and \
             stacks['eth']['ip']['gre']['ppp']['ip'].header['protocol'] == 17) >> udp

    code_generator(stacks).generate(sys.argv[1])
if __name__ == "__main__":
    build_PPTP_stack()