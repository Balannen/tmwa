#ifndef CHAR_HPP
#define CHAR_HPP

#include "../common/const_array.hpp"
#include "../common/mmo.hpp"

#define MAX_MAP_SERVERS 30

#define CHAR_CONF_NAME  "conf/char_athena.conf"

#define LOGIN_LAN_CONF_NAME     "conf/lan_support.conf"

#define DEFAULT_AUTOSAVE_INTERVAL 300*1000

struct mmo_map_server
{
    long ip;
    short port;
    int users;
    char map[MAX_MAP_PER_SERVER][16];
};

int search_character_index(const char *character_name);
char *search_character_name(int index);

int mapif_sendall(const uint8_t *buf, unsigned int len);
int mapif_sendallwos(int fd, const uint8_t *buf, unsigned int len);
int mapif_send(int fd, const uint8_t *buf, unsigned int len);

void char_log(const_string line);

#define CHAR_LOG(fmt, args...) \
    char_log(static_cast<const std::string&>(STRPRINTF(fmt, ## args)))

extern int autosave_interval;

#endif // CHAR_HPP
