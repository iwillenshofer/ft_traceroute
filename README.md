<p align="center">
	<img width="130px;" src="https://game.42sp.org.br/static/assets/images/42_logo_black.svg" align="center" alt="42" />
	<h1 align="center">malloc</h1>
</p>
<p align="center">
	<img src="https://img.shields.io/badge/Success-125/100_✓-gray.svg?colorA=61c265&colorB=4CAF50&style=for-the-badge">
	<img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black">
</p>

<p align="center">
	<b><i>Development repository for the 42cursus ft_ping project @ 42 Heilbronn</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/iwillenshofer/ft_ping?color=blueviolet" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/iwillenshofer/ft_ping?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/commit-activity/t/iwillenshofer/ft_ping?color=brightgreen" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/iwillenshofer/ft_ping?color=brightgreen" />
</p>
<br>

> _Summary: This project is about recoding the ping command._

> _Ping is the name of a command that allows to test the accessibility of another machine through the IP network. The command measures also the time taken to receive a response, called round-trip time.._

<br>

<p align="center">
	<table>
		<tr>
			<td><b>Est. Time</b></td>
			<td><b>Skills</b></td>
			<td><b>Allowed Functions</b></td>
			<td><b>Difficulty</b></td>
		</tr>
		<tr>
			<td valign="top">49 hours</td>
			<td valign="top">
<img src="https://img.shields.io/badge/Unix-555">
<img src="https://img.shields.io/badge/Network & system administration -555">
<img src="https://img.shields.io/badge/Imperative programming-555">
			</td>
			<td valign="top">
				<img src="https://img.shields.io/badge/gettimeofday()-lightgrey">
				<img src="https://img.shields.io/badge/exit()-lightgrey">
				<img src="https://img.shields.io/badge/inet__ntop()-lightgrey"><br>
				<img src="https://img.shields.io/badge/inet__pton()-lightgrey">
				<img src="https://img.shields.io/badge/nthos()-lightgrey">
				<img src="https://img.shields.io/badge/htons()-lightgrey">
				<img src="https://img.shields.io/badge/signal()-lightgrey"><br>
				<img src="https://img.shields.io/badge/alarm()-lightgrey">
				<img src="https://img.shields.io/badge/usleep()-lightgrey">
				<img src="https://img.shields.io/badge/socket()-lightgrey"><br>
				<img src="https://img.shields.io/badge/setsockopt()-lightgrey">
				<img src="https://img.shields.io/badge/close()-lightgrey">
				<img src="https://img.shields.io/badge/sendto()-lightgrey"><br>
				<img src="https://img.shields.io/badge/recvmsg()-lightgrey">
				<img src="https://img.shields.io/badge/getpid()-lightgrey">
				<img src="https://img.shields.io/badge/getuid()-lightgrey"><br>
				<img src="https://img.shields.io/badge/getaddrinfo()-lightgrey">
				<img src="https://img.shields.io/badge/getnameinfo()-lightgrey"><br>
				<img src="https://img.shields.io/badge/freeaddrinfo()-lightgrey">
				<img src="https://img.shields.io/badge/strerror()-lightgrey"><br>
				<img src="https://img.shields.io/badge/gai__strerror()-lightgrey">
				<img src="https://img.shields.io/badge/printf()_and_its_family-lightgrey"><br>
				<img src="https://img.shields.io/badge/libft_library-lightgrey">
			</td>
			<td valign="top"> 9450 XP</td>
		</tr>
	</table>
</p>

<br>

### Usage
```bash
$ make
$ ./ft_ping google.com
```

### Implemented Arguments

|shrt| long | description |
| -c	| --count=NUMBER       |   stop after sending NUMBER packets													|
| -i	| --interval=NUMBER    |   wait NUMBER seconds between sending each packet										|
| -n	| --numeric            |   do not resolve host addresses														|
| -T	| --ttl=N              |   specify N as time-to-live															|
| -v	| --verbose            |   verbose output																		|
| -w	| --timeout=N          |   stop after N seconds																	|
| -f	| --flood              |   flood ping																			|
| -l	| --preload=NUMBER     |   send NUMBER packets as fast as possible before falling into normal mode of behavior	|
| -p	| --pattern=PATTERN    |   fill ICMP packet with given pattern													|
| -q	| --quiet              |   quiet output																			|
| -s	| --size=NUMBER        |   send NUMBER data octets																|
| -?	| --help               |   give this help list																	|
| -U	| --usage              |   give a short usage message															|
| -V	| --version            |   print program version																|
