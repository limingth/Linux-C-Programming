#ifndef __TFTPPUT_H
#define __TFTPPUT_H

int tftp_put_begin(void);
int tftp_put(unsigned char *data, int len);
int tftp_put_end(void);

#endif /* __TFTPPUT_H */
