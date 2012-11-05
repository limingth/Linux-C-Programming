#ifndef __SKBUFF_H
#define __SKBUFF_H

#include "eth.h"

struct sk_buff {

	unsigned char pad[2];
	unsigned char buf[ETH_FRAME_LEN];
	unsigned int truesize;			/* Buffer size 					*/

	unsigned char *data;			/* Data head pointer				*/
	unsigned int len;			/* Length of actual data			*/
};

int skb_init(void);
struct sk_buff *alloc_skb(unsigned int size);
void free_skb(struct sk_buff *skb);
unsigned char *skb_put(struct sk_buff *skb, unsigned int len);
unsigned char *skb_push(struct sk_buff *skb, unsigned int len);
unsigned char *skb_pull(struct sk_buff *skb, unsigned int len);
void skb_reserve(struct sk_buff *skb, unsigned int len);

#endif	/* __SKBUFF_H */
