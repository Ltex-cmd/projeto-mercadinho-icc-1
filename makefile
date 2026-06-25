CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
TARGET = mercadinho

all:
	$(CC) $(CFLAGS) main.c funcoes.c -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) entrega.zip estoque.txt

zip:
	zip entrega.zip main.c funcoes.c funcoes.h README.txt
