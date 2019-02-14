multi_segments: max.c seg.c multi_segments.c
	mkdir -p target
	gcc -Wall -pthread -lwiringPi -lrt -o target/multi_segments max.c seg.c multi_segments.c

multi_segments_init: max.c seg.c multi_segments_init.c
	mkdir -p target
	gcc -Wall -pthread -lwiringPi -lrt -o target/multi_segments_init max.c seg.c multi_segments_init.c

matrix: font/font.c max.c mat.c matrix.c
	mkdir -p target
	gcc -Wall -pthread -lwiringPi -lrt -o target/matrix font/font.c max.c mat.c matrix.c

font_visualizer: font/font.c font/font_visualizer.c
	mkdir -p target
	gcc -Wall -o target/font_visualizer font/font.c font/font_visualizer.c

clean:
	rm -rf target
