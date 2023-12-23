//
// Created by Maxime BILLY on 23/12/2023.
//

#ifndef SECTRANS_SECTRANSCLIENT_H
#define SECTRANS_SECTRANSCLIENT_H


class SecTransClient {
public:
    void upload(const char *file);
    void download(const char *file);
    void list();
};


#endif //SECTRANS_SECTRANSCLIENT_H
