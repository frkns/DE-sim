all:
	g++ -std=c++23 -DLOCAL -O2 -g -Wall -Wextra -Wshadow -Wformat=2 -Wlogical-op -Wduplicated-cond -Wshift-overflow -fstack-protector-all -fsanitize=address,undefined -fsanitize-recover=all -Wno-unused-result -Wno-sign-conversion -Wno-sign-compare \
	main.cc && ./a.out && rm ./a.out && \
	feh -F --zoom max --force-aliasing ./output/image.ppm

clean:
	rm -f ./output/image.ppm
