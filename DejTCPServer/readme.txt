This project is a demo for dejero
 
1. Source files are inside src and include files are inside include.There are 2 applications, namely TCPServer and TestClient. 
TestClient is the test driver for the TCPServer application.
2. There are separate make files for 2 applications. One is the server and other is the tester app.
However, there is common CMakeLists.txt in the build folder which should be used for building the entire project.
3. run <cmake CMakeList.txt> from ../DejTCPServer/build folder to start building in Linux or Windows system.

In windows builds:-
a. run <cmake CMakeList.txt> from build folder to get the project solution for vc++ (tested in VC2015).
b. ZERO_CHECK - will rerun cmake. Execute this after changing something on CMakeList.txt files.
c. ALL_BUILD - target which builds all and everything project in the active solution.
d. Make sure that the boost library is in the DEPENDECY_DIR specified in the environment, or change these 
variables with the exact location of boost libraries specified in the CMakeLists.txt in each source folders
	set(DEPS_DIR $ENV{DEPENDENCY_DIR})        
	set(BOOST_DIR "${DEPS_DIR}/boost/1.55.0")	 
e. If the build is succeeded the binaries will be inside ../DejTCPServer/bin/win folder.
g. In windows the boost library version used is 1.55
h. There are 2 binary files inside the folder  ..DejTCPServer\bin\win; namely
TCPServer.exe and TestClient.exe.  Execute the server from command line and then the client. 
This tests the server with minimal messaging function. 

In Linux builds:- (tested in Ubuntu 16.04)
a. Issue <cmake CMakeLists.txt> from ../DejTCPServer/build folder. This will generate the makefile
b. Issue <make> from the build folder to get the linux binaries
c. Make sure the CMakeLists.txt inside the ../../src/TCPServer and ../../src/TestClient has the right path for the boost folder
currently it is set to "set(BOOST_DIR "/media/alex/alex_store/alex/boost_1_61_0/")"

4. It is tested with ncat also. Use <echo 'E11000000000DA7A0000000501020304050B1E00000000' | xxd -r -p | nc -p 5678 "serveripaddress" 1234> where
serveripaddress is the ip address where the TCPServer program runs.

5. Any feedback to alexvgeorge@gmail.com