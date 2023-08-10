<p align="center">
	<img width="130px;" src="https://game.42sp.org.br/static/assets/images/42_logo_black.svg" align="center" alt="42" />
	<h1 align="center">ft_traceroute</h1>
</p>
<p align="center">
	<!--img src="https://img.shields.io/badge/Success-125/100_✓-gray.svg?colorA=61c265&colorB=4CAF50&style=for-the-badge"-->
	<img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black">
</p>

<p align="center">
	<b><i>Development repository for the 42cursus ft_traceroute project @ 42 Heilbronn</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/iwillenshofer/ft_traceroute?color=blueviolet" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/iwillenshofer/ft_traceroute?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/commit-activity/t/iwillenshofer/ft_traceroute?color=brightgreen" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/iwillenshofer/ft_traceroute?color=brightgreen" />
</p>
<br>

> _Summary: This project will make you recode the traceroute command._

> _Traceroute (aka tracert on Windows) is a utility program that allows to track the route a data packet (IP packets) will follow from one local machine to another one that’s connected to the same IP network. It was designed within the Lawrence-Berkeley national Laboratory (and here, at the 42 network international laboratory, we'll just recode it)._

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
				<img src="https://img.shields.io/badge/getpid()-lightgrey">
				<img src="https://img.shields.io/badge/getuid()-lightgrey"><br>
				<img src="https://img.shields.io/badge/getaddrinfo()-lightgrey">
				<img src="https://img.shields.io/badge/gettimeofday()-lightgrey">
				<img src="https://img.shields.io/badge/freeaddrinfo()-lightgrey">
				<img src="https://img.shields.io/badge/exit()-lightgrey">
				<img src="https://img.shields.io/badge/select()-lightgrey">
				<img src="https://img.shields.io/badge/setsockopt()-lightgrey">
				<img src="https://img.shields.io/badge/inet__ntop()-lightgrey"><br>
				<img src="https://img.shields.io/badge/inet__pton()-lightgrey">
				<img src="https://img.shields.io/badge/recvfrom()-lightgrey">
				<img src="https://img.shields.io/badge/sendto()-lightgrey">
				<img src="https://img.shields.io/badge/nthos()-lightgrey">
				<img src="https://img.shields.io/badge/htons()-lightgrey"><br>
				<img src="https://img.shields.io/badge/bind()-lightgrey">
				<img src="https://img.shields.io/badge/close()-lightgrey">
				<img src="https://img.shields.io/badge/socket()-lightgrey">
				<img src="https://img.shields.io/badge/strerror()-lightgrey"><br>
				<img src="https://img.shields.io/badge/gai__strerror()-lightgrey">
				<img src="https://img.shields.io/badge/printf()_and_its_family-lightgrey"><br>
				<img src="https://img.shields.io/badge/libft_library-lightgrey">
			</td>
			<td valign="top"> 4200 XP</td>
		</tr>
	</table>
</p>

<br>

### Usage
```bash
$ make
$ ./ft_traceroute google.com
```





#TODO:
[X] upon receival of the packet, verify if it is a valid ICMP packet, and if it is the last hop.

[X] error messages

[ ] norme

[X] review and improve structures

[X] resolve hosts options

[ ] test all options and finish parser