# -*-Makefile-*-
tareas_abc: tareas_abc.o
	gcc tareas_abc.o  -lpthread -Wall -o exc/tareas_abc 
tareas_abc.o: src/tareas_abc.c
	gcc -lpthread -Wall -c src/tareas_abc.c

mini_sh: mini_sh.o createD.o createF.o eliminateD.o exit.o help.o modPer.o showCont.o	
	gcc mini_sh.o -lpthread -Wall -o exc/mini_sh
mini_sh.o: src/mini_sh.c src/cmd_mini_sh/createD.c src/cmd_mini_sh/createF.c src/cmd_mini_sh/eliminateD.c \
src/cmd_mini_sh/exit.c src/cmd_mini_sh/help.c src/cmd_mini_sh/modPer.c src/cmd_mini_sh/showCont.c	
	gcc -lpthread -Wall -c src/mini_sh.c src/cmd_mini_sh/*.c

demasiadas_botellas: damasiadas_botellas.o
	gcc demasiadas_botellas.o  -lpthread -Wall -o exc/demasiadas_botellas
demasiadas_botellas.o: demasiadas_botellas.c
	gcc -lpthread -Wall -c src/demasiadas_botellas.c 

demasiadas_botellas_encoladas: damasiadas_botellas_encoladas.o
	gcc demasiadas_botellas_encoladas.o  -lpthread -Wall -o exc/demasiadas_botellas_encoladas
demasiadas_botellas_encoladas.o: demasiadas_botellas_encoladas.c
	gcc -lpthread -Wall -c  src/demasiadas_botellas_encoladas.c

comida_rapida: comida_rapida.o
	gcc comida_rapida.o  -lpthread -Wall -o exc/comida_rapida
comida_rapida.o: comida_rapida.c
	gcc  -lpthread -Wall -c src/comida_rapida.c

comida_rapida_encolada: comida_rapida_encolada.o
	gcc src/comida_rapida_encolada.o  -lpthread -Wall -o exc/comida_rapida_encolada
comida_rapida_encolada.o: comida_rapida_encolada.c
	gcc  -lpthread -Wall -c src/comida_rapida_encolada.c 

clean:
	rm -f *.o exc/*
