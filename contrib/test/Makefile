CXXFLAGS=-I/home/ingo/projects/gquickdraw/cvs/ -I../../src/
LDFLAGS=-L/home/ingo/projects/gquickdraw/cvs/ -lgquickdraw -L/usr/X11R6/lib/ -lX11

triangle : triangle.cxx
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

quad : quad.cxx
	$(CXX) $(CXXFLAGS) ../../src/math.cxx $< -o $@ $(LDFLAGS)

# EOF #