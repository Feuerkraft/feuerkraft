tilegen : tilegen.cc
	$(CXX) -Wall -O0 -g -o $@ $< -lpng

tiles:
	./tilegen ./tilegen 40x40/wwbw.png \
           40x40/sand1.png  \
           40x40/darksand1.png \
           --output 40x40-output/wwsw1.png

# EOF #