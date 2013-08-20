CC := g++
BASEFLAGS= -lpthread 
CPPFLAGS = -O0 -g3 -Wall -c -fmessage-length=0  -MMD -MP
MySQLFLAGS = `mysql_config --cflags --libs`

all	: conectorSerial 
	${CC} main.cpp -o conector.out "serie.o" -fpermissive ${BASEFLAGS} 
serverIP: listen
#	${CC} -fpermissive ${BASEFLAGS}  ${CPPFLAGS} -MF"serverIP.d" -MT"serverIP.d" -o "serverIP.o" serverIP.cpp
conectorSerial	: 
	${CC} -fpermissive ${BASEFLAGS} ${CPPFLAGS} -MF"serie.d" -MT"serie.d" -o "serie.o" conectorSerial.cpp
sgbd	:
#	${CC} ${MySQLFLAGS} ${CPPFLAGS} -MF"sgbd_baseConector.d" -MT"sgbd_baseConector.d" -o "sgbd_baseConector.o" conector_SGBD/sgbd_baseConector.cpp
clean	:
	rm *.o *.d
no-temporal:
	rm *.cpp~ *.h~ 
