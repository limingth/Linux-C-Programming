#include "types.h"
#include "skbuff.h"
#include "eth.h"
#include "arp.h"
#include "ip.h"
#include "udp.h"
#include "tftp.h"
#include "tftpput.h"
#include "utils.h"

unsigned long client_ip;
unsigned short client_port;
unsigned short client_block;


int tftp_send_ack(struct tftphdr *tftp_hdr, int block)
{
	struct tftphdr *tftp_ack;
	struct sk_buff *skb;

	skb = alloc_skb(ETH_FRAME_LEN);
	udp_skb_reserve(skb);
	tftp_ack = (struct tftphdr *)skb_put(skb, sizeof(struct tftphdr));
	tftp_ack->th_opcode = htons(ACK);
	tftp_ack->th_block = htons(block);

	udp_send(skb, client_ip, TFTP, client_port);

	return 0;
}

int tftp_rcv_wrq(struct sk_buff *skb)
{
	struct tftphdr *tftp_hdr;

	client_ip = ip_get_source_ip(skb);
	client_port = udp_get_source_port(skb);

	tftp_hdr = (struct tftphdr *)skb->data;
	tftp_send_ack(tftp_hdr, 0);
	client_block = 1;

	tftp_put_begin();

	return 0;
}

int tftp_rcv_data(struct sk_buff *skb)
{
	struct tftphdr *tftp_hdr;
	int len;

	if (client_ip != ip_get_source_ip(skb))
		return -1;
	if (client_port != udp_get_source_port(skb))
		return -1;

	tftp_hdr = (struct tftphdr *)skb->data;
	if (client_block == ntohs(tftp_hdr->th_block)) {

		len = skb->len - sizeof(struct tftphdr);
//		tftp_put(tftp_hdr->th_data, len);
		tftp_put((unsigned char *)tftp_hdr+sizeof(struct tftphdr), len);

		tftp_send_ack(tftp_hdr, client_block);
		client_block++;

		if (len < 512)		
			tftp_put_end();		

	} else if (client_block > ntohs(tftp_hdr->th_block)) {

		tftp_send_ack(tftp_hdr, ntohs(tftp_hdr->th_block));

	} else {

		tftp_send_ack(tftp_hdr, client_block);
	}

	return 0;
}

int tftp_rcv_packet(struct sk_buff *skb)
{
	struct tftphdr *tftp_hdr;
	
	tftp_hdr = (struct tftphdr *)skb->data;

	switch (ntohs(tftp_hdr->th_opcode)) {

	case RRQ:
		break;
	case WRQ:
		tftp_rcv_wrq(skb);
		break;
	case DATA:
		tftp_rcv_data(skb);
		break;
	case ACK:
		break;
	case ERROR:
		break;
	default:
		break;
	}

	return 0;
}
