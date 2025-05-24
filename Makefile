# İŞLETİM SİSTEMLERİ DÖNEM ÖDEVİ - Makefile
# Apartman inşaat simülasyonu derleme dosyası

# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -pthread -g
TARGET = apartman_insaat

# Kaynak dosyaları
SRCS = main.c temel.c kat.c daire.c isci.c final.c
OBJS = $(SRCS:.c=.o)

# Ana hedef
all: $(TARGET)

# Çalıştırılabilir dosya oluşturma
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# .c dosyalarından .o dosyaları oluşturma
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Temizlik
clean:
	rm -f $(OBJS) $(TARGET)

# Programı çalıştır
run: $(TARGET)
	./$(TARGET)

# Yeniden derleme
rebuild: clean all

.PHONY: all clean run rebuild
