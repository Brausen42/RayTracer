This directory contains the Ray tracing program for Homework1d in CSCI 5607
The contents of this directory were authored by Alex Brausen (braus028, 5033191)

I used cmake to compile and build my program so the following commands should build an executable called 'raytracer':
cmake ./ 
make -j

where ./ is a path to the src folder
then the executable 'raytracer' should be ran with a command line arg. of a .txt file, e.g.:
./raytracer example.txt

and if given an appropriate scene file, a .ppm image will be generated and will share the name of the .txt file, e.g.:
example.ppm

An appropriate scene file should have the following format:

eye eyex eyey eyez
viewdir vdirx vdiry vdirz
updir upx upy upz
fovv fovv
imsize width height
bkgcolor r g b
mtlcolor dr dg db sr sg sb ka kd ks n a r
sphere cx cy cz r
ellipsoid cx cy cz rx ry rz
light x y z w r g b
...

where the first string on each line is a keyword and the following are the associated parameters.
