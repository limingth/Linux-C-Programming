#include "skbuff.h"
#include "utils.h"

struct sk_buff skbuff[5];
int skb_cur = 0;

int skb_init(void)
{
	return 0;
}

void skb_headerinit(struct sk_buff *skb)
{
	memset(skb, 0, sizeof(struct sk_buff));

	skb->data = skb->buf;
	skb->len = 0;
	skb->truesize = ETH_FRAME_LEN;
}

struct sk_buff *alloc_skb(unsigned int size)
{
	struct sk_buff *skb;
	
	skb = &skbuff[skb_cur];
	skb_cur = (skb_cur + 1) % 5;
	skb_headerinit(skb);
	return skb;
}

void free_skb(struct sk_buff *skb)
{
}

unsigned char *skb_put(struct sk_buff *skb, unsigned int len)
{
	skb->len += len;
	return skb->data;
}

unsigned char *skb_pull(struct sk_buff *skb, unsigned int len)
{
	skb->data += len;
	skb->len -= len;
	return skb->data;
}

unsigned char *skb_push(struct sk_buff *skb, unsigned int len)
{
	skb->data -= len;
	skb->len += len;
	return skb->data;
}

void skb_reserve(struct sk_buff *skb, unsigned int len)
{
	skb->data += len;
}
