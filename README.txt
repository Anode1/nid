Some projects require anonymization of ID, the identification key (such as
SIN, SSN, Driver License ID, Name+Birth_Date+Birth_Place, or any other natural
or surrogate key which cannot be passed due to security reasons.
In that case an organization, collecting statistics can still identify the
same person even not holding private information. What is necessary is
hashing the key and keeping the surrogate key held to identify the person.
If the next time (in a different institution) the same personal information
will be hashed using the same private keys and the same algorithm, the same 
hashed ID will be generated, so the institutions will be able to connect the 
records.

Here, for demonstrating purposes, I use the code of the hash and encoder from 
the public domain, but any other encoder (from Linux projects or commercial)
can be used as well.



compile: 
	$make clean debug
		or
	$make clean release

compile test:
	$make clean base64
	etc

adding new tests:
	Add main and symbol SOMETHING_ELSE, so you can run:
	$make clean ut1 
add new tests like ut, base64, ut1

(this is for individual tests - when main() entry point is necessary, but probably
runtime tests without the compilation is more preferable)
