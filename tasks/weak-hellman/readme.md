## Well-known protocol

We have captured some traffic from enemy's paseca. Investigate it and help us to invade paseca on {{IP}}.
Have you ever heard about hellman?

## Flag
paseca{4nd_h0N3Y_W1ll_FL0w_0NC3_m0r3}

## WriteUp
It is obvious that task description is about the diffie-hellman protocol.
Read specification of diffie-hellman protocol.
Open traffic in wireshark -> follow TCP stream -> open hex-dump.
1) First of all client sends initial message "baraban".
Server returns 8 bytes "37 13 00 00 be ba fe ca".
We can start to write client for server and send initial message. We will receive same constant 8 bytes.
We can make a guess that first 4 bytes are g (public constant), next 4 bytes are p (public modulus).
2) Client sends 4 bytes "63 27 ad 29". Probably it is g**a mod p.
3) Server sends 4 bytes "d7 6c da 4b". Probably it is g**b mod p. Server and client generated private key.
4) Server sends some encrypted data. We can guess that it simple xor with cycled key.
If we created client we would check this proposal ... and it works!
Server sends "Welcome to secure PASECA server!\nEnter your login: "
5) Oh, we should decrypt correct credentials from traffic.
We can do that by simple exhaustive search of key, because number parameters are small (example in writeup/dump_hack.py).
6) Now we can just login into the server and get flag!
