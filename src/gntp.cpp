#include "gntp.h"

using namespace CryptoPP;
using namespace CryptoPP::Weak1;

extern "C" {

void
gntp_notify_send(const char* application, const char* event, const char* title, const char* message) {
  try {
    gntp client(application);
    client.regist<DES, MD5>(event);
    client.notify<DES, MD5>(event, title, message);
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void*
gntp_create(const char* host, const char* port, const char* application, const char* password) {
  return (void*) new gntp(application, "", password, host, port);
}

void
gntp_register(void* p, const char* event) {
  gntp* client = static_cast<gntp *>(p);
  client->regist(event);
}

void
gntp_notify(void* p, const char* event, const char* title, const char* message, const char* icon, const char* url) {
  gntp* client = static_cast<gntp *>(p);
  client->notify(event, title, message, icon, url);
}

void
gntp_release(void* p) {
  delete static_cast<gntp *>(p);
}

}
