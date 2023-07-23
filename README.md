Usage: ./ft_ping [OPTION...] HOST ...
Send ICMP ECHO_REQUEST packets to network hosts.

  -c, --count=NUMBER         stop after sending NUMBER packets
  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet
  -n, --numeric              do not resolve host addresses
      --ttl=N                specify N as time-to-live
  -v, --verbose              verbose output
  -w, --timeout=N            stop after N seconds
  -f, --flood                flood ping (root only)
  -l, --preload=NUMBER       send NUMBER packets as fast as possible before
                             falling into normal mode of behavior (root only)
  -p, --pattern=PATTERN      fill ICMP packet with given pattern (hex)
  -q, --quiet                quiet output
  -s, --size=NUMBER          send NUMBER data octets
  -?, --help                 give this help list
      --usage                give a short usage message
  -V, --version              print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Options marked with (root only) are available only to superuser.

Report bugs to <iwillens@student.42heilbronn.de>.
