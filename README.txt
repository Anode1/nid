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
