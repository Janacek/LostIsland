//
// main.hpp for r-type in /home/arzaroth/svn/r-type/server
//
// Made by
// Login   <arzaroth@epitech.net>
//
// Started on  Sun Nov  3 23:10:29 2013
// Last update Sun Nov 24 17:12:02 2013 lekva
//

#ifndef         CROSSTYPE_HH_
# define        CROSSTYPE_HH_

# include	<string>

# ifdef		_WIN32
#  define       WIN32_LEAN_AND_MEAN
#  include	<winsock2.h>
#  define       NOMINMAX
#  include	<windows.h>
#  include	<winioctl.h>
#  include	<ws2tcpip.h>
#  include	<stdint.h>
#  define PACKED_STRUCT(name) __pragma(pack(push, 1)) struct name __pragma(pack(pop))
#  pragma comment(lib, "ws2_32.lib")
#  pragma comment(lib, "winmm.lib")
#  pragma warning(disable: 4127)
# else
#  include	<sys/types.h>
#  include	<sys/socket.h>
#  include	<sys/ioctl.h>
#  include	<netinet/in.h>
#  include	<arpa/inet.h>
#  include	<unistd.h>
#  include      <netdb.h>
#  define PACKED_STRUCT(name) struct __attribute__((__packed__)) name

typedef		int			SOCKET;
typedef		struct sockaddr_in	SOCKADDR_IN;
typedef		struct sockaddr_in6	SOCKADDR_IN6;
typedef		struct sockaddr_storage	SOCKADDR_STORAGE;
typedef		struct sockaddr		SOCKADDR;
typedef		struct in_addr		IN_ADDR;
# endif         /* !_WIN32 */

# include       <algorithm>

# ifndef        INET6_ADDRSTRLEN
#  define       INET6_ADDRSTRLEN 46
# endif         /* !INET6_ADDRSTRLEN */

# ifdef         max
#  undef        max
# endif         /* !max */

# ifdef         min
#  undef        min
# endif         /* !min */

# ifdef         UNICODE
typedef         std::wstring            String;
# else
typedef         std::string             String;
# endif         /* !UNICODE */

# if		(defined(__linux__) && defined(CLOCK_MONOTONIC_RAW))
#  define	CLOCK_FLAG		(CLOCK_MONOTONIC_RAW)
# elif		(defined(CLOCK_MONOTONIC))
#  define	CLOCK_FLAG		(CLOCK_MONOTONIC)
# else
#  define	CLOCK_FLAG		(CLOCK_REALTIME)
# endif

enum          e_type
  {
    UDP,
    TCP,
  };

enum          e_ipv
  {
    IPV4,
    IPV6,
    BOTH,
  };

const String inline toString(const char *str)
{
  std::string ex(str);
  return String(ex.begin(), ex.end());
}

# define        THREAD_NUMBERZ          50

#endif          /* !CROSSTYPE_HH_ */
