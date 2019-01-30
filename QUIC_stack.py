from rubik import layer
from protocols.loopback import *
from protocols.IP import *
from protocols.UDP import *
from protocols.QUIC_frame import *
from protocols.QUIC_header import *
from protocols.loopback import *


def build_quic_layer():
    stack = layer()

    loopback = loopback_layer()
    stack['loopback'] = loopback

    ip, ip_temp = ip_layer()
    stack['loopback']['ip'] = ip

    udp = udp_layer()
    stack['loopback']['ip']['udp'] = udp
    
    quic_header = \
        quic_header_layer(stack['loopback']['ip'], stack['loopback']['ip']['udp'])

    stack['loopback']['ip']['udp']['quic_header'] = quic_header

    quic_frame_protocol, quic_frame_temp_data = \
        quic_frame_layer(stack['loopback']['ip'], stack['loopback']['ip']['udp'])

    stack['loopback']['ip']['udp']['quic_header']['quic_frame'] = \
        while_(quic_frame_protocol.SDU_length > 0) >> \
            (quic_frame_protocol + set_(quic_frame_protocol.SDU, \
            quic_frame_protocol.SDU + quic_frame_temp_data['length']) + \
            set_(quic_frame_protocol.SDU_length, \
                quic_frame_protocol.SDU_length - quic_frame_temp_data["length"]))

    code_generator(stack).generate(sys.argv[1])

if __name__ == "__main__":
    build_quic_layer()


