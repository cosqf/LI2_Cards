CFLAGS = -Wall -Wextra -pedantic -O2

cards: main.o guiao1.o
	gcc $(CFLAGS) -o $@ $^

# Procura funções demasiado complexas 
complexidade:
	@echo Only printing when Modified McCabe Cyclomatic Complexity is above 5
	@echo | pmccabe -v
	@pmccabe *.c| sort -nr | awk '{if($$1>5)print}'

# Procura problemas no código 
check:
	cppcheck --enable=all --suppress=missingIncludeSystem .

main.o: main.c
	gcc $(CFLAGS) -c $^

guiao1.o: guiao1.c guiao1.h
	gcc $(CFLAGS) -c guiao1.c

codigo.zip: *.h *.c
	zip -9r $@ $^	

clean:
	rm main.o guiao1.o cards	
#rm $(OBJS) a.out cards

# $@ nome da target
# $^ argumentos da target