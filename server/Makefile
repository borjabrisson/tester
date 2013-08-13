CC := g++
BASEFLAGS= -lpthread ${MySQLFLAGS}
CPPFLAGS = -O0 -g3 -Wall -c -fmessage-length=0  -MMD -MP
MySQLFLAGS = `mysql_config --cflags --libs`

all	: listen serverIP
# 	${CC} server.cpp  -fpermissive ${BASEFLAGS} -o server.out ./hijo.o 
# 	${CC} main.cpp  -fpermissive ${BASEFLAGS} -o server.out ./hijo.o 
	${CC} main.cpp -o server.out "hijo.o" "serverIP.o" -fpermissive ${BASEFLAGS} 
serverIP: listen
	${CC} -fpermissive ${BASEFLAGS}  ${CPPFLAGS} -MF"serverIP.d" -MT"serverIP.d" -o "serverIP.o" serverIP.cpp
listen	: sgbd
	${CC} ${BASEFLAGS} ${CPPFLAGS} -MF"hijo.d" -MT"hijo.d" -o "hijo.o" "sgbd_baseConector.o" listen/hijo.cpp
sgbd	:
	${CC} ${MySQLFLAGS} ${CPPFLAGS} -MF"sgbd_baseConector.d" -MT"sgbd_baseConector.d" -o "sgbd_baseConector.o" conector_SGBD/sgbd_baseConector.cpp
clean	:
	rm *.o *.d
no-temporal:
	rm *.cpp~ *.h~ listen/*.cpp~ listen/*.h~
