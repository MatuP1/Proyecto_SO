# -*-Makefile-*-
all: tareas_abc mini_sh demasiadas_botellas demasiadas_botellas_encoladas\
	comida_rapida comida_rapida_encolada createD createF listCont showCont modPer\
	eliminateD help exit

demasiadas_botellas: demasiadas_botellas.o
	gcc demasiadas_botellas.o  -lpthread -Wall -o exc/demasiadas_botellas
demasiadas_botellas.o: src/demasiadas_botellas.c
	gcc -lpthread -Wall -c src/demasiadas_botellas.c 

tareas_abc: tareas_abc.o
	gcc tareas_abc.o  -lpthread -Wall -o exc/tareas_abc 
tareas_abc.o: src/tareas_abc.c
	gcc -lpthread -c src/tareas_abc.c

demasiadas_botellas_encoladas: demasiadas_botellas_encoladas.o
	gcc demasiadas_botellas_encoladas.o  -lpthread -Wall -o exc/demasiadas_botellas_encoladas
demasiadas_botellas_encoladas.o: src/demasiadas_botellas_encoladas.c
	gcc -lpthread -Wall -c  src/demasiadas_botellas_encoladas.c

comida_rapida: comida_rapida.o
	gcc comida_rapida.o  -lpthread -Wall -o exc/comida_rapida
comida_rapida.o: src/comida_rapida.c
	gcc  -lpthread -Wall -c src/comida_rapida.c

comida_rapida_encolada: comida_rapida_encolada.o
	gcc comida_rapida_encolada.o  -lpthread -Wall -o exc/comida_rapida_encolada
comida_rapida_encolada.o: src/comida_rapida_encolada.c
	gcc  -lpthread -Wall -c src/comida_rapida_encolada.c 

mini_sh: mini_sh.o createD createF showCont listCont eliminateD exit help modPer 	
	gcc mini_sh.o -lpthread -o exc/mini_sh
mini_sh.o: src/mini_sh.c	
	gcc -lpthread -Wall -c src/mini_sh.c src/cmd_mini_sh/*.c

createD: createD.o
	gcc createD.o -lpthread -Wall -o exc/createD
createD.o: src/cmd_mini_sh/createD.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/createD.c

createF: createF.o
	gcc createF.o -lpthread -Wall -o exc/createF
createF.o: src/cmd_mini_sh/createF.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/createF.c

help: help.o
	gcc help.o -lpthread -Wall -o exc/help
help.o: src/cmd_mini_sh/createD.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/help.c

exit: exit.o
	gcc exit.o -lpthread -Wall -o exc/exit
exit.o: src/cmd_mini_sh/exit.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/exit.c

modPer: modPer.o
	gcc modPer.o -lpthread -Wall -o exc/modPer
modPer.o: src/cmd_mini_sh/modPer.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/exit.c

eliminateD: eliminateD.o
	gcc exit.o -lpthread -Wall -o exc/eliminateD
eliminateD.o: src/cmd_mini_sh/eliminateD.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/eliminateD.c

listCont: listCont.o
	gcc exit.o -lpthread -Wall -o exc/listCont
listCont.o: src/cmd_mini_sh/listCont.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/exit.c

showCont: showCont.o
	gcc showCont.o -lpthread -Wall -o exc/showCont
showCont.o: src/cmd_mini_sh/showCont.c
	gcc -lpthread -Wall -c src/cmd_mini_sh/showCont.c

clean:
	rm -f *.o exc/*
