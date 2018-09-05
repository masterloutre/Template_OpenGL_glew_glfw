# Template_OpenGL_glew_glfw
Template cmake project for using OpenGl with glew and glfw set up

##Installation

You can either use this project with an IDE compatible with cmake projects ( I would recommande Clion ), or download and install Cmake to use this project directly in command line ( example on how to do this here : https://stackoverflow.com/questions/32185079/installing-cmake-with-home-brew )

You also need to download and install glew and glfw. Either by following directions on their web site or by installing homebrew (https://brew.sh/index) and using the command :
`brew install glew`
`brew install glfw

##Compiling

###Clion : 
Just reload the project and click build and run.
You may have to wait a little the first time or click it twice

###Command Line :
- Create a directory to store build files (ex "Build" ).
- Go inside that directory and use the command : cmake <path to the project directory>
- use de command : make 
  
You should now have a executable in at the path : Build/Project/executable
  
##Help : 
  There are some debug notes at the end of the CmakeLists.txt file
  I set this up some time ago so it is possible that I forgot some library or config files somewhere else on my computer.
  If something doesn't work or seems to be missing do hesitate to tell me.
  
Cmake : 
  Cmake helps you compile code by creating a makefile that you can more easily configurate through the CMakeLists.txt file.
  In this template I have it set up so that it will compile the main.cpp file with all .cpp .hpp and .glsl files in the directory named Project and link with the OpenGL glew and glfw library. 
  That can of course be changed and I have documented the CMakeList.txt file so that it would be more understandable
  The files in the Cmake directory help cmake find the libraries on your computer, you may need to add one for OpenGl, templates are found easily on the internet
