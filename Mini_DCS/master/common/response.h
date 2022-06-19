#ifndef RESPONSE_H
#define RESPONSE_H

#include "buffer.h"

class Response{
public:
    Response();
    ~Response()=default;
    void init();
    void makeResponse(Buffer& buffer);
private:
    
};

#endif