/*
 * main.c
 *
 *  Created on: 4 Jun 2021
 *      Author: pi
 */
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int gm66_address;

void gm66_init(void)
{


	char *portname = "/dev/ttyACM0";
	gm66_address = open (portname, O_RDWR | O_NONBLOCK);
	if (gm66_address < 0)
	{
			printf("error %d opening %s: %s", errno, portname, strerror (errno));
		exit(-1);
	}

	struct termios tty;
	memset (&tty, 0, sizeof tty);

	if (tcgetattr (gm66_address, &tty) != 0)
	{
			printf("error %d from tcgetattr(%s)\n", errno,strerror(errno));
	exit(-1);
	}


	cfsetospeed (&tty, B9600);
	cfsetispeed (&tty, B9600);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
									// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 0;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
									// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= 0;   //This was parity
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (gm66_address, TCSANOW, &tty) != 0)
	{
		printf("error %d from tcsetattr(%s)\n", errno,strerror(errno));
		exit(-1);
	}
}


void gm66_read(){
	unsigned char buf[1000];
	int n = read(gm66_address,buf,sizeof(buf));
	if(n > 0){
		for(int a = 0; a < n-1; a++){
			printf("%d | %c \n", n, buf[a]);
		}
	}
}

int main(){

	printf("BISMILLAH\n");
	printf("BISMILLAH\n");
	printf("BISMILLAH\n");
	printf("BISMILLAH\n");
	printf("BISMILLAH\n");
	printf("BISMILLAH\n");
	printf("BISMILLAH\n");
	printf("BISMILLAH\n");



	gm66_init();
	while(1){
		gm66_read();
	}


	return 0;
}

