//
// Created by Maxime BILLY on 21/12/2023.
//

#ifndef SECTRANS_SERVER_H
#define SECTRANS_SERVER_H

int startserver(int port);
int stopserver();

/* read message sent by client */
int getmsg(char msg_read[1024]);

#endif //SECTRANS_SERVER_H
