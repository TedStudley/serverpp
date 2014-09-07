#pragma once

class Socket {
  public:
    Socket();
    ~Socket();

    bool isValid() const;
  protected:

    int _socketFD;
};
