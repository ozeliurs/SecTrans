//
// Created by Maxime BILLY on 21/12/2023.
//

#ifndef SECTRANS_CLIENT_H
#define SECTRANS_CLIENT_H

/* send message (maximum size: 1024 bytes) */
int sndmsg(char msg[1024], int port);

#endif //SECTRANS_CLIENT_H
